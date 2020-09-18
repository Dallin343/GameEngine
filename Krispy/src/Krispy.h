//
// Created by dallin on 8/11/20.
//

#pragma once

#pragma mark --Base--
#include "Krispy/Core/Base.h"
#pragma mark -- --Debug
#include "Krispy/Debug/Debuggable.h"
#include "Krispy/Debug/Instrumentor.h"

#pragma mark --Core--
#include "Krispy/Core/Application.h"
#include "Krispy/Core/Layer.h"
#include "Krispy/Core/Log.h"
#include "Krispy/Core/Timestep.h"
#include "Krispy/Core/Input.h"

#pragma mark -- --Controllers
#include "Krispy/Core/OrthographicCameraController.h"

#pragma mark -- --Inputs
#include "Krispy/Core/Input.h"
#include "Krispy/Core/KeyCodes.h"
#include "Krispy/Core/MouseCodes.h"

#pragma mark --Events--
#include "Krispy/Events/KeyEvent.h"
#include "Krispy/Events/MouseEvent.h"
#include "Krispy/Events/ApplicationEvent.h"

#pragma mark --ImGui--
#include "Krispy/ImGui/ImGuiLayer.h"

#pragma mark --Renderer--
#include "Krispy/Renderer/Renderer.h"
#include "Krispy/Renderer/Renderer2D.h"
#include "Krispy/Renderer/RenderCommand.h"

#include "Krispy/Renderer/Buffer.h"
#include "Krispy/Renderer/Shader.h"
#include "Krispy/Renderer/Texture.h"
#include "Krispy/Renderer/VertexArray.h"
#include "Krispy/Materials/Material.h"

#pragma mark -- --Cameras
#include "Krispy/Renderer/OrthographicCamera.h"


