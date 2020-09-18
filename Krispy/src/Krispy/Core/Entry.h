//
// Created by dallin on 8/11/20.
//

#pragma once
#include "Krispy/Debug/Instrumentor.h"

extern Krispy::Application* Krispy::CreateApplication();

#pragma mark --Entry Point--
int main() {
    Krispy::Log::Init();

    KRISPY_PROFILE_BEGIN_SESSION("Create Application", "StartupResults.json");
    auto application = Krispy::CreateApplication();
    KRISPY_PROFILE_END_SESSION();

    KRISPY_PROFILE_BEGIN_SESSION("Run", "RunResults.json");
    application->Run();
    KRISPY_PROFILE_END_SESSION();

    delete application;
}