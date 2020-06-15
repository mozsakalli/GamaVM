/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.digitoygames.lang;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class PreProcessor {
    List<Token> tokens;
    HashSet<String> defs = new HashSet();
    
    public PreProcessor(List<Token> tokens, String...defs) {
        this.tokens = new ArrayList(tokens);
        for(String d : defs)
            this.defs.add(d);
    }
    
    public List<Token> process() {
        List<Token> result = new ArrayList();
        int doAdd = 1;
        
        while(tokens.size() > 0) {
            Token t = tokens.remove(0);
            if(t.value.startsWith("#if ")) {
                boolean success = checkCondition(t.value.substring(3).trim());
                if(!success) doAdd--; 
            } 
            else if(t.value.startsWith("#elif ")) {
                boolean success = checkCondition(t.value.substring(5).trim());
                if(!success) doAdd--; 
            }
            else if(t.value.startsWith("#endif")) {
                doAdd++;
            }
            else if(doAdd > 0){
                result.add(t);
            }
        }
        return result;
    }
    
    boolean checkCondition(String raw) {
        return false;
    }
    static class IfToken extends Token {
        public List<Token> tokens;
        public IfToken _else;
    }
}
