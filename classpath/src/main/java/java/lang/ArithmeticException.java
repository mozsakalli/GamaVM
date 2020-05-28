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
 * Thrown when an exceptional arithmetic condition has occurred. For example, an integer "divide by zero" throws an instance of this class.
 * Since: JDK1.0, CLDC 1.0
 */
public class ArithmeticException extends java.lang.RuntimeException{
    /**
     * Constructs an ArithmeticException with no detail message.
     */
    public ArithmeticException(){
    }

    /**
     * Constructs an ArithmeticException with the specified detail message.
     * s - the detail message.
     */
    public ArithmeticException(java.lang.String s){
         super(s);
    }

}
