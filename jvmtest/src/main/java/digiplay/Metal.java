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

package digiplay;

/**
 *
 * @author mustafa
 */
public class Metal {
    
    public native static boolean isSupported();
    public native static long createVertexBuffer();
    public native static long createIndexBuffer();
    
    public native static void viewport(int x, int y, int width, int height);
    public native static void scissor(int x, int y, int width, int height);
    public native static void enable(int flags);
    public native static void disable(int flags);
}
