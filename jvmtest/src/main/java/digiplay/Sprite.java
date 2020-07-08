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
public class Sprite {

    int flags = VISIBLE | LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY;
    float x, y, z, _x, _y, _z;
    float sx = 1, sy = 1, sz = 1, _sx, _sy, _sz;
    float rx, ry, rz, _rx, _ry, _rz;
    float skx, sky; //skew
    float alpha = 1, _alpha, worldAlpha = 1;
    float px = .5f, py = .5f;
    float width, height, midy, midx;
    float clipX, clipY, clipW, clipH;
    int numChildren, depth, parentVersion, color = 0xFFFFFFFF, depthEnabled, stencilMode, blendMode = 1, textureMode, cullMode;
    Sprite parent, next, prev, firstChild, lastChild;
    Mat4 local = new Mat4(), world = new Mat4(), inverse = new Mat4();
    protected Mesh mesh;
    Texture texture;
    Shader shader;
    Behaviour behaviours;
    int visibleState = -1, batchOrder;

    public Action1<Sprite> onShow, onInit;
    
    // Various flags used by Sprite and subclasses
    public final static int VISIBLE = 1 << 0;
    public final static int PVISIBLE = 1 << 1;
    public final static int INTERACTIVE = 1 << 2;
    public final static int LOCAL_MATRIX_DIRTY = 1 << 3;
    public final static int VIEW_MATRIX_DIRTY = 1 << 4;
    public final static int INTERACTIVE_CHILD = 1 << 5;
    public final static int ROT_SKEW_DIRTY = 1 << 6;
    public final static int IN_STAGE = 1 << 7;
    public final static int CONTENT_INVALID = 1 << 8;
    public final static int DISPOSED = 1 << 9;
    public final static int STOP_PROPAGATION = 1 << 10;
    public final static int HIDES_SCENE = 1 << 11;
    public final static int STAY_ON_TOP = 1 << 12;
    public final static int STRETCH_ZERO = 1 << 13;
    public final static int BATCH_CHILDREN = 1 << 14;
    
    public float getX() {
        return x + _x;
    }

