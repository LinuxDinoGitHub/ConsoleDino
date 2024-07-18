#include <iostream>
#include <string>

using namespace std;

void printCanvas(const char canvas[][50]) {
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 50; j++) {
            cout << canvas[i][j];
        }
        cout << endl;
    }
}

void drawDino(int posx, int posy, const char *canvas){ //posx and pos y referes to top right of screen
    const string dino[5] = 
    {"              / _",
    "     _.----._/ /",
    "    /         /",
    " __/ (  | (  |",
    "/__.-'|_|--|_|"};
    for(int i = 0; i<dino->length(); i++){
        for(char c : line){
            break;
        }
    }
}


int main(){
    char canvas[14][50];
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 50; j++) {
            canvas[i][j] = ' ';
        }
    }
    printCanvas(canvas);
    return 0;
}