
import java.lang.reflect.Field;

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

    public Main() {
    }

    static int field = 100;

    static int val(double d, int v) {
        return (int) d + 12 + v + field;
    }

    static long val2() {
        return 10;
    }

    static int fibonacci(int n) {
        if (n == 0 || n == 1) {
            return n;
        } else {
            return fibonacci(n - 1) + fibonacci(n - 2);
        }
    }

    byte b;
    long l;
    double d;
    int fi;

    static void walk(Class cls) {
        while(cls != null) {
            System.out.println(cls.getName());
            Field[] fields = cls.getDeclaredFields();
            for(Field f : fields) {
                System.out.println("    "+f.getName());
            }
            cls = cls.getSuperclass();
        }
        
        System.out.println("-----");
    }

    static void run(Runnable r) {
        r.run();
    }
    
    public static void main() {
        while(true) {
            long time = System.currentTimeMillis();
            byte[] bytes = new byte[1024*1024];
            for(int i=0; i<128; i++) bytes[i] = (byte)i;
            System.out.println(bytes.length);
            System.gc();
            time = System.currentTimeMillis() - time;
            System.out.println("took: "+time);
        }
    }

    static void lambda() {
        System.out.println("Lambda #2");
    }
    @Override
    public String toString() {
        return "Hello!";
    }
    
    public static void main(String...args) {
        
    }

}
