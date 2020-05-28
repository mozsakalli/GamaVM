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

import gamavm.VM;
import java.lang.reflect.Array;

public class Object{
    
            
    public Object(){
    }

    public boolean equals(Object obj) {
        return obj == this;
    }

    public final Class getClass() {
        return VM.getClass(this);
    }

    public int hashCode() {
        return (int)VM.getAddress(this);
    }

    public final void notify() {}

    public final void notifyAll() {}

    public String toString() {
        return getClass().getName()+"#"+hashCode();
    }

    public final void wait() throws java.lang.InterruptedException{
        wait(0);
    }

    
    public final void wait(long timeout) throws java.lang.InterruptedException{
        wait(timeout, 0);
    }

    public final void wait(long timeout, int nanos) throws java.lang.InterruptedException {}

    protected native Object clone() throws java.lang.CloneNotSupportedException;
    
    protected void finalize() throws Throwable {}
    
}
