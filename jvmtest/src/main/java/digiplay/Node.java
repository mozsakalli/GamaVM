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
public class Node {
    public final static int VISIBLE         = 1;
    public final static int LOCAL_DIRTY     = 2;
    public final static int VIEW_DIRTY      = 4;
    public final static int ROT_DIRTY       = 8;
    public final static int IN_STAGE        = 16;
    public final static int CONTENT_INVALID = 32;
    
    int flags = VISIBLE | LOCAL_DIRTY | VIEW_DIRTY | ROT_DIRTY;
    float x,y,z, _x,_y,_z;
    float sx=1,sy=1,sz=1, _sx,_sy,_sz;
    float rx,ry,rz, _rx,_ry,_rz;
    float skx, sky; //skew
    float alpha=1,_alpha,worldAlpha=1;
    float px=.5f,py=.5f;
    float width,height, midy, midx;
    int numChildren, depth, parentVersion, color;
    Node parent, next, prev, firstChild, lastChild;
    Mat4 local=new Mat4(),world=new Mat4(), inverse = new Mat4();
    Mesh mesh;
    int material;
    Texture texture;
   
     void updateWorldAlpha() {
        if (parent == null) {
            return;
        }
        worldAlpha = parent.worldAlpha * (alpha + _alpha);
        Node child = firstChild;
        while (child != null) {
            child.updateWorldAlpha();
            child = child.next;
        }
    }

    void dispose(){}
    
    void unlinkChild(Node child) {
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

    void linkChild(Node child) {
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
                Node target = firstChild;
                while (target != null && target.depth <= child.depth) {
                    target = target.next;
                }
                Node pre = target.prev;
                if (pre != null) {
                    pre.next = child;
                }
                child.prev = pre;

                child.next = target;
                target.prev = child;
            }
        }
    }

    public void removeChild(Node child) {
        if (child != null && child.parent == this) {
            unlinkChild(child);
            numChildren--;
            //child.OnRemoved?.Invoke(this);
            child.dispose();
        }
    }

    public void addChild(Node child) {
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

        child.flags |= LOCAL_DIRTY | VIEW_DIRTY;
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
    
    void setInStage() {
        if ((flags & IN_STAGE) != 0) {
            return;
        }
        flags |= IN_STAGE;
        markContentInvalid();

        Node ptr = firstChild;
        while (ptr != null) {
            ptr.setInStage();
            ptr = ptr.next;
        }

        //if (parent == Stage2D.I) {
        //    invalidateContent();
        //}

        //init();
        //if (onInit != null) {
        //    onInit.invoke(this);
        //}
    }  
    
    public native Mat4 getLocalMatrix();
    public native Mat4 getWorldMatrix();
    
    
}
