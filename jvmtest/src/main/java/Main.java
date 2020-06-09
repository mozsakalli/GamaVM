
import digiplay.Platform;

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
    
    public static void main() {
        //Platform.run(new MyGame());
        
        System.out.println("Hello GamaVM!");
        for(int i=0; i<1000; i++) {
            byte b[] = new byte[1024*124];
            b[10] = (byte)test(i,i*2,(byte)12);
            System.out.println(b[9]);
            System.gc();
        }
        for(;;) {
            System.out.println(Math.random()+"/"+System.currentTimeMillis()+"/>>");
            System.gc();
        }
        //IosPlatform.run(new MyGame());*/
    }
    
    static int test(long l, int i, byte b) {
        long v = l*12;
        v += i;
        v += b;
        int iv = (int)v;
        return iv;
    }
    
    public static void main(String...args) {
    }



}
