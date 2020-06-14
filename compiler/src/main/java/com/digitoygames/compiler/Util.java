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

import java.util.*;

/**
 *
 * @author mustafa
 */
public class Util {

    public static String typeToStack(String name) {
        if(name.startsWith("[") || name.startsWith("L")) return "O";
        return name;
    }

    public static boolean typeSameStack(String type, String type2) {
        return typeToStack(type).equals(typeToStack(type2));
    }
    
    
    public static String getReturnType(String desc) {
        int p = desc.lastIndexOf(')');
        String r = desc.substring(p+1);
        if(r.startsWith("[") || r.startsWith("L")) return "O";
        switch(r) {
            case "B":
            case "Z":
            case "S":
            case "C":
            case "I":
                return "I";
        }
        return r;
    }

    public static String getPlatformType(String type) {
        if(type.startsWith("[") || type.startsWith("L")) return "Object*";
        switch(type) {
            case "Z": return "JBOOL";
            case "B": return "JBYTE";
            case "C": return "JCHAR";
            case "S": return "JSHORT";
            case "I": return "JINT";
            case "F": return "JFLOAT";
            case "D": return "JDOUBLE";
            case "J": return "JLONG";
            case "O": return "Object*";
        }
        return type;
    }
    
    public static String getCallType(List<String> args, String returnType) {
        String str = "CALL_";
        for(String a : args) str += a;
        str += "_"+returnType;
        return str;
    }
    
    public static int countArguments(String signature) {
        int count = 0;
        int p = 1;
        while(signature.charAt(p) != ')') {
            while(signature.charAt(p) == '[') p++;
            if(signature.charAt(p) == 'L') while(signature.charAt(p)!=';') p++;
            p++;
            count++;
        }
        return count;
    }
    
    public static List<String> parseMethodSignature(String signature) {
        List<String> arguments = new ArrayList();
        int p = 1;
        while(signature.charAt(p) != ')') {
            while(signature.charAt(p) == '[') p++;
            if(signature.charAt(p) == 'L') while(signature.charAt(p)!=';') p++;
            switch(signature.charAt(p++)) {
                case ';': 
                    arguments.add("O");
                    break;
                default:
                    arguments.add(signature.substring(p-1,p));
            }
        }
        return arguments;
    }  
    
    public static String esc(String n) {
        return n.replace('/', '_').replace('(', '_')
                .replace(')', '_').replace('<', '_').replace('>', '_')
                .replace(';','_').replace('[', '_');
    }
}
