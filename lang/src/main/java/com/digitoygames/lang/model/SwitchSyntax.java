package com.digitoygames.lang.model;

import java.util.ArrayList;
import java.util.List;

public class SwitchSyntax extends Expression {

    public Expression condition;
    public List<Case> cases = new ArrayList();

    public static class Case extends Expression {

        public Expression value;
        public List<Expression> body = new ArrayList();
    }
}
