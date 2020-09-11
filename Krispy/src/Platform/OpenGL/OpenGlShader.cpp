//
// Created by dallin on 8/24/20.
//

#include "OpenGlShader.h"

#include <fstream>
#include <filesystem>

#include <glm/gtc/type_ptr.hpp>

namespace Krispy {

    static GLenum ShaderTypeFromString(const std::string& type) {
        if (type == "vertex") {
            return GL_VERTEX_SHADER;
        } else if (type == "fragment" || type == "pixel") {
            return GL_FRAGMENT_SHADER;
        }

        KRISPY_CORE_ASSERT(false, "Unknown Shader Type!");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string &path) {
        std::filesystem::path filepath = path;
        m_Name = filepath.stem().string();

        std::ifstream in(path, std::ios::in | std::ios::binary);
        std::string shaderString = ReadFile(path);
        auto shaderSources = PreProcess(shaderString);
        Compile(shaderSources);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string &vertexSrc, const std::string &fragmentSrc)
        : m_Name(name) {

        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
    }

    std::string OpenGLShader::ReadFile(const std::string &path) {
        std::string result;
        std::ifstream in(path, std::ios::in | std::ios::binary);

        if (in) {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        } else {
            KRISPY_CORE_ERROR("Could not open Shader File '{0}'", path);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string &source) {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while (pos != std::string::npos) {
            size_t eol = source.find_first_of(KRISPY_PLATFORM_NEWLINE, pos);
            KRISPY_CORE_ASSERT(eol != std::string::npos, "Syntax error!");

            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            KRISPY_CORE_ASSERT(type == "vertex" || type == "fragment", "Invalid Shader Type!");

            size_t nextLinePos = source.find_first_not_of(KRISPY_PLATFORM_NEWLINE, eol);
            pos = source.find(typeToken, nextLinePos);

            shaderSources[ShaderTypeFromString(type)] =
                    source.substr(
                        nextLinePos,
                        pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos)
                    );
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(std::unordered_map<GLenum, std::string> &shaderSources) {

        GLuint program = glCreateProgram();

        std::array<GLenum, 2> glShaderIDs;
        int glShaderIDIndex = 0;

        for (auto &entry : shaderSources) {
            GLenum type = entry.first;
            const std::string& source = entry.second;

            GLuint shader = glCreateShader(type);

            const GLchar *sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, nullptr);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                KRISPY_CORE_ERROR("{0}", infoLog.data());
                KRISPY_CORE_ASSERT(false, "Shader compilation failed!");
                return;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }

// Vertex and fragment shaders are successfully compiled.
// Now time to link them together into a program.
// Get a program object.
        m_RendererID = program;

        glLinkProgram(m_RendererID);

        GLint isLinked = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(m_RendererID);

            for (auto id : glShaderIDs) {
                glDeleteShader(id);
            }

            KRISPY_CORE_ERROR("{0}", infoLog.data());
            KRISPY_CORE_ASSERT(false, "Shader linking failed!");
            return;
        }

        for (auto id : glShaderIDs) {
            glDetachShader(program, id);
        }
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4 &uniform) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());

        //TODO error handle location
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }

    void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &uniform) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());

        //TODO error handle location
        glUniform3f(location, uniform.x, uniform.y, uniform.z);
    }

    void OpenGLShader::UploadUniformMat2(const std::string &name, const glm::mat2 &uniform) {

    }

    void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &uniform) {

    }

    void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &uniform) {

    }

    void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &uniform) {

    }

    void OpenGLShader::UploadUniformFloat(const std::string &name, float uniform) {

    }

    void OpenGLShader::UploadUniformUInt(const std::string &name, uint32_t uniform) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());

        glUniform1i(location, uniform);
    }

    void OpenGLShader::UploadUniformUInt2(const std::string &name, const glm::vec2 &uniform) {

    }

    void OpenGLShader::UploadUniformUInt3(const std::string &name, const glm::vec3 &uniform) {

    }

    void OpenGLShader::UploadUniformUInt4(const std::string &name, const glm::vec4 &uniform) {

    }
}


