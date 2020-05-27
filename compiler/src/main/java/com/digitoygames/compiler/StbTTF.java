package com.digitoygames.compiler;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mustafa
 */
public class StbTTF {

    final static int STBTT_vmove = 1;
    final static int STBTT_vline = 2;
    final static int STBTT_vcurve = 3;

    final static int STBTT_MACSTYLE_DONTCARE = 0;
    final static int STBTT_MACSTYLE_BOLD = 1;
    final static int STBTT_MACSTYLE_ITALIC = 2;
    final static int STBTT_MACSTYLE_UNDERSCORE = 4;
    final static int STBTT_MACSTYLE_NONE = 8; // <= not same as 0, this makes us check the bitfield is 0

    // platformID
    final static int STBTT_PLATFORM_ID_UNICODE = 0;
    final static int STBTT_PLATFORM_ID_MAC = 1;
    final static int STBTT_PLATFORM_ID_ISO = 2;
    final static int STBTT_PLATFORM_ID_MICROSOFT = 3;

    // encodingID for STBTT_PLATFORM_ID_UNICODE
    final static int STBTT_UNICODE_EID_UNICODE_1_0 = 0;
    final static int STBTT_UNICODE_EID_UNICODE_1_1 = 1;
    final static int STBTT_UNICODE_EID_ISO_10646 = 2;
    final static int STBTT_UNICODE_EID_UNICODE_2_0_BMP = 3;
    final static int STBTT_UNICODE_EID_UNICODE_2_0_FULL = 4;

    // encodingID for STBTT_PLATFORM_ID_MICROSOFT
    final static int STBTT_MS_EID_SYMBOL = 0;
    final static int STBTT_MS_EID_UNICODE_BMP = 1;
    final static int STBTT_MS_EID_SHIFTJIS = 2;
    final static int STBTT_MS_EID_UNICODE_FULL = 10;

    // encodingID for STBTT_PLATFORM_ID_MAC; same as Script Manager codes
    final static int STBTT_MAC_EID_ROMAN = 0;
    final static int STBTT_MAC_EID_ARABIC = 4;
    final static int STBTT_MAC_EID_JAPANESE = 1;
    final static int STBTT_MAC_EID_HEBREW = 5;
    final static int STBTT_MAC_EID_CHINESE_TRAD = 2;
    final static int STBTT_MAC_EID_GREEK = 6;
    final static int STBTT_MAC_EID_KOREAN = 3;
    final static int STBTT_MAC_EID_RUSSIAN = 7;

    // languageID for STBTT_PLATFORM_ID_MICROSOFT; same as LCID...
    // problematic because there are e.g. 16 english LCIDs and 16 arabic LCIDs
    final static int STBTT_MS_LANG_ENGLISH = 0x0409;
    final static int STBTT_MS_LANG_ITALIAN = 0x0410;
    final static int STBTT_MS_LANG_CHINESE = 0x0804;
    final static int STBTT_MS_LANG_JAPANESE = 0x0411;
    final static int STBTT_MS_LANG_DUTCH = 0x0413;
    final static int STBTT_MS_LANG_KOREAN = 0x0412;
    final static int STBTT_MS_LANG_FRENCH = 0x040c;
    final static int STBTT_MS_LANG_RUSSIAN = 0x0419;
    final static int STBTT_MS_LANG_GERMAN = 0x0407;
    final static int STBTT_MS_LANG_SPANISH = 0x0409;
    final static int STBTT_MS_LANG_HEBREW = 0x040d;
    final static int STBTT_MS_LANG_SWEDISH = 0x041D;

    // languageID for STBTT_PLATFORM_ID_MAC
    final static int STBTT_MAC_LANG_ENGLISH = 0;
    final static int STBTT_MAC_LANG_JAPANESE = 11;
    final static int STBTT_MAC_LANG_ARABIC = 12;
    final static int STBTT_MAC_LANG_KOREAN = 23;
    final static int STBTT_MAC_LANG_DUTCH = 4;
    final static int STBTT_MAC_LANG_RUSSIAN = 32;
    final static int STBTT_MAC_LANG_FRENCH = 1;
    final static int STBTT_MAC_LANG_SPANISH = 6;
    final static int STBTT_MAC_LANG_GERMAN = 2;
    final static int STBTT_MAC_LANG_SWEDISH = 5;
    final static int STBTT_MAC_LANG_HEBREW = 10;
    final static int STBTT_MAC_LANG_CHINESE_SIMPLIFIED = 33;
    final static int STBTT_MAC_LANG_ITALIAN = 3;
    final static int STBTT_MAC_LANG_CHINESE_TRAD = 19;

    final static int STBTT_MAX_OVERSAMPLE = 8;
    //**typedef int stbtt__test_oversample_pow2[(STBTT_MAX_OVERSAMPLE & (STBTT_MAX_OVERSAMPLE-1)) == 0 ? 1 : -1];
    final static int STBTT_RASTERIZER_VERSION = 2;

    public static class Stbtt_fontinfo {

        public byte[] data;
        public int fontstart;

        public int numGlyphs;

        // table locations as offset from start of .ttf
        public int loca;
        public int head;
        public int glyf;
        public int hhea;
        public int hmtx;
        public int kern;

        public int index_map;
        public int indexToLocFormat;
    }

    public static class Stbtt_vertex {
        public int x;
        public int y;
        public int cx;
        public int cy;
        public int type;
    }

    public static class Stbtt_temp_rect {

        public int x0;
        public int y0;
        public int x1;
        public int y1;
    }
    
    final static Stbtt_temp_rect RECT = new Stbtt_temp_rect();

    public static class Stbtt_temp_glyph_h_metrics {

        public int advanceWidth;
        public int leftSideBearing;
    }
    
    final static Stbtt_temp_glyph_h_metrics HMETRICS = new Stbtt_temp_glyph_h_metrics();

    public static class Stbtt_temp_font_v_metrics {

        public int ascent;
        public int descent;
        public int lineGap;
    }
    
    final static Stbtt_temp_font_v_metrics VMETRICS = new Stbtt_temp_font_v_metrics();
    
    static class Stbtt__edge {
        public float x0;
        public float y0;
        public float x1;
        public float y1;
        public boolean invert;
    }

    static class Stbtt__active_edge {
        public Stbtt__active_edge next;
        public float fx;
        public float fdx;
        public float fdy;
        public float direction;
        public float sy;
        public float ey;
    }

    static class Stbtt__point {

        public float x;
        public float y;
    }

    public static interface Stbtt__output {
        public void setPixel(int x, int y, int alpha);
    }

    static int ttBYTE(byte[] p, int pos) {
        return p[pos]&0xff;
    }

    static int ttCHAR(byte[] p, int pos) {
        int n = p[pos];
        if (n >= 128) {
            return n - 256;
        }
        return n;
    }

    static int ttUSHORT(byte[] p, int pos) {
        int ch1 = p[pos + 0]&0xff;
        int ch2 = p[pos + 1]&0xff;
        return ch2 | (ch1 << 8);
    }

    static int ttSHORT(byte[] p, int pos) {
        int ch1 = p[pos + 0]&0xff;
        int ch2 = p[pos + 1]&0xff;
        int n = ch2 | (ch1 << 8);
        if ((n & 0x8000) != 0) {
            return n - 0x10000;
        }
        return n;
    }

    static int ttULONG(byte[] p, int pos) {
        return ttLONG(p, pos);
    }

    static int ttLONG(byte[] p, int pos) {
        int ch1 = p[pos + 0]&0xff;
        int ch2 = p[pos + 1]&0xff;
        int ch3 = p[pos + 2]&0xff;
        int ch4 = p[pos + 3]&0xff;
        return ch4 | (ch3 << 8) | (ch2 << 16) | (ch1 << 24);
    }

    static int ttFixed(byte[] p, int pos) {
        return ttLONG(p, pos);
    }

    static boolean stbtt_tag4(byte[] p, int pos, int c0, int c1, int c2, int c3) {
        return p[pos + 0] == c0 && p[pos + 1] == c1 && p[pos + 2] == c2 && p[pos + 3] == c3;
    }

