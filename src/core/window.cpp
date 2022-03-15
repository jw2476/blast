#include "window.h"
#include "raylib.h"
#include "events/input.h"
#include "events/close.h"

Window::Window()
{
    InitWindow(WIDTH, HEIGHT, "BLAST");
    SetTargetFPS(60);
    this->ctx = Context::Get();
}

Window::~Window()
{
    CloseWindow();
}

void Window::OnTick()
{
    char character;
    while (character = GetCharPressed()) {
        this->ctx->eventBus.push(new KeyPressEvent(character));
        this->ctx->eventBus.push(new CharPressEvent(character));
    }

    int keycode;
    while (keycode = GetKeyPressed())
    {
        this->ctx->eventBus.push(new KeyPressEvent(keycode));
    }

    Vector2 delta = GetMouseDelta();
    if (delta.x != 0 || delta.y != 0) {
        this->ctx->eventBus.push(new MouseMoveEvent(GetMouseX(), GetMouseY()));
    }

    if (WindowShouldClose()) {
        this->ctx->eventBus.push(new CloseEvent());
    }
}