//
// Created by dallin on 8/11/20.
//

#include <Krispy.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 camera(float Translate, glm::vec2 const & Rotate) {
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}

class ExampleLayer: public Krispy::Layer {
public:
    ExampleLayer() : Layer("Example") {
        glm::mat4 cam = camera(5.0f, {0.5f, 0.5f});
    }

    void OnUpdate() override {
        if (Krispy::Input::IsKeyPressed(KRISPY_KEY_SPACE)) {
            KRISPY_TRACE("Space is pressed (poll)!");
        }
    }

    void OnEvent(Krispy::Event &event) override {
        if (event.GetEventType() == Krispy::EventType::KeyPressed) {
            Krispy::KeyPressedEvent& e = (Krispy::KeyPressedEvent &) event;
            if (e.GetKeyCode() == KRISPY_KEY_SPACE) {
                KRISPY_TRACE("Space is pressed (event)!");
            }
            KRISPY_TRACE("{0}", (char)e.GetKeyCode());
        }
    }
};

class Sandbox : public Krispy::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {

    }
};

Krispy::Application* Krispy::CreateApplication() {
    Sandbox* sandbox = new Sandbox();
    return sandbox;
};