package com.digitoygames.lang.model;

import com.digitoygames.lang.SourceWriter;

import java.util.ArrayList;
import java.util.List;

public class Module {

    public List<Using> usings = new ArrayList();
    public List<Namespace> namespaces = new ArrayList();

    @Override
    public String toString() {
        String str = "";
        for(Using u : usings) {
            str += u+";\n";
        }

        for(Namespace n : namespaces) {
            str += n + "\n";
        }
        return str;
    }

    public void generateCPP(SourceWriter out) {
        for(Using u : usings)
            out.println("#include \"%s\"", u.name);

        for (Namespace n : namespaces)
            n.generateCPP(out);
    }
}
