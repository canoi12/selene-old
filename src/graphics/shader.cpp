#include "shader.h"

namespace solunar { namespace graphics {
    
    std::string Shader::read_file(const char* filepath)
    {
        FILE* file = fopen(filepath, "rt");
        fseek(file, 0, SEEK_END);
        unsigned long length = ftell(file);
        char* data = new char[length + 1];
        memset(data, 0, length + 1);
        fseek(file, 0, SEEK_SET);
        fread(data, 1, length, file);
        fclose(file);
        
        std::string result(data);
        
        delete[] data;
        return result;
    }
    
    Shader::Shader(const char* vertPath, const char* fragPath)
       : m_VertPath(vertPath), m_FragPath(fragPath)
    {
        m_ShaderID = load();
    }
    
    GLuint Shader::load()
    {
        GLuint program = glCreateProgram();
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        
        std::string vertSource = read_file(m_VertPath);
        std::string fragSource = read_file(m_FragPath);
        
        const char* v = vertSource.c_str();
        const char* f = fragSource.c_str();
        
        
        
        glShaderSource(vertex, 1, &v, NULL);
        glCompileShader(vertex);
        
        GLint result;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
        if(result == GL_FALSE)
        {
            int length;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(vertex, length, &length, &error[0]);
            std::cout << "Failed to compile vertex shader! " << std::endl << &error[0] << std::endl;
            glDeleteShader(vertex);
            return 0;
        }
        
        
        glShaderSource(fragment, 1, &f, NULL);
        glCompileShader(fragment);
        
        
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
        if(result == GL_FALSE)
        {
            int length;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(fragment, length, &length, &error[0]);
            std::cout << "Failed to compile fragment shader! " << std::endl << &error[0] << std::endl;
            glDeleteShader(fragment);
            return 0;
        }
        
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        
        glLinkProgram(program);
        glValidateProgram(program);
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        
        return program;
    }
    
    void Shader::enable() const
    {
        glUseProgram(m_ShaderID);
    }
    
    void Shader::disable() const
    {
        glUseProgram(0);
    }
    
}}