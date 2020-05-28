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

package java.lang;
/**
 * Thrown by the charAt method in class String and by other String methods to indicate that an index is either negative or greater than or equal to the size of the string.
 * Since: JDK1.0, CLDC 1.0 See Also:String.charAt(int)
 */
public class StringIndexOutOfBoundsException extends java.lang.IndexOutOfBoundsException{
    /**
     * Constructs a StringIndexOutOfBoundsException with no detail message.
     * JDK1.0.
     */
    public StringIndexOutOfBoundsException(){
    }

    /**
     * Constructs a new StringIndexOutOfBoundsException class with an argument indicating the illegal index.
     * index - the illegal index.
     */
    public StringIndexOutOfBoundsException(int index){
        super("" + index);
    }

    /**
     * Constructs a StringIndexOutOfBoundsException with the specified detail message.
     * s - the detail message.
     */
    public StringIndexOutOfBoundsException(java.lang.String s){
         super(s);
    }

}
