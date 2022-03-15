#include "editor.h"

#include "events/input.h"
#include "nodes/fn.h"

Editor::Editor()
{
    this->ctx = Context::Get();
}

Editor::~Editor()
{
}

bool Editor::OnEvent(Event *e)
{
    if (e->GetType() == CHAR_PRESS)
    {
        CharPressEvent *event = (CharPressEvent *)e;
        this->ctx->currentField->data += event->key;
    }

    if (e->GetType() == KEY_PRESS)
    {
        KeyPressEvent *event = (KeyPressEvent *)e;
        if (event->key == KEY_BACKSPACE && !this->ctx->currentField->data.empty())
        {
            this->ctx->currentField->data.pop_back();
        }

        if (event->key == KEY_TAB) {
            auto it = std::find(this->fields.begin(), this->fields.end(), this->ctx->currentField);
            uint32_t idx;
            if (it != this->fields.end()) {
                idx = it - this->fields.begin();
            }

            if (idx == this->fields.size()-1) {
                this->ctx->currentField = this->fields[0];
            } else {
                this->ctx->currentField = this->fields[idx+1];
            }
        }

    }

    if (e->GetType() == ACTION_BOX_ANSWER)
    {
        ActionBoxAnswerEvent* event = (ActionBoxAnswerEvent*)e;
        
        if (this->insertionStage == 0) return false;

        if (this->insertionStage == 1) {
            if (event->text == "function" || event->text == "fn") {
                this->insertionType = FUNCTION;
                this->insertionStage = 2;
                this->ctx->actionBoxPrompt = "Function name?";
                INFO("Starting function node wizard");
            } else {
                this->insertionStage = 0;
            }
            return true;   
        }

        if (this->insertionStage == 2) {
            if (this->insertionType == FUNCTION) {
                auto* node = new Fn(&this->ctx->root, this->ctx->actionBoxAnswer);
                this->SetCurrentField(node);
                this->insertionStage = 0;
            }
            return true;
        }

        return true;
    }

    return false;
}

void Editor::OnDraw()
{
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_I))
    {
        this->insertionStage = 1;
        this->ctx->actionBoxPrompt = "Node type to insert?";
    }

    this->fields.clear();
    this->FindFields(&this->ctx->root);
    INFO(this->fields.size());

    this->text = this->ctx->root.Stringify();

    ClearBackground(DARK100);
    DrawTextEx(this->ctx->font, this->text.c_str(), {50, 50}, 24, 0, RAYWHITE);
}

void Editor::FindFields(Node* node) {
    for (auto* field : node->fields) {
        this->fields.push_back(field);
    }

    for (auto* child: node->children) {
        FindFields(child);
    }
}