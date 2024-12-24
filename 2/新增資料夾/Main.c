#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define WIDTH 30   // 遊戲區域寬度
#define HEIGHT 10  // 遊戲區域高度

void drawGame(int ballHeight, int obstaclePos, int obstaclePattern, double elapsedTime, int score) {
    system("cls"); // 清屏

    // 顯示遊戲操作提示與分數
    printf("按1時跳過一層障礙物 (#) 可得分\n");
    printf("按2時跳過兩層障礙物 (##) 可得分\n");
    printf("Time: %.2f s   Score: %d\n", elapsedTime, score);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y == HEIGHT - ballHeight - 1 && x == 5) {
                printf("O"); // 琴的位置
            }
            else if (x == obstaclePos) {
                // 根據障礙物類型繪製
                if (obstaclePattern == 1) {
                    // 一層障礙物 #
                    if (y == HEIGHT - 1) {
                        printf("#");
                    }
                    else {
                        printf(" ");
                    }
                }
                else if (obstaclePattern == 2) {
                    // 兩層障礙物 ##
                    if (y == HEIGHT - 1 || y == HEIGHT - 2) {
                        printf("#");
                    }
                    else {
                        printf(" ");
                    }
                }
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void recordHistory(int gameNumber, double elapsedTime, int score) {
    printf("\n[Game %d] Time: %.2f s   Score: %d\n", gameNumber, elapsedTime, score);
}

int main() {
    int gameNumber = 0; // 遊戲局數

    while (1) {
        int ballHeight = 0;         // 琴的高度
        int obstaclePos = WIDTH - 1; // 障礙物的初始位置
        int obstaclePattern = (rand() % 2) + 1; // 隨機生成障礙物模式（1: #, 2: ##）
        int jumping = 0;            // 是否在跳躍
        int jumpHeight = 0;         // 當前跳躍的高度
        int jumpTimer = 0;          // 跳躍計時器
        int score = 0;              // 遊戲分數
        char playerInput = 0;       // 玩家輸入

        // 遊戲開始時間
        clock_t startTime = clock();
        gameNumber++;

        srand((unsigned int)time(NULL));

        while (1) {
            // 計算已經過的時間
            clock_t currentTime = clock();
            double elapsedTime = (double)(currentTime - startTime) / CLOCKS_PER_SEC;

            if (_kbhit()) {
                playerInput = _getch();
            }

            // 判斷玩家輸入跳躍
            if (playerInput == '1' && !jumping) {
                jumping = 1;  // 開始跳躍
                jumpHeight = 1; // 跳 1 層
                jumpTimer = 6; // 跳躍的持續時間
            }
            else if (playerInput == '2' && !jumping) {
                jumping = 1;  // 開始跳躍
                jumpHeight = 2; // 跳 2 層
                jumpTimer = 8; // 跳躍的持續時間
            }

            // 更新遊戲邏輯
            if (jumping) {
                if (jumpTimer > jumpHeight) {
                    ballHeight = jumpHeight; // 向上跳
                }
                else if (jumpTimer > 0) {
                    ballHeight = 0; // 向下落
                }
                else {
                    jumping = 0; // 結束跳躍
                    ballHeight = 0; // 回到底部
                }
                jumpTimer--;
            }

            // 檢查碰撞（判定是否 Game Over）
            if (obstaclePos == 5 && (HEIGHT - ballHeight - 1) >= (HEIGHT - 2)) {
                printf("Game Over!\n");
                printf("Total Time: %.2f seconds\n", elapsedTime);
                printf("Your Score: %d\n", score);  // 顯示遊戲結束時的分數

                // 紀錄歷史結果
                recordHistory(gameNumber, elapsedTime, score);

                // 詢問是否繼續遊玩
                printf("\nDo you want to play again? (Y/N): ");
                char choice;
                do {
                    choice = _getch();
                    if (choice == 'Y' || choice == 'y') {
                        printf("\nRestarting game...\n");
                        Sleep(1000); // 稍作延遲
                        break;
                    }
                    else if (choice == 'N' || choice == 'n') {
                        printf("\nThank you for playing!\n");
                        system("pause");
                        return 0;
                    }
                } while (1);
                break; // 跳出內層遊戲迴圈，重新開始遊戲
            }

            // 檢查是否成功跳過障礙物
            if (obstaclePos == 4 && ballHeight > 0) {
                if (obstaclePattern == 1 && ballHeight >= 1 && playerInput == '1') {
                    score++; // 障礙物 # 被成功跳過，按1才得分
                }
                else if (obstaclePattern == 2 && ballHeight >= 2 && playerInput == '2') {
                    score++; // 障礙物 ## 被成功跳過，按2才得分
                }
            }

            // 移動障礙物
            obstaclePos--;
            if (obstaclePos < 0) {
                obstaclePos = WIDTH - 1;
                obstaclePattern = (rand() % 2) + 1; // 隨機生成新障礙物模式
            }

            // 繪製遊戲畫面
            drawGame(ballHeight, obstaclePos, obstaclePattern, elapsedTime, score);

            // 延遲 (模擬遊戲速度)
            Sleep(100);
        }
    }

    return 0;
}

