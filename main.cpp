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

void drawDino(int posx, int posy, const char *canvas){
    return;
}


int main(){
    char canvas[14][50];
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 50; j++) {
            canvas[i][j] = ' ';
        }
    }
    /*const string dino[5] = 
    {"              / _",
    "     _.----._/ /",
    "    /         /",
    " __/ (  | (  |",
    "/__.-'|_|--|_|"}; */
    printCanvas(canvas);
    return 0;
}