    static boolean stbtt_tag(byte[] p, int pos, String str) {
        return stbtt_tag4(p, pos, str.charAt(0), str.charAt(1), str.charAt(2), str.charAt(3));
    }

    static boolean stbtt__isfont(byte[] font) {
        // check the version number
        if (stbtt_tag4(font, 0, '1', 0, 0, 0)) {
            return true; // TrueType 1
        }
        if (stbtt_tag(font, 0, "typ1")) {
            return true; // TrueType with type 1 font -- we don't support this!
        }
        if (stbtt_tag(font, 0, "OTTO")) {
            return true; // OpenType with CFF
        }
        if (stbtt_tag4(font, 0, 0, 1, 0, 0)) {
            return true; // OpenType 1.0
        }
        return false;
    }

    static int stbtt__find_table(byte[] data, int fontstart, String tag) {
        int num_tables = ttUSHORT(data, fontstart + 4);
        int tabledir = fontstart + 12;
        for (int i = 0; i < num_tables; i++) {
            int loc = tabledir + 16 * i;
            if (stbtt_tag(data, loc + 0, tag)) {
                return ttULONG(data, loc + 8);
            }
        }
        return 0;
    }

    static int stbtt_GetFontOffsetForIndex(byte[] font_collection, int index) {
        // if it's just a font, there's only one valid index
        if (stbtt__isfont(font_collection)) {
            return index == 0 ? 0 : -1;
        }

        // check if it's a TTC
        if (stbtt_tag(font_collection, 0, "ttcf")) {
            // version 1?
            if (ttULONG(font_collection, 4) == 0x00010000 || ttULONG(font_collection, 4) == 0x00020000) {
                int n = ttLONG(font_collection, 8);
                if (index >= n) {
                    return -1;
                }
                return ttULONG(font_collection, 12 + index * 4);
            }
        }
        return -1;
    }

    public static boolean stbtt_InitFont(Stbtt_fontinfo info, byte[] data, int fontstart) {
        int cmap, t;
        int numTables;

        info.data = data;
        info.fontstart = fontstart;

        cmap = stbtt__find_table(data, fontstart, "cmap");       // required
        info.loca = stbtt__find_table(data, fontstart, "loca"); // required
        info.head = stbtt__find_table(data, fontstart, "head"); // required
        info.glyf = stbtt__find_table(data, fontstart, "glyf"); // required
        info.hhea = stbtt__find_table(data, fontstart, "hhea"); // required
        info.hmtx = stbtt__find_table(data, fontstart, "hmtx"); // required
        info.kern = stbtt__find_table(data, fontstart, "kern"); // not required
        if (cmap == 0 || info.loca == 0 || info.head == 0 || info.glyf == 0 || info.hhea == 0 || info.hmtx == 0) {
            return false;
        }

        t = stbtt__find_table(data, fontstart, "maxp");
        if (t != 0) {
            info.numGlyphs = ttUSHORT(data, t + 4);
        } else {
            info.numGlyphs = 0xffff;
        }

        // find a cmap encoding table we understand *now* to avoid searching
        // later. (todo: could make this installable)
        // the same regardless of glyph.
        numTables = ttUSHORT(data, cmap + 2);
        info.index_map = 0;

        for (int i = 0; i < numTables; i++) {
            int encoding_record = cmap + 4 + 8 * i;
            // find an encoding we understand:
            switch (ttUSHORT(data, encoding_record)) {
                case STBTT_PLATFORM_ID_MICROSOFT:
                    switch (ttUSHORT(data, encoding_record + 2)) {
                        case STBTT_MS_EID_UNICODE_BMP:
                        case STBTT_MS_EID_UNICODE_FULL:
                            // MS/Unicode
                            info.index_map = cmap + ttULONG(data, encoding_record + 4);
                    }
                    break;

                case STBTT_PLATFORM_ID_UNICODE:
                    // Mac/iOS has these
                    // all the encodingIDs are unicode, so we don't bother to check it
                    info.index_map = cmap + ttULONG(data, encoding_record + 4);
                    break;
            }
        }
        if (info.index_map == 0) {
            return false;
        }

        info.indexToLocFormat = ttUSHORT(data, info.head + 50);
        return true;
    }

    public static int stbtt_FindGlyphIndex(Stbtt_fontinfo info, int unicode_codepoint) {
        byte[] data = info.data;
        int index_map = info.index_map;

        int format = ttUSHORT(data, index_map + 0);
        if (format == 0) { // apple byte encoding
            int bytes = ttUSHORT(data, index_map + 2);
            if (unicode_codepoint < bytes - 6) {
                return ttBYTE(data, index_map + 6 + unicode_codepoint);
            }
            return 0;
        } else if (format == 6) {
            int first = ttUSHORT(data, index_map + 6);
            int count = ttUSHORT(data, index_map + 8);
            if (unicode_codepoint >= first && unicode_codepoint < first + count) {
                return ttUSHORT(data, index_map + 10 + (unicode_codepoint - first) * 2);
            }
            return 0;
        } else if (format == 2) {
            return 0;
        } else if (format == 4) { // standard mapping for windows fonts: binary search collection of ranges
            int segcount = ttUSHORT(data, index_map + 6) >> 1;
            int searchRange = ttUSHORT(data, index_map + 8) >> 1;
            int entrySelector = ttUSHORT(data, index_map + 10);
            int rangeShift = ttUSHORT(data, index_map + 12) >> 1;

            // do a binary search of the segments
            int endCount = index_map + 14;
            int search = endCount;

            if (unicode_codepoint > 0xffff) {
                return 0;
            }

            // they lie from endCount .. endCount + segCount
            // but searchRange is the nearest power of two, so...
            if (unicode_codepoint >= ttUSHORT(data, search + rangeShift * 2)) {
                search += rangeShift * 2;
            }

            // now decrement to bias correctly to find smallest
            search -= 2;
            while (entrySelector != 0) {
                int end;
                searchRange >>= 1;
                end = ttUSHORT(data, search + searchRange * 2);
                if (unicode_codepoint > end) {
                    search += searchRange * 2;
                }
                --entrySelector;
            }
            search += 2;

            {
                int offset, start;
                int item = (search - endCount) >> 1;

                //STBTT_assert(unicode_codepoint <= ttUSHORT(data, endCount + 2*item));
                start = ttUSHORT(data, index_map + 14 + segcount * 2 + 2 + 2 * item);
                if (unicode_codepoint < start) {
                    return 0;
                }

                offset = ttUSHORT(data, index_map + 14 + segcount * 6 + 2 + 2 * item);
                if (offset == 0) {
                    return unicode_codepoint + ttSHORT(data, index_map + 14 + segcount * 4 + 2 + 2 * item);
                }
                return ttUSHORT(data, offset + (unicode_codepoint - start) * 2 + index_map + 14 + segcount * 6 + 2 + 2 * item);
            }
        } else if (format == 12 || format == 13) {
            int ngroups = ttULONG(data, index_map + 12);
            int low, high;
            low = 0;
            high = ngroups;
            // Binary search the right group.
            while (low < high) {
                int mid = low + ((high - low) >> 1); // rounds down, so low <= mid < high
                int start_char = ttULONG(data, index_map + 16 + mid * 12);
                int end_char = ttULONG(data, index_map + 16 + mid * 12 + 4);
                if (unicode_codepoint < start_char) {
                    high = mid;
                } else if (unicode_codepoint > end_char) {
                    low = mid + 1;
                } else {
                    int start_glyph = ttULONG(data, index_map + 16 + mid * 12 + 8);
                    if (format == 12) {
                        return start_glyph + unicode_codepoint - start_char;
                    } else // format == 13
                    {
                        return start_glyph;
                    }
                }
            }
            return 0; // not found
        }
        return 0;
    }

    /*public static List<Stbtt_vertex> stbtt_GetCodepointShape(Stbtt_fontinfo info, int unicode_codepoint) {
        return stbtt_GetGlyphShape(info, stbtt_FindGlyphIndex(info, unicode_codepoint));
    }*/

    private static void stbtt_setvertex(Stbtt_vertex v, int type, int x, int y, int cx, int cy) {
        v.type = type;
        v.x = x;
        v.y = y;
        v.cx = cx;
        v.cy = cy;
    }

