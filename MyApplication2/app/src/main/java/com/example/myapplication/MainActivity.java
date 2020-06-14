package com.example.myapplication;

import android.content.res.AssetManager;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;


public class MainActivity extends AppCompatActivity {

    static AssetManager AM;
    static MainActivity I;
    GameView gameView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().getDecorView().setSystemUiVisibility(View.STATUS_BAR_HIDDEN);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        try { hideSystemUI(); }catch (Exception e){}
        super.onCreate(savedInstanceState);
        AM = this.getAssets();
        I = this;
        gamaVMMain();
    }

    private void hideSystemUI() {
        View decorView = getWindow().getDecorView();
        decorView.setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_IMMERSIVE
                        // Set the content to appear under the system bars so that the
                        // content doesn't resize when the system bars hide and show.
                        | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        // Hide the nav bar and status bar
                        | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_FULLSCREEN
                        | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                        );
    }
    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        if (hasFocus) {
            try { hideSystemUI(); }catch(Exception e){}
        }
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
