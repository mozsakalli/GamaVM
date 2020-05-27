package com.digitoygames.lang.model;

import java.util.ArrayList;
import java.util.List;

public class Type extends Expression {

    public String name;
    public Type constraint;
    public List<Type> generic = new ArrayList();

    @Override
    public String toString() {
        String str = name;
        if(!generic.isEmpty()) {
            str += "<";
            for(int i=0; i<generic.size(); i++) {
                if(i > 0) str += ",";
                str += generic.get(i);
            }
            str += ">";
        }
        return str;
    }
}
