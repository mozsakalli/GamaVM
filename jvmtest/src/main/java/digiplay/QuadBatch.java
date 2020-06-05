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

/**
 *
 * @author mustafa
 */
public class QuadBatch {
    
    long vbo, ibo;
    float[] vertices;
    int vertexPtr, indexPtr;
    
    Camera camera = new Camera();
    Matrix3D projectionMatrix = new Matrix3D();
    Matrix3D combinedMatrix = new Matrix3D();
    Matrix3D cameraMatrix = new Matrix3D();
    boolean projectionDirty;
    
    final static int FLOAT_PER_VERTEX = 4;
    final static Shader2D DEFAULT_SHADER = new Shader2D();
    
    public QuadBatch(int capacity) {
        vertices = new float[capacity * 4 * FLOAT_PER_VERTEX];
        short[] indices = new short[capacity * 6];
        for(int i=0; i<capacity; i++) {
            indices[i * 6] = (short)(i * 4);
            indices[i * 6 + 1] = (short)(i * 4 + 1);
            indices[i * 6 + 2] = (short)(i * 4 + 2);

            indices[i * 6 + 3] = (short)(i * 4);
            indices[i * 6 + 4] = (short)(i * 4 + 2);
            indices[i * 6 + 5] = (short)(i * 4 + 3);
        }
        ibo = GL.createIndexBuffer();
        GL.bufferIndexData(ibo, indices, 0, indices.length);
        
        vbo = GL.createVertexBuffer();
    }
    
    public void begin() {
        vertexPtr = 0;
        cameraMatrix.identity();
        projectionDirty = true;
        
        int w = Digiplay.graphics.getScreenWidth();
        int h = Digiplay.graphics.getScreenHeight();
        GL.viewport(0, 0, w, h);
        GL.clearColor(0, 0, 0, 1);
        GL.clear(GL.COLOR_BUFFER_BIT);
        projectionMatrix = camera.setupFor2D(w, h);
        projectionDirty = true;
        DEFAULT_SHADER.bind();
    }
    
    public void flush() {
        if(indexPtr > 0) {
            if(projectionDirty) {
                Matrix3D.multiply(projectionMatrix, cameraMatrix, combinedMatrix);
                DEFAULT_SHADER.setProjection(combinedMatrix);
                projectionDirty = false;
            }
            GL.bufferVertexData(vbo, vertices, 0, vertexPtr);
            GL.bindVertexBuffer(vbo);
            GL.enableVertexAttribArray(DEFAULT_SHADER.attrPos);
            GL.vertexAttribPointer(DEFAULT_SHADER.attrPos, 3, GL.FLOAT, false, FLOAT_PER_VERTEX * 4, 0);
            GL.enableVertexAttribArray(DEFAULT_SHADER.attrColor);
            GL.vertexAttribPointer(DEFAULT_SHADER.attrColor, 4, GL.UNSIGNED_BYTE, true, FLOAT_PER_VERTEX * 4, 12);
            GL.bindIndexBuffer(ibo);
            
            GL.drawElements(GL.TRIANGLES, indexPtr, 0);
            indexPtr = vertexPtr = 0;
        }
    }
    
    public void quad(float x, float y, float width, float height, int color) {
        float x2 = x + width;
        float y2 = y + height;
        int ptr = vertexPtr;
        float fcolor = Float.intBitsToFloat(color);
        vertices[ptr++] = x;
        vertices[ptr++] = y;
        vertices[ptr++] = 0;
        vertices[ptr++] = fcolor;

        vertices[ptr++] = x2;
        vertices[ptr++] = y;
        vertices[ptr++] = 0;
        vertices[ptr++] = fcolor;

        vertices[ptr++] = x2;
        vertices[ptr++] = y2;
        vertices[ptr++] = 0;
        vertices[ptr++] = fcolor;

        vertices[ptr++] = x;
        vertices[ptr++] = y2;
        vertices[ptr++] = 0;
        vertices[ptr++] = fcolor;
        
        vertexPtr = ptr;
        indexPtr += 6;
    }
    
}