    private static int stbtt__GetGlyfOffset(Stbtt_fontinfo info, int glyph_index) {
        int g1, g2;

        if (glyph_index >= info.numGlyphs) {
            return -1; // glyph index out of range
        }
        if (info.indexToLocFormat >= 2) {
            return -1; // unknown index->glyph map format
        }
        if (info.indexToLocFormat == 0) {
            g1 = info.glyf + ttUSHORT(info.data, info.loca + glyph_index * 2) * 2;
            g2 = info.glyf + ttUSHORT(info.data, info.loca + glyph_index * 2 + 2) * 2;
        } else {
            g1 = info.glyf + ttULONG(info.data, info.loca + glyph_index * 4);
            g2 = info.glyf + ttULONG(info.data, info.loca + glyph_index * 4 + 4);
        }

        return g1 == g2 ? -1 : g1; // if length is 0, return -1
    }

    public static boolean stbtt_GetGlyphBox(Stbtt_fontinfo info, int glyph_index, Stbtt_temp_rect rect) {
        int g = stbtt__GetGlyfOffset(info, glyph_index);
        if (g < 0) {
            return false;
        }

        rect.x0 = ttSHORT(info.data, g + 2);
        rect.y0 = ttSHORT(info.data, g + 4);
        rect.x1 = ttSHORT(info.data, g + 6);
        rect.y1 = ttSHORT(info.data, g + 8);
        return true;
    }

    public static boolean stbtt_GetCodepointBox(Stbtt_fontinfo info, int codepoint, Stbtt_temp_rect rect) {
        return stbtt_GetGlyphBox(info, stbtt_FindGlyphIndex(info, codepoint), rect);
    }

    public static boolean stbtt_IsGlyphEmpty(Stbtt_fontinfo info, int glyph_index) {
        int numberOfContours;
        int g = stbtt__GetGlyfOffset(info, glyph_index);
        if (g < 0) {
            return true;
        }
        numberOfContours = ttSHORT(info.data, g);
        return numberOfContours == 0;
    }

    private static int stbtt__close_shape(List<Stbtt_vertex> vertices, int num_vertices, boolean was_off, boolean start_off,
            int sx, int sy, int scx, int scy, int cx, int cy) {
        if (start_off) {
            if (was_off) {
                stbtt_setvertex(vertices.get(num_vertices++), STBTT_vcurve, (cx + scx) >> 1, (cy + scy) >> 1, cx, cy);
            }
            stbtt_setvertex(vertices.get(num_vertices++), STBTT_vcurve, sx, sy, scx, scy);
        } else if (was_off) {
            stbtt_setvertex(vertices.get(num_vertices++), STBTT_vcurve, sx, sy, cx, cy);
        } else {
            stbtt_setvertex(vertices.get(num_vertices++), STBTT_vline, sx, sy, 0, 0);
        }
        return num_vertices;
    }

    private static void copyVertices(List<Stbtt_vertex> from, List<Stbtt_vertex> to, int offset, int count) {
        while (to.size() < offset + count) {
            to.add(null);
        }
        for (int i = 0; i < count; i++) {
            to.set(offset + i, from.get(i));
        }
    }

