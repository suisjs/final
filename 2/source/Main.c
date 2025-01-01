#include <stdio.h>
#include <conio.h>    // �Ω�D������L��J
#include <stdlib.h>    // �Ω��H���ƥͦ��M�t�Υ\��
#include <time.h>      // �Ω�p��
#include <windows.h>   // �Ω� Sleep ���

#define WIDTH 30   // �C���ϰ쪺�e��
#define HEIGHT 10  // �C���ϰ쪺����

// ø�s�C���e�����禡
void drawGame(int ballHeight, int obstaclePos, int obstaclePattern, double elapsedTime, int score) {
    system("cls"); // �M�̡A��s�e��

    // ��ܴ��ܰT���M�C�����A
    printf("\
��1�ɸ��L�@�h��ê�� (#) �i�o��\n");
    printf("��2�ɸ��L��h��ê�� (##) �i�o��\n");
    printf("Time: %.2f s   Score: %d\n", elapsedTime, score);

    // ø�s�C���ϰ�
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y == HEIGHT - ballHeight - 1 && x == 5) {
                printf("O"); // ø�s���a���y
            }
            else if (x == obstaclePos) {
                // �ھڻ�ê���Ҧ�ø�s��ê��
                if (obstaclePattern == 1) {
                    // �@�h��ê�� (#)
                    if (y == HEIGHT - 1) {
                        printf("#");
                    }
                    else {
                        printf(" ");
                    }
                }
                else if (obstaclePattern == 2) {
                    // ��h��ê�� (##)
                    if (y == HEIGHT - 1 || y == HEIGHT - 2) {
                        printf("#");
                    }
                    else {
                        printf(" ");
                    }
                }
            }
            else {
                printf(" "); // �ťճ���
            }
        }
        printf("\n");
    }
}

// �����C�����v���禡
void recordHistory(int gameNumber, double elapsedTime, int score) {
    printf("\n[Game %d] Time: %.2f s   Score: %d\n", gameNumber, elapsedTime, score);
}

int main() {
    int gameNumber = 0; // �����C������

    while (1) {
        // ��l�ƹC���ܼ�
        int ballHeight = 0;         // �y����e����
        int obstaclePos = WIDTH - 1; // ��ê������l��m
        int obstaclePattern = (rand() % 2) + 1; // �H���ͦ���ê���Ҧ��]1: #, 2: ##�^
        int jumping = 0;            // �O�_���b���D
        int jumpHeight = 0;         // ��e���D������
        int jumpTimer = 0;          // ���D�p�ɾ�
        int score = 0;              // ���a����

        // �����C���}�l�ɶ�
        clock_t startTime = clock();
        gameNumber++;

        srand((unsigned int)time(NULL)); // ��l���H���ƥͦ���

        while (1) {
            // �p��C���g�L���ɶ�
            clock_t currentTime = clock();
            double elapsedTime = (double)(currentTime - startTime) / CLOCKS_PER_SEC;

            // �B�z��L��J
            if (_kbhit()) {
                char ch = _getch();
                if (ch == '1') {
                    if (!jumping) {
                        jumping = 1;     // �}�l���D
                        jumpHeight = 1;  // �]�w���D���׬� 1
                        jumpTimer = 6;   // �]�w���D�p�ɾ�
                    }
                }
                else if (ch == '2') {
                    if (!jumping) {
                        jumping = 1;     // �}�l���D
                        jumpHeight = 2;  // �]�w���D���׬� 2
                        jumpTimer = 8;   // �]�w���D�p�ɾ�
                    }
                }
            }

            // ��s���D�޿�
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

            // �ˬd�O�_ Game Over
            if (obstaclePos == 5 && (HEIGHT - ballHeight - 1) >= (HEIGHT - obstaclePattern)) {
                printf("Game Over!\n");
                printf("Total Time: %.2f seconds\n", elapsedTime);
                printf("Your Score: %d\n", score);

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
                if (obstaclePattern == 1 && jumpHeight == 1) {
                    score++; // ��h��ê���Q���\���L
                }
                else if (obstaclePattern == 2 && jumpHeight == 2) {
                    score++; // ���h��ê���Q���\���L
                }
            }

            // ���ʻ�ê��
            obstaclePos--;
            if (obstaclePos < 0) {
                obstaclePos = WIDTH - 1;               // ���m��ê����m
                obstaclePattern = (rand() % 2) + 1;    // �H���ͦ��s��ê���Ҧ�
            }

            // ø�s�C���e��
            drawGame(ballHeight, obstaclePos, obstaclePattern, elapsedTime, score);

            // ����A�����C���t��
            Sleep(100);
        }
    }

    return 0;
}
