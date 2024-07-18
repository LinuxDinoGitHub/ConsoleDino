#include <iostream>
#include <string>

using namespace std;

void printCanvas(char **canvas) {
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 80; j++) {
            cout << canvas[i][j];
        }
        cout << endl;
    }
}

void drawDino(int posx, int posy, char **canvas){ //posx and pos y refers to bottom left of screen
    const string dino[5] = 
    {"              / _",
    "     _.----._/ /",
    "    /         /",
    " __/ (  | (  |",
    "/__.-'|_|--|_|"};
    for(int i = 0; i<=5; i++){
        for(int j = 0; j<dino[i].length(); j++){
            if(i+posx >= 0 && i+posx < 80 && j+posy >= 0 && j+posy < 11){
                canvas[i+posx][j+posy] = dino[i][j];
            }  
        }
    }
}

void startGame(){
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
    drawDino(2,8,canvas);
    printCanvas(canvas);
    for (int i = 0; i < 14; i++) {
        delete[] canvas[i];
    }
    delete[] canvas;
}


int main(){
    startGame();
    return 0;
}
