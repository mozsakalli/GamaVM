package digiplay.render;

/**
 *
 * @author mustafa
 */
public class GPU {
    static int pendingMask, vpX, vpY, vpW, vpH, scX, scY, scW, scH,
            blendSrc = -1, blendDst = -1, cullMode, depthMask, depthTest;
    
    static VertexBuffer currentVBO;
    static IndexBuffer currentIBO;
    
    
    public final static int PM_VIEWPORT = (1 << 0);
    public final static int PM_INDEXBUF = (1 << 1);
    public final static int PM_VERTLAYOUT = (1 << 2);
    public final static int PM_TEXTURES = (1 << 3);
    public final static int PM_SCISSOR = (1 << 4);
    public final static int PM_BLEND = (1 << 5);
    public final static int PM_CULLMODE = (1 << 6);
    public final static int PM_DEPTH_TEST = (1 << 7);
    public final static int PM_BLEND_EQ = (1 << 8);
    public final static int PM_DEPTH_MASK = (1 << 9);

    public final static int BLENDEQ_ADD = 0;
    public final static int BLENDEQ_SUBTRACT = 1;
    public final static int BLENDEQ_REVERSE_SUBTRACT = 2;
    public final static int BLENDEQ_MIN = 3;
    public final static int BLENDEQ_MAX = 4;

    public final static int BLENDFUNC_ZERO = 0;
    public final static int BLENDFUNC_ONE = 1;
    public final static int BLENDFUNC_SRC_COLOR = 2;
    public final static int BLENDFUNC_ONE_MINUS_SRC_COLOR = 3;
    public final static int BLENDFUNC_SRC_ALPHA = 4;
    public final static int BLENDFUNC_ONE_MINUS_SRC_ALPHA = 5;
    public final static int BLENDFUNC_DST_ALPHA = 6;
    public final static int BLENDFUNC_ONE_MINUS_DST_ALPHA = 7;
    public final static int BLENDFUNC_DST_COLOR = 8;
    public final static int BLENDFUNC_ONE_MINUS_DST_COLOR = 9;
    
    //public final static int CLEAR_NONE      = 0;
    public final static int CLEAR_COLOR     = 1;
    public final static int CLEAR_DEPTH     = 2;
    public final static int CLEAR_STENCIL   = 4;

    public final static int PRIM_LINES = 0;
    public final static int PRIM_LINESSTRIP = 1;
    public final static int PRIM_TRIANGLES = 2;
    public final static int PRIM_TRISTRIP = 3;
    public final static int PRIM_QUADS = 4;
    
    public static void commit() {
        commit(0xFFFFFFFF);
    }
    public native static void commit(int flags);
    
    public native static void clear(int flags, float r, float g, float b, float a, float depth);
    
    public static void setViewport(int x, int y, int width, int height) {
        vpX = x;
        vpY = y;
        vpW = width;
        vpH = height;
        pendingMask |= PM_VIEWPORT;
    }
    
    public static void setBlending(int src, int dst) {
        blendSrc = src;
        blendDst = dst;
        pendingMask |= PM_BLEND;
    }
    
}
