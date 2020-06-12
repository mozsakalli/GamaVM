//
//  vm.hpp
//  Digiplay
//
//  Created by mustafa on 6.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#ifndef vm_h
#define vm_h

#include <stdio.h>

typedef union VMValue {
    long long longVal;
    void* ptrVal;
    char byteVal;
    short shortVal;
    int intVal;
    float floatVal;
    double doubleVal;
} VMValue;

#define VM_MAX_LOCAL    32
typedef struct VMFrame {
    VMValue locals[VM_MAX_LOCAL];
    VMValue args[VM_MAX_LOCAL];
} VMFrame;

static VMFrame VMF;

typedef struct VM {
    VMFrame frames[1024];
    int fp;
} VM;

typedef struct VMObject {

} VMObject;

class VMField {

};


class VMClass {

};


class VMExpr {
public:
    virtual int asInt() { return 0; }
    virtual float asFloat() { return 0; }
    virtual bool asBool() { return false; }
    virtual long long asLong() { return 0; }
    virtual double asDouble() { return 0; }
    virtual VMExpr* eval() { return this; }
};

template <class T> class VMPrimitiveExpr : public VMExpr {
public:
    T value;
    VMPrimitiveExpr(T value) : value(value) {}
    inline int asInt() override { return value; }
    inline float asFloat() override { return value; }
    inline bool asBool() override { return value != 0; }
    inline long long asLong() override { return value; }
    inline double asDouble() override { return value; }
};

class VMIntExpr : public VMPrimitiveExpr<int> {};
class VMFloatExpr : public VMPrimitiveExpr<float> {};
class VMLongExpr : public VMPrimitiveExpr<long long> {};
class VMDoubleExpr : public VMPrimitiveExpr<double> {};

class VMEqExpr : public VMExpr {
public:
    VMExpr *left, *right;
    bool asBool() override { return left->asDouble() == right->asDouble(); }
};
class VMLtExpr : public VMExpr {
public:
    VMLtExpr(VMExpr *left, VMExpr *right) : left(left), right(right) {}
    VMExpr *left, *right;
    inline bool asBool() override { return left->asDouble() < right->asDouble(); }
};
class VMLeExpr : public VMExpr {
public:
    VMExpr *left, *right;
    bool asBool() override { return left->asDouble() <= right->asDouble(); }
};
class VMGtExpr : public VMExpr {
public:
    VMExpr *left, *right;
    bool asBool() override { return left->asDouble() > right->asDouble(); }
};
class VMGeExpr : public VMExpr {
public:
    VMExpr *left, *right;
    bool asBool() override { return left->asDouble() >= right->asDouble(); }
};
class VMNeqExpr : public VMExpr {
public:
    VMExpr *left, *right;
    bool asBool() override { return left->asDouble() != right->asDouble(); }
};
class VMVarExpr : public VMExpr {
public:
    VMVarExpr(int index) : index(index) {}
    int index;
    int asInt() override { return VMF.locals[index].intVal; }
    double asDouble() override { return VMF.locals[index].intVal; }
};
class VMSetVarExpr : public VMExpr {
public:
    VMSetVarExpr(int index, VMExpr* value) : index(index), value(value) {}
    int index;
    VMExpr* value;
    inline int asInt() override {
        return VMF.locals[index].intVal = value->asInt();
    }
};
class VMAddExpr : public VMExpr {
public:
    VMAddExpr(VMExpr *left, VMExpr *right) : left(left), right(right) {}
    VMExpr *left, *right;
    inline int asInt() override {
        return left->asInt() + right->asInt();
    }
};

class VMForLoop : public VMExpr {
public:
    VMExpr *init, *condition, *increment, *body;

    int asInt() override {
        init->asInt();
        bool run = condition->asBool();
        while(run) {
            body->asInt();
            increment->asInt();
            run = condition->asBool();
        }
        return 0;
    }
};
/*
class VMIntExpr : public VMExpr {
public:
    VMIntExpr(int value):value(value) {}
    int value;

    int asInt() override { return value; }
    float asFloat() override { return value; }
    bool asBool() override { return value != 0; }
};

class VMFloatExpr : public VMExpr {
public:
    VMFloatExpr(float value):value(value) {}
    float value;

    int asInt() override { return value; }
    float asFloat() override { return value; }
    bool asBool() override { return value != 0; }
};

class VMLtExpr : public VMExpr {
public:
    VMExpr *left, *right;
    bool asBool() override { return left->asFloat() < right->asFloat(); }
};

class VMCallExpr : public VMExpr {
public:

};

class VMObject : public VMExpr {
public:
    void* value;
};

class VMArray : public VMExpr {
public:

};
 */
#endif /* vm_hpp */
