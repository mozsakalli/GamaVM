
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.ServerSocket;

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
public class Tmp {

    static void work(Socket socket) throws Exception {
        InputStream in = socket.getInputStream();
        OutputStream out = socket.getOutputStream();
        byte[] inBytes = new byte[1024 * 8];
        int readed = in.read(inBytes);
        String reqheader = null;
        String reqbody = null;
        for (int i = 0; i < readed; i++) {
            if (inBytes[i] == 10 && inBytes[i + 2] == 10) {
                reqheader = new String(inBytes, 0, i);
                if (reqheader.startsWith("POST")) {
                    ByteArrayOutputStream bytestream = new ByteArrayOutputStream();
                    String lines[] = reqheader.split("\n");
                    int contentLength = 0;
                    for (String str : lines) {
                        if (str.startsWith("Content-Length:")) {
                            contentLength = Integer.parseInt(str.substring(15).trim());
                            break;
                        }
                    }
                    ByteArrayOutputStream bytes = new ByteArrayOutputStream();
                    int rest = readed - i - 3;
                    if (rest > 0) {
                        bytes.write(inBytes, i + 3, rest);
                        contentLength -= rest;
                    }
                    while (contentLength > 0) {
                        readed = in.read(inBytes);
                        if (readed > 0) {
                            bytes.write(inBytes, 0, readed);
                            contentLength -= readed;
                        } else {
                            break;
                        }
                    }
                    reqbody = new String(bytes.toByteArray());
                }
                break;
            }
        }
        String url = null;
        String lines[] = reqheader.split("\n");
        String fullUrl[] = lines[0].split(" ")[1].split("\\?");
        url = fullUrl[0];
    }

    public static void main(String... args) throws Exception {
        ServerSocket ss = new ServerSocket(7777);
        while (true) {
            Socket cs = ss.accept();
            work(cs);
        }
    }

}
