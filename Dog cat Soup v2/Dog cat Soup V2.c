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
    printf("**** 야옹이와 수프 ****\n\n");
    printf("      /\\_/\\\n");
    printf(" /\\  / o o \\\n");
    printf("//\\\\ \\~(*)~/\n");
    printf("`  \\/   ^ /\n");
    printf("   | \\|| ||\n");
    printf("   \\ '|| ||\n");
    printf("    \\)()-())\n\n");
}

void printState(int soupCount, int intimacy, int cp, int mood) {
    printf("==================== 현재 상태 ====================\n");
    printf("현재까지 만든 수프: %d개\n", soupCount);
	printf("CP: %d 포인트\n", cp);
    printf("개냥이 기분(0~3): %d\n", mood);
    switch (mood) {
    case 0: printf("기분이 매우 나쁩니다.\n"); break;
    case 1: printf("심심해합니다.\n"); break;
	case 2: printf("식빵을 굽습니다.\n"); break;
	case 3: printf("골골송을 부릅니다.\n"); break;
    }
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
    printf("야옹이의 이름은 개냥이입니다.\n");
    Sleep(1000);
    system("cls");

    while (1) {
        Sleep(1000);
        system("cls");

        printState(soupCount, intimacy, cp, mood);

        int moveCat(int catPosition, int intimacy, int prevCatPosition); {
            printf("\n6-2: 주사위 눈이 %d이하면 그냥 기분이 나빠집니다.\n" ,6-intimacy);
            printf("주사위를 굴립니다. 또르륵...\n");
            Sleep(500);
            int dice = RollDice();
            Sleep(500);
            if(dice<= 6 - intimacy) {
                printf("%d이(가) 나왔습니다!\n", dice);
                mood = (mood > 0) ? mood - 1 : 0;
                printf("개냥이의 기분이 나빠집니다.\n");
                mood--;
            }

			prevCatPosition = catPosition;

            if (mood == 0) {
                if (catPosition > HOME_POS) {
                    catPosition = catPosition - 1;
                    printf("기분이 매우 나쁜 쫀떡은 집으로 돌아갑니다.\n");
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

                    if (target == SCR_POS) printf("개냥이는 심심해서 스크래처 쪽으로 이동합니다.\n");
                    else printf("개냥이는 심심해서 캣타워 쪽으로 이동합니다.\n");
                }
                else {
                    mood = mood - 1;
                    printf("놀 거리가 없어서 기분이 매우 나빠집니다.\n");
                }
            }
            else if (mood == 2) {
                printf("개냥이는 기분좋게 식빵을 굽고 있습니다.\n");
            }
            else if (mood == 3) {
                if (catPosition < BOWL_POS) {
                    catPosition = catPosition + 1;
                    printf("개냥이는 골골송을 부르며 수프를 만들러 갑니다.\n");
                }
            }
            if (catPosition == HOME_POS && prevCatPosition == HOME_POS) {
                if (mood < 3) {
                    mood = mood + 1;
                    printf("개냥이는 집에서 휴식을 취하며 기분이 좋아졌습니다.\n");
                }
            }
            else if (catPosition == BOWL_POS && prevCatPosition == BOWL_POS) {
                int soupType = rand() % 3;
                if (soupType == 0) printf("개냥이가 감자 수프를 만들었습니다!\n");
                else if (soupType == 1) printf("개냥이가 양송이 수프를 만들었습니다!\n");
                else printf("개냥이가 브로콜리 수프를 만들었습니다!\n");
                soupCount++;
                printf("현재까지 만든 수프: %d개\n", soupCount);
            }
            else if (hasScratcher == 1 && SCR_POS != -1 && catPosition == SCR_POS && prevCatPosition != SCR_POS) {
                if (mood < 3) mood++;
                printf("개냥이가 스크래처를 긁고 놀았습니다.\n");
            }
            else if (hasTower == 1 && TWR_POS != -1 && catPosition == TWR_POS && prevCatPosition != TWR_POS) {
                if (mood <= 1) mood += 2;
                else mood = 3;
                printf("개냥이가 캣타워를 뛰어다닙니다.\n");
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
			printf("\n어떤 상호작용을 하시겠습니까?\n");
            printf("0. 아무것도 하지 않기\n");
            printf("1. 긁어 주기\n");

            if (toyMouse == 1 && toyLaser == 1) {
                printf("2. 장난감 쥐로 놀아 주기\n");
                printf("3. 레이저 포인터로 놀아 주기\n");
                optionCount = 4;
            }
            else if (toyMouse == 1) {
                printf("2. 장난감 쥐로 놀아 주기\n");
                optionCount = 3;
            }
            else if (toyLaser == 1) {
                printf("2. 레이저 포인터로 놀아 주기\n");
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
                    printf("개냥이의 기분이 나빠졌습니다: %d -> %d\n", beforeMood, mood);
                }

                if (RollDice <= 5) {
                    if (intimacy > 0) {
                        intimacy = intimacy - 1;
                        printf("개냥이와의 관계가 나빠집니다.\n");
                    }
                }
            }
            else if (choice == 1) {
                printf("개냥이의 기분은 그대로 입니다.\n");

                if (RollDice >= 5) {
                    if (intimacy < 4) {
                        intimacy = intimacy + 1;
                        printf("집사와의 관계가 깊어집니다.\n");
                    }
                }
            }
            else if (choice == 2) {
                if (mood < 3) {
                    mood = mood + 1;
                }
                printf("장난감 쥐로 놀아주었습니다. 개냥이의 기분이 조금 좋아졌습니다: %d -> %d\n", beforeMood, mood);

                if (RollDice >= 4) {
                    if (intimacy < 4) {
                        intimacy = intimacy + 1;
                        printf("집사와의 관계가 깊어집니다.\n");
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
                printf("레이저 포인터로 신나게 놀아 주었습니다. 개냥이의 기분이 꽤 좋아졌습니다: %d -> %d\n", beforeMood, mood);

                if (dice >= 2) {
                    if (intimacy < 4) {
                        intimacy = intimacy + 1;
                        printf("집사와의 관계가 깊어집니다.\n");
                    }
                }
            }

            }
       
        }
    }
}
