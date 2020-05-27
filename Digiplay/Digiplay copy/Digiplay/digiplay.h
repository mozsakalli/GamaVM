//
//  digiplay.h
//  Digiplay
//
//  Created by mustafa on 20.04.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#ifndef digiplay_h
#define digiplay_h

#include <stdio.h>
#include "geom.h"

namespace digiplay {

typedef void (*Action)(void*);

template <class T> class Bag {
public:
    T* Items;
    int Count, Capacity;
    
    Bag() {
        Items = new T[Capacity = 16];
        Count = 0;
    }
    void Add(T item) {
        if(Count == Capacity) {
            T* tmp = new T[Capacity * 2];
            memmove(tmp, Items, Capacity * sizeof(T*));
            delete Items;
            Items = tmp;
        }
        Items[Count++] = item;
    }
    
    void Reset() {
        Count = 0;
    }
    
    T* Get(int index) {
        return index>=0 && index<Count ? Items[index] : nullptr;
    }
};

class Sprite2D {
public:
    const int VISIBLE            = (1 << 0);
    const int INTERACTIVE        = (1 << 1);
    const int LOCAL_MATRIX_DIRTY = (1 << 2);
    const int VIEW_MATRIX_DIRTY  = (1 << 3);
    const int INTERACTIVE_CHILD  = (1 << 4);
    const int ROT_SKEW_DIRTY     = (1 << 5);
    const int IN_STAGE           = (1 << 6);
    const int CONTENT_INVALID    = (1 << 7);
    const int RENDERABLE         = (1 << 8);
    const int DISPOSED           = (1 << 9);
    const int STOP_PROPAGATION   = (1 << 10);
    const int HIDES_SCENE        = (1 << 11);
    const int STAY_ON_TOP        = (1 << 12);
    const int STRETCH_ZERO       = (1 << 13);

    int FrameVersion, MatrixUpdateCount, ParentMatrixUpdateCount, _Depth;
    float _X,_Y,_AnimX,_AnimY,_ScaleX,_ScaleY,_AnimScaleX,_AnimScaleY,
    _Rotation,_AnimRotation,_SkewX,_SkewY,_AnimSkewX,_AnimSkewY, _PivotX, _PivotY,
    _Alpha, _AnimAlpha, _WorldAlpha;
    #define DEFPROP(name,extra) \
    float Get##name() { return _##name + _Anim##name; } \
    void Set##name(float value) { \
    if(value != _##name) { \
    _##name = value; \
            Flags |= extra; \
            FrameVersion = 0; \
        }\
    }

