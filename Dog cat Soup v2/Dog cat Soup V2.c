#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <locale.h>

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
	setlocale(LC_ALL, "korean");
	SetConsoleOutputCP(65001);
	
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
    int turnCount = 0;
    int questDone = 0;

    printMainScreen();
    printf("야옹이의 이름은 개냥이입니다.\n");
    Sleep(1000);
    system("cls");

    while (1) {
        if (turnCount == 4 && questDone == 0) {
            int choice;
            beforeMood = mood;

            printf("\n[돌발 퀘스트] 고양이 운세 돌리기!\n");
            printf("개냥이의 운세를 확인하려면 1을 입력하세요: ");

            while (1) {
                scanf_s("%d", &choice);
                if (choice == 1) break;
            }

            int fortune = rand() % 3;

            if (fortune == 0) {
                if (mood > 0) mood--;
                printf("흉입니다... 기분이 나빠졌습니다: %d -> %d\n", beforeMood, mood);
            }
            else if (fortune == 1) {
                printf("보통입니다. 기분은 그대로입니다: %d\n", mood);
            }
            else {
                if (mood < 3) mood++;
                printf("대길입니다! 기분이 좋아졌습니다: %d -> %d\n", beforeMood, mood);
            }

            questDone = 1;

            continue;
        }

        while (1) {
            Sleep(1000);
            system("cls");


            printState(soupCount, intimacy, cp, mood);

            int moveCat(int catPosition, int intimacy, int prevCatPosition); {
                printf("\n6-2: 주사위 눈이 %d이하면 그냥 기분이 나빠집니다.\n", 6 - intimacy);
                printf("주사위를 굴립니다. 또르륵...\n");
                Sleep(500);
                int dice = RollDice();
                Sleep(500);
                if (dice <= 6 - intimacy) {
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

                for (int i = 0; i < ROOM_WIDTH + 2; i++) printf("#");
                printf("\n");

                printf("#");
                for (int i = 0; i < ROOM_WIDTH; i++) {
                    if (i == HOME_POS) printf("H");
                    else if (i == BOWL_POS) printf("B");
                    else if (hasScratcher == 1 && i == SCR_POS && SCR_POS != -1) printf("S");
                    else if (hasTower == 1 && i == TWR_POS && TWR_POS != -1) printf("T");
                    else printf(" ");
                }

                printf("#\n");
                printf("#");
                for (int i = 0; i < ROOM_WIDTH; i++) {
                    if (i == catPosition) printf("C");
                    else if (i == prevCatPosition && catPosition != prevCatPosition) printf(".");
                    else printf(" ");
                }
                printf("#\n");

                for (int i = 0; i < ROOM_WIDTH + 2; i++) printf("#");
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

                    if (dice <= 5) {
                        if (intimacy > 0) {
                            intimacy = intimacy - 1;
                            printf("개냥이와의 관계가 나빠집니다.\n");
                        }
                    }
                }
                else if (choice == 1) {
                    printf("개냥이의 기분은 그대로 입니다.\n");

                    if (dice >= 5) {
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

                    if (dice >= 4) {
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

                int produce = 0;
                if (mood > 0) {
                    produce = (mood - 1) + intimacy;
                }
                else {
                    produce = intimacy;
                }
                cp = cp + produce;

                printf("개냥이의 기분과 친밀도에 따라서 CP가 %d 포인트 생산되었습니다.\n", produce);
                printf("보유 CP: %d 포인트\n", cp);

                int shopChoice;
                while (1) {
                    printf("\n상점에서 물건을 살 수 있습니다.\n");
                    printf("어떤 물건을 구매할까요?\n");
                    printf("0. 아무것도 구매하지 않는다.\n");

                    printf(" 1. 장난감 쥐: 1 CP");
                    if (toyMouse == 1) printf(" (품절)");
                    printf("\n");

                    printf(" 2. 레이저 포인터: 2 CP");
                    if (toyLaser == 1) printf(" (품절)");
                    printf("\n");

                    printf(" 3. 스크래처: 4 CP");
                    if (hasScratcher == 1) printf(" (품절)");
                    printf("\n");

                    printf(" 4. 캣타워: 6 CP");
                    if (hasTower == 1) printf(" (품절)");
                    printf("\n");

                    printf(">> ");
                    scanf_s("%d", &shopChoice);

                    if (shopChoice < 0 || shopChoice > 4) continue;

                    if (shopChoice == 0) break;

                    if ((shopChoice == 1 && toyMouse == 1) || (shopChoice == 2 && toyLaser == 1) || (shopChoice == 3 && hasScratcher == 1) || (shopChoice == 4 && hasTower == 1)) {
                        printf("이미 구매한 물건입니다.\n");
                        continue;
                    }

                    int cost = 0;
                    if (shopChoice == 1) cost = 1;
                    if (shopChoice == 2) cost = 2;
                    if (shopChoice == 3) cost = 4;
                    if (shopChoice == 4) cost = 6;

                    if (cp < cost) {
                        printf("CP가 부족합니다.\n");
                        continue;
                    }

                    cp = cp - cost;

                    if (shopChoice == 1) {
                        toyMouse = 1;
                        printf("장난감 쥐를 구매했습니다.\n");
                    }
                    else if (shopChoice == 2) {
                        toyLaser = 1;
                        printf("레이저 포인터를 구매했습니다.\n");
                    }
                    else if (shopChoice == 3) {
                        hasScratcher = 1;
                        printf("스크래처를 구매했습니다.\n");
                        while (1) {
                            int pos = rand() % (ROOM_WIDTH - 2) + 1;
                            if (pos != HOME_POS && pos != BOWL_POS && pos != SCR_POS && pos != catPosition) {
                                SCR_POS = pos;
                                break;
                            }
                        }
                    }
                    else if (shopChoice == 4) {
                        hasTower = 1;
                        printf("캣타워를 구매했습니다.\n");
                        while (1) {
                            int pos = rand() % (ROOM_WIDTH - 2) + 1;
                            if (pos != HOME_POS && pos != BOWL_POS && pos != TWR_POS && pos != catPosition && pos != SCR_POS) {
                                TWR_POS = pos;
                                break;
                            }
						}
                    }
                    break;
                }
                printf("현재 친밀도: %d\n", intimacy);
                turnCount++;
            }
        }
        return 0;
    }
}
