#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define WIDTH 30   // �C���ϰ�e��
#define HEIGHT 10  // �C���ϰ찪��

void drawGame(int ballHeight, int obstaclePos, int obstaclePattern, double elapsedTime, int score) {
    system("cls"); // �M��

    // ��ܹC���ާ@���ܻP����
    printf("��1�ɸ��L�@�h��ê�� (#) �i�o��\n");
    printf("��2�ɸ��L��h��ê�� (##) �i�o��\n");
    printf("Time: %.2f s   Score: %d\n", elapsedTime, score);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y == HEIGHT - ballHeight - 1 && x == 5) {
                printf("O"); // �^����m
            }
            else if (x == obstaclePos) {
                // �ھڻ�ê������ø�s
                if (obstaclePattern == 1) {
                    // �@�h��ê�� #
                    if (y == HEIGHT - 1) {
                        printf("#");
                    }
                    else {
                        printf(" ");
                    }
                }
                else if (obstaclePattern == 2) {
                    // ��h��ê�� ##
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
    int gameNumber = 0; // �C������

    while (1) {
        int ballHeight = 0;         // �^������
        int obstaclePos = WIDTH - 1; // ��ê������l��m
        int obstaclePattern = (rand() % 2) + 1; // �H���ͦ���ê���Ҧ��]1: #, 2: ##�^
        int jumping = 0;            // �O�_�b���D
        int jumpHeight = 0;         // ��e���D������
        int jumpTimer = 0;          // ���D�p�ɾ�
        int score = 0;              // �C������
        char playerInput = 0;       // ���a��J

        // �C���}�l�ɶ�
        clock_t startTime = clock();
        gameNumber++;

        srand((unsigned int)time(NULL));

        while (1) {
            // �p��w�g�L���ɶ�
            clock_t currentTime = clock();
            double elapsedTime = (double)(currentTime - startTime) / CLOCKS_PER_SEC;

            if (_kbhit()) {
                playerInput = _getch();
            }

            // �P�_���a��J���D
            if (playerInput == '1' && !jumping) {
                jumping = 1;  // �}�l���D
                jumpHeight = 1; // �� 1 �h
                jumpTimer = 6; // ���D������ɶ�
            }
            else if (playerInput == '2' && !jumping) {
                jumping = 1;  // �}�l���D
                jumpHeight = 2; // �� 2 �h
                jumpTimer = 8; // ���D������ɶ�
            }

            // ��s�C���޿�
            if (jumping) {
                if (jumpTimer > jumpHeight) {
                    ballHeight = jumpHeight; // �V�W��
                }
                else if (jumpTimer > 0) {
                    ballHeight = 0; // �V�U��
                }
                else {
                    jumping = 0; // �������D
                    ballHeight = 0; // �^�쩳��
                }
                jumpTimer--;
            }

            // �ˬd�I���]�P�w�O�_ Game Over�^
            if (obstaclePos == 5 && (HEIGHT - ballHeight - 1) >= (HEIGHT - 2)) {
                printf("Game Over!\n");
                printf("Total Time: %.2f seconds\n", elapsedTime);
                printf("Your Score: %d\n", score);  // ��ܹC�������ɪ�����

                // �������v���G
                recordHistory(gameNumber, elapsedTime, score);

                // �߰ݬO�_�~��C��
                printf("\nDo you want to play again? (Y/N): ");
                char choice;
                do {
                    choice = _getch();
                    if (choice == 'Y' || choice == 'y') {
                        printf("\nRestarting game...\n");
                        Sleep(1000); // �y�@����
                        break;
                    }
                    else if (choice == 'N' || choice == 'n') {
                        printf("\nThank you for playing!\n");
                        system("pause");
                        return 0;
                    }
                } while (1);
                break; // ���X���h�C���j��A���s�}�l�C��
            }

            // �ˬd�O�_���\���L��ê��
            if (obstaclePos == 4 && ballHeight > 0) {
                if (obstaclePattern == 1 && ballHeight >= 1 && playerInput == '1') {
                    score++; // ��ê�� # �Q���\���L�A��1�~�o��
                }
                else if (obstaclePattern == 2 && ballHeight >= 2 && playerInput == '2') {
                    score++; // ��ê�� ## �Q���\���L�A��2�~�o��
                }
            }

            // ���ʻ�ê��
            obstaclePos--;
            if (obstaclePos < 0) {
                obstaclePos = WIDTH - 1;
                obstaclePattern = (rand() % 2) + 1; // �H���ͦ��s��ê���Ҧ�
            }

            // ø�s�C���e��
            drawGame(ballHeight, obstaclePos, obstaclePattern, elapsedTime, score);

            // ���� (�����C���t��)
            Sleep(100);
        }
    }

    return 0;
}