    public static List<Stbtt_vertex> stbtt_GetGlyphShape(Stbtt_fontinfo info, int glyph_index) {
        int numberOfContours;
        byte[] endPtsOfContours;
        byte[] data = info.data;
        List<Stbtt_vertex> vertices = null;
        int num_vertices = 0;
        int g = stbtt__GetGlyfOffset(info, glyph_index);

        if (g < 0) {
            return null;
        }

        numberOfContours = ttSHORT(data, g);
        int dg = g + 10;

        if (numberOfContours > 0) {
            int flags = 0, flagcount;
            int ins, j = 0, m, n, next_move = 0, off = 0;
            boolean was_off = false;
            boolean start_off = false;
            int x, y, cx, cy, sx, sy, scx, scy;
            byte[] points;
            int pointsIndex = 0;
            endPtsOfContours = data;//data.sub(g + 10, data.length - (g + 10));
            ins = ttUSHORT(data, g + 10 + numberOfContours * 2);
            points = data; //data.sub(g + 10 + numberOfContours * 2 + 2 + ins, data.length - (g + 10 + numberOfContours * 2 + 2 + ins));
            int pointsPtr = g+10+numberOfContours*2+ins+2;
            
            n = 1 + ttUSHORT(endPtsOfContours, numberOfContours * 2 - 2 + dg);

            m = n + 2 * numberOfContours;  // a loose bound on how many vertices we might need
            vertices = new ArrayList<>(m);
            if (vertices == null) {
                return null;
            } else {
                for (int i = 0; i < m; i++) {
                    vertices.add(new Stbtt_vertex());
                }
            }

            next_move = 0;
            flagcount = 0;

            // in first pass, we load uninterpreted data into the allocated array
            // above, shifted to the end of the array so we won't overwrite it when
            // we create our final data starting from the front
            off = m - n; // starting offset for uninterpreted data, regardless of how m ends up being calculated

            // first load flags
            for (int i = 0; i < n; i++) {
                if (flagcount == 0) {
                    flags = points[pointsPtr + pointsIndex++]&0xff;
                    if ((flags & 8) != 0) {
                        flagcount = points[pointsPtr + pointsIndex++]&0xff;
                    }
                } else {
                    --flagcount;
                }
                vertices.get(off + i).type = flags;
            }

            // now load x coordinates
            x = 0;
            for (int i = 0; i < n; i++) {
                flags = vertices.get(off + i).type;
                if ((flags & 2) != 0) {
                    int dx = points[pointsPtr + pointsIndex++]&0xff;
                    x += ((flags & 16) != 0) ? dx : -dx; // ???
                } else if ((flags & 16) == 0) {
                    int value;
                    int ch1 = points[pointsPtr + pointsIndex + 0]&0xff;
                    int ch2 = points[pointsPtr + pointsIndex + 1]&0xff;
                    int n2 = ch2 | (ch1 << 8);
                    if ((n2 & 0x8000) != 0) {
                        value = n2 - 0x10000;
                    } else {
                        value = n2;
                    }
                    x = x + value;
                    pointsIndex += 2;
                }
                vertices.get(off + i).x = x;
            }

            // now load y coordinates
            y = 0;
            for (int i = 0; i < n; i++) {
                flags = vertices.get(off + i).type;
                if ((flags & 4) != 0) {
                    int dy = points[pointsPtr + pointsIndex++]&0xff;
                    y += ((flags & 32) != 0) ? dy : -dy; // ???
                } else if ((flags & 32) == 0) {
                    int value;
                    int ch1 = points[pointsPtr + pointsIndex + 0]&0xff;
                    int ch2 = points[pointsPtr + pointsIndex + 1]&0xff;
                    int n2 = ch2 | (ch1 << 8);
                    if ((n2 & 0x8000) != 0) {
                        value = n2 - 0x10000;
                    } else {
                        value = n2;
                    }
                    y = y + value;
                    pointsIndex += 2;
                }
                vertices.get(off + i).y = y;
            }

            // now convert them to our format
            num_vertices = 0;
            sx = sy = cx = cy = scx = scy = 0;
            int i = 0;
            while (i < n) {
                flags = vertices.get(off + i).type;
                x = vertices.get(off + i).x;
                y = vertices.get(off + i).y;

                if (next_move == i) {
                    if (i != 0) {
                        num_vertices = stbtt__close_shape(vertices, num_vertices, was_off, start_off, sx, sy, scx, scy, cx, cy);
                    }

                    // now start the new one               
                    start_off = (flags & 1) == 0;
                    if (start_off) {
                        // if we start off with an off-curve point, then when we need to find a point on the curve
                        // where we can start, and we need to save some state for when we wraparound.
                        scx = x;
                        scy = y;
                        if ((vertices.get(off + i + 1).type & 1) == 0) {
                            // next point is also a curve point, so interpolate an on-point curve
                            sx = (x + vertices.get(off + i + 1).x) >> 1;
                            sy = (y + vertices.get(off + i + 1).y) >> 1;
                        } else {
                            // otherwise just use the next point as our start point
                            sx = vertices.get(off + i + 1).x;
                            sy = vertices.get(off + i + 1).y;
                            ++i; // we're using point i+1 as the starting point, so skip it
                        }
                    } else {
                        sx = x;
                        sy = y;
                    }
                    stbtt_setvertex(vertices.get(num_vertices++), STBTT_vmove, sx, sy, 0, 0);
                    was_off = false;
                    next_move = 1 + ttUSHORT(endPtsOfContours, j * 2+dg);
                    ++j;
                } else if ((flags & 1) == 0) { // if it's a curve
                    if (was_off) // two off-curve control points in a row means interpolate an on-curve midpoint
                    {
                        stbtt_setvertex(vertices.get(num_vertices++), STBTT_vcurve, (cx + x) >> 1, (cy + y) >> 1, cx, cy);
                    }
                    cx = x;
                    cy = y;
                    was_off = true;
                } else {
                    if (was_off) {
                        stbtt_setvertex(vertices.get(num_vertices++), STBTT_vcurve, x, y, cx, cy);
                    } else {
                        stbtt_setvertex(vertices.get(num_vertices++), STBTT_vline, x, y, 0, 0);
                    }
                    was_off = false;
                }
                ++i;
            }
            num_vertices = stbtt__close_shape(vertices, num_vertices, was_off, start_off, sx, sy, scx, scy, cx, cy);
        } else if (numberOfContours == -1) {
            // Compound shapes.
            int more = 1;
            byte[] comp = data;//: Blob = data.sub(g + 10, data.length - (g + 10));
            int compIndex = g+10;
            num_vertices = 0;
            vertices = null;
            while (more != 0) {
                int flags, gidx;
                int comp_num_verts = 0, i;
                List<Stbtt_vertex> comp_verts = null;
                List<Stbtt_vertex> tmp = null;
                float mtx0 = 1;
                float mtx1 = 0;
                float mtx2 = 0;
                float mtx3 = 1;
                float mtx4 = 0;
                float mtx5 = 0;
                float m, n;

                flags = ttSHORT(comp, compIndex);
                compIndex += 2;
                gidx = ttSHORT(comp, compIndex);
                compIndex += 2;

                if ((flags & 2) != 0) { // XY values
                    if ((flags & 1) != 0) { // shorts
                        mtx4 = ttSHORT(comp, compIndex);
                        compIndex += 2;
                        mtx5 = ttSHORT(comp, compIndex);
                        compIndex += 2;
                    } else {
                        mtx4 = ttCHAR(comp, compIndex);
                        compIndex += 1;
                        mtx5 = ttCHAR(comp, compIndex);
                        compIndex += 1;
                    }
                } else {
                    // @TODO handle matching point
                    //STBTT_assert(false);
                }
                if ((flags & (1 << 3)) != 0) { // WE_HAVE_A_SCALE
                    mtx0 = mtx3 = ttSHORT(comp, compIndex) / 16384.0f;
                    compIndex += 2;
                    mtx1 = mtx2 = 0;
                } else if ((flags & (1 << 6)) != 0) { // WE_HAVE_AN_X_AND_YSCALE
                    mtx0 = ttSHORT(comp, compIndex) / 16384.0f;
                    compIndex += 2;
                    mtx1 = mtx2 = 0;
                    mtx3 = ttSHORT(comp, compIndex) / 16384.0f;
                    compIndex += 2;
                } else if ((flags & (1 << 7)) != 0) { // WE_HAVE_A_TWO_BY_TWO
                    mtx0 = ttSHORT(comp, compIndex) / 16384.0f;
                    compIndex += 2;
                    mtx1 = ttSHORT(comp, compIndex) / 16384.0f;
                    compIndex += 2;
                    mtx2 = ttSHORT(comp, compIndex) / 16384.0f;
                    compIndex += 2;
                    mtx3 = ttSHORT(comp, compIndex) / 16384.0f;
                    compIndex += 2;
                }

                // Find transformation scales.
                m = (float) Math.sqrt(mtx0 * mtx0 + mtx1 * mtx1);
                n = (float) Math.sqrt(mtx2 * mtx2 + mtx3 * mtx3);

                // Get indexed glyph.
                comp_verts = stbtt_GetGlyphShape(info, gidx);
                comp_num_verts = comp_verts == null ? 0 : comp_verts.size();
                if (comp_num_verts > 0) {
                    // Transform vertices.
                    for (i = 0; i < comp_num_verts; i++) {
                        Stbtt_vertex v = comp_verts.get(i);
                        int x, y;
                        x = v.x;
                        y = v.y;
                        v.x = (int) (m * (mtx0 * x + mtx2 * y + mtx4));
                        v.y = (int) (n * (mtx1 * x + mtx3 * y + mtx5));
                        x = v.cx;
                        y = v.cy;
                        v.cx = (int) (m * (mtx0 * x + mtx2 * y + mtx4));
                        v.cy = (int) (n * (mtx1 * x + mtx3 * y + mtx5));
                    }
                    // Append vertices.
                    tmp = new ArrayList<Stbtt_vertex>(num_vertices + comp_num_verts);
                    if (tmp == null) {
                        return null;
                    }
                    if (num_vertices > 0) {
                        copyVertices(vertices, tmp, 0, num_vertices);
                    }
                    copyVertices(comp_verts, tmp, num_vertices, comp_num_verts);
                    vertices = tmp;
                    num_vertices += comp_num_verts;
                }
                // More components ?
                more = flags & (1 << 5);
            }
        } else if (numberOfContours < 0) {
            // @TODO other compound variations?
            //STBTT_assert(false);
        } else {
            // numberOfCounters == 0, do nothing
        }

        if (vertices == null) {
            return null;
        }
        //STBTT_assert(vertices.length >= num_vertices);
        if (num_vertices < vertices.size()) {
            List<Stbtt_vertex> tmp = new ArrayList<Stbtt_vertex>(num_vertices);
            copyVertices(vertices, tmp, 0, num_vertices);
            return tmp;
        } else {
            return vertices;
        }
    }

    public static Stbtt_temp_glyph_h_metrics stbtt_GetGlyphHMetrics(Stbtt_fontinfo info, int glyph_index) {
        int numOfLongHorMetrics = ttUSHORT(info.data, info.hhea + 34);
        Stbtt_temp_glyph_h_metrics metrics = HMETRICS;
        if (glyph_index < numOfLongHorMetrics) {
            metrics.advanceWidth = ttSHORT(info.data, info.hmtx + 4 * glyph_index);
            metrics.leftSideBearing = ttSHORT(info.data, info.hmtx + 4 * glyph_index + 2);
        } else {
            metrics.advanceWidth = ttSHORT(info.data, info.hmtx + 4 * (numOfLongHorMetrics - 1));
            metrics.leftSideBearing = ttSHORT(info.data, info.hmtx + 4 * numOfLongHorMetrics + 2 * (glyph_index - numOfLongHorMetrics));
        }
        return metrics;
    }

    public static int stbtt_GetGlyphKernAdvance(Stbtt_fontinfo info, int glyph1, int glyph2) {
        byte[] data = info.data;// info.data.sub(info.kern, info.data.length - info.kern);
        int needle, straw;
        int l, r, m;
        int dg = info.kern;

        // we only look at the first table. it must be 'horizontal' and format 0.
        if (info.kern == 0) {
            return 0;
        }
        if (ttUSHORT(data, 2 + dg) < 1) // number of tables, need at least 1
        {
            return 0;
        }
        if (ttUSHORT(data, 8 + dg) != 1) // horizontal flag must be set in format
        {
            return 0;
        }

        l = 0;
        r = ttUSHORT(data, 10 + dg) - 1;
        needle = glyph1 << 16 | glyph2;
        while (l <= r) {
            m = (l + r) >> 1;
            straw = ttULONG(data, 18 + (m * 6) + dg); // note: unaligned read
            if (needle < straw) {
                r = m - 1;
            } else if (needle > straw) {
                l = m + 1;
            } else {
                return ttSHORT(data, 22 + (m * 6) + dg);
            }
        }
        return 0;
    }

