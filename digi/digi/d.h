//
// Created by mustafa on 2020-06-18.
//

#ifndef MY_APPLICATION_D_H
#define MY_APPLICATION_D_H

typedef unsigned short CHAR;

class Object {
public:
    virtual void ToString() = 0;
};

template<typename Element>
class Array : public Object {
int _Size;
Element *_Data;
public:
    Array(int size) {
        _Data = new Element[_Size = size];
    }
    ~Array() {
        delete [] _Data;
    }
    int Size() { return _Size; }
    Element const& operator[](int index) const {
        if(index < 0 || index >= _Size)
            throw "ArrayBounds";
        return _Data[index];
    }
    Element *Data() { return _Data; }
};

class String : public Object {
Array<CHAR> *_Chars;
int _Offset, _Length;
public:
    String(wchar_t *chars) {
        if(!chars) throw "Null";
        int len = (int)wcslen(chars);
        _Chars = new Array<CHAR>(len);
        memcpy(_Chars->Data(), chars, sizeof(CHAR) * len);
        _Offset = 0;
        _Length = 0;
    }
    ~String() {
        if(_Chars) delete _Chars;
    }
};

class Sprite2D {
public:

};
#endif //MY_APPLICATION_D_H
