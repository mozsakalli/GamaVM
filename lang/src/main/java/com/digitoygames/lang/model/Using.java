package com.digitoygames.lang.model;

public class Using {

    public String name;
    public String qualified;

    @Override
    public String toString() {
        String str = "using";
        if(name != null) str += " "+name+" =";
        return str + " "+qualified;
    }
}
