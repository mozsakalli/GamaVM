package com.digitoygames.lang.model;

import java.util.ArrayList;
import java.util.List;

public class BlockSyntax extends Expression {

    public List<Expression> statements = new ArrayList();

    @Override
    public String toString() {
        String str = "{\n";
        for(Expression e : statements)
            str += e+"\n";
        str += "}\n";

        return str;
    }
}
