
import gamavm.apple.ObjC;
import gamavm.apple.ObjCClass;
import gamavm.apple.SKPaymentQueue;
import gamavm.apple.Selector;



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
        System.out.println(SKPaymentQueue.defaultQueue().getHandle());
        System.out.println("float = "+(3.4567f));
        System.out.println("double = "+(3.4567d));
        System.out.println("long = "+(34567l));
        System.out.println("int = "+(3));
    }

    public static void main(String...args) {
        main();
    }

}
