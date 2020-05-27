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

import java.io.DataInputStream;
import java.io.DataOutputStream;

/**
 *
 * @author mustafa
 */
public class CP {
    
    public static class Item {
        public int type;
        public Object value;
        public int index1;
        public int index2;
        public boolean used;
    }
    
    public Item[] items;
    
    public String getClassName(int index) {
        return items[items[index].index1].value.toString();
    }
    public String getFieldName(int index) {
        return items[index].value.toString();
    }
    public String getRefClassName(int index) {
        return getClassName(items[index].index1);
    }
    public String getRefName(int index) {
        return items[items[items[index].index2].index1].value.toString();
    }
    public String getRefSignature(int index) {
        return items[items[items[index].index2].index2].value.toString();
    }
    
    public Object get(int index) {
        return items[index].value;
    }
    
    public int getAndAddString(String value) {
        for(int i=1; i<items.length; i++)
            if(items[i]!=null && items[i].type==1 && items[i].value.toString().equals(value))
                return i;
        //not found
        Item item = new Item();
        item.value = value;
        item.type = 1;
        Item[] tmp = new Item[items.length+1];
        System.arraycopy(items, 0, tmp, 0, items.length);
        tmp[tmp.length - 1] = item;
        items = tmp;
        return tmp.length - 1;
    }
    
    public CP(DataInputStream in) throws Exception {
        int count = in.readUnsignedShort();
        items = new Item[count];
        for(int i=1; i<count; i++) {
            Item item = new Item();            
            item.type = in.readByte();
            items[i] = item;
            switch(item.type) {
                case 1: //CONSTANT_Utf8
                    item.value = in.readUTF();
                    break;
                case 3: //CONSTANT_Integer
                    item.value = in.readInt();
                    break;
                case 4: //CONSTANT_Float
                    item.value = in.readFloat();
                    break;
                case 5: //CONSTANT_Long
                    item.value = in.readLong();
                    i++;
                    break;
                case 6: //CONSTANT_Double
                    item.value = in.readDouble();
                    i++;
                    break;
                
                case 7: //CONSTANT_Class
                case 8: //CONSTANT_String
                case 16: // CONSTANT_MethodType
                case 19: // CONSTANT_Module
                case 20: // CONSTANT_Package
                    item.index1 = in.readUnsignedShort();
                    break;
                    
                case 9: //CONSTANT_Fieldref
                case 10: //CONSTANT_Methodref
                case 11: //CONSTANT_InterfaceMethodref
                case 12: //CONSTANT_NameAndType
                case 18: // CONSTANT_InvokeDynamic
                    item.index1 = in.readUnsignedShort();
                    item.index2 = in.readUnsignedShort();
                    break;
                case 15: // CONSTANT_MethodHandle
                    item.index1 = in.readUnsignedByte();
                    item.index2 = in.readUnsignedShort();
                    break;
                    
                default: throw new Exception("Unknown cp type "+item.type);
            }
        }
        
    }
    
    public void dump(DataOutputStream out) throws Exception {
        //int count = 1;
        //for(Item i : items) if(i!=null) count++;
        out.writeShort(items.length);
        for(int i=1; i<items.length; i++) {
            Item item = items[i];
            if(item == null) continue;
            out.writeByte(item.type);
            switch(item.type) {
                case 1: //CONSTANT_Utf8
                    out.writeUTF(item.value.toString());
                    break;
                case 3: //CONSTANT_Integer
                    out.writeInt((Integer)item.value);
                    break;
                case 4: //CONSTANT_Float
                    out.writeFloat((Float)item.value);
                    break;
                case 5: //CONSTANT_Long
                    out.writeLong((Long)item.value);
                    i++;
                    break;
                case 6: //CONSTANT_Double
                    out.writeDouble((Double)item.value);
                    i++;
                    break;
                
                case 7: //CONSTANT_Class
                case 8: //CONSTANT_String
                case 16: // CONSTANT_MethodType
                case 19: // CONSTANT_Module
                case 20: // CONSTANT_Package
                    out.writeShort(item.index1);
                    break;
                    
                case 9: //CONSTANT_Fieldref
                case 10: //CONSTANT_Methodref
                case 11: //CONSTANT_InterfaceMethodref
                case 12: //CONSTANT_NameAndType
                case 18: // CONSTANT_InvokeDynamic
                    out.writeShort(item.index1);
                    out.writeShort(item.index2);
                    break;
                    
                default: throw new Exception("Unknown cp type "+item.type);
            }            
        }
    }
}
