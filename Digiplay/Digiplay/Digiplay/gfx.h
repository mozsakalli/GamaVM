//
//  gfx.hpp
//  Digiplay
//
//  Created by Mustafa Ozsakalli on 4.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#ifndef gfx_hpp
#define gfx_hpp

#include <stdio.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

class ShaderProgram {
public:
    virtual void activate()=0;
    virtual void deactivate()=0;
};

class ShaderTexture {
public:
    
};
class ShaderBuffer {
public:
};
class ShaderEngine {
public:
    static ShaderEngine *Engine;
    virtual ShaderTexture *createTexture()=0;
    virtual ShaderProgram *createShaderProgram(const char *vertex, const char *fragment);
};

class OGL2ShaderProgram : public ShaderProgram {
public:
    GLuint vertexShader, fragmentShader, program;
    
};

#endif /* gfx_hpp */
