package com.digitoygames.lang.model;

import com.digitoygames.lang.SourceWriter;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class MethodSyntax extends Unit {

    public Type type;
    public Type name;
    public List<ArgSyntax> args = new ArrayList();
    public Set<String> modifiers;
    public boolean isConstructor;
    public Expression body;


    @Override
    public String toString() {
        String str = "";
        for(String m : modifiers) {
            if(!str.isEmpty()) str += " ";
            str += m;
        }
        str += " "+type+" "+name+"(";
        for(int i=0; i<args.size(); i++) {
            if(i>0) str += ",";
            str += args.get(i);
        }
        str += ")";
        if(body != null)
            str += body;
        else str += ";";
        return str;
    }

    @Override
    public void generateCPP(SourceWriter out) {
        out.print("%s %s(",type,name);
        for(int i=0; i<args.size(); i++) {
            if(i>0) out.print(",");
            args.get(i).generateCPP(out);

        }
        out.println(") {");
    }
}
