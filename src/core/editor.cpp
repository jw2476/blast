#include "editor.h"

#include "events/input.h"
#include "nodes/call.h"
#include "nodes/fn.h"
#include "nodes/str.h"
#include "nodes/extern.h"
#include "nodes/arg.h"
#include "nodes/assign.h"
#include "nodes/var.h"
#include "raylib.h"

Editor::Editor() { this->ctx = Context::Get(); }

Editor::~Editor() {}

bool Editor::OnEvent(Event *e) {
  if (e->GetType() == CHAR_PRESS) {
    CharPressEvent *event = (CharPressEvent *)e;
    if (this->ctx->currentField != nullptr)
      this->ctx->currentField->data += event->key;
  }

  if (e->GetType() == KEY_PRESS) {
    KeyPressEvent *event = (KeyPressEvent *)e;
    if (event->key == KEY_BACKSPACE && !this->ctx->currentField->data.empty()) {
      this->ctx->currentField->data.pop_back();
    }

    if (event->key == KEY_TAB) {
      auto it = std::find(this->fields.begin(), this->fields.end(),
                          this->ctx->currentField);
      uint32_t idx;
      if (it != this->fields.end()) {
        idx = it - this->fields.begin();
      } else if (!this->fields
                      .empty()) { // If there are fields to move to but there is
                                  // no current field, move to the first one
        this->ctx->currentField = this->fields[0];
        return true;
      }

      if (idx == this->fields.size() - 1) {
        this->ctx->currentField = this->fields[0];
      } else {
        this->ctx->currentField = this->fields[idx + 1];
      }
    }

    // Codegen
    if (event->key == KEY_F5) {
      this->ctx->root.Codegen();
    }
  }

  if (e->GetType() == ACTION_BOX_ANSWER) {
    ActionBoxAnswerEvent *event = (ActionBoxAnswerEvent *)e;

    if (this->insertionStage == 0)
      return false;

    if (this->insertionStage == 1) {
      if (event->text == "function" || event->text == "fn") {
        this->insertionType = FUNCTION;
        this->insertionStage = 2;
        this->ctx->actionBoxPrompt = "Function name?";
      } else if (event->text == "call" || event->text == "c") {
        this->insertionType = CALL;
        this->insertionStage = 2;
        this->ctx->actionBoxPrompt = "Function name?";
      } else if (event->text == "string" || event->text == "str" || event->text == "s") {
        this->insertionType = STRING;
        this->insertionStage = 2;
        this->ctx->actionBoxPrompt = "Value for string?";
      } else if (event->text == "extern") {
        this->insertionType = EXTERN;
        this->insertionStage = 2;
        this->ctx->actionBoxPrompt = "Function name?";
      } else if (event->text == "arg") {
        this->insertionType = ARG;
        this->insertionStage = 2;
        this->ctx->actionBoxPrompt = "Argument name?";
      } else if (event->text == "assign" || event->text == "a") {
        this->insertionType = ASSIGN;
        this->insertionStage = 2;
        this->ctx->actionBoxPrompt = "Variable name?";
      } else if (event->text == "var" || event->text == "v") {
        this->insertionType = VARIABLE;
        this->insertionStage = 2;
        this->ctx->actionBoxPrompt = "Variable name?";
      } else {
        this->insertionStage = 0;
      }
      return true;
    }

    if (this->insertionStage == 2) {
      if (this->insertionType == FUNCTION) {
        if (this->CheckValidate(Fn::Validate(this->GetParent()))) {
          auto *node = new Fn(this->GetParent(), this->ctx->actionBoxAnswer);
          this->SetCurrentField(node);
        }
        this->insertionStage = 0;
      } else if (this->insertionType == CALL) {
        if (this->CheckValidate(Call::Validate(this->GetParent()))) {
          auto *node = new Call(this->GetParent(), this->ctx->actionBoxAnswer);
          this->SetCurrentField(node);
        }
        this->insertionStage = 0;
      } else if (this->insertionType == STRING) {
        if (this->CheckValidate(String::Validate(this->GetParent()))) {
          auto *node = new String(this->GetParent(), this->ctx->actionBoxAnswer);
          this->SetCurrentField(node);
        }
        this->insertionStage = 0;
      } else if (this->insertionType == EXTERN) {
        if (this->CheckValidate(Extern::Validate(this->GetParent()))) {
          auto *node = new Extern(this->GetParent(), this->ctx->actionBoxAnswer);
          this->SetCurrentField(node);
        }
        this->insertionStage = 0;
      } else if (this->insertionType == ARG) {
        if (this->CheckValidate(Arg::Validate(this->GetParent()))) {
          auto *node = new Arg(this->GetParent(), this->ctx->actionBoxAnswer);
          this->SetCurrentField(node);
        }
        this->insertionStage = 0;
      } else if (this->insertionType == ASSIGN) {
        if (this->CheckValidate(Assign::Validate(this->GetParent()))) {
          auto *node = new Assign(this->GetParent(), this->ctx->actionBoxAnswer);
          this->SetCurrentField(node);
        }
        this->insertionStage = 0;
      } else if (this->insertionType == VARIABLE) {
        if (this->CheckValidate(Var::Validate(this->GetParent()))) {
          auto *node = new Var(this->GetParent(), this->ctx->actionBoxAnswer);
          this->SetCurrentField(node);
        }
        this->insertionStage = 0;
      }
      return true;
    }

    return true;
  }

  // Node deletion
  if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_D)) {
    if (this->ctx->currentField != nullptr) {
      delete this->ctx->currentField->node;
      this->ctx->currentField = nullptr;
    }
  }

  // Normal node insertion
  if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_I)) {
    this->insertionStage = 1;
    this->ctx->actionBoxPrompt = "Node type to insert?";
    this->insertMode = INSIDE;
  }

  // Root-mode node insertion
  if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_A)) {
    this->insertionStage = 1;
    this->ctx->actionBoxPrompt = "Node type to insert?";
    this->insertMode = AFTER;
  }

  return false;
}

