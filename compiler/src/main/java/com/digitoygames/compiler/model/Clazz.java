/*
 * Copyright (C) 2019 Digitoy Games.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.digitoygames.compiler.model;

import com.digitoygames.compiler.Util;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class Clazz {
    
    public CP cp;
    public int thisIndex, superIndex = -1, accessFlags;
    public List<Field> fields = new ArrayList();
    public List<Method> methods = new ArrayList();
    public List<Attr> attrs = new ArrayList();
    int[] interfaces;
    
    public Clazz(InputStream stream) throws Exception {
        DataInputStream in = new DataInputStream(stream);
        int magic = in.readInt();
        if( magic != 0xCAFEBABE ) {
            throw new IOException( "Invalid class magic: " + Integer.toHexString( magic ) );
        }
        int minorVersion = in.readUnsignedShort();
        int majorVersion = in.readUnsignedShort();
        cp = new CP(in);
        accessFlags = in.readUnsignedShort();
        thisIndex = in.readUnsignedShort() ;
        superIndex = in.readUnsignedShort();
        int count = in.readUnsignedShort();
        interfaces = new int[count];
        for(int i=0; i<count; i++) {
            interfaces[i] = in.readUnsignedShort();
        }
        
        count = in.readUnsignedShort();
        for(int i=0; i<count; i++) {
            Field f = new Field();
            f.declaringClass = this;
            fields.add(f);
            f.accessFlags = in.readUnsignedShort();
            f.nameIndex = in.readUnsignedShort();
            f.signatureIndex = in.readUnsignedShort();
            readAttrs(f.attrs, in);
        }
        
        count = in.readUnsignedShort();
        for(int i=0; i<count; i++) {
            Method m = new Method();
            m.declaringClass = this;
            methods.add(m);
            m.accessFlags = in.readUnsignedShort();
            m.nameIndex = in.readUnsignedShort();
            m.signatureIndex = in.readUnsignedShort();
            readAttrs(m.attrs, in);
        }
        
        readAttrs(attrs, in);
    }
    
    void readAttrs(List<Attr> target, DataInputStream in) throws Exception {
        int attrCount = in.readUnsignedShort();
        for(int k=0; k<attrCount; k++) {
            Attr a = new Attr();
            a.declaringClass = this;
            a.nameIndex = in.readUnsignedShort();
            a.data = new byte[in.readInt()];
            //System.out.println("--attr: "+cp.items[a.nameIndex].value);
            in.readFully(a.data);
            target.add(a);
        }
    }
    
    public String getName() {
        return cp.getClassName(thisIndex);
    }
    
    public String getSuperName() {
        return cp.getClassName(superIndex);
    }
    
    public Method getMethod(String name, String signature) {
        for(Method m : methods)
            if(m.getName().equals(name) && m.getSignature().equals(signature))
                return m;
        return null;
    }
    
    public String getAOTName() {
        return Util.esc(getName());
    }
    
    public Attr getAttr(String name) {
        for(Attr a : attrs) {
            if(cp.getFieldName(a.nameIndex).equals(name)) return a;
        }
        return null;
    }
    
    BootstrapMethod[] bootMethods;
    public BootstrapMethod[] getBootstrapMethods() throws Exception {
        if(bootMethods != null) return bootMethods;
        Attr attr = getAttr("BootstrapMethods");
        if(attr == null) return bootMethods = new BootstrapMethod[0];
        DataInputStream in = attr.getStream();
        int count = in.readUnsignedShort();
        bootMethods = new BootstrapMethod[count];
        for(int i=0; i<count; i++) {
            bootMethods[i] = new BootstrapMethod(in, cp);
        }
        return bootMethods;
    }
    
    public byte[] dump() throws Exception {
        ByteArrayOutputStream bytes = new ByteArrayOutputStream();
        DataOutputStream dout = new DataOutputStream(bytes);
        dout.writeInt(0xCAFEBABE);
        dout.writeShort(0); //major
        dout.writeShort(0); //minor
        cp.dump(dout);
        dout.writeShort(accessFlags);
        dout.writeShort(thisIndex);
        dout.writeShort(superIndex);
        dout.writeShort(interfaces.length);
        for(int intf : interfaces) dout.writeShort(intf);
        
        dout.writeShort(fields.size());
        for(Field f : fields) {
            dout.writeShort(f.accessFlags);
            dout.writeShort(f.nameIndex);
            dout.writeShort(f.signatureIndex);
            dout.writeShort(f.attrs.size());
            for(Attr a : f.attrs) a.dump(dout);
        }
        
        dout.writeShort(methods.size());
        for(Method m : methods) {
            dout.writeShort(m.accessFlags);
            dout.writeShort(m.nameIndex);
            dout.writeShort(m.signatureIndex);
            dout.writeShort(m.attrs.size());
            for(Attr a : m.attrs) a.dump(dout);
        }
        
        dout.writeShort(0); //attrs
        for(Attr a : attrs) a.dump(dout);
        
        return bytes.toByteArray();
    }    
}
