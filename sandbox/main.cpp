//
// Created by dallin on 8/11/20.
//

#include <Krispy.h>
class Sandbox : public Krispy::Application {
public:
    Sandbox() {

    }

    ~Sandbox() {

    }
};

Krispy::Application* Krispy::CreateApplication() {
    Sandbox* sandbox = new Sandbox();
    return sandbox;
};