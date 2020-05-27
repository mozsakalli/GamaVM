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

/**
 *
 * @author mustafa
 */
public class Token {
    
    public final static int STRING          = 0;
    public final static int IDENT           = 1;
    public final static int NUMBER          = 2;
    public final static int SYMBOL          = 3;
    public final static int COMMENT         = 4;
    public final static int MULTICOMMENT    = 5;
    
    public String value;
    public int line;
    public int type;
    public int ptr;

    @Override
    public String toString() {
        return value+" ["+type+"@"+line+"]";
    }

    public boolean isComment() {
        return type == COMMENT || type == MULTICOMMENT;
    }
    public boolean isIdent() { return type == IDENT; }
}
