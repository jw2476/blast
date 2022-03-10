#include "editor.h"

Editor::Editor()
{
    this->font = LoadFont("./resources/fonts/JetBrainsMono-Medium.ttf");
}

Editor::~Editor()
{
}

void Editor::Draw()
{
    DrawTextEx(this->font, this->code.c_str(), {100, 100}, 32, 0, {12, 12, 12, 255});
}

void Editor::OnEvent(Event *event, std::queue<Event *> eventBus)
{
}