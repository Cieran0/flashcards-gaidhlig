#include "raylib.h"
#include "clib/clibdict.h"
#include "clib/clibstr.h"
#include "clib/clibio.h"

#define SIZE 1000
#define TXTSIZE_G 80
#define TXTSIZE_B 60

int current = 0;
clib::string* Gàidhlig;
clib::string* Berula;
clib::string page;

clib::string to_string(int n, int base) {

    const char* digits = "0123456789ABCDEF";

    if (n < base) {

        return clib::string(digits[n]);

    }

    clib::string s = to_string(n/base, base);
    s.append(digits[n%base]);
    return s;
}

void loadWords() {
    Gàidhlig = clib::FileReadAllText("gàidhlig.txt").split('\n',SIZE);
    Berula = clib::FileReadAllText("berula.txt").split('\n',SIZE);
    page = to_string(current+1,10);
    page += "/1000";
}

void moveBy(int count) {
    current += count;
    current = (current >= SIZE)? 0 : current;
    current = (current < 0)? SIZE-1 : current;
    std::cout << Gàidhlig[current] << ": " << Berula[current]  << std::endl;
    page = to_string(current+1,10);
    page += "/1000";
}

int main(void)
{
    loadWords();
    const int screenWidth = 600;
    const int screenHeight = 350;
    InitWindow(screenWidth, screenHeight, "Flashcards");
    clib::string s = to_string(1000,10);
    SetTargetFPS(15);

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(WHITE);
            DrawText(Gàidhlig[current], (screenWidth/2)-(MeasureText(Gàidhlig[current],TXTSIZE_G)/2), 50, TXTSIZE_G, BLACK);
            DrawText(Berula[current], (screenWidth/2)-(MeasureText(Berula[current],TXTSIZE_B)/2), 120, TXTSIZE_B, BLACK);
            DrawText(page, 600-MeasureText(page,50),300,50, BLACK);
            if(IsKeyDown(KEY_RIGHT)) {moveBy(1);}
            if(IsKeyDown(KEY_LEFT)) {moveBy(-1);}

        EndDrawing();
    }
    CloseWindow();

    return 0;
}