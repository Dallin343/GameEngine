//
// Created by dallin on 8/11/20.
//

#pragma once

extern Krispy::Application* Krispy::CreateApplication();

#pragma mark --Entry Point--
int main() {
    Krispy::Log::Init();
    KRISPY_CORE_INFO("Initialized Log...");

    KRISPY_CORE_INFO("Creating Application...");
    auto application = Krispy::CreateApplication();
    application->Run();
    delete application;
}