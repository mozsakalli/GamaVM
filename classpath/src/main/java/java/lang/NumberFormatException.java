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
 * Thrown to indicate that the application has attempted to convert a string to one of the numeric types, but that the string does not have the appropriate format.
 * Since: JDK1.0, CLDC 1.0 See Also:Integer.toString()
 */
public class NumberFormatException extends java.lang.IllegalArgumentException{
    /**
     * Constructs a NumberFormatException with no detail message.
     */
    public NumberFormatException(){
    }

    /**
     * Constructs a NumberFormatException with the specified detail message.
     * s - the detail message.
     */
    public NumberFormatException(java.lang.String s){
         super(s);
    }

}
