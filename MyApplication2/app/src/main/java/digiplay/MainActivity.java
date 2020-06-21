package digiplay;

import android.content.res.AssetManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class MainActivity extends AppCompatActivity {

    static AssetManager AM;
    static MainActivity I;
    GameView gameView;
    public static ExecutorService ThreadPool = Executors.newFixedThreadPool(4);

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
        if(gameView == null) {
            gameView = new GameView(this);
            setContentView(gameView);
        } else {
            ThreadPool.shutdownNow();
            ThreadPool = Executors.newFixedThreadPool(4);
            gameView.reload();
        }
    }
    public static byte[] readFile(String path) {
        try {
            long time = System.currentTimeMillis();
            InputStream in = AM.open(path);
            ByteArrayOutputStream bytes = new ByteArrayOutputStream();

            byte[] buffer = new byte[1024*128];
            while(true) {
                int readed = in.read(buffer);
                if(readed > 0) bytes.write(buffer, 0, readed); else break;
            }
            time = System.currentTimeMillis() - time;
            return bytes.toByteArray();
        } catch(Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void readFile(final String path, final long completable) {
        protectGamaVMObject(completable); //protect completable from gc
        ThreadPool.execute(new Runnable() {
            @Override
            public void run() {
                byte[] bytes = readFile(path);
                GameView.postCompletable(completable, bytes);
            }
        });
    }

    /*public static void platformRun() {
        MainActivity.I.start();
    }*/

    public static native void gamaVMMain();
    public static native void platformResize(int width, int height);
    public static native void platformStep();
    public static native void completeCompletable(long handle, byte[] data);
    public static native void protectGamaVMObject(long handle);
    static {
        System.loadLibrary("native-lib");
    }
}
