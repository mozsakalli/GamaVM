package com.digitoygames.lang.model;

import com.digitoygames.lang.SourceWriter;
import java.util.Set;

public class FieldSyntax extends Unit {

    public Type type;
    public String name;
    public Expression value;
    public Set<String> modifiers;

    public Expression getter;
    public Expression setter;


    @Override
    public String toString() {
        String str = "";
        for(String m : modifiers) {
            if(!str.isEmpty()) str += " ";
            str += m;
        }
        str += " "+type+" "+name;

        if(getter != null || setter != null) {
            str += " {\n";
            if(getter != null) {
                str += "get "+getter+"\n";
            }
            if(setter != null) {
                str += "set "+setter+"\n";
            }
            str += "}\n";
        }

        if(value != null) str += " = "+value;
        return str;
    }

    @Override
    public void generateCPP(SourceWriter out) {
        if(modifiers.contains("const")) out.print("const ");
        out.println("%s %s;",type.toString(), name);
        if(getter != null) {
            out.println("%s %s_getter() {", type.toString(), name).indent();
            out.println(getter.toString());
            out.undent().println("}");
        }
    }
    
    
}
