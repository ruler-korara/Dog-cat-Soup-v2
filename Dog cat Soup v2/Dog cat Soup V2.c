#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define ROOM_WIDTH 6
#define HOME_POS 0
#define BOWL_POS (ROOM_WIDTH - 1)

int RollDice() {
    return rand() % 6 + 1;
}

void printMainScreen() {
    printf("**** �߿��̿� ���� ****\n\n");
    printf("      /\\_/\\\n");
    printf(" /\\  / o o \\\n");
    printf("//\\\\ \\~(*)~/\n");
    printf("`  \\/   ^ /\n");
    printf("   | \\|| ||\n");
    printf("   \\ '|| ||\n");
    printf("    \\)()-())\n\n");
}

void printState(int soupCount, int intimacy) {
    printf("==================== ���� ���� ====================\n");
    printf("������� ���� ����: %d��\n", soupCount);
    printf("������� ����(0~4): %d\n", intimacy);
    switch (intimacy) {
    case 0: printf("�翡 ���� ������ �Ⱦ��մϴ�.\n"); break;
    case 1: printf("���� ���Ǳ� ����Դϴ�.\n"); break;
    case 2: printf("�׷����� ������ �����Դϴ�.\n"); break;
    case 3: printf("�Ǹ��� ����� ���� �ް� �ֽ��ϴ�.\n"); break;
    case 4: printf("������ �������Դϴ�.\n"); break;
    }
    printf("================================================\n");
}



int main() {
    srand(time(NULL));
    int soupCount = 0;
    int intimacy = 2;
    int choice;
    int catPosition = 0;
    int prevCatPosition = 0;

    printMainScreen();
    printf("�߿����� �̸��� �������Դϴ�.\n");
    Sleep(1000);
    system("cls");

    while (1) {
        Sleep(1000);
        system("cls");

        printState(soupCount, intimacy);

        int moveCat(int catPosition, int intimacy, int prevCatPosition); {
            printf("\n������ �̵�: ����� ģ���Ҽ��� ���� ������ �� Ȯ���� �������ϴ�.\n");
            printf("�ֻ��� ���� %d �̻��̸� ���� ������ �̵��մϴ�.\n", 6 - intimacy);
            printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
            Sleep(500);
            int dice = RollDice();
            Sleep(500);
            printf("%d��(��) ���Խ��ϴ�!\n", dice);

            prevCatPosition = catPosition; // �̵� �� ��ġ ����

            if (dice >= 6 - intimacy) {
                // ������ �̵�
                if (catPosition < BOWL_POS) {
                    (catPosition)++;
                    printf("���� ������ �����Դϴ�.\n");
                }
                else {
                    printf("������ ���� ������ ������ �� �����ϴ�.\n");
                }
            }
            else {
                // ���� �̵�
                if (catPosition > HOME_POS) {
                    (catPosition)--;
                    printf("�� ������ �����Դϴ�.\n");
                }
                else {
                    printf("���� ���� ������ ������ �� �����ϴ�.\n");
                }
            }
        }

        int renderRoom(int catPosition, int prevCatPosition); {
            printf("\n");
            for (int i = 0; i < ROOM_WIDTH + 2; i++) {
                printf("#");
            }
            printf("\n#H");
            for (int i = 0; i < ROOM_WIDTH - 2; i++) {
                printf(" ");
            }
            printf("B#\n");

            printf("#");
            for (int i = 0; i < ROOM_WIDTH; i++) {
                if (i == catPosition) {
                    printf("C");
                }
                else if (prevCatPosition < catPosition && i == catPosition - 1) {
                    printf("."); // ������ �̵� �� ���ʿ� ��
                }
                else if (prevCatPosition > catPosition && i == catPosition + 1) {
                    printf("."); // ���� �̵� �� �����ʿ� ��
                }
                else {
                    printf(" ");
                }
            }
            printf("#\n");

            for (int i = 0; i < ROOM_WIDTH + 2; i++) {
                printf("#");
            }
            printf("\n");
        }

        if (catPosition == HOME_POS) {
            printf("�����̴� �ڽ��� ������ ������� �����ϴ�.\n");
        }

        if (catPosition == BOWL_POS) {
            int soupType = rand() % 3;
            if (soupType == 0) printf("�����̰� ���� ������ ��������ϴ�!\n");
            else if (soupType == 1) printf("�����̰� ����� ������ ��������ϴ�!\n");
            else printf("�����̰� ����ݸ� ������ ��������ϴ�!\n");
            soupCount++;
            printf("������� ���� ����: %d��\n", soupCount);
        }

        printf("\n� ��ȣ�ۿ��� �Ͻðڽ��ϱ�? 0. �ƹ��͵� ���� ���� 1. �ܾ� �ֱ�\n");

        while (1) {
            printf(">> ");
            scanf_s("%d", &choice);
            if (choice == 0 || choice == 1) {
                if (choice == 0) {
                    printf("�ƹ��͵� ���� �ʽ��ϴ�.\n");
                    Sleep(500);
                    printf("4/6�� Ȯ���� ģ�е��� �������ϴ�.\n");
                    Sleep(500);
                    printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
                    Sleep(500);
                    int dice = RollDice();
                    Sleep(500);
                    printf("%d��(��) ���Խ��ϴ�!\n", dice);
                    if (dice <= 4) {
                        intimacy = (intimacy > 0) ? intimacy - 1 : 0;
                        printf("ģ�е��� �������ϴ�.\n");
                    }
                    else {
                        printf("������ ģ�е��� �������� �ʽ��ϴ�.\n");
                    }
                    printf("���� ģ�е�: %d\n", intimacy);
                    break;
                }
                else if (choice == 1) {
                    printf("�������� ���� �ܾ��־����ϴ�.\n");
                    Sleep(500);
                    printf("2/6�� Ȯ���� ģ�е��� �������ϴ�.\n");
                    Sleep(500);
                    printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
                    Sleep(500);
                    int dice = RollDice();
                    Sleep(1000);
                    printf("%d��(��) ���Խ��ϴ�!\n", dice);
                    if (dice >= 5) {
                        intimacy = (intimacy < 4) ? intimacy + 1 : 4;
                        printf("ģ�е��� �������ϴ�.\n");
                    }
                    else {
                        printf("ģ�е��� �״���Դϴ�.\n");
                    }
                    printf("���� ģ�е�: %d\n", intimacy);
                    Sleep(1000);
                    break;
                }
            }
            else {

            }
        }
    }
}