    public static int stbtt_GetCodepointKernAdvance(Stbtt_fontinfo info, int ch1, int ch2) {
        if (info.kern == 0) // if no kerning table, don't waste time looking up both codepoint->glyphs
        {
            return 0;
        }
        return stbtt_GetGlyphKernAdvance(info, stbtt_FindGlyphIndex(info, ch1), stbtt_FindGlyphIndex(info, ch2));
    }

    public static Stbtt_temp_glyph_h_metrics stbtt_GetCodepointHMetrics(Stbtt_fontinfo info, int codepoint) {
        return stbtt_GetGlyphHMetrics(info, stbtt_FindGlyphIndex(info, codepoint));
    }

    public static Stbtt_temp_font_v_metrics stbtt_GetFontVMetrics(Stbtt_fontinfo info) {
        Stbtt_temp_font_v_metrics metrics = VMETRICS;
        metrics.ascent = ttSHORT(info.data, info.hhea + 4);
        metrics.descent = ttSHORT(info.data, info.hhea + 6);
        metrics.lineGap = ttSHORT(info.data, info.hhea + 8);
        return metrics;
    }

    public static Stbtt_temp_rect stbtt_GetFontBoundingBox(Stbtt_fontinfo info) {
        Stbtt_temp_rect rect = RECT;
        rect.x0 = ttSHORT(info.data, info.head + 36);
        rect.y0 = ttSHORT(info.data, info.head + 38);
        rect.x1 = ttSHORT(info.data, info.head + 40);
        rect.y1 = ttSHORT(info.data, info.head + 42);
        return rect;
    }

    public static float stbtt_ScaleForPixelHeight(Stbtt_fontinfo info, float height) {
        float fheight = ttSHORT(info.data, info.hhea + 4) - ttSHORT(info.data, info.hhea + 6);
        return height / fheight;
    }

    public static float stbtt_ScaleForMappingEmToPixels(Stbtt_fontinfo info, float pixels) {
        float unitsPerEm = ttUSHORT(info.data, info.head + 18);
        return pixels / unitsPerEm;
    }

//////////////////////////////////////////////////////////////////////////////
//
// antialiasing software rasterizer
//
    public static Stbtt_temp_rect stbtt_GetGlyphBitmapBoxSubpixel(Stbtt_fontinfo font, int glyph, float scale_x, float scale_y, float shift_x, float shift_y) {
        Stbtt_temp_rect rect = RECT;
        if (!stbtt_GetGlyphBox(font, glyph, rect)) {
            // e.g. space character
            rect.x0 = 0;
            rect.y0 = 0;
            rect.x1 = 0;
            rect.y1 = 0;
        } else {
            // move to integral bboxes (treating pixels as little squares, what pixels get touched)?
            int x0 = rect.x0;
            int x1 = rect.x1;
            int y0 = rect.y0;
            int y1 = rect.y1;
            rect.x0 = (int) Math.floor(x0 * scale_x + shift_x);
            rect.y0 = (int) Math.floor(-y1 * scale_y + shift_y);
            rect.x1 = (int) Math.ceil(x1 * scale_x + shift_x);
            rect.y1 = (int) Math.ceil(-y0 * scale_y + shift_y);
        }
        return rect;
    }

    public static Stbtt_temp_rect stbtt_GetGlyphBitmapBox(Stbtt_fontinfo font, int glyph, float scale_x, float scale_y) {
        return stbtt_GetGlyphBitmapBoxSubpixel(font, glyph, scale_x, scale_y, 0, 0);
    }

    public static Stbtt_temp_rect stbtt_GetCodepointBitmapBoxSubpixel(Stbtt_fontinfo font, int codepoint, float scale_x, float scale_y, float shift_x, float shift_y) {
        return stbtt_GetGlyphBitmapBoxSubpixel(font, stbtt_FindGlyphIndex(font, codepoint), scale_x, scale_y, shift_x, shift_y);
    }

    public static Stbtt_temp_rect stbtt_GetCodepointBitmapBox(Stbtt_fontinfo font, int codepoint, float scale_x, float scale_y) {
        return stbtt_GetCodepointBitmapBoxSubpixel(font, codepoint, scale_x, scale_y, 0, 0);
    }

    //////////////////////////////////////////////////////////////////////////////
    //
    //  Rasterizer
    private static Stbtt__active_edge stbtt__new_active(List<Stbtt__edge> e, int eIndex, int off_x, float start_point) {
        Stbtt__active_edge z = new Stbtt__active_edge();
        Stbtt__edge ee = e.get(eIndex);
        float dxdy = (ee.x1 - ee.x0) / (ee.y1 - ee.y0);
        //STBTT_assert(e->y0 <= start_point);
        if (z == null) {
            return null;
        }
        z.fdx = dxdy;
        z.fdy = dxdy != 0.0f ? (1.0f / dxdy) : 0.0f;
        z.fx = ee.x0 + dxdy * (start_point - ee.y0);
        z.fx -= off_x;
        z.direction = ee.invert ? 1.0f : -1.0f;
        z.sy = ee.y0;
        z.ey = ee.y1;
        z.next = null;
        return z;
    }

    // the edge passed in here does not cross the vertical line at x or the vertical line at x+1
    // (i.e. it has already been clipped to those)
    private static void stbtt__handle_clipped_edge(float[] scanline, int scanlineIndex, int x, Stbtt__active_edge e, float x0, float y0, float x1, float y1) {
        if (y0 == y1) {
            return;
        }
        //STBTT_assert(y0 < y1);
        //STBTT_assert(e.sy <= e.ey);
        if (y0 > e.ey) {
            return;
        }
        if (y1 < e.sy) {
            return;
        }
        if (y0 < e.sy) {
            x0 += (x1 - x0) * (e.sy - y0) / (y1 - y0);
            y0 = e.sy;
        }
        if (y1 > e.ey) {
            x1 += (x1 - x0) * (e.ey - y1) / (y1 - y0);
            y1 = e.ey;
        }

        /*
		if (x0 == x)
			STBTT_assert(x1 <= x+1);
		else if (x0 == x+1)
			STBTT_assert(x1 >= x);
		else if (x0 <= x)
			STBTT_assert(x1 <= x);
		else if (x0 >= x+1)
			STBTT_assert(x1 >= x+1);
		else
			STBTT_assert(x1 >= x && x1 <= x+1);
         */
        if (x0 <= x && x1 <= x) {
            scanline[scanlineIndex + x] += e.direction * (y1 - y0);
        } else if (x0 >= x + 1 && x1 >= x + 1) {

        } else {
            //STBTT_assert(x0 >= x && x0 <= x+1 && x1 >= x && x1 <= x+1);
            scanline[scanlineIndex + x] += e.direction * (y1 - y0) * (1 - ((x0 - x) + (x1 - x)) / 2); // coverage = 1 - average x position
        }
    }

