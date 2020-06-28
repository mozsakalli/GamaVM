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

package digiplay;

import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author mustafa
 */
public class Texture2D {    
    public int width,height,drawWidth,drawHeight,drawX,drawY;
    public float u1,v1,u2,v2,u3,v3,u4,v4;
    public Texture texture;
    
    static Map<String, Texture2D> cache = new HashMap();
    
    public static Texture2D get(String name) {
        if(name == null || name.isEmpty()) return null;
        Texture2D result = cache.get(name);
        if(result == null) {
            byte[] bytes = Platform.readAsset(name+".png");
            if(bytes == null) bytes = Platform.readAsset(name+".jpg");
            if(bytes == null) return null;
            Texture tex = new Texture();
            tex.upload(bytes);
            
            result = new Texture2D();
            result.drawWidth = result.width = tex.width;
            result.drawHeight = result.height = tex.height;
            result.texture = tex;
            result.u1 = result.v1 = 0;
            result.u2 = 1; result.v2 = 0;
            result.u3 = 1; result.v3 = 1;
            result.u4 = 0; result.v4 = 1;
            cache.put(name, result);
        }
        return result;
    }
    
    public static Texture2D create(GLTexture gt) {
        return null;
    }
}
