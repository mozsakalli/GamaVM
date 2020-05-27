package com.digitoygames.lang.model;

import com.digitoygames.lang.SourceWriter;

public class Unit {

    public int line;

    public boolean isBlock() {
        return this instanceof BlockSyntax;
    }

    public void generateCPP(SourceWriter out) {
        out.println(this.getClass());
    }
}
