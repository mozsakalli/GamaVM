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

package com.cava.debugger;

/**
 *
 * @author mustafa
 */
public class DebuggerSocket {
    public native static int connect(String host, int port);
    public native static int listen(int port);
    public native static int accept(int fd);
    public native static void close(int fd);
    public native static int read(int fd,byte[] buffer, int offset, int length);
    public native static int write(int fd,byte[] buffer, int offset, int length);
}
