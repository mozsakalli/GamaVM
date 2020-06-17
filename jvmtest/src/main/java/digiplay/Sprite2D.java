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
public class Sprite2D {
    int flags = VISIBLE | LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
    float x, y, scaleX=1, scaleY=1, width,height,rotation, skewX, skewY, alpha = 1, worldAlpha = 1;
    float animX, animY, animScaleX, animScaleY, animRotation, animSkewX, animSkewY, animAlpha;
    float midX, midY;
    float pivotX = .5f, pivotY = .5f;
    int matrixUpdateCount, parentMatrixUpdateCount;
    int depth, numChildren;
    public int color = 0xFFFFFF;
    public int blendMode = 1;
    int frameVersion;
    Sprite2D parent, firstChild, lastChild, next, prev;
    Mat2D localMatrix = new Mat2D();
    Mat2D worldMatrix = new Mat2D();
    String name;
    SpriteAction actions;
    
    static int GLOBAL_FRAME_VERSION;

    
    // Various flags used by Sprite and subclasses
    public final static int VISIBLE = 1 << 0;
    public final static int INTERACTIVE = 1 << 1;
    public final static int LOCAL_MATRIX_DIRTY = 1 << 2;
    public final static int VIEW_MATRIX_DIRTY = 1 << 3;
    public final static int INTERACTIVE_CHILD = 1 << 4;
    public final static int ROT_SKEW_DIRTY = 1 << 5;
    public final static int IN_STAGE = 1 << 6;
    public final static int CONTENT_INVALID = 1 << 7;
    public final static int DISPOSED = 1 << 8;
    public final static int STOP_PROPAGATION = 1 << 9;
    public final static int HIDES_SCENE = 1 << 10;
    public final static int STAY_ON_TOP = 1 << 11;
    public final static int STRETCH_ZERO = 1 << 12;

    public float x() {
        return x + animX;
    }

