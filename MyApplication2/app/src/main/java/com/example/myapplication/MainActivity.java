package com.example.myapplication;

import android.content.res.AssetManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;


public class MainActivity extends AppCompatActivity {

    static AssetManager AM;
    static MainActivity I;
    GameView gameView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        AM = this.getAssets();
        I = this;
        gamaVMMain();
    }

    void start() {
        gameView = new GameView(this);
        setContentView(gameView);
    }
    public static byte[] readFile(String path) {
        try {
            long time = System.currentTimeMillis();
            System.out.println("reading: "+path);
            InputStream in = AM.open(path);
            ByteArrayOutputStream bytes = new ByteArrayOutputStream();

            byte[] buffer = new byte[1024*128];
            while(true) {
                int readed = in.read(buffer);
                if(readed > 0) bytes.write(buffer, 0, readed); else break;
            }
            time = System.currentTimeMillis() - time;
            System.out.println("readed in "+time);
            /*
            int ch;
            while((ch = in.read()) != -1) bytes.write(ch);
             */
            return bytes.toByteArray();
        } catch(Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void platformRun() {
        MainActivity.I.start();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public static native void gamaVMMain();
    public static native void platformResize(int width, int height);
    public static native void platformStep();

    static {
        System.loadLibrary("native-lib");
    }
}
