#include "raylib.h"
#include "clib/clibdict.h"
#include "clib/clibstr.h"
#include "clib/clibio.h"

#define TXTSIZE_G 80
#define TXTSIZE_B 60

int current = 0;
int size = 0;
clib::string* Gàidhlig;
clib::string* Berula;
clib::string page;
clib::string sizeStr;

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
    clib::string rawGàidhlig = clib::FileReadAllText("gàidhlig.txt");
    size = rawGàidhlig.countOccur('\n');
    Gàidhlig = rawGàidhlig.split('\n',size);
    Berula = clib::FileReadAllText("english.txt").split('\n',size);
    sizeStr = clib::string("/") + to_string(size,10);
    std::cout << sizeStr << std::endl;
    page = to_string(current+1,10);
    std::cout << page << std::endl;
    page = page + sizeStr;
    std::cout << page << std::endl;
}

void moveBy(int count) {
    current += count;
    current = (current >= size)? 0 : current;
    current = (current < 0)? size-1 : current;
    std::cout << Gàidhlig[current] << ": " << Berula[current]  << std::endl;
    page = to_string(current+1,10);
    page += sizeStr;
}

int main(void)
{
    loadWords();
    const int screenWidth = 600;
    const int screenHeight = 350;
    InitWindow(screenWidth, screenHeight, "Flashcards");
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(WHITE);
            DrawText(Gàidhlig[current], (screenWidth/2)-(MeasureText(Gàidhlig[current],TXTSIZE_G)/2), 50, TXTSIZE_G, BLACK);
            DrawText(Berula[current], (screenWidth/2)-(MeasureText(Berula[current],TXTSIZE_B)/2), 120, TXTSIZE_B, BLACK);
            DrawText(page, 0,300,50, BLACK);
            if(IsKeyPressed(KEY_RIGHT)) {moveBy(1);}
            if(IsKeyPressed(KEY_LEFT)) {moveBy(-1);}

        EndDrawing();
    }
    CloseWindow();

    return 0;
}