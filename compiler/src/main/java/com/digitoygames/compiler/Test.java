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

package com.digitoygames.compiler;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class Test {

static int fibonacci(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}
    public static int main() {
        List<Integer> array = new ArrayList();
        int[] arr = new int[]{0,1,2,3};
        for(int i=0; i<arr.length; i++) array.add(i);
        int r = 0;
        for(int v : array)
            r += v + arr.length;
        
        return r;
    }
}
