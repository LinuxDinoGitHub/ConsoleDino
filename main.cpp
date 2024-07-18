#include <iostream>
#include <string>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;
void setCursorPosition(int x, int y){
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}


void printCanvas(char **canvas) {
    for (int i = 0; i < 18; i++) {
        setCursorPosition(0,i);
        for (int j = 0; j < 80; j++) {
            cout << canvas[i][j];
        }
        cout << endl;
    }
}

void drawDino(int posx, int posy, char **canvas, int dino, bool *gameOverStat){ //posx and pos y refers to bottom left of screen
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
                if(canvas[i+posx][j+posy] == ' '){
                    canvas[i+posx][j+posy] = pDino[i][j];
                }
                else{
                    *gameOverStat = true;
                }
            }  
        }
    }
}

void drawCactus(char **canvas){
    const string cactus1[5] = {
        "  _ | |   ",
        " | || | _ ",
        "  \\_  || |",
        "    |  _/ ",
        "   -|_|   ",
    };
    const string cactus2[5] = {
        "  ",
        " ",
        "     _  ",
        "    | |) ",
        "   (|_|   ",
    };
    const string cactus3[5] = {
        " _  _        _    ",
        "| || | _    | | _ ",
        " \\_  || | (_  || |",
        "   |  _/    |  _ )",
        "  -|_|     -|_|   ",
    };
    int randomint = rand() % 3;
    int offset = 69;
    const string *cactus;
    switch (randomint){
        case 0:
            cactus = cactus1;
            break;
        case 1:
            cactus = cactus2;
            break;
        case 2:
            cactus = cactus3;
            offset = 55;
            break;
    }
    for(int i = 0; i<5; i++){
        for(int j=0; j< cactus[i].length(); j++){
            canvas[i+8][j+offset] = cactus[i][j]; //floor = 13 so 13-6 = 7 rows from top actually 8 from testing
        }
    }
}


void clearDino(char **canvas, int lastposx, int lastposy){ //top dino length is 19 THIS ALSO CLEARS THE SCORE
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
    for(int i = 0; i < 19; i++){
        canvas[0][i+60] = ' '; //offset = 80-18 = 62 just in case 60
    }
}

void drawScore(int score, int highscore,char **canvas){ // HI 000000   000000   2+1+6+3+6 = 18 chars
    string highS = to_string(highscore);
    while (highS.length() < 6) {
        highS.insert(0, "0");
    }
    string scoreS = to_string(score);
    while (scoreS.length() < 6) {
        scoreS.insert(0, "0");
    }
    string format = "HI " + highS + "   " + scoreS;
    for(int i = 0; i < format.length(); i++){
        canvas[0][i+60] = format[i];
    }
}

void drawGameOver(char **canvas){
    string phrase1 = "G A M E   O V E R";
    string phrase2 = "Type y to try again, n to exit";
    for(int i = 0; i < phrase1.length(); i++){
        canvas[3][i+7] = phrase1[i];
    }
    for(int i = 0; i < phrase2.length(); i++){
        canvas[4][i+7] = phrase2[i];
    }
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void shiftCanvas(char **canvas) {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 79; j++) {
            canvas[i][j] = canvas[i][j + 4];
        }
        canvas[i][76] = ' ';
        canvas[i][77] = ' ';
        canvas[i][78] = ' ';
        canvas[i][79] = ' ';
    }
    canvas[13][76] = '_';
    canvas[13][77] = '_';
    canvas[13][78] = '_';
    canvas[13][79] = '_';
}

void startGame(int *high){
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
    int dinoVelocity = 0; // upwards
    int timePassed = 0; // for cactus
    bool canJump = true;
    int posx = 0;
    int posy = 8;
    int score = 0;
    while(!gameOver){ //Runs every frame
        clearDino(canvas, posx, posy);
        //Dino event handlers
        shiftCanvas(canvas);
        if(GetKeyState(VK_SPACE) & 0x8000 && dinoVelocity == 0 && canJump == true){
            dinoVelocity = 7;
            canJump = false;
            posy -= 1;
        }

        if(dinoVelocity != 0){
            posy -= 1;
            dinoVelocity -= 1;
            drawDino(posy,posx,canvas, 0, &gameOver);
        }
        else{
            if(posy < 8){
                posy += 1;
            }
            drawDino(posy,posx,canvas, dinostate%2 + 1, &gameOver); //y, x, default 6, 0
        }
        if (posy == 8){
            canJump = true;
        }
        //cactus event handlers
        if(timePassed >= 500){
            drawCactus(canvas);
            timePassed = 0;
        }
        dinostate++;
        drawScore(score, *high, canvas);
        printCanvas(canvas); //renders this frame
        this_thread::sleep_for(chrono::milliseconds(10));
        timePassed += 20;
        score += 5;
    }
    drawGameOver(canvas);
    printCanvas(canvas);
    for(int i = 0; i < 18; i++) {
        delete[] canvas[i];
    }
    delete[] canvas;
    if (score > *high){
        *high = score;
        cout << "New high score!";
    }
}

void pregame(int *high){
    startGame(high);
    char userinput;
    setCursorPosition(0, 14);
    ShowConsoleCursor(true);
    cin >> userinput;
    system("cls");
    if(userinput == 'y'){
        pregame(high);
    }
    cout << "Thanks for playing! Hope to see you again.";
    sleep(1);
}

int main(){
    int *highscore = new int(0);
    pregame(highscore);
    return 0;
}
