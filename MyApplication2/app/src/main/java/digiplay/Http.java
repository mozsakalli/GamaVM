package digiplay;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class Http implements Runnable {
    long gamaHandle;
    String url;
    byte[] postData;

    public Http(long gamaHandle, String url, byte[] postData) {
        this.gamaHandle = gamaHandle;
        this.url = url;
        this.postData = postData;
    }

    @Override
    public void run() {
        byte[] response = null;
        HttpURLConnection conn = null;
        try {
            if(url.startsWith("//")) url = "http://" + url;
            conn = (HttpURLConnection)new URL(url).openConnection();
            if(postData != null) {
                conn.setDoOutput(true);
                conn.setRequestMethod("POST");
                conn.setRequestProperty("Content-Length", String.valueOf(postData.length));
                OutputStream out = conn.getOutputStream();
                out.write(postData);
                out.flush();
                out.close();
            }

            if(conn.getResponseCode() == 200) {
                byte[] buf = new byte[1024];
                ByteArrayOutputStream bytes = new ByteArrayOutputStream();
                InputStream in = conn.getInputStream();
                while(true) {
                    int size = in.read(buf);
                    if(size > 0) bytes.write(buf, 0, size); else break;
                }
                response = bytes.toByteArray();
            }
        } catch(Exception e){

        } finally {
            try { conn.disconnect(); }catch(Exception e){}
        }
        GameView.postCompletable(gamaHandle, response);
    }

    public static void makeRequest(long gamaHandle, String url, byte[] postData) {
        Http h = new Http(gamaHandle, url, postData);
        MainActivity.ThreadPool.execute(h);
    }


}
