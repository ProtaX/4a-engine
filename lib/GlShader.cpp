#include "GlShader.hpp"
#include <iostream>
#include <fstream>
#include <math.h>

namespace fae{

    void GlShader :: linkProgram (){
        GLint link_ok = GL_FALSE;
        if (!vertex_shader || !fragment_shader){
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
            //printInfoLogShader(ShaderProgram);
            ShaderProgram = GL_FALSE;
            return;
            }
        }
    void GlShader :: use(){
        glUseProgram(ShaderProgram);
    }
    GLuint GlShader :: compileSource (const GLchar* source, GLuint shader_type){
        std::cout << source;
        
        GLuint shader = GLCall(glCreateShader(shader_type));
        std::cout << source;
        glShaderSource(shader,1,&source,NULL);
        glCompileShader(shader);
        //printInfoLogShader(shader);
        return shader;
    } 
    GLuint GlShader :: loadSourcefile (const std::string& source_file_name, GLuint shader_type){
        const char* path = source_file_name.c_str();
        std::cout << path << "\n";
        std::ifstream m_shader(path);
        if (!m_shader){
            std :: cout<< source_file_name << " file not found\n";
            return GL_FALSE;
        }
        std :: istreambuf_iterator<char> begin(m_shader), end;
        std::string sourceStr (begin, end);
        m_shader.close();
        return compileSource (sourceStr.c_str(), shader_type);
    }
    //Attribute get
    GLint GlShader :: getAttribLocation(const GLchar* name) const{
        GLint location = -1;
        location = glGetAttribLocation (ShaderProgram, name);
        if (location == -1)
            std :: cout<<"Could not bind attribute" << name << "\n";
        return location;
    }
    GLint GlShader :: getAttribLocation (const std::string& name) const{
        return getAttribLocation(name.c_str());
    }
    //Uniform
    GLint GlShader :: getUniformLocation(const GLchar* name) const{
        GLint location = -1;
        location = glGetUniformLocation (ShaderProgram, name);
        if (location == -1)
            std :: cout<<"Could not bind uniform"<< name<<"\n";
        return location;
    }
    GLint GlShader :: getUniformLocation (const std::string& name) const{
        return getUniformLocation (name.c_str());
    }
    //Set Uniform 
    void GlShader :: setUniform(GLint location, const vec4& value){
        glUniform4fv(location,1,&value[0]);
    }
    void GlShader :: setUniform(GLint location, const vec3& value){
        glUniform3fv(location,1,&value[0]);
    }
    void GlShader :: setUniform(GLint location, const vec2& value){
        glUniform2fv(location,1,&value[0]);
    }
    void GlShader :: setUniform(GLint location, const mat4& value){
        glUniformMatrix4fv(location,1,GL_FALSE, &value[0][0]);
    }
    void GlShader :: setUniform(GLint location, const GLint& value){
        glUniform1i(location,value);
    }

    void GlShader :: linkProgram (){
        GLint link_ok = GL_FALSE;
        if (!vertex_shader || !fragment_shader){
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
            printInfoLogShader(ShaderProgram);
            ShaderProgram = GL_FALSE;
            return;
            }
        }
    void GlShader :: use(){
        glUseProgram(ShaderProgram);
    }
    GLuint GlShader :: compileSource (const GLchar* source, GLuint shader_type){
        GLuint shader = glCreateShader(shader_type);
        glShaderSource(shader,1,&source,NULL);
        glCompileShader(shader);
        printInfoLogShader(shader);
        return shader;
    } 
    GLuint GlShader :: loadSourcefile (const std::string& source_file_name, GLuint shader_type){
        const char* path = source_file_name.c_str();
        std::cout << path << "\n";
        std::ifstream m_shader(path);
        if (!m_shader){
            std :: cout<< source_file_name << " file not found\n";
            return GL_FALSE;
        }
        std :: istreambuf_iterator<char> begin(m_shader), end;
        std::string sourceStr (begin, end);
        m_shader.close();
        return compileSource (sourceStr.c_str(), shader_type);
    }
    //Attribute get
    GLint GlShader :: getAttribLocation(const GLchar* name) const{
        GLint location = -1;
        location = glGetAttribLocation (ShaderProgram, name);
        if (location == -1)
            std :: cout<<"Could not bind attribute" << name << "\n";
        return location;
    }
    GLint GlShader :: getAttribLocation (const std::string& name) const{
        return getAttribLocation(name.c_str());
    }
    //Uniform
    GLint GlShader :: getUniformLocation(const GLchar* name) const{
        GLint location = -1;
        location = glGetUniformLocation (ShaderProgram, name);
        if (location == -1)
            std :: cout<<"Could not bind uniform"<< name<<"\n";
        return location;
    }
    GLint GlShader :: getUniformLocation (const std::string& name) const{
        return getUniformLocation (name.c_str());
    }
    //Set Uniform 
    void GlShader :: setUniform(GLint location, const vec4& value){
        glUniform4fv(location,1,&value[0]);
    }
    void GlShader :: setUniform(GLint location, const vec3& value){
        glUniform3fv(location,1,&value[0]);
    }
    void GlShader :: setUniform(GLint location, const vec2& value){
        glUniform2fv(location,1,&value[0]);
    }
    void GlShader :: setUniform(GLint location, const mat4& value){
        glUniformMatrix4fv(location,1,GL_FALSE, &value[0][0]);
    }
    void GlShader :: setUniform(GLint location, const GLint& value){
        glUniform1i(location,value);
    }

    // InfoLog 
    // Лог компидяции шейдера
    void GlShader :: printInfoLogShader (GLuint shader){
        int infologLen=0;
        int charsWritten =0;
        glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infologLen);
        if (infologLen >1){
            GLchar *infoLog = new GLchar [infologLen];
            if (infoLog == NULL){
                std :: cout <<"ERROR: Could not allocate InfoLog buffer\n ";
                exit(1);
            }
            glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
            std :: cout<< "InfoLog: "<<infoLog<<"\n\n\n";
            delete [] infoLog;
        }
    }
    //Лог линковки шейдерной программы
    void GlShader :: printInfoLogProgram (GLuint shader){
        int infologLen=0;
        int charsWritten =0;
        glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infologLen);
        if (infologLen >1){
            GLchar *infoLog = new GLchar [infologLen];
            if (infoLog == NULL){
                    std :: cout <<"ERROR: Could not allocate InfoLog buffer\n ";
                    exit(1);
            }
            glGetProgramInfoLog(shader, infologLen, &charsWritten, infoLog);
            std :: cout<< "InfoLog: "<<infoLog<<"\n\n\n";
            delete [] infoLog;
        }
    }
    
}
 





























