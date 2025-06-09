#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define ROOM_WIDTH 10
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

void printState(int soupCount, int intimacy, int cp, int mood) {
    printf("==================== ���� ���� ====================\n");
    printf("������� ���� ����: %d��\n", soupCount);
	printf("CP: %d ����Ʈ\n", cp);
    printf("������ ���(0~3): %d\n", mood);
    switch (mood) {
    case 0: printf("����� �ſ� ���޴ϴ�.\n"); break;
    case 1: printf("�ɽ����մϴ�.\n"); break;
	case 2: printf("�Ļ��� �����ϴ�.\n"); break;
	case 3: printf("������ �θ��ϴ�.\n"); break;
    }
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
    int cp = 0;
    int mood = 3;
    int hasScratcher = 0;
    int hasTower = 0;
    int SCR_POS = -1;
	int TWR_POS = -1;
    int toyMouse = 0;
    int toyLaser = 0;
    int beforeMood = mood;
    int beforeInimacy = intimacy;

    printMainScreen();
    printf("�߿����� �̸��� �������Դϴ�.\n");
    Sleep(1000);
    system("cls");

    while (1) {
        Sleep(1000);
        system("cls");

        printState(soupCount, intimacy, cp, mood);

        int moveCat(int catPosition, int intimacy, int prevCatPosition); {
            printf("\n6-2: �ֻ��� ���� %d���ϸ� �׳� ����� �������ϴ�.\n" ,6-intimacy);
            printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
            Sleep(500);
            int dice = RollDice();
            Sleep(500);
            if(dice<= 6 - intimacy) {
                printf("%d��(��) ���Խ��ϴ�!\n", dice);
                mood = (mood > 0) ? mood - 1 : 0;
                printf("�������� ����� �������ϴ�.\n");
                mood--;
            }

			prevCatPosition = catPosition;

            if (mood == 0) {
                if (catPosition > HOME_POS) {
                    catPosition = catPosition - 1;
                    printf("����� �ſ� ���� �˶��� ������ ���ư��ϴ�.\n");
                }
            }
            else if (mood == 1) {
                if (hasScratcher == 1 || hasTower == 1) {
                    int distScratcher = ROOM_WIDTH - 2;
                    int distTower = ROOM_WIDTH - 2;

                    if (hasScratcher == 1) {
                        if (SCR_POS > catPosition)  distScratcher = SCR_POS - catPosition;
                        else distScratcher = catPosition - SCR_POS;
                    }
                    if (hasTower == 1) {
                        if (TWR_POS > catPosition) distTower = TWR_POS - catPosition;
                        else distTower = catPosition - TWR_POS;
                    }

                    int target;
                    if (distScratcher <= distTower) target = SCR_POS;
                    else target = TWR_POS;

                    if (catPosition < target) catPosition = catPosition + 1;
                    else if (catPosition > target) catPosition = catPosition - 1;

                    if (target == SCR_POS) printf("�����̴� �ɽ��ؼ� ��ũ��ó ������ �̵��մϴ�.\n");
                    else printf("�����̴� �ɽ��ؼ� ĹŸ�� ������ �̵��մϴ�.\n");
                }
                else {
                    mood = mood - 1;
                    printf("�� �Ÿ��� ��� ����� �ſ� �������ϴ�.\n");
                }
            }
            else if (mood == 2) {
                printf("�����̴� ������� �Ļ��� ���� �ֽ��ϴ�.\n");
            }
            else if (mood == 3) {
                if (catPosition < BOWL_POS) {
                    catPosition = catPosition + 1;
                    printf("�����̴� ������ �θ��� ������ ���鷯 ���ϴ�.\n");
                }
            }
            if (catPosition == HOME_POS && prevCatPosition == HOME_POS) {
                if (mood < 3) {
                    mood = mood + 1;
                    printf("�����̴� ������ �޽��� ���ϸ� ����� ���������ϴ�.\n");
                }
            }
            else if (catPosition == BOWL_POS && prevCatPosition == BOWL_POS) {
                int soupType = rand() % 3;
                if (soupType == 0) printf("�����̰� ���� ������ ��������ϴ�!\n");
                else if (soupType == 1) printf("�����̰� ����� ������ ��������ϴ�!\n");
                else printf("�����̰� ����ݸ� ������ ��������ϴ�!\n");
                soupCount++;
                printf("������� ���� ����: %d��\n", soupCount);
            }
            else if (hasScratcher == 1 && SCR_POS != -1 && catPosition == SCR_POS && prevCatPosition != SCR_POS) {
                if (mood < 3) mood++;
                printf("�����̰� ��ũ��ó�� �ܰ� ��ҽ��ϴ�.\n");
            }
            else if (hasTower == 1 && TWR_POS != -1 && catPosition == TWR_POS && prevCatPosition != TWR_POS) {
                if (mood <= 1) mood += 2;
                else mood = 3;
                printf("�����̰� ĹŸ���� �پ�ٴմϴ�.\n");
            }

            for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
            printf("\n");

            printf("#");
            for(int i = 1; i<ROOM_WIDTH - 1; i++) {
                if (i == HOME_POS) printf("H");
                else if (i == BOWL_POS) printf("B");
                else if (hasScratcher == 1 && i == SCR_POS && SCR_POS != -1) printf("S");
                else if (hasTower == 1 && i == TWR_POS && TWR_POS != -1) printf("T");
                else printf(" ");
			}

            printf("#\n");
			printf("#");
            for (int i = 1; i < ROOM_WIDTH - 1; i++) {
                if (i == catPosition) printf("C");
                else if (i == prevCatPosition && catPosition != prevCatPosition) printf(".");
                else printf(" ");
            }
            printf("#\n");

            for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
            printf("\n\n");

            int optionCount = 2;
			printf("\n� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?\n");
            printf("0. �ƹ��͵� ���� �ʱ�\n");
            printf("1. �ܾ� �ֱ�\n");

            if (toyMouse == 1 && toyLaser == 1) {
                printf("2. �峭�� ��� ��� �ֱ�\n");
                printf("3. ������ �����ͷ� ��� �ֱ�\n");
                optionCount = 4;
            }
            else if (toyMouse == 1) {
                printf("2. �峭�� ��� ��� �ֱ�\n");
                optionCount = 3;
            }
            else if (toyLaser == 1) {
                printf("2. ������ �����ͷ� ��� �ֱ�\n");
                optionCount = 3;
			}

			beforeMood = mood;
            beforeInimacy = intimacy;

            while (1) {
                printf(">> ");
                scanf_s("%d", &choice);
                if (choice >= 0 && choice < optionCount) break;
			}

            if (choice == 0) {
                if (mood > 0) {
                    mood = mood - 1;
                    printf("�������� ����� ���������ϴ�: %d -> %d\n", beforeMood, mood);
                }

                if (RollDice <= 5) {
                    if (intimacy > 0) {
                        intimacy = intimacy - 1;
                        printf("�����̿��� ���谡 �������ϴ�.\n");
                    }
                }
            }
            else if (choice == 1) {
                printf("�������� ����� �״�� �Դϴ�.\n");

                if (RollDice >= 5) {
                    if (intimacy < 4) {
                        intimacy = intimacy + 1;
                        printf("������� ���谡 ������ϴ�.\n");
                    }
                }
            }
            else if (choice == 2) {
                if (mood < 3) {
                    mood = mood + 1;
                }
                printf("�峭�� ��� ����־����ϴ�. �������� ����� ���� ���������ϴ�: %d -> %d\n", beforeMood, mood);

                if (RollDice >= 4) {
                    if (intimacy < 4) {
                        intimacy = intimacy + 1;
                        printf("������� ���谡 ������ϴ�.\n");
                    }
                }
            }
            else if (choice == 3) {
                if (mood <= 1) {
                    mood = mood + 2;
                }
                else {
                    mood = 3;
                }
                printf("������ �����ͷ� �ų��� ��� �־����ϴ�. �������� ����� �� ���������ϴ�: %d -> %d\n", beforeMood, mood);

                if (dice >= 2) {
                    if (intimacy < 4) {
                        intimacy = intimacy + 1;
                        printf("������� ���谡 ������ϴ�.\n");
                    }
                }
            }

            }
       
        }
    }
}
