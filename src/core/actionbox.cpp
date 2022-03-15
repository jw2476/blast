#include "actionbox.h"
#include "raylib.h"
#include "events/input.h"

#define BOX_HEIGHT 32

bool ActionBox::OnEvent(Event *e)
{
    if (!this->ctx->actionBoxPrompt.empty())
    {
        if (e->GetType() == CHAR_PRESS)
        {
            auto *event = (CharPressEvent *)e;
            this->response += event->key;
            return true;
        }
        if (e->GetType() == KEY_PRESS)
        {
            auto *event = (KeyPressEvent*)e;
            if (event->key == KEY_ENTER) {
                this->ctx->actionBoxAnswer = this->response;
                this->ctx->actionBoxPrompt = "";
                this->response = "";

                this->ctx->eventBus.push(new ActionBoxAnswerEvent(this->ctx->actionBoxAnswer));
            }
            return true;
        };
    }
    return false;
}

void ActionBox::OnDraw()
{
    if (!this->ctx->actionBoxPrompt.empty())
    {
        DrawRectangle(0, HEIGHT - BOX_HEIGHT, WIDTH, BOX_HEIGHT, DARK300);
        DrawTextEx(this->ctx->font, this->ctx->actionBoxPrompt.c_str(), {10, HEIGHT - BOX_HEIGHT + 4}, 24, 0, RAYWHITE);
        Vector2 questionSize = MeasureTextEx(this->ctx->font, this->ctx->actionBoxPrompt.c_str(), 24, 0);
        DrawTextEx(this->ctx->font, this->response.c_str(), {questionSize.x + 18, HEIGHT - BOX_HEIGHT + 4}, 24, 0, RAYWHITE);
    }
}