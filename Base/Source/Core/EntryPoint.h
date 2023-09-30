#ifndef BASE_ENTRYPOINT_H
#define BASE_ENTRYPOINT_H

#include "Core/Application.h"

extern Base::Application* Base::CreateApplication(int argc, char** argv);

int main(int argc, char** argv)
{
    auto app = Base::CreateApplication(argc, argv);
    app->Run();
    delete app;
    return 0;
}

#endif // BASE_ENTRYPOINT_H
