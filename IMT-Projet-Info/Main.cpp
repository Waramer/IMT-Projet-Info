#include <iostream>

using namespace std;
#include <raylib.h>



int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    Color color = BLACK;
    const char* s1 = "Press Enter to start";

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(color);
        
        
        if (IsKeyPressed(KEY_ENTER)) {
            color = RED;
            s1 = "Let's GO!!!";
        }
        DrawText(("%c", s1), 300, 200, 20, LIGHTGRAY);
        EndDrawing();
       
        //----------------------------------------------------------------------------------
    }

    CloseWindow();

    return 0;
}