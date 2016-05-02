//#ifndef SHADER_H
//#define SHADER_H

#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "../utils/fileutils.h"

namespace selene { namespace graphics {

    class Shader
    {
    private:
        GLuint m_ShaderID;
        const char *m_VertPath;
        const char *m_FragPath;
    public:
        Shader(const char* vertPath, const char* fragPath);  
        ~Shader();
        
        //std::string read_file(const char* filepath);
        
        void enable() const;
        void disable() const;
    private:
        GLuint load();
    };
    
}   }

//#endif /* SHADER_H */