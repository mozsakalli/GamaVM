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

package com.digitoygames.compiler.model;

import java.io.DataInputStream;

/**
 *
 * @author mustafa
 */
public class BootstrapMethod {
    
    public int kind;
    public String clsName;
    public String methodName;
    public String methodSignature;
    public int args[];
    
    public BootstrapMethod(DataInputStream in, CP cp) throws Exception {
        int methodRef = in.readUnsignedShort();
        kind = cp.items[methodRef].index1;
        clsName = cp.items[cp.items[cp.items[cp.items[methodRef].index2].index1].index1].value.toString();
        methodName = cp.items[cp.items[cp.items[cp.items[methodRef].index2].index2].index1].value.toString();
        methodSignature = cp.items[cp.items[cp.items[cp.items[methodRef].index2].index2].index2].value.toString();
        int argCount = in.readUnsignedShort();
        args = new int[argCount];
        for(int i=0; i<argCount; i++)
            args[i] = in.readUnsignedShort();
        /*
        System.out.println("Bootstrap #"+i+": "+methodRef);
        int argCount = in.readUnsignedShort();
        for(int k=0; k<argCount; k++) {
            int argIndex = in.readUnsignedShort();
            System.out.println("   arg#"+k+": "+argIndex);
        }
        */
    }
}
