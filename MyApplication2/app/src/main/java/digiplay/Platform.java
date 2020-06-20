package digiplay;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;

public class Platform {

    public static byte[] readAsset(String path) {
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

    public static void run() {
        MainActivity.I.start();
    }

    public static void reload(byte[] bytes, int offset, int length) {
        System.out.println(bytes);
    }
}