    public void x(float x) {
        if (x != this.x) {
            this.x = x;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float y() {
        return y + animY;
    }

    public void y(float y) {
        if (y != this.y) {
            this.y = y;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float scaleX() {
        return scaleX + animScaleX;
    }

    public void scaleX(float scaleX) {
        if (scaleX != this.scaleX) {
            this.scaleX = scaleX;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getScaleY() {
        return scaleY + animScaleY;
    }

    public void setScaleY(float scaleY) {
        if (scaleY != this.scaleY) {
            this.scaleY = scaleY;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float rotation() {
        return rotation + animRotation;
    }

    public void rotation(float rotation) {
        if (rotation != this.rotation) {
            this.rotation = rotation;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY;
        }
    }

    public float width() { return width; }
    public void width(float w) {
        if(w != width) {
            width = w;
            midX = w * pivotX;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }
    public float height() { return height; }
    public void height(float w) {
        if(w != height) {
            height = w;
            midY = w * pivotY;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }
    
    public float getSkewX() {
        return skewX + animSkewX;
    }

    public void setSkewX(float skewX) {
        if (skewX != this.skewX) {
            this.skewX = skewX;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY;
        }
    }

    public float getSkewY() {
        return skewY + animSkewY;
    }

    public void setSkewY(float skewY) {
        if (skewY != this.skewY) {
            this.skewY = skewY;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY;
        }
    }

    public float getAnimX() {
        return animX;
    }

    public void setAnimX(float animX) {
        if (animX != this.animX) {
            this.animX = animX;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getAnimY() {
        return animY;
    }

    public void setAnimY(float animY) {
        if (animY != this.animY) {
            this.animY = animY;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getAnimScaleX() {
        return animScaleX;
    }

    public void setAnimScaleX(float animScaleX) {
        if (animScaleX != this.animScaleX) {
            this.animScaleX = animScaleX;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getAnimScaleY() {
        return animScaleY;
    }

    public void setAnimScaleY(float animScaleY) {
        if (animScaleY != this.animScaleY) {
            this.animScaleY = animScaleY;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getAnimRotation() {
        return animRotation;
    }

    public void setAnimRotation(float animRotation) {
        if (animRotation != this.animRotation) {
            this.animRotation = animRotation;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY;
        }
    }

    public float getAlpha() {
        return alpha + animAlpha;
    }

    public void setAlpha(float value) {
        if (value != alpha) {
            alpha = value;
            if ((flags & IN_STAGE) != 0) {
                updateWorldAlpha();
            }
        }
    }

    public float getAnimAlpha() {
        return animAlpha;
    }

    public void setAnimAlpha(float value) {
        if (value != animAlpha) {
            animAlpha = value;
            if ((flags & IN_STAGE) != 0) {
                updateWorldAlpha();
            }
        }
    }

    public float getPivotX() {
        return pivotX;
    }

    public void setPivotX(float value) {
        if (value != this.pivotX) {
            this.pivotX = value;
            midX = value * width;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }
    public float getPivotY() {
        return pivotY;
    }

    public void setPivotY(float value) {
        if (value != this.pivotY) {
            this.pivotY = value;
            midY = value * height;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }
    
    void updateWorldAlpha() {
        if (parent == null) {
            return;
        }
        worldAlpha = parent.worldAlpha * (alpha + animAlpha);
        Sprite2D child = firstChild;
        while (child != null) {
            child.updateWorldAlpha();
            child = child.next;
        }
    }

    public int getFlags() {
        return flags;
    }

    public void setFlags(int flags) {
        this.flags |= flags;
    }
    public void cleatFlags(int mask) {
        this.flags &= ~mask;
    }

    public native Mat2D getLocalMatrix();/* {
        if ((flags & LOCAL_MATRIX_DIRTY) != 0) {
            localMatrix.compose(x + animX, y + animY, scaleX + animScaleX, scaleY + animScaleY, midX, midY, (flags & ROT_SKEW_DIRTY) != 0, rotation + animRotation, skewX + animSkewX, skewY + animSkewY);
            flags &= ~(ROT_SKEW_DIRTY | LOCAL_MATRIX_DIRTY);
            //localMatrix.modifyCounter++;
            matrixUpdateCount++;
        }
        return localMatrix;
    }*/

    public native Mat2D getWorldMatrix(int globalFrameVersion);/* {
        if (frameVersion != GLOBAL_FRAME_VERSION) {
            frameVersion = GLOBAL_FRAME_VERSION;
            int updateCount = matrixUpdateCount;
            Mat2D localMat = getLocalMatrix();
            Sprite2D traParent = parent; //TransformParent != null ? TransformParent : Parent;
            if (traParent == null) {
                return localMatrix;
            }
            Mat2D parentMat = traParent.getWorldMatrix();
            if (traParent.matrixUpdateCount != parentMatrixUpdateCount || updateCount != matrixUpdateCount) {
                Mat2D.multiply(parentMat, localMat, worldMatrix);
                parentMatrixUpdateCount = traParent.matrixUpdateCount;
                //worldMatrix.modifyCounter = localMatrix.modifyCounter;
                //worldMatrix.cacheVersion++;
                matrixUpdateCount++;
            }
        }
        return worldMatrix;
    }*/

    public void dispose() {
    }

    void unlinkChild(Sprite2D child) {
        if (child.prev == null) {
            firstChild = firstChild.next;
        }
        if (child.next == null) {
            lastChild = lastChild.prev;
        }
        if (child.prev != null) {
            child.prev.next = child.next;
        }
        if (child.next != null) {
            child.next.prev = child.prev;
        }
        child.next = child.prev = null;
    }

    void linkChild(Sprite2D child) {
        if (firstChild == null) {
            firstChild = lastChild = child;
            child.prev = child.next = null;
        } else {
            if (child.depth < firstChild.depth) {
                child.next = firstChild;
                firstChild.prev = child;
                firstChild = child;
                firstChild.prev = null;
            } else if (child.depth >= lastChild.depth) {
                lastChild.next = child;
                child.prev = lastChild;
                lastChild = child;
                lastChild.next = null;
            } else {
                Sprite2D target = firstChild;
                while (target != null && target.depth <= child.depth) {
                    target = target.next;
                }
                Sprite2D pre = target.prev;
                if (pre != null) {
                    pre.next = child;
                }
                child.prev = pre;

                child.next = target;
                target.prev = child;
            }
        }
    }

    public void removeChild(Sprite2D child) {
        if (child != null && child.parent == this) {
            unlinkChild(child);;
            numChildren--;
            //child.OnRemoved?.Invoke(this);
            child.dispose();
        }
    }

    public void addChild(Sprite2D child) {
        if (child == null || child.parent == this) {
            return;
        }
        if (child.parent != null) {
            child.parent.unlinkChild(child);
        }

        child.next = null;
        child.parent = this;
        linkChild(child);
        numChildren++;

        if ((flags & IN_STAGE) != 0) {
            child.updateWorldAlpha();
            child.setInStage();
        }

        child.flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        //child.OnAdded?.Invoke();
    }

    static int InvalidationCounter;

    public void markContentInvalid() {
        if ((flags & CONTENT_INVALID) == 0) {
            flags |= CONTENT_INVALID;
            InvalidationCounter++;
        }
    }

    public void invalidateContent() {
    }

    public void invalidateContentIfRequired() {
        if ((flags & CONTENT_INVALID) != 0) {
            invalidateContent();
            flags &= ~CONTENT_INVALID;
        }
    }

    public void init() {
    }

    void setInStage() {
        if ((flags & IN_STAGE) != 0) {
            return;
        }
        flags |= IN_STAGE;
        markContentInvalid();

        Sprite2D ptr = firstChild;
        while (ptr != null) {
            ptr.setInStage();
            ptr = ptr.next;
        }

        if (parent == Stage2D.I) {
            invalidateContent();
        }

        init();
        //OnInit?.Invoke(this);
    }
    
    public void draw() {
    }
    
    public native void drawChildren();/* {
        Sprite2D ptr = firstChild;
        while(ptr != null) {
            if((ptr.flags & VISIBLE) != 0 && ptr.worldAlpha > 0) {
                ptr.draw();
                ptr.drawChildren();
            }
            ptr = ptr.next;
        }
    }*/
    
    public void addAction(SpriteAction action) {
        action.next = actions;
        action.disposed = false;
        action.parent = this;
        action.startTime = -1;
    }
    
    native void updateActions(int time);
}
