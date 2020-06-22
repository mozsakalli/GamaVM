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

package gamavm;

/**
 *
 * @author mustafa
 */
public class SysClassLoader extends ClassLoader {
    byte[] jar;

    @Override 
    protected native Class loadClass(String name, boolean resolve) throws ClassNotFoundException;
    
    @Override
    protected byte[] readResource(String path) {
        return VM.extractZip(path, jar, 0);
    }
}