    DEFPROP(X,LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY)
    DEFPROP(Y,LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY)
    DEFPROP(ScaleX,LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY)
    DEFPROP(ScaleY,LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY)
    DEFPROP(Rotation,LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY)
    DEFPROP(SkewX,LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY)
    DEFPROP(SkewY,LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY | ROT_SKEW_DIRTY)
    float GetPivotX() { return _PivotX; }
    void SetPivotX(float value) {
        if(value != _PivotX) {
            _PivotX = value;
            Flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }
    float GetPivotY() { return _PivotY; }
    void SetPivotY(float value) {
        if(value != _PivotY) {
            _PivotY = value;
            Flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        }
    }

    float GetAlpha() { return _Alpha + _AnimAlpha; }
    void SetAlpha(float value) {
        if(value != _Alpha) {
            _Alpha = value;
            if((Flags & IN_STAGE) != 0) UpdateWorldAlpha();
        }
    }
    float GetAnimAlpha() { return _AnimAlpha; }
    void SetAnimAlpha(float value) {
        if(value != _AnimAlpha) {
            _AnimAlpha = value;
            if((Flags & IN_STAGE) != 0) UpdateWorldAlpha();
        }
    }

    int Flags, _NumChildren;
    Matrix2D *localMatrix,*worldMatrix,*viewMatrix;
    Sprite2D *_Parent, *_TransformParent, *Next, *Prev, *FirstChild, *LastChild;
    
    static int GlobalFrameVersion;
    
    Sprite2D() {
        AllocMatrices();
        _X = _Y = _AnimX = _AnimY = _Rotation = _AnimRotation = 0;
        FrameVersion = MatrixUpdateCount = ParentMatrixUpdateCount = _NumChildren =
        _AnimAlpha = 0;
        _Alpha = _WorldAlpha = 1;
        Flags = _Depth = 0;
        _Parent = _TransformParent = Next = Prev = FirstChild = LastChild = nullptr;
        _PivotX = _PivotY = .5f;
    }
    
    ~Sprite2D() {
        if(localMatrix) localMatrix->Release();
        if(worldMatrix) worldMatrix->Release();
        if(viewMatrix) viewMatrix->Release();
        Dispose();
    }
    
    void SetFlags(int flags) { Flags |= Flags; }
    bool HasFlags(int flags) { return (Flags & flags) != 0; }
    void ClearFlags(int flags) { Flags &= ~flags; }
    
    virtual void Dispose() {}
    
    virtual void AllocMatrices() {
        localMatrix = Matrix2D::Alloc();
        worldMatrix = Matrix2D::Alloc();
        viewMatrix = nullptr;
    }
    
    virtual float GetNaturalWidth() { return 0; }
    virtual float GetNaturalHeight() { return 0; }
    virtual Matrix2D* GetLocalMatrix()
    {
        if ((Flags & LOCAL_MATRIX_DIRTY) != 0)
        {
            Flags &= ~LOCAL_MATRIX_DIRTY;

            if ((Flags & ROT_SKEW_DIRTY) != 0)
            {
                localMatrix->UpdateRotAndSkew(_Rotation+_AnimRotation, _SkewX+_AnimSkewX, _SkewY+_AnimSkewY);
                Flags &= ~ROT_SKEW_DIRTY;
            }
            localMatrix->Compose(_X+_AnimX, _Y+_AnimY, _ScaleX+_AnimScaleX, _ScaleY+_AnimScaleY, _PivotX * GetNaturalWidth(), _PivotY * GetNaturalHeight());
            localMatrix->ModifyCounter++;
            MatrixUpdateCount++;
        }
        return localMatrix;
    }

    virtual Matrix2D* GetWorldMatrix()
    {
        if (FrameVersion != GlobalFrameVersion)
        {
            FrameVersion = GlobalFrameVersion;
            Matrix2D *localMatrix = GetLocalMatrix();
            Sprite2D* traParent = _TransformParent != nullptr ? _TransformParent : _Parent;
            if (!traParent) return localMatrix;
            Matrix2D* parentMatrix = traParent->GetWorldMatrix();
            if (traParent->MatrixUpdateCount != ParentMatrixUpdateCount || localMatrix->ModifyCounter != worldMatrix->ModifyCounter)
            {
                Matrix2D::Multiply(parentMatrix, localMatrix, worldMatrix);
                ParentMatrixUpdateCount = traParent->MatrixUpdateCount;
                worldMatrix->ModifyCounter = localMatrix->ModifyCounter;
                worldMatrix->CacheVersion++;
                MatrixUpdateCount++;
            }
        }
        return worldMatrix;
    }
    
    void UnlinkChild(Sprite2D* child)
    {
        if (!child->Prev) FirstChild = FirstChild->Next;
        if (!child->Next) LastChild = LastChild->Prev;
        if (child->Prev) child->Prev->Next = child->Next;
        if (child->Next) child->Next->Prev = child->Prev;
        child->Next = child->Prev = child->_Parent = nullptr;
        child->_Parent = nullptr;
        _NumChildren--;
    }

    void LinkChild(Sprite2D* child)
    {
        if (!FirstChild)
        {
            FirstChild = LastChild = child;
            child->Prev = child->Next = nullptr;
        }
        else
        {
            if (child->_Depth < FirstChild->_Depth)
            {
                child->Next = FirstChild;
                FirstChild->Prev = child;
                FirstChild = child;
                FirstChild->Prev = nullptr;
            }
            else if (child->_Depth >= LastChild->_Depth)
            {
                LastChild->Next = child;
                child->Prev = LastChild;
                LastChild = child;
                LastChild->Next = nullptr;
            }
            else
            {
                Sprite2D* target = FirstChild;
                while (target && target->_Depth <= child->_Depth)
                {
                    target = target->Next;
                }
                Sprite2D* pre = target->Prev;
                if (pre) pre->Next = child;
                child->Prev = pre;

                child->Next = target;
                target->Prev = child;
            }
        }
        child->_Parent = this;
        _NumChildren++;
    }
    
    virtual void RemoveChild(Sprite2D* child, bool dispose = true)
    {
        if (child && child->_Parent == this)
        {
#if DEBUG
            //if (child is debug.DebugConsole) return;
#endif
            UnlinkChild(child);
            if(dispose) delete child;
            //child.OnRemoved?.Invoke(this);
            //child.Dispose();
        }
    }

    void RemoveSelf()
    {
        if (_Parent) _Parent->RemoveChild(this);
    }

    virtual void AddChild(Sprite2D* child)
    {
        if (!child || child->_Parent == this) return;
        if (child->_Parent) child->_Parent->UnlinkChild(child);

        child->Next = child->Prev = nullptr;
        child->_Parent = this;
        LinkChild(child);

        if ((Flags & IN_STAGE) != 0)
        {
            child->UpdateWorldAlpha();
            child->SetInStage();
        }

        child->Flags |= LOCAL_MATRIX_DIRTY | VIEW_MATRIX_DIRTY;
        //child.OnAdded?.Invoke();
    }

    void UpdateWorldAlpha()
    {
        if (!_Parent) return;
        _WorldAlpha = _Parent->_WorldAlpha * (_Alpha + _AnimAlpha);
        if(_WorldAlpha < 0) _WorldAlpha = 0; else if(_WorldAlpha > 1) _WorldAlpha = 1;
        Sprite2D* child = FirstChild;
        while (child)
        {
            child->UpdateWorldAlpha();
            child = child->Next;
        }
    }
    
    void SetInStage();
    
    static int InvalidationCounter;
    virtual void MarkContentInvalid()
    {
        if ((Flags & CONTENT_INVALID) == 0)
        {
            Flags |= CONTENT_INVALID;
            InvalidationCounter++;
        }
    }

    virtual void InvalidateContent() { }
    void InvalidateContentIfRequired()
    {
        if((Flags & CONTENT_INVALID) != 0)
        {
            InvalidateContent();
            Flags &= ~CONTENT_INVALID;
        }
    }

    virtual void Init() {}
    
    static Bag<Sprite2D*> IterateBag;
    static void IterateChildren(Sprite2D* root, Action action);
};


class Stage2D : public Sprite2D {
public:
    static Stage2D* I;
    Point2D DesignSize;
    float ScaleFactor;
    
