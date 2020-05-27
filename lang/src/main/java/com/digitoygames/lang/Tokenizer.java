/*
 * Copyright (C) 2019 Digitoy Games.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.digitoygames.lang;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mustafa
 */
public final class Tokenizer {
    
    interface Rule {
        public boolean check(char c);
    }
    
    String code;
    int ptr;
    int lastLine = 0;
    int lastLinePtr;
    public List<Token> tokens = new ArrayList();
    
    char chr() {
        return ptr < code.length() ? code.charAt(ptr) : 0;
    }
    boolean is(char c, int delta) {
        return ptr+delta < code.length() && code.charAt(ptr+delta) == c;
    }
    boolean isAlpha(char c) {
        return (c>='a' && c<='z') || (c>='A' && c<='Z');
    }
    boolean isNumber(char c) {
        return c >= '0' && c<='9';
    }
    String grab(Rule rule) {
        int p = ptr;
        while(ptr < code.length() && rule.check(code.charAt(ptr))) ptr++;
        return code.substring(p,ptr);
    }
    void token(String value, int type) {
        while(lastLinePtr < ptr) {
            if(code.charAt(lastLinePtr++) == '\n') lastLine ++;
        }
        if(type == Token.COMMENT || type == Token.MULTICOMMENT) return;
        Token t = new Token();
        t.value = value;
        t.line = lastLine+1;
        t.type = type;
        tokens.add(t);
    }
    
    public Tokenizer(File file) throws Exception {
        code = new String(FileUtils.readFully(file));
        while(ptr < code.length()) {
            char c = chr();
            if(c <= 32 || c == 65279) {
                while(ptr < code.length() && (chr()<=32 || chr()==65279)) ptr++;
                continue;
            }
            if(c == '/' && is('/',1)) {
                token(grab((ch) -> ch != 10), Token.COMMENT);
                ptr++;
                continue;
            }
            if(c == '/' && is('*',1)) {
                int start = ptr;
                while(ptr < code.length()-1) {
                    if(is('*',0) && is('/',1)) {
                        ptr+=2;
                        break;
                    }
                    ptr++;
                }
                token(code.substring(start,ptr), Token.MULTICOMMENT);
                continue;
            }
            if(c == '=') {
                ptr++;
                if(chr()=='=') {
                    ptr++;
                    token("==", Token.SYMBOL);
                } else if(chr()=='>') {
                    ptr++;
                    token("=>", Token.SYMBOL);
                }
                else token("=", Token.SYMBOL);
                continue;
            }
            if(c == '<') {
                ptr++;
                if(chr()=='<') {
                    ptr++;
                    token("<<", Token.SYMBOL);
                } else if(chr()=='=') {
                    ptr++;
                    token("<=", Token.SYMBOL);
                } 
                else token("<", Token.SYMBOL);
                continue;
            }
            if(c == '>') {
                ptr++;
                if(chr()=='>') {
                    ptr++;
                    token(">>", Token.SYMBOL);
                } else if(chr()=='=') {
                    ptr++;
                    token(">=", Token.SYMBOL);
                } else token(">", Token.SYMBOL);
                continue;
            }
            if(c == '&') {
                ptr++;
                if(chr()=='=') {
                    ptr++;
                    token("&=", Token.SYMBOL);
                } else if(chr()=='&') {
                    ptr++;
                    token("&&", Token.SYMBOL);
                }
                else token("&", Token.SYMBOL);
                continue;
            }
            if(c == '|') {
                ptr++;
                if(chr()=='=') {
                    ptr++;
                    token("|=", Token.SYMBOL);
                } else if(chr()=='|') {
                    ptr++;
                    token("||", Token.SYMBOL);
                }
                else token("|", Token.SYMBOL);
                continue;
            }
            if(c == '+') {
                ptr++;
                if(chr()=='=') {
                    ptr++;
                    token("+=", Token.SYMBOL);
                } else if(chr()=='+') {
                    ptr++;
                    token("++", Token.SYMBOL);
                }
                else token("+", Token.SYMBOL);
                continue;
            }
            if(c == '-') {
                ptr++;
                if(chr()=='=') {
                    ptr++;
                    token("-=", Token.SYMBOL);
                } else if(chr()=='-') {
                    ptr++;
                    token("--", Token.SYMBOL);
                }
                else token("-", Token.SYMBOL);
                continue;
            }
            if(c == '*') {
                ptr++;
                if(chr()=='=') {
                    ptr++;
                    token("*=", Token.SYMBOL);
                } 
                else token("*", Token.SYMBOL);
                continue;
            }
            if(c == '/') {
                ptr++;
                if(chr()=='=') {
                    ptr++;
                    token("/=", Token.SYMBOL);
                } 
                else token("/", Token.SYMBOL);
                continue;
            }
            
            if(c == '?') {
                ptr++;
                if(chr()=='?') {
                    ptr++;
                    token("??", Token.SYMBOL);
                } else if(chr()=='.') {
                    ptr++;
                    token("?.", Token.SYMBOL);
                }
                else token("?", Token.SYMBOL);
                continue;
            }
            
            if(c == '!') {
                ptr++;
                if(chr()=='=') {
                    ptr++;
                    token("!=", Token.SYMBOL);
                } else token("!", Token.SYMBOL);
                continue;
            }
            if(c == '#') {
                token(grab((ch) -> ch != 10), Token.SYMBOL);
                ptr++;
                continue;
            }
            if(c=='"' || c=='\'' || (c=='$' && is('"',1))) {
                char search = c;
                int start = ptr++;
                if(c=='$') {
                    search = '"';
                    ptr++;
                }
                while(ptr < code.length()) {
                    if(chr()=='\\') {
                        ptr+=2;
                        continue;
                    }
                    if(chr()==search) {
                        ptr++;
                        break;
                    }
                    ptr++;
                }
                token(code.substring(start,ptr), Token.STRING);
                continue;
            }
            if(isAlpha(c) || c=='_' || c=='@' || c=='$') {
                token(grab((ch) -> isAlpha(ch) || isNumber(ch) || ch=='_' || ch=='@' || ch=='$'), Token.IDENT);
                continue;
            }
            if(isNumber(c)) {
                int start = ptr;
                boolean hasDot = false;
                boolean isHex = false;
                while(ptr < code.length()) {
                    char ch = code.charAt(ptr);
                    if(isNumber(ch)) { ptr++; continue; }
                    if(isHex && (ch>='a' && ch<='f') || (ch>='A' && ch<='F')) {ptr++; continue;}
                    if(ch == '.') {
                        if(hasDot) error("Invalid number");
                        hasDot = true;
                        ptr++;
                        continue;
                    }
                    if(ch == 'x' || ch == 'X') {
                        ptr++;
                        isHex = true;
                        continue;
                    }
                    if((!isHex && (ch == 'f' || ch == 'F' || ch == 'd' || ch == 'd')) || ch == 'l' || ch == 'L') {
                        ptr++;
                        break;
                    }
                    break;
                }
                token(code.substring(start,ptr), Token.NUMBER);
                continue;
            }
            if(c=='.' || c==';' || c=='{' || c=='}' || c=='(' || c==')' || c=='[' || c==']' || c=='~' || c==',' || c==':' || c == '%') {
                token(""+c, Token.SYMBOL);
                ptr++;
                continue;
            }
            error("Unknown");
        }
    }
    
    void error(String message) throws Exception {
        int col = 0;
        int row = 0;
        for(int i=0; i<ptr; i++) {
            if(code.charAt(i) == '\n') {
                col = 0;
                row++;
            } else col++;
        }
        throw new Exception(message+" at "+(row+1)+"x"+(col+1));
    }
}
