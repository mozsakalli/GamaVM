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

package gamavm.apple.uikit;

import gamavm.apple.NSMutableObject;
import gamavm.apple.ObjC;
import gamavm.apple.ObjCClass;
import gamavm.apple.Selector;

/**
 *
 * @author mustafa
 */
public class UIApplication extends NSMutableObject {

    public native static void main(UIApplicationDelegate delegate);
    
    static UIApplication sharedApplication;
    public static UIApplication sharedApplication() {
        if(sharedApplication == null)
            sharedApplication = ObjC.callObject(ObjCClass.get("UIApplication"), Selector.register("sharedApplication"), UIApplication.class);
        return sharedApplication;
    }
}
