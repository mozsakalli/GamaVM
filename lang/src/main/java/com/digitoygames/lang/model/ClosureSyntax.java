package com.digitoygames.lang.model;

import java.util.ArrayList;
import java.util.List;

public class ClosureSyntax extends Expression {

    public List<ArgSyntax> args = new ArrayList();
    public Expression body;

    @Override
    public String toString() {
        return " => " + body;
    }
}