    public void setX(float x) {
        if (x != this.x) {
            this.x = x;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getY() {
        return y + _y;
    }

    public void setY(float y) {
        if (y != this.y) {
            this.y = y;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public void setPosition(float x, float y) {
        setX(x);
        setY(y);
    }

    public float getScaleX() {
        return sx + _sx;
    }

    public void setScaleX(float scaleX) {
        if (scaleX != sx) {
            sx = scaleX;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getScaleY() {
        return sy + _sy;
    }

    public void setScaleY(float scaleY) {
        if (scaleY != sy) {
            sy = scaleY;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getRotation() {
        return rz + _rz;
    }

    public void setRotation(float rotation) {
        if (rotation != rz) {
            rz = rotation;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY;
        }
    }

    public float getRotationY() {
        return ry + _ry;
    }

    public void setRotationY(float rotation) {
        if (rotation != ry) {
            ry = rotation;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY;
        }
    }

    public float getRotationX() {
        return rx + _rx;
    }

    public void setRotationX(float rotation) {
        if (rotation != rx) {
            rx = rotation;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY;
        }
    }

    public float getWidth() {
        return width;
    }

    public void setWidth(float w) {
        if (w != width) {
            width = w;
            midx = w * px;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getHeight() {
        return height;
    }

    public void setHeight(float w) {
        if (w != height) {
            height = w;
            midy = w * py;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getSkewX() {
        return skx;
    }

    public void setSkewX(float skewX) {
        if (skewX != skx) {
            skx = skewX;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY;
        }
    }

    public float getSkewY() {
        return sky;
    }

    public void setSkewY(float skewY) {
        if (skewY != sky) {
            sky = skewY;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY;
        }
    }

    public float getAnimX() {
        return _x;
    }

    public void setAnimX(float animX) {
        if (animX != _x) {
            _x = animX;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getAnimY() {
        return _y;
    }

    public void setAnimY(float animY) {
        if (animY != _y) {
            _y = animY;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getAnimScaleX() {
        return _sx;
    }

    public void setAnimScaleX(float animScaleX) {
        if (animScaleX != _sx) {
            _sx = animScaleX;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getAnimScaleY() {
        return _sy;
    }

    public void setAnimScaleY(float animScaleY) {
        if (animScaleY != _sy) {
            _sy = animScaleY;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getAnimRotation() {
        return _rz;
    }

    public void setAnimRotation(float animRotation) {
        if (animRotation != _rz) {
            _rz = animRotation;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY;
        }
    }

    public float getAlpha() {
        return alpha + _alpha;
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
        return _alpha;
    }

    public void setAnimAlpha(float value) {
        if (value != _alpha) {
            _alpha = value;
            if ((flags & IN_STAGE) != 0) {
                updateWorldAlpha();
            }
        }
    }

    public float getPivotX() {
        return px;
    }

    public void setPivotX(float value) {
        if (value != px) {
            px = value;
            midx = value * width;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    public float getPivotY() {
        return py;
    }

    public void setPivotY(float value) {
        if (value != py) {
            py = value;
            midy = value * height;
            flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }
    
    public int getDepth() { return depth; }
    public void setDepth(int depth) {
        if(depth != this.depth) {
           if(parent != null) {
               parent.unlinkChild(this);
               this.depth = depth;
               parent.linkChild(this);
           } else this.depth = depth;
        }
    }

    public boolean isVisible() {
        return (flags & (VISIBLE | PVISIBLE)) == (VISIBLE | PVISIBLE);
    }

    public void setVisible(boolean v) {
        if (v) {
            if ((flags & VISIBLE) == 0) {
                setVisibility(VISIBLE, false);
            }
        } else {
            if ((flags & VISIBLE) != 0) {
                setVisibility(VISIBLE, true);
            }
        }
    }

    public int getBlendMode() {
        return blendMode;
    }

    public void setBlendMode(int mode) {
        blendMode = mode;
    }

    public void dispose() {
        if ((flags & DISPOSED) != 0) {
            return;
        }

        if (parent != null) {
            parent.removeChild(this);
        }

        //clear behaviours
        Behaviour b = behaviours;
        while (b != null) {
            b.setParent(null);
            b = b.next;
        }

        while (firstChild != null) {
            removeChild(firstChild);
        }

        flags |= DISPOSED;
    }

    void updateWorldAlpha() {
        if (parent == null) {
            return;
        }
        worldAlpha = parent.worldAlpha * (alpha + _alpha);
        Sprite child = firstChild;
        while (child != null) {
            child.updateWorldAlpha();
            child = child.next;
        }
    }

    void unlinkChild(Sprite child) {
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

    void linkChild(Sprite child) {
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
                Sprite target = firstChild;
                while (target != null && target.depth <= child.depth) {
                    target = target.next;
                }
                Sprite pre = target.prev;
                if (pre != null) {
                    pre.next = child;
                }
                child.prev = pre;

                child.next = target;
                target.prev = child;
            }
        }
    }

    public void removeChild(Sprite child) {
        if (child != null && child.parent == this) {
            unlinkChild(child);;
            numChildren--;
            //child.OnRemoved?.Invoke(this);
            child.dispose();
        }
    }

    private void setVisibility(int flags, boolean clear) {
        if (clear) {
            this.flags &= ~flags;
        } else {
            this.flags |= flags;
        }
        int state = (flags & (VISIBLE | PVISIBLE)) == (VISIBLE | PVISIBLE) ? 1 : 0;
        if(state != visibleState) {
           if(state == 1 && onShow != null) onShow.invoke(this);
           visibleState = state; 
        }
        boolean clearChild = state == 0;
        Sprite ptr = firstChild;
        while (ptr != null) {
            ptr.setVisibility(PVISIBLE, clearChild);
            ptr = ptr.next;
        }
    }

    public void addChild(Sprite child) {
        if (child == this) {
            throw new RuntimeException("Can't add self as child");
        }

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
            child.setVisibility(PVISIBLE, (flags & VISIBLE) == 0);
        }

        child.flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
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

        Sprite ptr = firstChild;
        while (ptr != null) {
            ptr.setInStage();
            ptr = ptr.next;
        }

        if (parent == Stage.I) {
            invalidateContent();
        }

        init();
        if(onInit != null) onInit.invoke(this);
        //if (onInit != null) {
        //    onInit.invoke(this);
        //}
    }

    public Mesh getMesh() {
        return mesh;
    }

    public void setMesh(Mesh m) {
        mesh = m;
    }

    public Sprite getFirstChild() {
        return firstChild;
    }

    public Sprite getNext() {
        return next;
    }

    public void addBehaviour(Behaviour b) {
        if (b == null) {
            return;
        }
        Behaviour ptr = behaviours;
        while (ptr != null) {
            if (ptr == b) {
                ptr.setParent(this);
                return;
            }
            ptr = ptr.next;
        }
        b.next = behaviours;
        behaviours = b;
        b.setParent(this);
    }

    public void removeBehaviour(Behaviour b) {
        if (b != null) {
            b.markedForRemoval = true;
            b.isInterrupted = true;
        }
    }

    public void updateBehaviours(float time) {
        /* todo:
        int newState = isParentVisible && ((flags & VISIBLE) != 0) ? 1 : 0;
        if (newState != visibleState) {
            visibleState = newState;
            switch (newState) {
                case 1:
                    if (onShow != null) {
                        onShow.invoke(this);
                    }
                    break;
            }
        }
         */
        Behaviour ptr = behaviours;
        if (ptr != null) {
            Behaviour prev = null;
            while (ptr != null) {
                if (ptr.markedForRemoval) {
                    if (prev != null) {
                        prev.next = ptr.next;
                    }
                    if (ptr == behaviours) {
                        behaviours = behaviours.next;
                    }
                    ptr.setParent(null);
                } else {
                    if (!ptr.markedForRemoval && ptr.parent != null && !ptr.update(time - ptr.startTime)) {
                        ptr.markedForRemoval = true;
                    }
                    prev = ptr;
                }
                ptr = ptr.next;
            }
        }

        Sprite child = firstChild;
        if (child != null) {
            while (child != null) {
                child.updateBehaviours(time);
                child = child.next;
            }
        }
    }
}
