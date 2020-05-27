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

package com.digitoygames.compiler;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class Invoke extends Ref {
    
    public int callType;
    
    public final static int VIRTUAL = 0;
    public final static int SPECIAL = 1;
    public final static int STATIC = 2;
    public final static int INTERFACE = 3;

    @Override
    public void execute(Method meth, Stack stack) {
        
        List<String> args = Util.parseMethodSignature(type);
        String str = cls+":"+name+":"+type+"(";
        int len = args.size();
        if(callType != STATIC) len++;
        String[] argVals = new String[len];
        for(int i=0; i<len; i++) argVals[len-1-i] = stack.pop().value;
        for(int i=0; i<len; i++) {
            if(i > 0) str += ",";
            str += argVals[i];
        }
        str += ")";
        String ret = type.substring(type.indexOf(")")+1);
        if(!ret.equals("V")) {
            Stack.StackElement tmp = stack.getTemp(meth, ret);
            code = tmp.value + "=" + str;
            stack.push(tmp);
        } else {
            code = str;
        }
    }

    public String getMangled() {
        return Util.esc(cls+"_"+name+type);
    }
    
    @Override
    public void generate(SourceWriter out) {
        //String m = getMangled();
        List<String> args = Util.parseMethodSignature(type);
        String retType = Util.getReturnType(type);
        String base = null;
        if(callType != STATIC) {
            args.add(0, "O");
            base = "ST[SP-"+args.size()+"].O";
            out.println("//if(!%s) throw_null_pointer_exception();",base);
        }
        
        out.println("static void* resolved_%d = NULL;", pc);
        out.println("if(!resolved_%d) {",pc).indent();
        switch(callType) {
            case STATIC:
                out.println("resolved_%d = resolve_static_method(\"%s\",\"%s\",\"%s\");", pc, cls, name, type);
                break;
            case VIRTUAL:
                out.println("resolved_%d = resolve_virtual_method(%s->cls,\"%s\",\"%s\");", pc, base, name, type);
                break;
            case INTERFACE:
                out.println("resolved_%d = resolve_interface_method(%s->cls,\"%s\",\"%s\");", pc, base,name, type);
                break;
                
        }
        out.println("//if(!resolved_%d) throw_method_not_found();",pc);
        out.undent().println("}");
        
        //out.print("SP -= %d;",args.size());
        if(!retType.equals("V"))
            out.print("ST[SP-%d].%s = ", args.size(), retType);
        out.print("((%s)resolved_%d)(",Util.getCallType(args, retType),pc);
        int p = -args.size();
        for(int i=0; i<args.size(); i++) {
            if(i > 0) out.print(",");
            out.print("ST[SP%d].%s",p,args.get(i));
            p++;
        }
        out.print(");");
        if(!retType.equals("V")) out.print("SP += %d;",-args.size()+1);
        out.ln();
    }
    
    
    
}
