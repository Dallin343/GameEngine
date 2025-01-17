cmake_minimum_required(VERSION 3.17)
project(Krispy)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/lib")
include_directories(
        Krispy/vendor/stb/
        Krispy/vendor/spdlog/include
        Krispy/vendor/glfw/include
        Krispy/vendor/glad/include
        Krispy/vendor/imgui
        Krispy/vendor/glm
        Krispy/vendor/assimp/build/include
        Krispy/vendor/assimp/include
        Krispy/src
)

add_library(Krispy
        STATIC
        Krispy/src/Krispy/Core/Base.h
        Krispy/src/Krispy.h
        Krispy/src/Krispy/Core/Application.cpp
        Krispy/src/Krispy/Core/Application.h
        Krispy/src/Krispy/Core/Entry.h
        Krispy/src/Krispy/Core/Log.cpp
        Krispy/src/Krispy/Core/Log.h
        Krispy/src/Krispy/Events/Event.h
        Krispy/src/Krispy/Events/ApplicationEvent.h
        Krispy/src/Krispy/Events/KeyEvent.h
        Krispy/src/Krispy/Events/MouseEvent.h
        Krispy/src/Platform/Linux/LinuxWindow.cpp
        Krispy/src/Platform/Linux/LinuxWindow.h
        Krispy/src/Krispy/Core/Window.h
        Krispy/src/Krispy/Core/Layer.cpp
        Krispy/src/Krispy/Core/Layer.h
        Krispy/src/Krispy/Core/LayerStack.cpp
        Krispy/src/Krispy/Core/LayerStack.h
        Krispy/src/Krispy/Debug/Debuggable.h
        Krispy/src/Krispy/ImGui/ImGuiLayer.cpp
        Krispy/src/Krispy/ImGui/ImGuiLayer.h
        Krispy/src/Krispy/ImGui/ImGuiBuild.cpp
        Krispy/src/Krispy/Core/KeyCodes.h
        Krispy/src/Krispy/Core/MouseCodes.h
        Krispy/src/Krispy/Core/Input.h
        Krispy/src/Platform/Linux/LinuxInput.cpp
        Krispy/src/Platform/OpenGL/OpenGLContext.h
        Krispy/src/Platform/OpenGL/OpenGLContext.cpp
        Krispy/src/Krispy/Renderer/GraphicsContext.h
        Krispy/src/Krispy/Renderer/Shader.cpp
        Krispy/src/Krispy/Renderer/Shader.h
        Krispy/src/Krispy/Renderer/Buffer.cpp
        Krispy/src/Krispy/Renderer/Buffer.h
        Krispy/src/Krispy/Renderer/Renderer.cpp
        Krispy/src/Krispy/Renderer/Renderer.h
        Krispy/src/Platform/OpenGL/OpenGLBuffer.cpp
        Krispy/src/Platform/OpenGL/OpenGLBuffer.h
        Krispy/src/Krispy/Renderer/VertexArray.cpp
        Krispy/src/Krispy/Renderer/VertexArray.h
        Krispy/src/Platform/OpenGL/OpenGLVertexArray.cpp
        Krispy/src/Platform/OpenGL/OpenGLVertexArray.h
        Krispy/src/Krispy/Debug/OpenGLDebug.cpp
        Krispy/src/Krispy/Debug/OpenGLDebug.h
        Krispy/src/Krispy/Renderer/RenderCommand.cpp
        Krispy/src/Krispy/Renderer/RenderCommand.h
        Krispy/src/Krispy/Renderer/RendererApi.cpp
        Krispy/src/Krispy/Renderer/RendererApi.h
        Krispy/src/Platform/OpenGL/OpenGLRendererAPI.cpp
        Krispy/src/Platform/OpenGL/OpenGLRendererAPI.h
        Krispy/src/Krispy/Renderer/OrthographicCamera.cpp
        Krispy/src/Krispy/Renderer/OrthographicCamera.h
        Krispy/src/Platform/OpenGL/OpenGLShader.cpp
        Krispy/src/Platform/OpenGL/OpenGLShader.h
        Krispy/src/Krispy/Core/Timestep.h
        Krispy/src/Krispy/Renderer/Texture.cpp
        Krispy/src/Krispy/Renderer/Texture.h
        Krispy/src/Platform/OpenGL/OpenGLTexture.cpp
        Krispy/src/Platform/OpenGL/OpenGLTexture.h
        Krispy/vendor/stb/stb_image.cpp
        Krispy/src/Krispy/Core/OrthographicCameraController.cpp
        Krispy/src/Krispy/Core/OrthographicCameraController.h
        Krispy/src/Krispy/Renderer/Renderer2D.cpp
        Krispy/src/Krispy/Renderer/Renderer2D.h
        Krispy/src/Krispy/Debug/Instrumentor.h
        Krispy/src/Krispy/Renderer/Mesh.cpp
        Krispy/src/Krispy/Renderer/Mesh.h
        Krispy/src/Platform/OpenGL/OpenGLMesh.cpp
        Krispy/src/Platform/OpenGL/OpenGLMesh.h
        Krispy/src/Krispy/Renderer/Model.cpp
        Krispy/src/Krispy/Renderer/Model.h
        Krispy/src/Krispy/Renderer/PerspectiveCamera.cpp
        Krispy/src/Krispy/Renderer/PerspectiveCamera.h
        Krispy/src/Krispy/Core/PerspectiveCameraController.cpp
        Krispy/src/Krispy/Core/PerspectiveCameraController.h
        Krispy/src/Krispy/Materials/Material.cpp
        Krispy/src/Krispy/Materials/Material.h
        Krispy/src/Platform/OpenGL/OpenGLMaterial.cpp
        Krispy/src/Platform/OpenGL/OpenGLMaterial.h
        Krispy/src/Krispy/Core/Types.h Krispy/src/Krispy/Renderer/Renderer3D.cpp Krispy/src/Krispy/Renderer/Renderer3D.h)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(Krispy/vendor/glfw)

