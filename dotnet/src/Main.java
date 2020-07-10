
import edu.arizona.cs.mbel.mbel.ClassParser;
import java.io.FileInputStream;

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

/**
 *
 * @author mustafa
 */
public class Main {
    
    public static void main(String[] args) throws Exception {
        ClassParser p = new ClassParser(new FileInputStream("/Users/mustafa/Work/digitoygames/digiplay-net/GinRummyExtra/Android/bin/Debug/GinRummyExtra2.dll"));
    }
}
