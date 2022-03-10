#include "core/app.h"
#include "core/editor.h"

int main(void)
{
    App app;
    Editor editor;
    
    app.AttatchLayer(&editor);

    app.Run();

    return 0;
}