#include "OpenGL.hpp"

#include <windows.h>

#pragma comment (lib, "opengl32.lib")

static HMODULE glLibrary;

static void* getGLFunction(const char* name) {

	void* ptr = (void*)wglGetProcAddress(name);
	if (ptr == 0) {
		ptr = (void*)GetProcAddress(glLibrary, name);
	}

	return ptr;

}

namespace sdf {

	GLClearPtr glClear = nullptr;
	GLClearColorPtr glClearColor = nullptr;
	GLViewportPtr glViewport = nullptr;
	GLGetStringPtr glGetString = nullptr;
	GLGenBuffersPtr glGenBuffers = nullptr;
	GLDeleteBuffersPtr glDeleteBuffers = nullptr;
	GLBindBufferPtr glBindBuffer = nullptr;
	GLBufferDataPtr glBufferData = nullptr;
	GLBufferSubDataPtr glBufferSubData = nullptr;
	GLDrawElementsPtr glDrawElements = nullptr;
	GLDrawArraysPtr glDrawArrays = nullptr;
	GLVertexAttribPointerPtr glVertexAttribPointer = nullptr;
	GLEnableVertexAttribArrayPtr glEnableVertexAttribArray = nullptr;
	GLCreateProgramPtr glCreateProgram = nullptr;
	GLDeleteProgramPtr glDeleteProgram = nullptr;
	GLLinkProgramPtr glLinkProgram = nullptr;
	GLUseProgramPtr glUseProgram = nullptr;
	GLCreateShaderPtr glCreateShader = nullptr;
	GLShaderSourcePtr glShaderSource = nullptr;
	GLCompileShaderPtr glCompileShader = nullptr;
	GLGetShaderivPtr glGetShaderiv = nullptr;
	GLGetShaderInfoLogPtr glGetShaderInfoLog = nullptr;
	GLAttachShaderPtr glAttachShader = nullptr;
	GLDeleteShaderPtr glDeleteShader = nullptr;
	GLGetUniformLocationPtr glGetUniformLocation = nullptr;
	GLUniform1fPtr glUniform1f = nullptr;
	GLUniform1iPtr glUniform1i = nullptr;
	GLUniform2fvPtr glUniform2fv = nullptr;
	GLUniform3fvPtr glUniform3fv = nullptr;
	GLUniform4fvPtr glUniform4fv = nullptr;
	GLUniformMatrix2fvPtr glUniformMatrix2fv = nullptr;
	GLUniformMatrix3fvPtr glUniformMatrix3fv = nullptr;
	GLUniformMatrix4fvPtr glUniformMatrix4fv = nullptr;

	bool initGL() {

		glLibrary = LoadLibrary("opengl32.dll");
		if (glLibrary == NULL) {
			return false;
		}

		glClear = (GLClearPtr)getGLFunction("glClear");
		glClearColor = (GLClearColorPtr)getGLFunction("glClearColor");
		glViewport = (GLViewportPtr)getGLFunction("glViewport");
		glGetString = (GLGetStringPtr)getGLFunction("glGetString");
		glGenBuffers = (GLGenBuffersPtr)getGLFunction("glGenBuffers");
		glDeleteBuffers = (GLDeleteBuffersPtr)getGLFunction("glDeleteBuffers");
		glBindBuffer = (GLBindBufferPtr)getGLFunction("glBindBuffer");
		glBufferData = (GLBufferDataPtr)getGLFunction("glBufferData");
		glBufferSubData = (GLBufferSubDataPtr)getGLFunction("glBufferSubData");
		glDrawElements = (GLDrawElementsPtr)getGLFunction("glDrawElements");
		glDrawArrays = (GLDrawArraysPtr)getGLFunction("glDrawArrays");
		glVertexAttribPointer = (GLVertexAttribPointerPtr)getGLFunction("glVertexAttribPointer");
		glEnableVertexAttribArray = (GLEnableVertexAttribArrayPtr)getGLFunction("glEnableVertexAttribArray");
		glCreateProgram = (GLCreateProgramPtr)getGLFunction("glCreateProgram");
		glDeleteProgram = (GLDeleteProgramPtr)getGLFunction("glDeleteProgram");
		glLinkProgram = (GLLinkProgramPtr)getGLFunction("glLinkProgram");
		glUseProgram = (GLUseProgramPtr)getGLFunction("glUseProgram");
		glCreateShader = (GLCreateShaderPtr)getGLFunction("glCreateShader");
		glShaderSource = (GLShaderSourcePtr)getGLFunction("glShaderSource");
		glCompileShader = (GLCompileShaderPtr)getGLFunction("glCompileShader");
		glGetShaderiv = (GLGetShaderivPtr)getGLFunction("glGetShaderiv");
		glGetShaderInfoLog = (GLGetShaderInfoLogPtr)getGLFunction("glGetShaderInfoLog");
		glAttachShader = (GLAttachShaderPtr)getGLFunction("glAttachShader");
		glDeleteShader = (GLDeleteShaderPtr)getGLFunction("glDeleteShader");
		glGetUniformLocation = (GLGetUniformLocationPtr)getGLFunction("glGetUniformLocation");
		glUniform1f = (GLUniform1fPtr)getGLFunction("glUniform1f");
		glUniform1i = (GLUniform1iPtr)getGLFunction("glUniform1i");
		glUniform2fv = (GLUniform2fvPtr)getGLFunction("glUniform2fv");
		glUniform3fv = (GLUniform3fvPtr)getGLFunction("glUniform3fv");
		glUniform4fv = (GLUniform4fvPtr)getGLFunction("glUniform4fv");
		glUniformMatrix2fv = (GLUniformMatrix2fvPtr)getGLFunction("glUniformMatrix2fv");
		glUniformMatrix3fv = (GLUniformMatrix3fvPtr)getGLFunction("glUniformMatrix3fv");
		glUniformMatrix4fv = (GLUniformMatrix4fvPtr)getGLFunction("glUniformMatrix4fv");
	
		// FreeLibrary

		return true;

	}

}
