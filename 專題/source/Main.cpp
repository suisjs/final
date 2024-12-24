#include <iostream>
#include <windows.h>
#include <conio.h> // 如果你的 Visual Studio 支援 conio.h，這可以保留
#include <ctime>

using namespace std;

// 設定控制台游標位置
void moveTo(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 暫停執行指定的毫秒數
void pause(unsigned int milliseconds)
{
    Sleep(milliseconds);
}

// 顯示遊戲資訊
void displayGameInfo()
{
    system("cls"); // 清除控制台
    moveTo(10, 2);
    cout << "Press X to Exit, Press Space to Jump";
    moveTo(62, 2);
    cout << "SCORE : ";
    moveTo(1, 25);
    for (int x = 0; x < 79; x++)
        cout << "─";
}

// 全域變數
int jumpHeight = 0, gameSpeed = 40;

// 顯示角色
void displayCharacter(int jumpType = 0)
{
    static int animationState = 1;

    if (jumpType == 0)
        jumpHeight = 0;
    else if (jumpType == 2)
        jumpHeight--;
    else
        jumpHeight++;

    moveTo(2, 15 - jumpHeight);
    cout << "                ";
    moveTo(2, 16 - jumpHeight);
    cout << "     O      ";
    moveTo(2, 17 - jumpHeight);
    cout << "    /|\\     ";
    moveTo(2, 18 - jumpHeight);
    cout << "    / \\     ";

    pause(gameSpeed);
}

// 顯示障礙物
void displayObstacle()
{
    static int obstaclePosition = 0, score = 0;

    if (obstaclePosition == 56 && jumpHeight < 4) {
        score = 0;
        gameSpeed = 40;
        moveTo(36, 8);
        cout << "Game Over";
        _getch(); // 暫停等待玩家按鍵
        moveTo(36, 8);
        cout << "         ";
    }

    moveTo(74 - obstaclePosition, 20);
    cout << "||"; // 簡單的障礙物顯示

    obstaclePosition++;
    if (obstaclePosition == 73) {
        obstaclePosition = 0;
        score++;
        moveTo(70, 2);
        cout << "     ";
        moveTo(70, 2);
        cout << score;
        if (gameSpeed > 20)
            gameSpeed--;
    }
}

// 主程式
int main()
{
    system("mode con: lines=29 cols=82"); // 設定視窗大小
    char input;
    int i;
    displayGameInfo();

    while (true) {
        while (!_kbhit()) { // 等待按鍵輸入
            displayCharacter();
            displayObstacle();
        }

        input = _getch();
        if (input == ' ') { // 按空白鍵跳躍
            for (i = 0; i < 10; i++) {
                displayCharacter(1);
                displayObstacle();
            }
            for (i = 0; i < 10; i++) {
                displayCharacter(2);
                displayObstacle();
            }
        }
        else if (input == 'x' || input == 'X') { // 按 X 離開
            return 0;
        }
    }

    return 0;
}
