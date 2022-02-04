#include "OpenGL.hpp"

#include <windows.h>

#pragma comment (lib, "opengl32.lib")

#define LOAD_GL_FUNCTION(type, function) function = (type)getGLFunction(#function)

static HMODULE glLibrary;

static void* getGLFunction(const char* name) {
    
    void* ptr = (void*)wglGetProcAddress(name);
    if (ptr == 0) {
        ptr = (void*)GetProcAddress(glLibrary, name);
    }

    return ptr;

}

namespace sdf {

    GLClearPtr                      glClear                     = nullptr;
    GLClearColorPtr                 glClearColor                = nullptr;
    GLViewportPtr                   glViewport                  = nullptr;
    GLGetStringPtr                  glGetString                 = nullptr;
    GLGenBuffersPtr                 glGenBuffers                = nullptr;
    GLDeleteBuffersPtr              glDeleteBuffers             = nullptr;
    GLBindBufferPtr                 glBindBuffer                = nullptr;
    GLBufferDataPtr                 glBufferData                = nullptr;
    GLBufferSubDataPtr              glBufferSubData             = nullptr;
    GLGenVertexArraysPtr            glGenVertexArrays           = nullptr;
    GLDeleteVertexArraysPtr         glDeleteVertexArrays        = nullptr;
    GLBindVertexArrayPtr            glBindVertexArray           = nullptr;
    GLDrawElementsPtr               glDrawElements              = nullptr;
    GLDrawArraysPtr                 glDrawArrays                = nullptr;
    GLVertexAttribPointerPtr        glVertexAttribPointer       = nullptr;
    GLEnableVertexAttribArrayPtr    glEnableVertexAttribArray   = nullptr;
    GLCreateProgramPtr              glCreateProgram             = nullptr;
    GLDeleteProgramPtr              glDeleteProgram             = nullptr;
    GLLinkProgramPtr                glLinkProgram               = nullptr;
    GLUseProgramPtr                 glUseProgram                = nullptr;
    GLCreateShaderPtr               glCreateShader              = nullptr;
    GLShaderSourcePtr               glShaderSource              = nullptr;
    GLCompileShaderPtr              glCompileShader             = nullptr;
    GLGetShaderivPtr                glGetShaderiv               = nullptr;
    GLGetShaderInfoLogPtr           glGetShaderInfoLog          = nullptr;
    GLAttachShaderPtr               glAttachShader              = nullptr;
    GLDeleteShaderPtr               glDeleteShader              = nullptr;
    GLGetUniformLocationPtr         glGetUniformLocation        = nullptr;
    GLUniform1fPtr                  glUniform1f                 = nullptr;
    GLUniform1iPtr                  glUniform1i                 = nullptr;
    GLUniform2fvPtr                 glUniform2fv                = nullptr;
    GLUniform3fvPtr                 glUniform3fv                = nullptr;
    GLUniform4fvPtr                 glUniform4fv                = nullptr;
    GLUniformMatrix2fvPtr           glUniformMatrix2fv          = nullptr;
    GLUniformMatrix3fvPtr           glUniformMatrix3fv          = nullptr;
    GLUniformMatrix4fvPtr           glUniformMatrix4fv          = nullptr;

    bool loadGLFunctions() {

        glLibrary = LoadLibrary("opengl32.dll");
        if (glLibrary == NULL) {
            return false;
        }

        LOAD_GL_FUNCTION(GLClearPtr, glClear);
        LOAD_GL_FUNCTION(GLClearColorPtr, glClearColor);
        LOAD_GL_FUNCTION(GLViewportPtr, glViewport);
        LOAD_GL_FUNCTION(GLGetStringPtr, glGetString);
        LOAD_GL_FUNCTION(GLGenBuffersPtr, glGenBuffers);
        LOAD_GL_FUNCTION(GLDeleteBuffersPtr, glDeleteBuffers);
        LOAD_GL_FUNCTION(GLBindBufferPtr, glBindBuffer);
        LOAD_GL_FUNCTION(GLBufferDataPtr, glBufferData);
        LOAD_GL_FUNCTION(GLBufferSubDataPtr, glBufferSubData);
        LOAD_GL_FUNCTION(GLGenVertexArraysPtr, glGenVertexArrays);
        LOAD_GL_FUNCTION(GLDeleteVertexArraysPtr, glDeleteVertexArrays);
        LOAD_GL_FUNCTION(GLBindVertexArrayPtr, glBindVertexArray);
        LOAD_GL_FUNCTION(GLDrawElementsPtr, glDrawElements);
        LOAD_GL_FUNCTION(GLDrawArraysPtr, glDrawArrays);
        LOAD_GL_FUNCTION(GLVertexAttribPointerPtr, glVertexAttribPointer);
        LOAD_GL_FUNCTION(GLEnableVertexAttribArrayPtr, glEnableVertexAttribArray);
        LOAD_GL_FUNCTION(GLCreateProgramPtr, glCreateProgram);
        LOAD_GL_FUNCTION(GLDeleteProgramPtr, glDeleteProgram);
        LOAD_GL_FUNCTION(GLLinkProgramPtr, glLinkProgram);
        LOAD_GL_FUNCTION(GLUseProgramPtr, glUseProgram);
        LOAD_GL_FUNCTION(GLCreateShaderPtr, glCreateShader);
        LOAD_GL_FUNCTION(GLShaderSourcePtr, glShaderSource);
        LOAD_GL_FUNCTION(GLCompileShaderPtr, glCompileShader);
        LOAD_GL_FUNCTION(GLGetShaderivPtr, glGetShaderiv);
        LOAD_GL_FUNCTION(GLGetShaderInfoLogPtr, glGetShaderInfoLog);
        LOAD_GL_FUNCTION(GLAttachShaderPtr, glAttachShader);
        LOAD_GL_FUNCTION(GLDeleteShaderPtr, glDeleteShader);
        LOAD_GL_FUNCTION(GLGetUniformLocationPtr, glGetUniformLocation);
        LOAD_GL_FUNCTION(GLUniform1fPtr, glUniform1f);
        LOAD_GL_FUNCTION(GLUniform1iPtr, glUniform1i);
        LOAD_GL_FUNCTION(GLUniform2fvPtr, glUniform2fv);
        LOAD_GL_FUNCTION(GLUniform3fvPtr, glUniform3fv);
        LOAD_GL_FUNCTION(GLUniform4fvPtr, glUniform4fv);
        LOAD_GL_FUNCTION(GLUniformMatrix2fvPtr, glUniformMatrix2fv);
        LOAD_GL_FUNCTION(GLUniformMatrix3fvPtr, glUniformMatrix3fv);
        LOAD_GL_FUNCTION(GLUniformMatrix4fvPtr, glUniformMatrix4fv);

        // FreeLibrary

        return true;

    }

}
