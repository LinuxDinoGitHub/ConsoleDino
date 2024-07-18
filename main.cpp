#include <iostream>
#include <string>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

void printCanvas(char **canvas) {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 80; j++) {
            cout << canvas[i][j];
        }
        cout << endl;
    }
}

void drawDino(int posx, int posy, char **canvas, int dino){ //posx and pos y refers to bottom left of screen
    const string dinoJump[5] = 
    {"              / ._|", //19 chars
    "     _.----._/ /",
    "    /         /",
    " __/ (  | (  |",
    "/__.-'|_|--|_|"};
    const string dinoWalk1[5] = 
    {"              / ._|",
    "     _.----._/ /",
    "    /         /",
    " __/ (  |  (  |",
    "/__.-'/_/---/_/"};
    const string dinoWalk2[5] = 
    {"              / ._|",
    "     _.----._/ /",
    "    /         /",
    " __/ (  | ( \\",
    "/__.-'\\_|--\\_\\"};
    const string *pDino;
    if(dino == 0){
        pDino = dinoJump;
    }
    else if (dino == 1){
        pDino = dinoWalk1;
    }
    else{
        pDino = dinoWalk2;
    }
    for(int i = 0; i<5; i++){
        for(int j = 0; j<pDino[i].length(); j++){
            if(i+posx >= 0 && i+posx < 13 && j+posy >= 0 && j+posy < 80){
                canvas[i+posx][j+posy] = pDino[i][j];
            }  
        }
    }
}

void clearDino(char **canvas, int lastposx, int lastposy){ //top dino length is 19
    const string dinoSize[5] = 
    {"              / ._|",
    "     _.----._/ /",
    "    /         /",
    " __/ (  | (  \\|",
    "/__.-'\\_|--|_ |"};
    for (int i = 0; i < 5; i++){
        for (int j = 0; j<dinoSize[i].length(); j++){
            canvas[i+lastposy][j+lastposx] = ' '; //0, 8 current
        }
    }
}

int touching(char **canvas){
    return 0;
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void startGame(){
    ShowConsoleCursor(false);
    bool gameOver = false;
    int dinostate = 0;
    char **canvas = new char*[18];
    for (int i = 0; i < 18; i++) {
        canvas[i] = new char[80];
    }
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 80; j++) {
            if(i == 13){
                canvas[i][j] = '_';
            }
            else{
                canvas[i][j] = ' ';
            }
        }
    }
    int dinoVelocity = 0;
    int timePassed = 0;
    int posx = 0;
    int posy = 8;
    while(!gameOver){ //Runs every frame
        clearDino(canvas, posx, posy);
        if(GetKeyState(VK_SPACE) & 0x8000 && dinoVelocity == 0){
            dinoVelocity = 6;
        }
        if(dinoVelocity != 0){
            posy -= 1;
            dinoVelocity -= 1;
            dinostate = 0;
        }
        else{
            if(posy < 8){
                posy += 1;
            }
        }
        drawDino(posy,posx,canvas, dinostate%3); //y, x, default 6, 0
        dinostate++;
        this_thread::sleep_for(chrono::milliseconds(200));
        system("cls");
        printCanvas(canvas);
    }
    for(int i = 0; i < 18; i++) {
        delete[] canvas[i];
    }
    delete[] canvas;
}


int main(){
    startGame();
    return 0;
}