    private static void stbtt__fill_active_edges_new(float[] scanline, float[] scanline_fill, int scanline_fillIndex, int len, Stbtt__active_edge e, float y_top) {
        float y_bottom = y_top + 1;

        while (e != null) {
            // brute force every pixel

            //STBTT_assert(e.ey >= y_top);
            if (e.fdx == 0) {
                float x0 = e.fx;
                if (x0 < len) {
                    if (x0 >= 0) {
                        stbtt__handle_clipped_edge(scanline, 0, (int) (x0), e, x0, y_top, x0, y_bottom);
                        stbtt__handle_clipped_edge(scanline_fill, scanline_fillIndex - 1, (int) (x0 + 1), e, x0, y_top, x0, y_bottom);
                    } else {
                        stbtt__handle_clipped_edge(scanline_fill, scanline_fillIndex - 1, 0, e, x0, y_top, x0, y_bottom);
                    }
                }
            } else {
                float x0 = e.fx;
                float dx = e.fdx;
                float xb = x0 + dx;
                float x_top, x_bottom;
                float sy0, sy1;
                float dy = e.fdy;
                //STBTT_assert(e.sy <= y_bottom && e.ey >= y_top);

                // compute endpoints of line segment clipped to this scanline (if the
                // line segment starts on this scanline. x0 is the intersection of the
                // line with y_top, but that may be off the line segment.
                if (e.sy > y_top) {
                    x_top = x0 + dx * (e.sy - y_top);
                    sy0 = e.sy;
                } else {
                    x_top = x0;
                    sy0 = y_top;
                }
                if (e.ey < y_bottom) {
                    x_bottom = x0 + dx * (e.ey - y_top);
                    sy1 = e.ey;
                } else {
                    x_bottom = xb;
                    sy1 = y_bottom;
                }

                if (x_top >= 0 && x_bottom >= 0 && x_top < len && x_bottom < len) {
                    // from here on, we don't have to range check x values

                    if ((int) (x_top) == (int) (x_bottom)) {
                        float height;
                        // simple case, only spans one pixel
                        int x = (int) (x_top);
                        height = sy1 - sy0;
                        //STBTT_assert(x >= 0 && x < len);
                        scanline[x] += e.direction * (1 - ((x_top - x) + (x_bottom - x)) / 2) * height;
                        scanline_fill[scanline_fillIndex + x] += e.direction * height; // everything right of this pixel is filled
                    } else {
                        int x, x1, x2;
                        float y_crossing, step, sign, area;
                        // covers 2+ pixels
                        if (x_top > x_bottom) {
                            // flip scanline vertically; signed area is the same
                            float t;
                            sy0 = y_bottom - (sy0 - y_top);
                            sy1 = y_bottom - (sy1 - y_top);
                            t = sy0;
                            sy0 = sy1;
                            sy1 = t;
                            t = x_bottom;
                            x_bottom = x_top;
                            x_top = t;
                            dx = -dx;
                            dy = -dy;
                            t = x0;
                            x0 = xb;
                            xb = t;
                        }

                        x1 = (int) (x_top);
                        x2 = (int) (x_bottom);
                        // compute intersection with y axis at x1+1
                        y_crossing = (x1 + 1 - x0) * dy + y_top;

                        sign = e.direction;
                        // area of the rectangle covered from y0..y_crossing
                        area = sign * (y_crossing - sy0);
                        // area of the triangle (x_top,y0), (x+1,y0), (x+1,y_crossing)
                        scanline[x1] += area * (1 - ((x_top - x1) + (x1 + 1 - x1)) / 2);

                        step = sign * dy;
                        for (x = x1 + 1; x < x2; x++) {
                            scanline[x] += area + step / 2;
                            area += step;
                        }
                        y_crossing += dy * (x2 - (x1 + 1));

                        //STBTT_assert(Math.abs(area) <= 1.01);
                        scanline[x2] += area + sign * (1 - ((x2 - x2) + (x_bottom - x2)) / 2) * (sy1 - y_crossing);

                        scanline_fill[scanline_fillIndex + x2] += sign * (sy1 - sy0);
                    }
                } else {
                    // if edge goes outside of box we're drawing, we require
                    // clipping logic. since this does not match the intended use
                    // of this library, we use a different, very slow brute
                    // force implementation
                    for (int x = 0; x < len; x++) {
                        // cases:
                        //
                        // there can be up to two intersections with the pixel. any intersection
                        // with left or right edges can be handled by splitting into two (or three)
                        // regions. intersections with top & bottom do not necessitate case-wise logic.
                        //
                        // the old way of doing this found the intersections with the left & right edges,
                        // then used some simple logic to produce up to three segments in sorted order
                        // from top-to-bottom. however, this had a problem: if an x edge was epsilon
                        // across the x border, then the corresponding y position might not be distinct
                        // from the other y segment, and it might ignored as an empty segment. to avoid
                        // that, we need to explicitly produce segments based on x positions.

                        // rename variables to clear pairs
                        float y0 = y_top;
                        float x1 = x;
                        float x2 = x + 1;
                        float x3 = xb;
                        float y3 = y_bottom;
                        float y1, y2;

                        // x = e->x + e->dx * (y-y_top)
                        // (y-y_top) = (x - e->x) / e->dx
                        // y = (x - e->x) / e->dx + y_top
                        y1 = (x - x0) / dx + y_top;
                        y2 = (x + 1 - x0) / dx + y_top;

                        if (x0 < x1 && x3 > x2) {         // three segments descending down-right
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x0, y0, x1, y1);
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x1, y1, x2, y2);
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x2, y2, x3, y3);
                        } else if (x3 < x1 && x0 > x2) {  // three segments descending down-left
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x0, y0, x2, y2);
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x2, y2, x1, y1);
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x1, y1, x3, y3);
                        } else if (x0 < x1 && x3 > x1) {  // two segments across x, down-right
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x0, y0, x1, y1);
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x1, y1, x3, y3);
                        } else if (x3 < x1 && x0 > x1) {  // two segments across x, down-left
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x0, y0, x1, y1);
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x1, y1, x3, y3);
                        } else if (x0 < x2 && x3 > x2) {  // two segments across x+1, down-right
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x0, y0, x2, y2);
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x2, y2, x3, y3);
                        } else if (x3 < x2 && x0 > x2) {  // two segments across x+1, down-left
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x0, y0, x2, y2);
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x2, y2, x3, y3);
                        } else {  // one segment
                            stbtt__handle_clipped_edge(scanline, 0, x, e, x0, y0, x3, y3);
                        }
                    }
                }
            }
            e = e.next;
        }
    }

    static float[] SCANLINE = null;
    // directly AA rasterize edges w/o supersampling
    private static void stbtt__rasterize_sorted_edges(Stbtt__output result, int out_w, int out_h, List<Stbtt__edge> e, int n, int vsubsample, int off_x, int off_y) {
        Stbtt__active_edge active = null;
        int y, j = 0, i;
        float[] scanline, scanline2;
        int scanline2Index = 0;
        int eIndex = 0;

        int req = out_w > 64 ? out_w*2+1 : 129;
        if(SCANLINE == null || SCANLINE.length < req)
            SCANLINE = new float[req*2];

        scanline = SCANLINE;
        /*
        if (result.w > 64) {
            scanline = new float[result.w * 2 + 1];
        } else {
            scanline = new float[129];
        }*/

        scanline2 = scanline;
        scanline2Index = out_w;

        y = off_y;
        e.get(eIndex + n).y0 = (off_y + out_h) + 1;

        while (j < out_h) {
            // find center of pixel for this scanline
            float scan_y_top = y + 0.0f;
            float scan_y_bottom = y + 1.0f;
            Stbtt__active_edge stepValue = active;
            Stbtt__active_edge stepParent = null;

            for (i = 0; i < out_w; i++) {
                scanline[i] = 0;
            }
            for (i = 0; i < out_w + 1; i++) {
                scanline2[scanline2Index + i] = 0;
            }

            // update all active edges;
            // remove all active edges that terminate before the top of this scanline
            while (stepValue != null) {
                Stbtt__active_edge z = stepValue;
                if (z.ey <= scan_y_top) {
                    // delete from list
                    if (stepParent == null) {
                        active = z.next;
                        stepValue = z.next;
                    } else {
                        stepParent.next = z.next;
                        stepValue = z.next;
                    }

                    //STBTT_assert(z.direction != 0);
                    z.direction = 0;
                } else {
                    // advance through list
                    stepParent = stepValue;
                    stepValue = stepValue.next;
                }
            }

            // insert all edges that start before the bottom of this scanline
            while (e.get(eIndex).y0 <= scan_y_bottom) {
                if (e.get(eIndex).y0 != e.get(eIndex).y1) {
                    Stbtt__active_edge z = stbtt__new_active(e, eIndex, off_x, scan_y_top);
                    //STBTT_assert(z.ey >= scan_y_top);
                    // insert at front
                    z.next = active;
                    active = z;
                }
                ++eIndex;
            }

            // now process all active edges
            if (active != null) {
                stbtt__fill_active_edges_new(scanline, scanline2, scanline2Index + 1, out_w, active, scan_y_top);
            }

            {
                float sum = 0;
                for (i = 0; i < out_w; i++) {
                    float k;
                    int m;
                    sum += scanline2[scanline2Index + i];
                    k = scanline[i] + sum;
                    k = (float) (Math.abs(k) * 255.0f + 0.5f);
                    m = (int) (k);
                    if (m > 255) {
                        m = 255;
                    }
                    result.setPixel(i, j, m);
                    /////**** output result.pixels.writeU8(result.pixels_offset + j * result.stride + i, m);
                }
            }
            // advance all the edges
            stepParent = null;
            stepValue = active;
            while (stepValue != null) {
                Stbtt__active_edge z = stepValue;
                z.fx += z.fdx; // advance to position for current scanline
                // advance through list
                stepParent = stepValue;
                stepValue = stepValue.next;
            }

            ++y;
            ++j;
        }
    }

    private static boolean STBTT__COMPARE(Stbtt__edge a, Stbtt__edge b) {
        return a.y0 < b.y0;
    }

    private static void stbtt__sort_edges_ins_sort(List<Stbtt__edge> p, int n) {
        int i, j;
        for (i = 1; i < n; i++) {
            Stbtt__edge t = p.get(i);
            Stbtt__edge a = t;
            j = i;
            while (j > 0) {
                Stbtt__edge b = p.get(j - 1);
                boolean c = STBTT__COMPARE(a, b);
                if (!c) {
                    break;
                }
                p.set(j, p.get(j - 1));
                --j;
            }
            if (i != j) {
                p.set(j, t);
            }
        }
    }

    private static void stbtt__sort_edges_quicksort(List<Stbtt__edge> p, int pIndex, int n) {
        // threshhold for transitioning to insertion sort
        while (n > 12) {
            Stbtt__edge t;
            boolean c01, c12, c;
            int m, i, j;

            // compute median of three
            m = n >> 1;
            c01 = STBTT__COMPARE(p.get(pIndex + 0), p.get(pIndex + m));
            c12 = STBTT__COMPARE(p.get(pIndex + m), p.get(pIndex + n - 1));
            // if 0 >= mid >= end, or 0 < mid < end, then use mid
            if (c01 != c12) {
                // otherwise, we'll need to swap something else to middle
                int z;
                c = STBTT__COMPARE(p.get(pIndex + 0), p.get(pIndex + n - 1));
                // 0>mid && mid<n:  0>n => n; 0<n => 0
                // 0<mid && mid>n:  0>n => 0; 0<n => n
                z = (c == c12) ? 0 : n - 1;
                t = p.get(pIndex + z);
                p.set(pIndex + z, p.get(pIndex + m));
                p.set(pIndex + m, t);
            }
            // now p[m] is the median-of-three
            // swap it to the beginning so it won't move around
            t = p.get(pIndex + 0);
            p.set(pIndex + 0, p.get(pIndex + m));
            p.set(pIndex + m, t);

            // partition loop
            i = 1;
            j = n - 1;
            while (true) {
                // handling of equality is crucial here
                // for sentinels & efficiency with duplicates
                while (true) {
                    if (!STBTT__COMPARE(p.get(pIndex + i), p.get(pIndex + 0))) {
                        break;
                    }
                    ++i;
                }
                while (true) {
                    if (!STBTT__COMPARE(p.get(pIndex + 0), p.get(pIndex + j))) {
                        break;
                    }
                    --j;
                }
                // make sure we haven't crossed
                if (i >= j) {
                    break;
                }
                t = p.get(pIndex + i);
                p.set(pIndex + i, p.get(pIndex + j));
                p.set(pIndex + j, t);

                ++i;
                --j;
            }
            // recurse on smaller side, iterate on larger
            if (j < (n - i)) {
                stbtt__sort_edges_quicksort(p, pIndex, j);
                pIndex += i;
                n = n - i;
            } else {
                stbtt__sort_edges_quicksort(p, pIndex + i, n - i);
                n = j;
            }
        }
    }

    private static void stbtt__sort_edges(List<Stbtt__edge> p, int n) {
        stbtt__sort_edges_quicksort(p, 0, n);
        stbtt__sort_edges_ins_sort(p, n);
    }

    private static void stbtt__rasterize(Stbtt__output result, int out_w, int out_h, List<Stbtt__point> pts, int[] wcount, int windings, float scale_x, float scale_y, float shift_x, float shift_y, int off_x, int off_y, boolean invert) {
        float y_scale_inv = invert ? -scale_y : scale_y;
        List<Stbtt__edge> e;
        int n, i, j, k, m;
        int vsubsample = 1;
        int ptsIndex = 0;

        // vsubsample should divide 255 evenly; otherwise we won't reach full opacity
        // now we have to blow out the windings into explicit edge lists
        n = 0;
        for (i = 0; i < windings; i++) {
            n += wcount[i];
        }

        e = new ArrayList(n + 1); // add an extra one as a sentinel
        for (i = 0; i < n+1; i++) {
            e.add(new Stbtt__edge());
        }
        n = 0;

        m = 0;
        for (i = 0; i < windings; i++) {
            List<Stbtt__point> p = pts;
            int pIndex = ptsIndex + m;
            m += wcount[i];
            j = wcount[i] - 1;
            for (k = 0; k < wcount[i]; k++) {
                int a = k, b = j;
                // skip the edge if horizontal
                if (p.get(pIndex + j).y == p.get(pIndex + k).y) {
                    j = k;
                    continue;
                }
                Stbtt__edge en = e.get(n);
                // add edge from j to k to the list
                en.invert = false;
                if (invert ? p.get(pIndex + j).y > p.get(pIndex + k).y : p.get(pIndex + j).y < p.get(pIndex + k).y) {
                    en.invert = true;
                    a = j;
                    b = k;
                }
                
                Stbtt__point pa = p.get(pIndex + a);
                Stbtt__point pb = p.get(pIndex + b);
                
                en.x0 = pa.x * scale_x + shift_x;
                en.y0 = (pa.y * y_scale_inv + shift_y) * vsubsample;
                en.x1 = pb.x * scale_x + shift_x;
                en.y1 = (pb.y * y_scale_inv + shift_y) * vsubsample;
                ++n;
                j = k;
            }
        }

        // now sort the edges by their highest point (should snap to integer, and then by x)
        //STBTT_sort(e, n, sizeof(e[0]), stbtt__edge_compare);
        stbtt__sort_edges(e, n);

        // now, traverse the scanlines and find the intersections on each scanline, use xor winding rule
        stbtt__rasterize_sorted_edges(result, out_w, out_h, e, n, vsubsample, off_x, off_y);
    }

    private static void stbtt__add_point(List<Stbtt__point> points, int n, float x, float y) {
        if (points == null) {
            return; // during first pass, it's unallocated
        }
        points.get(n).x = x;
        points.get(n).y = y;
    }

    // tesselate until threshhold p is happy... @TODO warped to compensate for non-linear stretching
    private static int stbtt__tesselate_curve(List<Stbtt__point> points, int[] num_points, float x0, float y0, float x1, float y1, float x2, float y2, float objspace_flatness_squared, int n) {
        // midpoint
        float mx = (x0 + 2 * x1 + x2) / 4;
        float my = (y0 + 2 * y1 + y2) / 4;
        // versus directly drawn line
        float dx = (x0 + x2) / 2 - mx;
        float dy = (y0 + y2) / 2 - my;
        if (n > 16) // 65536 segments on one curve better be enough!
        {
            return 1;
        }
        if (dx * dx + dy * dy > objspace_flatness_squared) { // half-pixel error allowed... need to be smaller if AA
            stbtt__tesselate_curve(points, num_points, x0, y0, (x0 + x1) / 2.0f, (y0 + y1) / 2.0f, mx, my, objspace_flatness_squared, n + 1);
            stbtt__tesselate_curve(points, num_points, mx, my, (x1 + x2) / 2.0f, (y1 + y2) / 2.0f, x2, y2, objspace_flatness_squared, n + 1);
        } else {
            stbtt__add_point(points, num_points[0], x2, y2);
            num_points[0]++;
        }
        return 1;
    }

    // returns number of contours
    private static List<Stbtt__point> stbtt_FlattenCurves(List<Stbtt_vertex> vertices, int num_verts, float objspace_flatness, Object[] contour_lengths, int[] num_contours) {
        List<Stbtt__point> points = null;
        int num_points = 0;

        float objspace_flatness_squared = objspace_flatness * objspace_flatness;
        int i, n = 0, start = 0, pass;

        // count how many "moves" there are to get the contour count
        for (i = 0; i < num_verts; i++) {
            if (vertices.get(i).type == STBTT_vmove) {
                ++n;
            }
        }

        num_contours[0] = n;
        if (n == 0) {
            return null;
        }

        int[] icontour_lengths = new int[n];
        contour_lengths[0] = icontour_lengths;

        // make two passes through the points so we don't need to realloc
        for (pass = 0; pass < 2; pass++) {
            float x = 0, y = 0;
            if (pass == 1) {
                points = new ArrayList<Stbtt__point>(num_points);
                if (points == null) {
                    contour_lengths[0] = null;
                    num_contours[0] = 0;
                    return null;
                } else {
                    for (i = 0; i < num_points; i++) {
                        points.add(new Stbtt__point());
                    }
                }
            }
            num_points = 0;
            n = -1;
            for (i = 0; i < num_verts; i++) {
                switch (vertices.get(i).type) {
                    case STBTT_vmove:
                        // start the next contour
                        if (n >= 0) {
                            icontour_lengths[n] = num_points - start;
                        }
                        ++n;
                        start = num_points;

                        x = vertices.get(i).x;
                        y = vertices.get(i).y;
                        stbtt__add_point(points, num_points++, x, y);
                        break;

                    case STBTT_vline:
                        x = vertices.get(i).x;
                        y = vertices.get(i).y;
                        stbtt__add_point(points, num_points++, x, y);
                        break;

                    case STBTT_vcurve:
                        int[] num_points_reference = new int[]{num_points};
                        stbtt__tesselate_curve(points, num_points_reference, x, y,
                                vertices.get(i).cx, vertices.get(i).cy,
                                vertices.get(i).x, vertices.get(i).y,
                                objspace_flatness_squared, 0);
                        num_points = num_points_reference[0];
                        x = vertices.get(i).x;
                        y = vertices.get(i).y;
                        break;
                }
            }
            icontour_lengths[n] = num_points - start;
        }

        return points;
    }

    public static void stbtt_Rasterize(Stbtt__output result, int out_w, int out_h, float flatness_in_pixels, List<Stbtt_vertex> vertices, int num_verts, float scale_x, float scale_y, float shift_x, float shift_y, int x_off, int y_off, boolean invert) {
        float scale = scale_x > scale_y ? scale_y : scale_x;
        int[] winding_count = new int[1];
        Object[] winding_lengths = new Object[1];
        List<Stbtt__point> windings = stbtt_FlattenCurves(vertices, num_verts, flatness_in_pixels / scale, winding_lengths, winding_count);
        if (windings != null) {
            stbtt__rasterize(result, out_w, out_h, windings, (int[]) winding_lengths[0], winding_count[0], scale_x, scale_y, shift_x, shift_y, x_off, y_off, invert);
        }
    }

    /*
	public static function stbtt_GetGlyphBitmapSubpixel(info: Stbtt_fontinfo, scale_x: Float, scale_y: Float, shift_x: Float, shift_y: Float, glyph: Int, region: Stbtt_temp_region): Blob {
		var ix0: Int,iy0: Int,ix1: Int,iy1: Int;
		var gbm: Stbtt__bitmap = new Stbtt__bitmap();
		var vertices: Vector<Stbtt_vertex> = stbtt_GetGlyphShape(info, glyph);
		var num_verts: Int = vertices.length;

		if (scale_x == 0) scale_x = scale_y;
		if (scale_y == 0) {
			if (scale_x == 0) return null;
			scale_y = scale_x;
		}

		var rect = stbtt_GetGlyphBitmapBoxSubpixel(info, glyph, scale_x, scale_y, shift_x, shift_y);
		ix0 = rect.x0;
		iy0 = rect.y0;
		ix1 = rect.x1;
		iy1 = rect.y1;
		
		// now we get the size
		gbm.w = (ix1 - ix0);
		gbm.h = (iy1 - iy0);
		gbm.pixels = null; // in case we error

		region.width  = gbm.w;
		region.height = gbm.h;
		region.xoff   = ix0;
		region.yoff   = iy0;
   
		if (gbm.w != 0 && gbm.h != 0) {
			gbm.pixels = Blob.alloc(gbm.w * gbm.h);
			if (gbm.pixels != null) {
				gbm.stride = gbm.w;

				stbtt_Rasterize(gbm, 0.35, vertices, num_verts, scale_x, scale_y, shift_x, shift_y, ix0, iy0, true);
			}
		}
		return gbm.pixels;
	}

	public static function stbtt_GetGlyphBitmap(info: Stbtt_fontinfo, scale_x: Float, scale_y: Float, glyph: Int, region: Stbtt_temp_region): Blob {
		return stbtt_GetGlyphBitmapSubpixel(info, scale_x, scale_y, 0.0, 0.0, glyph, region);
	}
     */
    public static void stbtt_MakeGlyphBitmapSubpixel(Stbtt_fontinfo info, Stbtt__output output, int out_w, int out_h, float scale_x, float scale_y, float shift_x, float shift_y, int glyph) {
        int ix0 = 0, iy0 = 0;
        List<Stbtt_vertex> vertices = stbtt_GetGlyphShape(info, glyph);
        int num_verts = vertices == null ? 0 : vertices.size();
        //Stbtt__bitmap gbm = new Stbtt__bitmap();

        Stbtt_temp_rect rect = stbtt_GetGlyphBitmapBoxSubpixel(info, glyph, scale_x, scale_y, shift_x, shift_y);
        ix0 = rect.x0;
        iy0 = rect.y0;
        //gbm.pixels = output;
        //gbm.pixels_offset = output_offset;
        //gbm.w = out_w;
        //gbm.h = out_h;
        //gbm.stride = out_stride;

        if (out_w > 0 && out_h > 0) {
            stbtt_Rasterize(output, out_w, out_h, 0.35f, vertices, num_verts, scale_x, scale_y, shift_x, shift_y, ix0, iy0, true);
        }
    }

    /*
	public static function stbtt_MakeGlyphBitmap(info: Stbtt_fontinfo, output: Blob, output_offset: Int, out_w: Int, out_h: Int, out_stride: Int, scale_x: Float, scale_y: Float, glyph: Int): Void {
		stbtt_MakeGlyphBitmapSubpixel(info, output, output_offset, out_w, out_h, out_stride, scale_x, scale_y, 0.0, 0.0, glyph);
	}

	public static function stbtt_GetCodepointBitmapSubpixel(info: Stbtt_fontinfo, scale_x: Float, scale_y: Float, shift_x: Float, shift_y: Float, codepoint: Int, region: Stbtt_temp_region): Blob {
		return stbtt_GetGlyphBitmapSubpixel(info, scale_x, scale_y,shift_x,shift_y, stbtt_FindGlyphIndex(info,codepoint), region);
	}   

	public static function stbtt_MakeCodepointBitmapSubpixel(info: Stbtt_fontinfo, output: Blob, output_offset: Int, out_w: Int, out_h: Int, out_stride: Int, scale_x: Float, scale_y: Float, shift_x: Float, shift_y: Float, codepoint: Int): Void {
		stbtt_MakeGlyphBitmapSubpixel(info, output, output_offset, out_w, out_h, out_stride, scale_x, scale_y, shift_x, shift_y, stbtt_FindGlyphIndex(info,codepoint));
	}

	public static function stbtt_GetCodepointBitmap(info: Stbtt_fontinfo, scale_x: Float, scale_y: Float, codepoint: Int, region: Stbtt_temp_region): Blob {
		return stbtt_GetCodepointBitmapSubpixel(info, scale_x, scale_y, 0.0, 0.0, codepoint, region);
	}   

	public static function stbtt_MakeCodepointBitmap(info: Stbtt_fontinfo, output: Blob, output_offset: Int, out_w: Int, out_h: Int, out_stride: Int, scale_x: Float, scale_y: Float, codepoint: Int): Void {
		stbtt_MakeCodepointBitmapSubpixel(info, output, output_offset, out_w, out_h, out_stride, scale_x, scale_y, 0.0, 0.0, codepoint);
	}*/
}
