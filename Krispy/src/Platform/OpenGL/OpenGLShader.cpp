//
// Created by dallin on 8/24/20.
//

#include "OpenGLShader.h"

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
        KRISPY_PROFILE_FUNCTION();

        std::filesystem::path filepath = path;
        m_Name = filepath.stem().string();

        std::ifstream in(path, std::ios::in | std::ios::binary);
        std::string shaderString = ReadFile(path);
        auto shaderSources = PreProcess(shaderString);
        Compile(shaderSources);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string &vertexSrc, const std::string &fragmentSrc)
        : m_Name(name) {
        KRISPY_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
    }

    std::string OpenGLShader::ReadFile(const std::string &path) {
        KRISPY_PROFILE_FUNCTION();

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
        KRISPY_PROFILE_FUNCTION();

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
        KRISPY_PROFILE_FUNCTION();

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
        KRISPY_PROFILE_FUNCTION();

        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const {
        KRISPY_PROFILE_FUNCTION();

        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const {
        KRISPY_PROFILE_FUNCTION();

        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string &name, int value) {
        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetInt2(const std::string &name, const glm::vec2 &value) {
        UploadUniformInt2(name, value);
    }

    void OpenGLShader::SetInt3(const std::string &name, const glm::vec3 &value) {
        UploadUniformInt3(name, value);
    }

    void OpenGLShader::SetInt4(const std::string &name, const glm::vec4 &value) {
        UploadUniformInt4(name, value);
    }

    void OpenGLShader::SetIntArray(const std::string &name, int *data, uint32_t count) {
        UploadUniformIntArray(name, data, count);
    }

    void OpenGLShader::SetFloat(const std::string &name, float value) {
        UploadUniformFloat(name, value);
    }

    void OpenGLShader::SetFloat2(const std::string &name, const glm::vec2 &value) {
        UploadUniformFloat2(name, value);
    }

    void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &value) {
        UploadUniformFloat3(name, value);
    }

    void OpenGLShader::SetFloat4(const std::string &name, const glm::vec4 &value) {
        UploadUniformFloat4(name, value);
    }

    void OpenGLShader::SetMat2(const std::string &name, const glm::mat2 &value) {
        UploadUniformMat2(name, value);
    }

    void OpenGLShader::SetMat3(const std::string &name, const glm::mat3 &value) {
        UploadUniformMat3(name, value);
    }

    void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value) {
        UploadUniformMat4(name, value);
    }

    void OpenGLShader::UploadUniformInt(const std::string &name, uint32_t uniform) {
        uint32_t location = FindUniform(name);

        glUniform1i(location, uniform);
    }

    void OpenGLShader::UploadUniformInt2(const std::string &name, const glm::vec2 &uniform) {
        uint32_t location = FindUniform(name);

        //TODO error handle location
        glUniform2i(location, uniform.x, uniform.y);
    }

    void OpenGLShader::UploadUniformInt3(const std::string &name, const glm::vec3 &uniform) {
        uint32_t location = FindUniform(name);

        //TODO error handle location
        glUniform3i(location, uniform.x, uniform.y, uniform.z);
    }

    void OpenGLShader::UploadUniformInt4(const std::string &name, const glm::vec4 &uniform) {
        uint32_t location = FindUniform(name);

        //TODO error handle location
        glUniform4i(location, uniform.x, uniform.y, uniform.z, uniform.w);
    }

    void OpenGLShader::UploadUniformIntArray(const std::string &name, int *data, uint32_t count) {
        uint32_t location = FindUniform(name);

        //TODO error handle location
        glUniform1iv(location, count, data);
    }

    void OpenGLShader::UploadUniformFloat(const std::string &name, float uniform) {
        uint32_t location = FindUniform(name);

        //TODO error handle location
        glUniform1f(location, uniform);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &uniform) {
        uint32_t location = FindUniform(name);

        //TODO error handle location
        glUniform2f(location, uniform.x, uniform.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &uniform) {
        uint32_t location = FindUniform(name);

        //TODO error handle location
        glUniform3f(location, uniform.x, uniform.y, uniform.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &uniform) {
        uint32_t location = FindUniform(name);

        glUniform4f(location, uniform.x, uniform.y, uniform.z, uniform.w);
    }

    void OpenGLShader::UploadUniformMat2(const std::string &name, const glm::mat2 &uniform) {
        uint32_t location = FindUniform(name);

        //TODO error handle location
        glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }

    void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &uniform) {
        uint32_t location = FindUniform(name);

        //TODO error handle location
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4 &uniform) {
        uint32_t location = FindUniform(name);

        //TODO error handle location
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }

    uint32_t OpenGLShader::FindUniform(const std::string &name) {
        if (!UniformExists(name)) {
            ShaderUniform newUniform;
            newUniform.Location = glGetUniformLocation(m_RendererID, name.c_str());
            m_UniformCache[name] = newUniform;
            return newUniform.Location;

        }

        auto uniform = m_UniformCache.at(name);
        return uniform.Location;
    }

    bool OpenGLShader::UniformExists(const std::string &name) {
        auto exists = m_UniformCache.find(name);
        return exists != m_UniformCache.end();
    }
}