    Stage2D(Point2D DesignSize) {
        this->DesignSize = DesignSize;
        SetFlags(INTERACTIVE | INTERACTIVE_CHILD | IN_STAGE);
        Resize();
    }
    
    static void Setup(Point2D size) {
        if(!Stage2D::I) {
            Stage2D::I = new Stage2D(size);
        }
    }
    
    void Resize() {
        float ww = DesignSize.X;
        float hh = DesignSize.Y;
        float ratio = hh / ww;
        
        float screenWidth = 1025;
        float screenHeight = 768;
        
        float w = screenWidth;
        float h = (int)(w * ratio);
        if (h - 2 > screenHeight)
        {
            h = screenHeight;
            w = (int)(h / ratio);
            ScaleFactor = h / hh;
        }
        else
            ScaleFactor = w / ww;
        w = ScaleFactor * DesignSize.X;
        h = ScaleFactor * DesignSize.Y;

        SetScaleX(w / ww);
        SetScaleY(h / hh);

        SetX((screenWidth - w) / 2);
        SetY((screenHeight - h) / 2);

        SetPivotX(0);
        SetPivotY(0);
    }
    
    virtual void AddChild(Sprite2D* child) {
        if(child && !child->_Parent) {
            Sprite2D::AddChild(child);
            child->SetInStage();
        }
    }
    
    void Update() {
        bool invalidated = false;
        if (InvalidationCounter != 0)
        {
            InvalidationCounter = 0;
            Sprite2D::IterateChildren(this, [](void* p) { ((Sprite2D*)p)->InvalidateContentIfRequired(); });
            if (InvalidationCounter != 0)
                Sprite2D::IterateChildren(this, [](void* p) { ((Sprite2D*)p)->InvalidateContentIfRequired(); });
            invalidated = true;
        }
        /* todo
        if (_invokeLaterCount > 0)
        {
            for (int i = 0; i < _invokeLaterCount; i++)
            {
                _invokeLaterList[i].Invoke();
                _invokeLaterList[i] = null;
            }
            _invokeLaterCount = 0;
        }
        
        var currentTime = Platform.GetTimer();
        UpdateBehaviours(currentTime, true);
        */
        
        if (InvalidationCounter != 0)
        {
            InvalidationCounter = 0;
            Sprite2D::IterateChildren(this, [](void* p) { ((Sprite2D*)p)->InvalidateContentIfRequired(); });
            if (InvalidationCounter != 0)
                Sprite2D::IterateChildren(this, [](void* p) { ((Sprite2D*)p)->InvalidateContentIfRequired(); });
            invalidated = true;
        }
        /* todo
        if(invalidated && Scene2D.currentScene != null && !Scene2D.currentScene._invalidationCalled)
        {
            Scene2D.currentScene._invalidationCalled = true;
            Scene2D.currentScene.InitCompleted();
        }
         */
    }
    
    void Render() {
        
    }
    
};


}
#endif /* digiplay_h */
