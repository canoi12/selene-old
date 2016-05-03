//#ifndef SHADER_H
//#define SHADER_H

#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "../maths/maths.h"
#include "../utils/fileutils.h"

namespace selene { namespace graphics {

    class Shader
    {
    public:
        GLuint m_ShaderID;
        const char *m_VertPath;
        const char *m_FragPath;
    public:
        Shader(const char* vertPath, const char* fragPath);  
        ~Shader();
        
        //std::string read_file(const char* filepath);
        void setUniform1f(const GLchar* name, float value);
        void setUniform1i(const GLchar* name, int value);
        void setUniform2f(const GLchar* name, const maths::vec2& vector);
        void setUniform3f(const GLchar* name, const maths::vec3& vector);
        void setUniform4f(const GLchar* name, const maths::vec4& vector);       
        void setUniformMat4(const GLchar* name, const maths::mat4& matrix);
        
        void enable() const;
        void disable() const;
    private:
        GLuint load();
        GLint getUniformLocation(const GLchar* name);
    };
    
}   }

//#endif /* SHADER_H */