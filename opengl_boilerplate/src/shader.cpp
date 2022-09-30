#include "shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "renderer.h"


Shader::Shader(const std::string& filepath)
	: m_filepath(filepath), m_renderer_id(0)
{
    shader_program_source source = parse_shader(filepath);
    m_renderer_id = create_shader(source.vertex_source, source.fragment_source);
}

Shader::~Shader()
{
    glcall(glDeleteProgram(m_renderer_id));
}

shader_program_source Shader::parse_shader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];

    enum class shader_type
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    shader_type type = shader_type::NONE;
    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = shader_type::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = shader_type::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compile_shader(unsigned int type, const std::string& source)
{
    glcall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    glcall(glShaderSource(id, 1, &src, nullptr));
    glcall(glCompileShader(id));

    int result;
    glcall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        glcall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(sizeof(char) * length);
        glcall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile shader: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glcall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::create_shader(const std::string& vertex_shader, const std::string& fragment_shader)
{
    glcall(unsigned int program = glCreateProgram());
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    glcall(glAttachShader(program, vs));
    glcall(glAttachShader(program, fs));
    glcall(glLinkProgram(program));
    glcall(glValidateProgram(program));

    glcall(glDeleteShader(vs));
    glcall(glDeleteShader(fs));

    return program;
}


void Shader::bind() const
{
    glcall(glUseProgram(m_renderer_id));
}

void Shader::unbind() const
{
    glcall(glUseProgram(0));
}

void Shader::set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glcall(glUniform4f(get_uniform_location(name), v0, v1, v2, v3));
}

void Shader::set_uniformmat4f(const std::string& name, glm::mat4& matrix)
{
    glcall(glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::set_uniform1f(const std::string& name, float value)
{
    glcall(glUniform1f(get_uniform_location(name), value));
}

void Shader::set_uniform1i(const std::string& name, int value)
{
    glcall(glUniform1i(get_uniform_location(name), value));
}

void Shader::set_uniform1iv(const std::string& name, const GLint count, int* values)
{
    glcall(glUniform1iv(get_uniform_location(name), count, values));
}

int Shader::get_uniform_location(const std::string& name)
{
    if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
        return m_uniform_location_cache[name];
    glcall(int location = glGetUniformLocation(m_renderer_id, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
    m_uniform_location_cache[name] = location;
    return location;
}
