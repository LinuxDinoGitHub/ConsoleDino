#include <iostream>
#include <string>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

void printCanvas(char **canvas) {
    for (int i = 0; i < 14; i++) {
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
            if(i+posx >= 0 && i+posx < 11 && j+posy >= 0 && j+posy < 80){
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
    " __/ (  | ( \\",
    "/__.-'\\_|--\\_\\"};
    for (int i = 0; i < 5; i++){
        for (int j = 0; j<dinoSize[i].length(); j++){
            canvas[i+lastposx][j+lastposy] = ' ';
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
    char **canvas = new char*[14];
    for (int i = 0; i < 14; i++) {
        canvas[i] = new char[80];
    }
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 80; j++) {
            if(i == 11){
                canvas[i][j] = '_';
            }
            else{
                canvas[i][j] = ' ';
            }
        }
    }
    /*
    while (dinostate<30){
        clearDino(canvas, 6,0);
        drawDino(6,0,canvas, dinostate%3); //y, x, default 6, 0
        dinostate++;
        printCanvas(canvas);
        this_thread::sleep_for(chrono::milliseconds(200));
        system("cls");
    }*/
    for(int i = 0; i < 14; i++) {
        delete[] canvas[i];
    }
    delete[] canvas;
}


int main(){
    startGame();
    return 0;
}
