package com.digitoygames.lang.model;

import com.digitoygames.lang.SourceWriter;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class ClassSyntax extends Unit {

    public Set<String> modifiers;
    public Type type;
    public List<Unit> units = new ArrayList();

    @Override
    public String toString() {
        String str = "";
        for(String m : modifiers) {
            if(!str.isEmpty()) str += " ";
            str += m;
        }

        str += " class "+type;
        str += " {\n";

        for(Unit f : units) {
            str += f + "\n";
        }

        return str;
    }

    @Override
    public void generateCPP(SourceWriter out) {
        out.println("class %s {",type).indent().println("public:");
        for(Unit u : units)
            u.generateCPP(out);
        out.undent().println("};");
    }
}
