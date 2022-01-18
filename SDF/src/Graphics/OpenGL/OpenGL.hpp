#pragma once

// OpenGL 3.0+ Loader for Windows

namespace sdf::gl {

	enum {
		GL_TRUE = 1,
		GL_FALSE = 0,
		GL_VERSION = 0x1F02,
		GL_TRIANGLES = 0x0004,
		GL_ARRAY_BUFFER = 0x8892,
		GL_ELEMENT_ARRAY_BUFFER = 0x8893,
		GL_STATIC_DRAW = 0x88E4,
		GL_DYNAMIC_DRAW = 0x88E8,
		GL_COLOR_BUFFER_BIT = 0x00004000,
		GL_FLOAT = 0x1406,
		GL_UNSIGNED_INT = 0x1405,
		GL_VERTEX_SHADER = 0x8B31,
		GL_FRAGMENT_SHADER = 0x8B30,
		GL_COMPILE_STATUS = 0x8B81,
		GL_INFO_LOG_LENGTH = 0x8B84
	};

	#if defined(_WIN64)
		using GLintptr = signed long long int;
		using GLsizeiptr = signed long long int;
	#else
		using GLintptr = signed long int;
		using GLsizeiptr = signed long int;
	#endif

	using GLchar = char;
	using GLbyte = signed char;
	using GLubyte = unsigned char;
	using GLboolean = unsigned char;
	using GLint = signed int;
	using GLuint = unsigned int;
	using GLenum = unsigned int;
	using GLsizei = unsigned int; // unsigned?
	using GLbitfield = unsigned int;
	using GLfloat = float;

	// Prepend with '_'?
	using GLClearPtr = void (__stdcall*)(GLbitfield mask);
	using GLClearColorPtr = void (__stdcall*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	using GLViewportPtr = void (__stdcall*)(GLint x, GLint y, GLsizei width, GLsizei height);
	using GLGetStringPtr = const GLubyte* (__stdcall*)(GLenum name);
	using GLGenBuffersPtr = void (__stdcall*)(GLsizei n, GLuint* buffers);
	using GLDeleteBuffersPtr = void (__stdcall*)(GLsizei n, const GLuint* buffers);
	using GLBindBufferPtr = void (__stdcall*)(GLenum target, GLuint buffer);
	using GLBufferDataPtr = void (__stdcall*)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	using GLBufferSubDataPtr = void (__stdcall*)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
	using GLDrawElementsPtr = void (__stdcall*)(GLenum mode, GLsizei count, GLenum type, const void* indices);
	using GLDrawArraysPtr = void (__stdcall*)(GLenum mode, GLint first, GLsizei count);
	using GLVertexAttribPointerPtr = void (__stdcall*)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	using GLEnableVertexAttribArrayPtr = void (__stdcall*)(GLuint index);
	using GLCreateProgramPtr = GLuint (__stdcall*)(void);
	using GLDeleteProgramPtr = void (__stdcall*)(GLuint program);
	using GLLinkProgramPtr = void (__stdcall*)(GLuint program);
	using GLUseProgramPtr = void (__stdcall*)(GLuint program);
	using GLCreateShaderPtr = GLuint (__stdcall*)(GLenum shaderType);
	using GLShaderSourcePtr = void (__stdcall*)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
	using GLCompileShaderPtr = void (__stdcall*)(GLuint shader);
	using GLGetShaderivPtr = void (__stdcall*)(GLuint shader, GLenum pname, GLint* params);
	using GLGetShaderInfoLogPtr = void (__stdcall*)(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
	using GLAttachShaderPtr = void (__stdcall*)(GLuint program, GLuint shader);
	using GLDeleteShaderPtr = void (__stdcall*)(GLuint shader);
	using GLGetUniformLocationPtr = GLint (__stdcall*)(GLuint program, const GLchar* name);
	using GLUniform1fPtr = void (__stdcall*)(GLint location, GLfloat v0);
	using GLUniform1iPtr = void (__stdcall*)(GLint location, GLint v0);
	using GLUniform2fvPtr = void (__stdcall*)(GLint location, GLsizei count, const GLfloat* value);
	using GLUniform3fvPtr = void (__stdcall*)(GLint location, GLsizei count, const GLfloat* value);
	using GLUniform4fvPtr = void (__stdcall*)(GLint location, GLsizei count, const GLfloat* value);
	using GLUniformMatrix2fvPtr = void (__stdcall*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	using GLUniformMatrix3fvPtr = void (__stdcall*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	using GLUniformMatrix4fvPtr = void (__stdcall*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

	extern GLClearPtr glClear;
	extern GLClearColorPtr glClearColor;
	extern GLViewportPtr glViewport;
	extern GLGetStringPtr glGetString;
	extern GLGenBuffersPtr glGenBuffers;
	extern GLDeleteBuffersPtr glDeleteBuffers;
	extern GLBindBufferPtr glBindBuffer;
	extern GLBufferDataPtr glBufferData;
	extern GLBufferSubDataPtr glBufferSubData;
	extern GLDrawElementsPtr glDrawElements;
	extern GLDrawArraysPtr glDrawArrays;
	extern GLVertexAttribPointerPtr glVertexAttribPointer;
	extern GLEnableVertexAttribArrayPtr glEnableVertexAttribArray;
	extern GLCreateProgramPtr glCreateProgram;
	extern GLDeleteProgramPtr glDeleteProgram;
	extern GLLinkProgramPtr glLinkProgram;
	extern GLUseProgramPtr glUseProgram;
	extern GLCreateShaderPtr glCreateShader;
	extern GLShaderSourcePtr glShaderSource;
	extern GLCompileShaderPtr glCompileShader;
	extern GLGetShaderivPtr glGetShaderiv;
	extern GLGetShaderInfoLogPtr glGetShaderInfoLog;
	extern GLAttachShaderPtr glAttachShader;
	extern GLDeleteShaderPtr glDeleteShader;
	extern GLGetUniformLocationPtr glGetUniformLocation;
	extern GLUniform1fPtr glUniform1f;
	extern GLUniform1iPtr glUniform1i;
	extern GLUniform2fvPtr glUniform2fv;
	extern GLUniform3fvPtr glUniform3fv;
	extern GLUniform4fvPtr glUniform4fv;
	extern GLUniformMatrix2fvPtr glUniformMatrix2fv;
	extern GLUniformMatrix3fvPtr glUniformMatrix3fv;
	extern GLUniformMatrix4fvPtr glUniformMatrix4fv;

	bool init(); // Rename?

}
