
#pragma once

#include "glew.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include "glm/glm.hpp"

using std::string;
using namespace glm;
class GlShader
     {
         public:
        GlShader();
         ~GlShader();
        GLuint loadFiles(const string& vertex_file_name, const string& fragment_file_name);
        GLuint load(const string& vertex_source, const string& fragment_source);
        GLuint load(const GLchar* vertex_source, const GLchar* fragment_source);

        void use();
         GLuint getIDProgram() {return ShaderProgram;}
        bool isLoad() {return ShaderProgram !=0;}
        //! Attribute
       GLint getAttribLocation (const GLchar* name)  const;
         GLint getAttribLocation(const std::string& name) const;
        //! Uniform get
        GLint getUniformLocation (const GLchar* name) const;
        GLint getUniformLocation (const std :: string& name) const;
      //! Uniform set
        void setUniform (GLint location, const  vec4& value);
        void setUniform (GLint location, const  vec3& value);
        void setUniform (GLint location, const  vec2& value);

        void setUniform (GLint location, const  mat4& value);
        void setUniform (GLint location, const GLint& value);

         private:
         void printInfoLogShader (GLuint shader);

         void printInfoLogProgram (GLuint shader);

         GLuint loadSourcefile(const string& source_file_name, GLuint shader_type);

         GLuint compileSource(const GLchar* source, GLuint shader_type);

         void linkProgram();
         GLuint ShaderProgram;
         GLuint vertex_shader;
        GLuint fragment_shader;
    };
