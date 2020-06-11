package digiplay;

/**
 *
 * @author mustafa
 */
public class Render2D {
    
    static GLQuadBatch quadBatch = new GLQuadBatch(4096);
    static GLShader2D defaultShader = new GLShader2D("gl_FragColor = vColor;");
    static Mat2D modelMatrix;
    static float globalAlpha;
    
    public static void begin() {
        quadBatch.begin(Digiplay.platform.screenWidth, Digiplay.platform.screenHeight, true, 0xff000000);
        globalAlpha = 1;
    }
    
    public static void end() {
        quadBatch.end();
    }
    
    public static void setModelMatrix(Mat2D mat) {
        modelMatrix = mat;
    }
    
    public static void setGlobalAlpha(float alpha) {
        globalAlpha = alpha;
    }
    
    public static void drawQuadMesh(QuadMesh quad, int color, int blendMode) {
        quadBatch.drawQuadMesh(quad, modelMatrix, defaultShader, color, globalAlpha, blendMode);
    }
}
