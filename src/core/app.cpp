#include "app.h"
#include "raylib.h"


App::App()
{
    InitWindow(800, 450, "raylib [core] example - basic window");
    SetTargetFPS(60);
}

App::~App()
{
    CloseWindow();
}

void App::Run()
{
    while (!WindowShouldClose())
    {
        for (Layer *layer : this->layerStack)
        {
            layer->OnTick(this->eventBus);
        }

        while (Event *event = this->eventBus.front())
        {
            for (Layer *layer : this->layerStack)
            {
                layer->OnEvent(event, this->eventBus);
            }

            this->eventBus.pop();
        }

        BeginDrawing();
        for (Layer *layer : this->layerStack)
        {
            layer->Draw();
        }
        EndDrawing();
    }
}

void App::AttatchLayer(Layer *layer)
{
    this->layerStack.push_back(layer);
}