void Editor::OnDraw() {
  this->fields.clear();
  this->FindFields(&this->ctx->root);

  this->text = this->ctx->root.Stringify();
  this->textIndex = 0;
  Vector2 textPos = {50, 50};
  Color currentColor = RAYWHITE;
  std::string block;

  // Initialise frame before text render
  ClearBackground(DARK100);

  // Text rendering
  while (this->text.size() != 0) {
    if (this->textIndex == this->text.size() ||
        (this->textIndex + 7 <= this->text.size() &&
         this->text.compare(this->textIndex, 6, "/Color") == 0) ||
        this->text.compare(this->textIndex, 1, NEWLINE) ==
            0) { // If end of text, colour set or end of line
      // DRAW BLOCK CODE
      DrawTextEx(this->ctx->font, block.c_str(), textPos, 24, 0, currentColor);
      Vector2 dims = MeasureTextEx(this->ctx->font, block.c_str(), 24, 0);

      if (this->text.size() == this->textIndex)
        break;

      if (this->text.compare(this->textIndex, 1, NEWLINE) != 0) {
        textPos.x += dims.x;
      } else {
        textPos.x = 50;
        textPos.y += 24;
      }

      block = "";
    }

    if (this->text.compare(this->textIndex, 6, "/Color") == 0) {
      // COLOUR CODE
      this->textIndex += 6; // Move past the /colour
      // Pull colour out
      uint8_t red = std::stoi(this->text.substr(this->textIndex + 2, 3));
      uint8_t green = std::stoi(this->text.substr(this->textIndex + 5, 3));
      uint8_t blue = std::stoi(this->text.substr(this->textIndex + 8, 3));
      uint8_t alpha = std::stoi(this->text.substr(this->textIndex + 11, 3));
      currentColor = {red, green, blue, alpha};

      this->textIndex += 16; // 12 for the colour value, 2 for the curly
                             // brackets, 2 for the spaces
    } else {
      if (this->text.compare(this->textIndex, 1, NEWLINE) !=
          0) // Don't render newlines
        block += this->text[this->textIndex];
      this->textIndex++;
    }
  }
}

void Editor::FindFields(Node *node) {
  for (auto *field : node->fields) {
    this->fields.push_back(field);
  }

  for (auto *child : node->children) {
    FindFields(child);
  }
}