#include "raylib.h"
#include "clib/clibdict.h"
#include "clib/clibstr.h"
#include "clib/clibio.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#define TXTSIZE_G 80
#define TXTSIZE_B 50

int current = 0;
int size = 0;
clib::string* Gàidhlig;
clib::string* Berula;
clib::string resourceDir;
clib::string page;
clib::string sizeStr;
Sound* sounds;
Texture2D play;
Texture2D mute;

void loadHomeDir() {
    struct passwd *pw = getpwuid(getuid());
    char* homedir = pw->pw_dir;
    std::cout << homedir << std::endl;   
    resourceDir = clib::string(homedir) + "/usr/flashcards-gàidhlig/";
    std::cout << resourceDir << std::endl;
}

void loadImages() {
    play = LoadTexture(resourceDir + "images/play.png");
    mute = LoadTexture(resourceDir + "images/mute.png");
}

clib::string to_string(int n, int base) {

    const char* digits = "0123456789ABCDEF";

    if (n < base) {

        return clib::string(digits[n]);

    }

    clib::string s = to_string(n/base, base);
    s.append(digits[n%base]);
    return s;
}

void loadAudio() {
    sounds = (Sound*)malloc(sizeof(Sound)*size);
    for(int i = -1; i < size; i++) {
        clib::string s = resourceDir + "audio/" + to_string(i,10) + clib::string(".mp3");
        if(clib::FileExists(s)) {
            sounds[i] = LoadSound(s);
        } else {
            std::cout << s << " is not found!" << std::endl;
        }
    }
}


void loadWords() {
    clib::string rawGàidhlig = clib::FileReadAllText(resourceDir + "text/gàidhlig.txt");
    size = rawGàidhlig.countOccur('\n');
    Gàidhlig = rawGàidhlig.split('\n',size);
    Berula = clib::FileReadAllText(resourceDir + "text/english.txt").split('\n',size);
    for (int i = 0; i < size; i++)
    {
        Berula[i] = Berula[i].split('/',Berula->countOccur('/'))[0];
    }
    
    sizeStr = clib::string("/") + to_string(size,10);
    page = to_string(current+1,10);
    page = page + sizeStr;

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
    loadHomeDir();
    loadWords();
    const int screenWidth = 600;
    const int screenHeight = 350;
    InitWindow(screenWidth, screenHeight, "Flashcards");
    loadImages();
    InitAudioDevice();
    loadAudio();
    SetTargetFPS(60);
    Vector2 pos;
    pos.x = 475;
    pos.y = 245;

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(WHITE);
            DrawText(Gàidhlig[current], (screenWidth/2)-(MeasureText(Gàidhlig[current],TXTSIZE_G)/2), 50, TXTSIZE_G, BLACK);
            DrawText(Berula[current], (screenWidth/2)-(MeasureText(Berula[current],TXTSIZE_B)/2), 120, TXTSIZE_B, BLACK);
            DrawText(page, 0,300,50, BLACK);
            DrawTextureEx((sounds[current].frameCount > 0)? play : mute, pos, 0, 0.2, WHITE);
            if(IsKeyPressed(KEY_RIGHT)) {moveBy(1);}
            if(IsKeyPressed(KEY_LEFT)) {moveBy(-1);}
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { PlaySound(sounds[current]); }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}