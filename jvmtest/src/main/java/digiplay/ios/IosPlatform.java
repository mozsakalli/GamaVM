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

package digiplay.ios;

import digiplay.Digiplay;
import digiplay.Files;
import digiplay.Game;
import digiplay.Graphics;
import digiplay.Platform;

/**
 *
 * @author mustafa
 */
public class IosPlatform extends Platform {

    IosGraphics graphics;
    
    private IosPlatform(Game game) {
        this.game = game;
        Digiplay.graphics = this.graphics = new IosGraphics();
        digiplay.Digiplay.platform = this;
    }
    
    public static void run(Game game) {
        IosPlatform p = new IosPlatform(game);
        p.run();
    }
    
    private native void run();
    
    @Override
    public Graphics getGraphics() {
        return graphics;
    }

    @Override
    public Files getFiles() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
