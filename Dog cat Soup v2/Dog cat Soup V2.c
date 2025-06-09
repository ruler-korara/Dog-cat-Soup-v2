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
    printf("**** 야옹이와 수프 ****\n\n");
    printf("      /\\_/\\\n");
    printf(" /\\  / o o \\\n");
    printf("//\\\\ \\~(*)~/\n");
    printf("`  \\/   ^ /\n");
    printf("   | \\|| ||\n");
    printf("   \\ '|| ||\n");
    printf("    \\)()-())\n\n");
}

void printState(int soupCount, int intimacy) {
    printf("==================== 현재 상태 ====================\n");
    printf("현재까지 만든 수프: %d개\n", soupCount);
    printf("집사와의 관계(0~4): %d\n", intimacy);
    switch (intimacy) {
    case 0: printf("곁에 오는 것조차 싫어합니다.\n"); break;
    case 1: printf("간식 자판기 취급입니다.\n"); break;
    case 2: printf("그럭저럭 쓸만한 집사입니다.\n"); break;
    case 3: printf("훌륭한 집사로 인정 받고 있습니다.\n"); break;
    case 4: printf("집사의 껌딱지입니다.\n"); break;
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
    printf("야옹이의 이름은 개냥이입니다.\n");
    Sleep(1000);
    system("cls");

    while (1) {
        Sleep(1000);
        system("cls");

        printState(soupCount, intimacy);

        int moveCat(int catPosition, int intimacy, int prevCatPosition); {
            printf("\n개냥이 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n");
            printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", 6 - intimacy);
            printf("주사위를 굴립니다. 또르륵...\n");
            Sleep(500);
            int dice = RollDice();
            Sleep(500);
            printf("%d이(가) 나왔습니다!\n", dice);

            prevCatPosition = catPosition; // 이동 전 위치 저장

            if (dice >= 6 - intimacy) {
                // 오른쪽 이동
                if (catPosition < BOWL_POS) {
                    (catPosition)++;
                    printf("냄비 쪽으로 움직입니다.\n");
                }
                else {
                    printf("오른쪽 벽에 막혀서 움직일 수 없습니다.\n");
                }
            }
            else {
                // 왼쪽 이동
                if (catPosition > HOME_POS) {
                    (catPosition)--;
                    printf("집 쪽으로 움직입니다.\n");
                }
                else {
                    printf("왼쪽 벽에 막혀서 움직일 수 없습니다.\n");
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
                    printf("."); // 오른쪽 이동 시 왼쪽에 점
                }
                else if (prevCatPosition > catPosition && i == catPosition + 1) {
                    printf("."); // 왼쪽 이동 시 오른쪽에 점
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
            printf("개냥이는 자신의 집에서 편안함을 느낍니다.\n");
        }

        if (catPosition == BOWL_POS) {
            int soupType = rand() % 3;
            if (soupType == 0) printf("개냥이가 감자 수프를 만들었습니다!\n");
            else if (soupType == 1) printf("개냥이가 양송이 수프를 만들었습니다!\n");
            else printf("개냥이가 브로콜리 수프를 만들었습니다!\n");
            soupCount++;
            printf("현재까지 만든 수프: %d개\n", soupCount);
        }

        printf("\n어떤 상호작용을 하시겠습니까? 0. 아무것도 하지 않음 1. 긁어 주기\n");

        while (1) {
            printf(">> ");
            scanf_s("%d", &choice);
            if (choice == 0 || choice == 1) {
                if (choice == 0) {
                    printf("아무것도 하지 않습니다.\n");
                    Sleep(500);
                    printf("4/6의 확률로 친밀도가 떨어집니다.\n");
                    Sleep(500);
                    printf("주사위를 굴립니다. 또르륵...\n");
                    Sleep(500);
                    int dice = RollDice();
                    Sleep(500);
                    printf("%d이(가) 나왔습니다!\n", dice);
                    if (dice <= 4) {
                        intimacy = (intimacy > 0) ? intimacy - 1 : 0;
                        printf("친밀도가 떨어집니다.\n");
                    }
                    else {
                        printf("다행히 친밀도가 떨어지지 않습니다.\n");
                    }
                    printf("현재 친밀도: %d\n", intimacy);
                    break;
                }
                else if (choice == 1) {
                    printf("개냥이의 턱을 긁어주었습니다.\n");
                    Sleep(500);
                    printf("2/6의 확률로 친밀도가 높아집니다.\n");
                    Sleep(500);
                    printf("주사위를 굴립니다. 또르륵...\n");
                    Sleep(500);
                    int dice = RollDice();
                    Sleep(1000);
                    printf("%d이(가) 나왔습니다!\n", dice);
                    if (dice >= 5) {
                        intimacy = (intimacy < 4) ? intimacy + 1 : 4;
                        printf("친밀도가 높아집니다.\n");
                    }
                    else {
                        printf("친밀도는 그대로입니다.\n");
                    }
                    printf("현재 친밀도: %d\n", intimacy);
                    Sleep(1000);
                    break;
                }
            }
            else {

            }
        }
    }
}
