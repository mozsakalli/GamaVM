package com.digitoygames.lang.model;

import com.digitoygames.lang.SourceWriter;

import java.util.ArrayList;
import java.util.List;

public class Namespace extends Unit {

    public String name;
    public List<ClassSyntax> classes = new ArrayList();

    @Override
    public String toString() {
        String str = "namespace "+name+" {\n";
        for(ClassSyntax cls : classes) {
            str += cls + "\n";
        }
        str += "}\n";

        return str;
    }

    @Override
    public void generateCPP(SourceWriter out) {
        out.println("namespace %s {", name).indent();
        for(ClassSyntax cls : classes)
            cls.generateCPP(out);
        out.undent().println("}");
    }
}
