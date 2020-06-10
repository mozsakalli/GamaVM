
import digiplay.Camera;
import digiplay.Matrix3D;
import digiplay.Platform;

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
/**
 *
 * @author mustafa
 */
public class Main {
    
    public static void main() {
        Platform.run(new MyGame());
    }
    
    public static void main(String...args) {
        //main();
        Matrix3D id = new Matrix3D();
        Matrix3D cm = new Camera().setupFor2D(960, 640);
        Matrix3D r = new Matrix3D();
        Matrix3D.multiply(cm, id, r);
        r.t(0, 50, 0);
    }



}
