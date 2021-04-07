#include <iostream>
#include <raylib.h>
#include "Asteroid.h"
#include "Ecran.h"
#include <ctime>
#include <cstdlib>

using namespace std;
#include <raylib.h>
#include "optionMenu.h"



int main() {

    //const char* monitor = GetMonitorName();
    const int screenWidth = 800;
    const int screenHeight = 450;
    int selection = 0;
   
    InitWindow(screenWidth, screenHeight, "Asteroids");
    ToggleFullscreen();
    SetTargetFPS(60);


    Color color = BLACK;
    const char* s0 = "ASTEROIDS";
    int tailleS0 = MeasureText(s0, 80);


    OptionMenu option1("START GAME", true);
    OptionMenu option2("HIGHSCORES", false);
    OptionMenu option3("SETTINGS", false);
    OptionMenu option4("EXIT GAME",false);
    OptionMenu options[4] = { option1, option2, option3, option4 };
    Color tabcolors[4] = { options[0].getColor(), options[1].getColor(), options[2].getColor(), options[3].getColor() };


    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(color);
        
        
        if (IsKeyPressed(KEY_DOWN) && selection <3) {
            tabcolors[selection] = WHITE;
            options[selection].setSelection(false);

            tabcolors[selection +1] = RED;
            options[selection + 1].setSelection(true);

            selection++;
        }
        
        if (IsKeyPressed(KEY_UP) && selection > 0) {
            tabcolors[selection] = WHITE;
            options[selection].setSelection(false);

            tabcolors[selection-1] = RED;
            options[selection - 1].setSelection(true);
            selection--;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (selection == 0) {
                // Lancer le jeu
            }
            else if (selection == 1) {
                // Ouvrir la page Highscores
            }
            else if (selection == 2) {
                // Ouvrir la page Settings
            }
            else if (selection == 3) {
                // Quitter le jeu
                return 0;

            }
        }

        DrawText(("%c", s0), screenWidth/2-tailleS0/2, 100, 80, WHITE);
        DrawText(option1.getString(), option1.getPosition(screenWidth), 250, 20, tabcolors[0]);
        DrawText(option2.getString(), option2.getPosition(screenWidth), 300, 20, tabcolors[1]);
        DrawText(option3.getString(), option3.getPosition(screenWidth), 350, 20, tabcolors[2]);
        DrawText(option4.getString(), option4.getPosition(screenWidth), 400, 20, tabcolors[3]);
        EndDrawing();
       
    }

    CloseWindow();

    return 0;
void main() {
	Asteroid asteroid1;
	asteroid1.affiche();
	Ecran();
}