add_subdirectory(Krispy/vendor/spdlog)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(Krispy/vendor/assimp)

add_library(GLAD STATIC Krispy/vendor/glad/src/glad.c Krispy/vendor/glad/include/glad/glad.h)

add_library(ImGui STATIC
        Krispy/vendor/imgui/imconfig.h
        Krispy/vendor/imgui/imgui.cpp
        Krispy/vendor/imgui/imgui.h
        Krispy/vendor/imgui/imgui_draw.cpp
        Krispy/vendor/imgui/imgui_internal.h
        Krispy/vendor/imgui/imgui_widgets.cpp
        Krispy/vendor/imgui/imstb_rectpack.h
        Krispy/vendor/imgui/imstb_textedit.h
        Krispy/vendor/imgui/imstb_truetype.h
        Krispy/vendor/imgui/imgui_demo.cpp
        Krispy/vendor/imgui/examples/imgui_impl_opengl3.h
        Krispy/vendor/imgui/examples/imgui_impl_opengl3.cpp
        Krispy/vendor/imgui/examples/imgui_impl_glfw.h
        Krispy/vendor/imgui/examples/imgui_impl_glfw.cpp
        )

target_precompile_headers(Krispy
        PRIVATE
        <string>
        <iostream>
        <sstream>
        <memory>
        <utility>
        <functional>
        <algorithm>
        <vector>
        <cstdint>
        Krispy/src/Krispy/Core/Base.h
        Krispy/src/Krispy/Debug/Debuggable.h
        Krispy/src/Krispy/Debug/Instrumentor.h
        Krispy/src/Krispy/Core/Types.h
        Krispy/src/Krispy/Core/Log.h
        )

find_package(OpenGL REQUIRED)

set(glm_DIR Krispy/vendor/glm/cmake/glm)
find_package(glm REQUIRED)
target_link_libraries(Krispy PRIVATE glfw OpenGL::GL GLAD ImGui glm::glm spdlog::spdlog assimp)

# Sandbox
add_executable(Sandbox sandbox/src/Sandbox.cpp sandbox/src/Sandbox2D.cpp sandbox/src/Sandbox2D.h sandbox/src/Sandbox3D.cpp sandbox/src/Sandbox3D.h)
target_link_libraries(Sandbox PRIVATE Krispy glm::glm)


# Platform Specific Options
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PLATFORM_DEFS KRISPY_PLATFORM_WIN32)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(PLATFORM_DEFS KRISPY_PLATFORM_DARWIN)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PLATFORM_DEFS KRISPY_PLATFORM_LINUX)
else()
    set(PLATFORM_DEFS KRISPY_SYS_UNKNOWN)
endif (CMAKE_SYSTEM_NAME STREQUAL "Windows")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_TYPE_DEFS KRISPY_DEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(BUILD_TYPE_DEFS KRISPY_RELEASE)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

target_compile_definitions(Krispy PRIVATE ${PLATFORM_DEFS} ${BUILD_TYPE_DEFS})

