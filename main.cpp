#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    string canvas[50][13];
    const string dino[5] = 
    {"              / _",
    "     _.----._/ /",
    "    /         /",
    " __/ (  | (  |",
    "/__.-'|_|--|_|"};
    for(string x : dino){
        cout << x << endl;
    }
    cout << canvas;
    return 0;
}
void printCanvas(const vector<vector<string>>& canvas) {
    for (const auto& row : canvas) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}
char* initCanvas(){
    static char canvas[13][50];
    for (int i=0; i<14; i++) {
        for (int j=0; j<50; j++) {
            canvas[i][j] = " ";
        }
    }
    return canvas; //returns address of the array
}