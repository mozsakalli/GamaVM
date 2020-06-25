package gamavm;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;

import digiplay.MainActivity;

public class VM {

    public static byte[] readFile(String path) {
        try {
            long time = System.currentTimeMillis();
            InputStream in = MainActivity.AM.open(path);
            ByteArrayOutputStream bytes = new ByteArrayOutputStream();

            byte[] buffer = new byte[1024*128];
            while(true) {
                int readed = in.read(buffer);
                if(readed > 0) bytes.write(buffer, 0, readed); else break;
            }
            return bytes.toByteArray();
        } catch(Exception e) {
            e.printStackTrace();
        }
        return null;
    }

}
