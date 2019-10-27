#define GLEW_STATIC
#include "glew.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include "GlShader.hpp"

using std :: ifstream;

GlShader::GlShader():ShaderProgram(0)
{

}
GlShader::~GlShader()
{
    glUseProgram(0);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteShader(ShaderProgram);
}
GLuint GlShader :: loadFiles (const string& vertex_file_name, const string& fragment_file_name)
{
    vertex_shader = loadSourcefile (vertex_file_name, GL_VERTEX_SHADER);
    fragment_shader = loadSourcefile (fragment_file_name, GL_FRAGMENT_SHADER);
linkProgram();
return ShaderProgram;
}
GLuint  GlShader ::load(const string& vertex_source, const string& fragment_source)
{
    vertex_shader = compileSource (vertex_source.c_str(), GL_VERTEX_SHADER);
    fragment_shader = compileSource (fragment_source.c_str(), GL_FRAGMENT_SHADER);
    linkProgram();
    return ShaderProgram;
}
GLuint  GlShader ::load(const GLchar* vertex_source, const GLchar* fragment_source)
{
    vertex_shader = compileSource (vertex_source, GL_VERTEX_SHADER);
    fragment_shader = compileSource (fragment_source, GL_FRAGMENT_SHADER);
    linkProgram();
    return ShaderProgram;
}

void GlShader :: linkProgram ()
{
    GLint link_ok = GL_FALSE;
    if (!vertex_shader || !fragment_shader)
    {
        ShaderProgram = GL_FALSE;
        return;
    } 

ShaderProgram = glCreateProgram();
glAttachShader(ShaderProgram, vertex_shader);
glAttachShader(ShaderProgram, fragment_shader);
glLinkProgram(ShaderProgram);
glGetProgramiv (ShaderProgram, GL_LINK_STATUS, &link_ok);
if (!link_ok) {
    std::cout<< "glLinkProgram:";
    //функция на вывод информации о линке 

}
























