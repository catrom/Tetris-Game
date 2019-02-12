#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include "console.h"
#include "Func.h"
#include "Gameplay.h"

#define LEFT    8
#define TOP     3
#define MRow    21
#define MCol    11
#define Odd     178
#define Even    177

bool cnt = 0;
int Status[21][11];
int Color[21][11];

bool EnterName(Player *pplay) {
    AddBorder();
    TextColor(10);
    gotoXY(54, 24); printf("Enter Your Name");
    TextColor(14);
    gotoXY(33, 34); printf("ESC to Back to Menu\t\t\tENTER to Continue");
    while(!kbhit()) {
        TextColor(0); gotoXY(54, 26); printf("\\> "); Sleep(200);
        TextColor(10); gotoXY(54, 26); printf("\\> "); Sleep(600);
    }
    int i = 0;
    do {
        char c = getch();
        TextColor(0); gotoXY(57, 26); printf("%s", pplay->name);
        if(c == 27) {
            if(pplay->name[strlen(pplay->name) - 1] == '\n') pplay->name[strlen(pplay->name) - 1] == '\0';
            EraseBorder();
            return 0;
        }
        else if(c == 13) {
            pplay->name[i] = '\0';
            EraseBorder();
            return 1;
        }
        else if(c == 8 && i > 0) {
            pplay->name[--i] = '\0';
        }
        else {
            pplay->name[i++] = c;
        }
        TextColor(12); gotoXY(57, 26); printf("%s", pplay->name);
    } while(1);
}

void DrawBorder() {
    clrscr();
    int i, j;
    int a = 10, b = 13, c = 5, t = 15;
    for (i = 53/2; i >= 0; i--) {
        if (i > 0) {
            TextColor(a);
            gotoXY(3 + i, 2); putchar(205);
            gotoXY(56 - i, 2); putchar(205);
            gotoXY(3 + i, 39); putchar(205);
            gotoXY(56 - i, 39); putchar(205);
        }
        else {
            TextColor(a);
            gotoXY(3, 2); putchar(200);
            gotoXY(56, 2); putchar(188);
            gotoXY(3, 39); putchar(201);
            gotoXY(56, 39); putchar(187);
        }
        if (i > 2) {
            TextColor(b);
            gotoXY(3 + i, 1); putchar(205);
            gotoXY(56 - i, 1); putchar(205);
            gotoXY(3 + i, 40); putchar(205);
            gotoXY(56 - i, 40); putchar(205);
        }
        Sleep(t);
    }
    gotoXY(3, 1); putchar(186);
    gotoXY(56, 1); putchar(186);
    gotoXY(3, 40); putchar(186);
    gotoXY(56, 40); putchar(186);
    Sleep(t);
    gotoXY(3, 0); putchar(201);
    gotoXY(56, 0); putchar(187);
    gotoXY(3, 41); putchar(200);
    gotoXY(56, 41); putchar(188);
    Sleep(t);
    gotoXY(4, 0); putchar(205);
    gotoXY(5, 0); putchar(205);
    gotoXY(6, 0); putchar(205);
    gotoXY(55, 0); putchar(205);
    gotoXY(54, 0); putchar(205);
    gotoXY(53, 0); putchar(205);
    gotoXY(4, 41); putchar(205);
    gotoXY(5, 41); putchar(205);
    gotoXY(6, 41); putchar(205);
    gotoXY(55, 41); putchar(205);
    gotoXY(54, 41); putchar(205);
    gotoXY(53, 41); putchar(205);
    Sleep(t);
    gotoXY(7, 0); putchar(187);
    gotoXY(52, 0); putchar(201);
    gotoXY(7, 41); putchar(188);
    gotoXY(52, 41); putchar(200);
    TextColor(b);
    gotoXY(5, 1); putchar(201);
    gotoXY(54, 1); putchar(187);
    gotoXY(5, 40); putchar(200);
    gotoXY(54, 40); putchar(188);
    Sleep(t);
    for (i = 1; i <= 41/2; i++) {
        TextColor(a);
        gotoXY(7, i); putchar(186);
        gotoXY(52, i); putchar(186);
        gotoXY(7, 41-i); putchar(186);
        gotoXY(52, 41 - i); putchar(186);
        if (i >= 2) {
            TextColor(b);
            gotoXY(5, i); putchar(186);
            gotoXY(5, 41 - i); putchar(186);
            if (i < 19) {
                gotoXY(54, i); putchar(186);
                gotoXY(54, 41 - i); putchar(186);
            }
            if (i == 19) {
                gotoXY(54, 41 - i); putchar(186);
            }
        }
        Sleep(t);
    }

    TextColor(b);
    gotoXY(54, 19); putchar(200);
    gotoXY(54, 21); putchar(201);
    Sleep(t);
    //-----------
    char s[] = "TETRIS";
    for(i = 55; i <= 70; i++) {
        TextColor(b);
        gotoXY(i, 19); putchar(205);
        gotoXY(i, 21); putchar(205);
        if(57 <= i && i <= 67 && i%2 == 1) {
            int color = 10 + rand() % 6;
            TextColor(color);
            gotoXY(i, 20); printf("%c", s[(i-57) / 2]);
        }
        Sleep(t);
    }
    gotoXY(71, 19); putchar(188);
    gotoXY(71, 21); putchar(187);
    Sleep(t);
    //------------
    for(i = 0; i < 19; i++) {
        TextColor(b);
        gotoXY(71, 20 - i); putchar(219);
        gotoXY(71, 21 + i); putchar(219);
        TextColor(c);
        gotoXY(72, 20 - i); putchar(219);
        gotoXY(72, 21 + i); putchar(219);
        Sleep(t);
    }

    TextColor(c);
    //---------------
    gotoXY(73, 6); putchar(219);
    gotoXY(73, 20); putchar(219);
    gotoXY(73, 35); putchar(219); Sleep(t);
    for(i = 74; i <= 76; i++) {
        gotoXY(i, 6); putchar(254);
        gotoXY(i, 20); putchar(254);
        gotoXY(i, 35); putchar(254); Sleep(t);
    }
    gotoXY(77, 6); putchar(219);
    gotoXY(77, 20); putchar(219);
    gotoXY(77, 35); putchar(219); Sleep(t);
//----------
    TextColor(15);
    for(i = 1; i <= 11; i++) {
        for(j = 78; j <= 115; j++) {
            if((i == 1 || i == 11) && (j != 78 || j != 115)) {
                gotoXY(j, i); putchar(254);
            }
            else if(j == 78 || j == 115) {
                gotoXY(j, i); putchar(219);
            }
        }
    }
    Sleep(t + 200);
    for(i = 14; i <= 27; i++) {
        for(j = 78; j <= 115; j++) {
            if((i == 14 || i == 27) && (j != 78 || j != 115)) {
                gotoXY(j, i); putchar(254);
            }
            else if(j == 78 || j == 115) {
                gotoXY(j, i); putchar(219);
            }
        }
    }
    Sleep(t + 200);
    for(i = 30; i <= 40; i++) {
        for(j = 78; j <= 115; j++) {
            if((i == 30 || i == 40) && (j != 78 || j != 115)) {
                gotoXY(j, i); putchar(254);
            }
            else if(j == 78 || j == 115) {
                gotoXY(j, i); putchar(219);
            }
        }
    }
    Sleep(t + 200);
}

void Display() {
	int i, j;
	for (i = TOP; i < MRow; i++) {
		for (j = 0; j < MCol; j++) {
			if (Status[i][j]) {
				TextColor(Color[i][j]);
				if (i%2 - j%2) {
                    gotoXY(4*j + LEFT, 2*i - TOP); printf("%c%c%c%c", Odd, Odd, Odd, Odd);
                    gotoXY(4*j + LEFT, 2*i + 1 - TOP); printf("%c%c%c%c", Odd, Odd, Odd, Odd);
                }
                else {
                    gotoXY(4*j + LEFT, 2*i - TOP); printf("%c%c%c%c", Even, Even, Even, Even);
                    gotoXY(4*j + LEFT, 2*i + 1 - TOP); printf("%c%c%c%c", Even, Even, Even, Even);
                }
			}
			else {
				TextColor(0);
				gotoXY(4*j + LEFT, 2*i - TOP); printf("%c%c%c%c", Even, Even, Even, Even);
				gotoXY(4*j + LEFT, 2*i + 1 - TOP); printf("%c%c%c%c", Even, Even, Even, Even);
			}
		}
	}
}

int BlockType() {
    int x = rand() % 7;
    switch(x) {
        case 0: return 15; break;
        case 1: return 31; break;
        case 2: return 51; break;
        case 3: return 30; break;
        case 4: return 58; break;
        case 5: return 57; break;
        case 6: return 60; break;
    }
}

int Inside (int i, int j) {
    return i < MRow && j < MCol;
}

int Left (int i, int j) {
    return Inside(i, j) && j > 0 && !Status[i][j-1];
}

int Right (int i, int j) {
    return j < MCol - 1 && Inside(i, j) && !Status[i][j+1];
}

int Down (int i, int j) {
    return i < MRow - 1 && Inside(i, j) && !Status[i+1][j];
}

void LeftMove (block *pblock) {
    int i, j;
    for(i = 0; i < (*pblock).Row; i++)
        for(j = 0; j < (*pblock).Col; j++)
            if ((*pblock).arr[i][j])
                if (!Left((*pblock).SRow + i, (*pblock).SCol + j)) return;
    (*pblock).SCol -= 1;
}

void RightMove (block *pblock) {
    int i, j;
    for(i = 0; i < (*pblock).Row; i++)
        for(j = 0; j < (*pblock).Col; j++)
            if ((*pblock).arr[i][j])
                if (!Right((*pblock).SRow + i, (*pblock).SCol + j)) return;
    (*pblock).SCol += 1;
}

bool DownMove (block *pblock) {
    int i, j;
    for(i = 0; i < (*pblock).Row; i++)
        for(j = 0; j < (*pblock).Col; j++)
            if ((*pblock).arr[i][j])
                if (!Down((*pblock).SRow + i, (*pblock).SCol + j)) return 0;
    (*pblock).SRow += 1;
    return 1;
}

void BlockTurning (block *pblock) {
    int i, j;
    int **tarr;
    int tRow = (*pblock).Col, tCol = (*pblock).Row;
    tarr = (int**) malloc (tRow * sizeof(int*));
    for(i = 0; i < tRow; i++)
        tarr[i] = (int*) malloc (tCol * sizeof(int));
    for(i = 0; i < tRow; i++)
        for(j = 0; j < tCol; j++)
            tarr[i][j] = (*pblock).arr[(*pblock).Row-1-j][i];
    for(i = 0; i < tRow; i++)
        for(j = 0; j < tCol; j++)
            if(!Inside((*pblock).SRow + i, (*pblock).SCol + j) || Status[(*pblock).SRow + i][(*pblock).SCol + j])
                return;

    for(i = 0; i < (*pblock).Row; i++)
        free((*pblock).arr[i]);
    free((*pblock).arr);
    (*pblock).Col = tCol;
    (*pblock).Row = tRow;
    (*pblock).arr = tarr;
}

void DrawBlock (block *pblock, int color) {
    int i, j;
    for (i = 0; i < (*pblock).Row; i++) {
        for (j = 0; j < (*pblock).Col; j++) {
            if ((*pblock).arr[i][j] && (*pblock).SRow > TOP - i) {
                TextColor(color);
                if (i%2 - j%2) {
                    gotoXY(LEFT + 4 * ((*pblock).SCol + j), 2 * ((*pblock).SRow +  i) - TOP - 1);
                    printf("%c%c%c%c", Odd, Odd, Odd, Odd);
                    gotoXY(LEFT + 4 * ((*pblock).SCol + j), 2 * ((*pblock).SRow +  i) - TOP - 2);
                    printf("%c%c%c%c", Odd, Odd, Odd, Odd);
                }
                else {
                    gotoXY(LEFT + 4 * ((*pblock).SCol + j), 2 * ((*pblock).SRow +  i) - TOP - 1);
                    printf("%c%c%c%c", Even, Even, Even, Even);
                    gotoXY(LEFT + 4 * ((*pblock).SCol + j), 2 * ((*pblock).SRow +  i) - TOP - 2);
                    printf("%c%c%c%c", Even, Even, Even, Even);
                }
            }
        }
    }
}

void EraseBlock (block *pblock) {
    DrawBlock(pblock, 0);
}

block *BlockBuilding (int ID) {
    block *pblock = (block*) malloc (sizeof(block));
    switch(ID) {
        case 15:
            (*pblock).Row  = 4;
            (*pblock).Col  = 1;
            (*pblock).SRow = 0;
            (*pblock).SCol = 4;
            break;
        case 31:
            (*pblock).Row  = 2;
            (*pblock).Col  = 2;
            (*pblock).SRow = 2;
            (*pblock).SCol = 4;
            break;
        default:
            (*pblock).Row  = 2;
            (*pblock).Col  = 3;
            (*pblock).SRow = 2;
            (*pblock).SCol = 4;
            break;
    }
    (*pblock).arr = (int**) malloc ((*pblock).Row * sizeof(int*));
    int i;
    for (i = 0; i < (*pblock).Row; i++)
        (*pblock).arr[i] = (int*) malloc ((*pblock).Col * sizeof(int));
    for (i = 0; i < (*pblock).Col * (*pblock).Row; i++)
        (*pblock).arr[i / (*pblock).Col][i % (*pblock).Col] = (ID >> ((*pblock).Col * (*pblock).Row - 1 - i)) & 1;
    return pblock;
}

void Update (block *pblock, int color) {
    int i, j;
    for(i = 0; i < (*pblock).Row; i++)
        for(j = 0; j < (*pblock).Col; j++)
            if ((*pblock).arr[i][j]) {
                Color[(*pblock).SRow + i][(*pblock).SCol + j] = color;
                Status[(*pblock).SRow + i][(*pblock).SCol + j] = 1;
            }
}

bool GameChecking (block *pblock, Player *pplay) {
    if((*pblock).SRow <= TOP) return 0;
    int Score = 0;
    int i = (*pblock).Row - 1, j;
    for(; i >= 0; i--) {
        int cnt = 0;
        for(j = 0; j < MCol; j++)
            cnt += Status[(*pblock).SRow + i][j];
        if(cnt == MCol) {
            int k, l;
            for (k = (*pblock).SRow + i; k > 0 ; k--)
                for (l = 0; l < MCol; l++) {
                    Status[k][l] = Status[k-1][l];
                    Color[k][l] = Color[k-1][l];
                }
            Display();
            i++;
            Score++;
        }
    }
    if(Score > 0) {
        mciSendStringA("play Explosion.mp3", NULL, 0, NULL);
        int t = 10 * (*pplay).level * Score * Score;
        i = 0;
        while(i++ < 3) {
            TextColor(12); gotoXY(105, 21); printf("+%d", t); Sleep(300);
            TextColor(0); gotoXY(105, 21); printf("+%d", t); Sleep(50);
        }
        AddInfo(pplay, t, 0);
        mciSendStringA("stop Explosion.mp3", NULL, 0, NULL);
    }
    return 1;
}

void BlockDeleting (block *pblock) {
    int i;
    for(i = 0; i < (*pblock).Row; i++)
        free((*pblock).arr[i]);
    free((*pblock).arr);
    free(pblock);
    pblock = NULL;
}

void initPlayer (Player *pplay) {
    (*pplay).level = 1;
    (*pplay).score = 0;
    (*pplay).time = 0;
    strcpy((*pplay).name, "");
    cnt = 0;
    int i, j;
    for(i = 0; i < 21; i++)
        for(j = 0; j < 11; j++) {
            Status[i][j] = 0;
            Color[i][j] = 0;
        }
}

void AddInfo(Player *pplay, int extrapoints, bool check) {
    int i = 0;
    int a = 10, b = 11, c = 12;
    char LV[4][20] = {"NORMAL", "SPEED", "REVERSE"};
    TextColor(a);
    gotoXY(82, 3);
    printf("LEVEL %d :", (*pplay).level); if((*pplay).time == 0) Sleep(100);
    if((*pplay).level >= 2 && check) {
        TextColor(0); gotoXY(92, 3); printf("%s", LV[(*pplay).level-2]);
        TextColor(0); gotoXY(82, 32); printf("Seems like very easy, isn't it?");
                      gotoXY(82, 33); printf("Get points as much as possible");
                      gotoXY(89, 34); printf("and have fun :D");
        mciSendStringA("play LevelUp.mp3", NULL, 0, NULL);
        while(i++ < 3) {
            TextColor(c); gotoXY(92, 3);  printf("%s", LV[(*pplay).level-1]);
            TextColor(b); gotoXY(82, 32); printf("Great, you reached new level!!!"); Sleep(600);
            TextColor(0); gotoXY(92, 3);  printf("%s", LV[(*pplay).level-1]); Sleep(150);
            TextColor(0); gotoXY(82, 32); printf("Great, you reached new level!!!"); Sleep(150);
        }
        if((*pplay).level == 2) {
            TextColor(c); gotoXY(85, 33); printf("Becareful! Speed Upppp..."); Sleep(1000);
        }
        else if((*pplay).level == 3) {
            TextColor(0); gotoXY(85, 33); printf("Becareful! Speed Upppp...");
            TextColor(c); gotoXY(82, 33); printf("EVERYTHING will be reversed!!!"); Sleep(1000);
        }
        mciSendStringA("stop LevelUp.mp3", NULL, 0, NULL);
    }
    TextColor(12); gotoXY(92, 3); printf("%s", LV[(*pplay).level-1]); if((*pplay).time == 0) Sleep(100);

    TextColor(10); gotoXY(82, 5); printf("Next Block :"); if((*pplay).time == 0) Sleep(100);

    TextColor(a); gotoXY(82, 17); printf("Player : "); if((*pplay).time == 0) Sleep(100);
    TextColor(b); gotoXY(92, 18); printf("%s", (*pplay).name); if((*pplay).time == 0) Sleep(100);

    gotoXY(82, 20); TextColor(a); printf("Score :"); if((*pplay).time == 0) Sleep(100);
    TextColor(b);
    for(i = (*pplay).score; i <= (*pplay).score + extrapoints; i+=5) {
        gotoXY(92, 21); printf("%d", i); Sleep(20);
    }
    (*pplay).score += extrapoints;

    gotoXY(82, 23); TextColor(a); printf("Time :"); if((*pplay).time == 0) Sleep(100);
    if((*pplay).time == 0) {
        TextColor(11); gotoXY(92, 24); printf("00:00"); if((*pplay).time == 0) Sleep(100);
        CountDown();
    }

    if((*pplay).level == 1 && (*pplay).time >= 10 && !cnt && extrapoints > 0) {
        TextColor(0); gotoXY(82, 33); printf("Get points as much as possible");
        TextColor(c); gotoXY(82, 32); printf("Seems like very easy, isn't it?"); Sleep(1500);
        TextColor(b); gotoXY(82, 33); printf("Get points as much as possible");
                      gotoXY(89, 34); printf("and have fun :D"); Sleep(3000);
        cnt = 1;
    }

    gotoXY(82, 38); TextColor(15); printf("[..Press SPACE to Pause Game..]"); if((*pplay).time == 0) Sleep(500);
    gotoXY(82, 39); TextColor(15); printf("[......... ESC to Main Menu...]"); if((*pplay).time == 0) Sleep(500);
}

void AddTime (Player *pplay) {
    (*pplay).time ++;
    int a = (*pplay).time / 60, b = (*pplay).time % 60;
    TextColor(11); gotoXY(92, 24);
    printf("%d%d:%d%d", a/10, a%10, b/10, b%10);
}

void DrawNextBlock (block *nextblock, int nextcolor) {
    int i, j;
    if((*nextblock).Row == 4) {
        int **tarr;
        int tRow = (*nextblock).Col, tCol = (*nextblock).Row;
        tarr = (int**) malloc (tRow * sizeof(int*));
        for(i = 0; i < tRow; i++)
            tarr[i] = (int*) malloc (tCol * sizeof(int));
        for(i = 0; i < tRow; i++)
            for(j = 0; j < tCol; j++)
                tarr[i][j] = (*nextblock).arr[(*nextblock).Row-1-j][i];
        for(i = 0; i < (*nextblock).Row; i++)
            free((*nextblock).arr[i]);
        free((*nextblock).arr);
        (*nextblock).Col = tCol;
        (*nextblock).Row = tRow;
        (*nextblock).arr = tarr;
    }
    TextColor(nextcolor);
    for (i = 0; i < (*nextblock).Row; i++) {
        for (j = 0; j < (*nextblock).Col; j++) {
            if((*nextblock).arr[i][j]) {
                if(i%2 - j%2) {
                    gotoXY(97 + 4 * j, 6 + 2 * i); printf("%c%c%c%c", Odd, Odd, Odd, Odd);
                    gotoXY(97 + 4 * j, 6 + 2 * i + 1); printf("%c%c%c%c", Odd, Odd, Odd, Odd);
                }
                else {
                    gotoXY(97 + 4 * j, 6 + 2 * i); printf("%c%c%c%c", Even, Even, Even, Even);
                    gotoXY(97 + 4 * j, 6 + 2 * i + 1); printf("%c%c%c%c", Even, Even, Even, Even);
                }
            }
        }
    }
    if((*nextblock).Col == 4) {
        int **tarr;
        int tRow = (*nextblock).Col, tCol = (*nextblock).Row;
        tarr = (int**) malloc (tRow * sizeof(int*));
        for(i = 0; i < tRow; i++)
            tarr[i] = (int*) malloc (tCol * sizeof(int));
        for(i = 0; i < tRow; i++)
            for(j = 0; j < tCol; j++)
                tarr[i][j] = (*nextblock).arr[(*nextblock).Row-1-j][i];
        for(i = 0; i < (*nextblock).Row; i++)
            free((*nextblock).arr[i]);
        free((*nextblock).arr);
        (*nextblock).Col = tCol;
        (*nextblock).Row = tRow;
        (*nextblock).arr = tarr;
    }
}

void EraseNextBlock (block *nextblock) {
    DrawNextBlock(nextblock, 0);
}
//============================REVERSE GAME================================================

void ReverseMatrix() {
    int i, j;
    for(i = 0; i < 21/2; i++) {
        for(j = 0; j < 11; j++) {
            int t = Status[i][j];
            Status[i][j] = Status[20-i][j];
            Status[20-i][j] = t;
            int k = Color[i][j];
            Color[i][j] = Color[20-i][j];
            Color[20-i][j] = k;
        }
    }
    for(i = 0; i < 21; i++)
        for(j = 0; j < 11/2; j++) {
            int t = Status[i][j];
            Status[i][j] = Status[i][10-j];
            Status[i][10-j] = t;
            int k = Color[i][j];
            Color[i][j] = Color[i][10-j];
            Color[i][10-j] = k;
        }
}

block* ReverseBlockBuilding (int ID) {
    block (*pblock) = (block*) malloc (sizeof(block));
    switch(ID) {
        case 15:
            (*pblock).Row  = 4;
            (*pblock).Col  = 1;
            (*pblock).SRow = 17;
            (*pblock).SCol = 5;
            break;
        case 31:
            (*pblock).Row  = 2;
            (*pblock).Col  = 2;
            (*pblock).SRow = 18;
            (*pblock).SCol = 5;
            break;
        default:
            (*pblock).Row  = 2;
            (*pblock).Col  = 3;
            (*pblock).SRow = 18;
            (*pblock).SCol = 5;
            break;
    }
    (*pblock).arr = (int**) malloc ((*pblock).Row * sizeof(int*));
    int i;
    for (i = 0; i < (*pblock).Row; i++)
        (*pblock).arr[i] = (int*) malloc ((*pblock).Col * sizeof(int));
    for (i = 0; i < (*pblock).Col * (*pblock).Row; i++)
        (*pblock).arr[i / (*pblock).Col][i % (*pblock).Col] = (ID >> ((*pblock).Col * (*pblock).Row - 1 - i)) & 1;
    return pblock;
}

void ReverseDrawBlock (block *pblock, int color) {
    int i, j;
    for (i = (*pblock).Row - 1; i >= 0; i--) {
        for (j = (*pblock).Col - 1; j >= 0; j--) {
            if ((*pblock).arr[i][j] && (*pblock).SRow < MRow - TOP - i - 1) {
                TextColor(color);
                if (i%2 - j%2) {
                    gotoXY(LEFT + 4 * ((*pblock).SCol + j), 2 * ((*pblock).SRow +  i) + 2*TOP);
                    printf("%c%c%c%c", Odd, Odd, Odd, Odd);
                    gotoXY(LEFT + 4 * ((*pblock).SCol + j), 2 * ((*pblock).SRow +  i) + 2*TOP - 1);
                    printf("%c%c%c%c", Odd, Odd, Odd, Odd);
                }
                else {
                    gotoXY(LEFT + 4 * ((*pblock).SCol + j), 2 * ((*pblock).SRow +  i) + 2*TOP);
                    printf("%c%c%c%c", Even, Even, Even, Even);
                    gotoXY(LEFT + 4 * ((*pblock).SCol + j), 2 * ((*pblock).SRow +  i) + 2*TOP - 1);
                    printf("%c%c%c%c", Even, Even, Even, Even);
                }
            }
        }
    }
}

void ReverseEraseBlock(block *pblock) {
    ReverseDrawBlock(pblock, 0);
}

int ReverseDown (int i, int j) {
    return i > 0 && Inside(i, j) && !Status[i-1][j];
}

bool ReverseDownMove (block *pblock) {
    int i, j;
    for(i = (*pblock).Row - 1; i >= 0; i--)
        for(j = (*pblock).Col - 1; j >= 0; j--)
            if ((*pblock).arr[i][j])
                if (!ReverseDown((*pblock).SRow + i, (*pblock).SCol + j)) return 0;
    (*pblock).SRow -= 1;
    return 1;
}

bool ReverseGameChecking (block *pblock, Player *pplay) {
    if((*pblock).SRow >= MRow - TOP) return 0;
    int Score = 0;
    int i, j;
    for(i = (*pblock).Row - 1; i >= 0; i--) {
        int cnt = 0;
        for(j = 0; j < MCol; j++)
            cnt += Status[(*pblock).SRow + i][j];
        if(cnt == MCol) {
            int k, l;
            for (k = (*pblock).SRow + i; k < MRow - 1; k++)
                for (l = 0; l < MCol; l++) {
                    Status[k][l] = Status[k+1][l];
                    Color[k][l] = Color[k+1][l];
                }
            ReverseDisplay();
            i++;
            Score++;
        }
    }
    if(Score > 0) {
        mciSendStringA("play Explosion.mp3", NULL, 0, NULL);
        int t = 10 * (*pplay).level * Score * Score;
        i = 0;
        while(i++ < 3) {
            TextColor(12); gotoXY(105, 21); printf("+%d", t); Sleep(300);
            TextColor(0); gotoXY(105, 21); printf("+%d", t); Sleep(50);
        }
        AddInfo(pplay, t, 0);
        mciSendStringA("stop Explosion.mp3", NULL, 0, NULL);
    }
    return 1;
}

void ReverseDisplay() {
	int i, j;
	for (i = 0; i < MRow - TOP; i++) {
		for (j = 0; j < MCol; j++) {
			if (Status[i][j]) {
				TextColor(Color[i][j]);
				if (i%2 - j%2) {
                    gotoXY(4*j + LEFT, 2*i + TOP + 1); printf("%c%c%c%c", Odd, Odd, Odd, Odd);
                    gotoXY(4*j + LEFT, 2*i + TOP); printf("%c%c%c%c", Odd, Odd, Odd, Odd);
                }
                else {
                    gotoXY(4*j + LEFT, 2*i + TOP + 1); printf("%c%c%c%c", Even, Even, Even, Even);
                    gotoXY(4*j + LEFT, 2*i + TOP); printf("%c%c%c%c", Even, Even, Even, Even);
                }
			}
			else {
				TextColor(0);
				gotoXY(4*j + LEFT, 2*i + TOP + 1); printf("%c%c%c%c", Even, Even, Even, Even);
				gotoXY(4*j + LEFT, 2*i + TOP); printf("%c%c%c%c", Even, Even, Even, Even);
			}
		}
	}
}

//------------------------------------------

void CountDown() {
    int i, j;
    Sleep(1000);
    TextColor(0);
    for(i = 32; i <= 39; i++)
        for(j = 80; j <= 113; j++) {
            gotoXY(j, i); putchar('=');
        }
    char str[2][50] = {"GET READY ???", "LET'S START!"};
    TextColor(11); gotoXY(91, 33); printf("%s", str[0]); Sleep(1500);
    TextColor(0) ; gotoXY(91, 33); printf("%s", str[0]);
    TextColor(10); gotoXY(93, 32); printf(" ####### ");
                   gotoXY(93, 33); printf("##     ##");
                   gotoXY(93, 34); printf("       ##");
                   gotoXY(93, 35); printf(" ####### ");
                   gotoXY(93, 36); printf("       ##");
                   gotoXY(93, 37); printf("##     ##");
                   gotoXY(93, 38); printf(" ####### "); Sleep(1000);
    TextColor(13); gotoXY(93, 32); printf(" ####### ");
                   gotoXY(93, 33); printf("##     ##");
                   gotoXY(93, 34); printf("       ##");
                   gotoXY(93, 35); printf(" ####### ");
                   gotoXY(93, 36); printf("##       ");
                   gotoXY(93, 37); printf("##       ");
                   gotoXY(93, 38); printf(" ########"); Sleep(1000);
    TextColor(14); gotoXY(93, 32); printf("    ##   ");
                   gotoXY(93, 33); printf("  ####   ");
                   gotoXY(93, 34); printf("    ##   ");
                   gotoXY(93, 35); printf("    ##   ");
                   gotoXY(93, 36); printf("    ##   ");
                   gotoXY(93, 37); printf("    ##   ");
                   gotoXY(93, 38); printf(" ########"); Sleep(1000);
    TextColor(0);
    for(i = 32; i <= 39; i++)
        for(j = 80; j <= 113; j++) {
            gotoXY(j, i); putchar('=');
        }
    TextColor(11); gotoXY(91, 33); printf("%s", str[1]); Sleep(1000);
}

bool ESC_handle(Player *pplay) {
re: TextColor(0);
    int i, j, pos = 0;
    for(i = 32; i <= 38; i++)
        for(j = 80; j <= 113; j++) {
            gotoXY(j, i); putchar('=');
        }
    TextColor(14) ;
    gotoXY(82, 33); printf("Do you want to Save the game ?");
    gotoXY(82, 39); TextColor(15); printf("[...... ENTER to choose ......]");
    char str[3][10] = {    "YES",       "NO",      "Cancel"};
    while(1) {
        for(i = 0; i < 3; i++) {
            if(i == pos) TextColor(12);
            else TextColor(10);
            gotoXY(82 + 12*i, 35); printf("%s", str[i]);
        }
        char c = _getch();
        if(c == 13) {
            if(pos == 0) {
                if(Write(pplay, 1)) return 1;
                else goto re;
            }
            if(pos == 1) {
                Write(pplay, 0);
                return 1;}
            if(pos == 2) {
                TextColor(0);
                for(i = 32; i <= 38; i++)
                    for(j = 80; j <= 113; j++) {
                        gotoXY(j, i); putchar('=');
                    }
                return 0;
            }
        }
        if(c == 224) c = _getch();
        if(c == 75 || c == 'A' || c == 'a') {pos--; if(pos == -1) pos = 2;}
        if(c == 77 || c == 'D' || c == 'd') {pos++; if(pos == 3) pos = 0;}
    }
}

bool Write(Player *pplay, bool check) {
    Sleep(500);
    FILE *f = fopen("SavedGame.txt", "wt");
    if(f == NULL) {
        gotoXY(85, 37); TextColor(12); printf("FAILED to save the game :("); Sleep(3000);
        return 0;
    }
    if(!check) {
        fprintf(f, "0");
        fclose(f);
        return 1;
    }
    fprintf(f, "1\n");
    fprintf(f, "%s\n", (*pplay).name);
    fprintf(f, "%d\n", (*pplay).score);
    fprintf(f, "%d\n", (*pplay).level);
    fprintf(f, "%d\n", (*pplay).time);

    int i, j;
    for(i = 0; i < 21; i++) {
        for(j = 0; j < 11; j++)
            fprintf(f, "%d ", Status[i][j]);
        fprintf(f, "\n");
    }
    for(i = 0; i < 21; i++) {
        for(j = 0; j < 11; j++)
            fprintf(f, "%d ", Color[i][j]);
        fprintf(f, "\n");
    }
    fclose(f);
    gotoXY(85, 37); TextColor(12); printf("Save game SUCCESSFULLY :)"); Sleep(2000);
    return 1;
}

void GetInfo(Player *pplay) {
    FILE *f = fopen("SavedGame.txt", "rt");
    int i, j, t;
    fscanf(f, "%d ", &t);
    fgets((*pplay).name, 100, f);
    fscanf(f, "%d ", &(*pplay).score);
    fscanf(f, "%d ", &(*pplay).level);
    fscanf(f, "%d ", &(*pplay).time);
    for(i = 0; i < 21; i++)
        for(j = 0; j < 11; j++)
            fscanf(f, "%d ", &Status[i][j]);

    for(i = 0; i < 21; i++)
        for(j = 0; j < 11; j++)
            fscanf(f, "%d ", &Color[i][j]);
}

void EndGame(Player *pplay) {
    Write(pplay, 0);
    Player List[7];
    FILE *f = fopen("HighScore.txt", "rt");
    int i = 0, j = 0, n = 0;
    fscanf(f, "%d ", &n);
    for(i = 0; i < n; i++) {
        fgets(List[i].name, 100, f);
        if(List[i].name[strlen(List[i].name) - 1] == '\n') List[i].name[strlen(List[i].name) - 1] = '\0';
        fscanf(f, "%d ", &List[i].score);
        fscanf(f, "%d ", &List[i].level);
        fscanf(f, "%d ", &List[i].time);
    }
    fclose(f);

    List[n++] = *pplay;
    for(i = 0; i < n - 1; i++)
        for(j = i + 1; j < n; j++) {
            if(List[i].score < List[j].score ||
               (List[i].score == List[j].score && List[i].level < List[j].level) ||
               (List[i].score == List[j].score && List[i].level == List[j].level && List[i].time < List[j].time)) {
                Player t = List[i];
                List[i] = List[j];
                List[j] = t;
            }
        }
    if(n > 6) n = 6;
    FILE *t = fopen("HighScore.txt", "wt");
    fprintf(t, "%d\n", n);
    for(i = 0; i < n; i++) {
        fprintf(t, "%s\n", List[i].name);
        fprintf(t, "%d %d %d\n", List[i].score, List[i].level, List[i].time);
    }
    fclose(t);

    TextColor(0);
    for(i = 32; i <= 39; i++)
        for(j = 80; j <= 113; j++) {
            gotoXY(j, i); putchar(' ');
        }

    i = 0;
    while(i++ < 2) {
        TextColor(14); gotoXY(91, 33); printf("GAME OVER!!!"); Sleep(500);
        TextColor(0); gotoXY(91, 33); printf("GAME OVER!!!"); Sleep(150);
    }
    TextColor(14); gotoXY(91, 33); printf("GAME OVER!!!"); Sleep(2000);
    for(i = 0; i < n; i++)
        if(strcmp(List[i].name, pplay->name) == 0 && List[i].score == pplay->score &&
           List[i].level == pplay->level && List[i].time == pplay->time) break;
    if(i == n) {
        TextColor(13);
        gotoXY(82, 33); printf("You are not in top 6 players :(");
        gotoXY(82, 34); printf("Try your best on the next time!"); Sleep(2000);
    }
    else {
        TextColor(13);
        gotoXY(90, 33); printf("Congratulation,");
        gotoXY(84, 34); printf("you rank #%d in Scoreboard!", i + 1); Sleep(2000);
    }
    gotoXY(82, 38); TextColor(15); printf("[.Press V to View Scoreboard..]");
    gotoXY(82, 39); TextColor(15); printf("[.... ESC to Main Menu........]");

    while(1) {
        char c = _getch();
        if(c == 'V' || c == 'v') {
            AddBorder();
            TextColor(14); gotoXY(55, 38); printf("SCOREBOARD");
            TextColor(12);
            gotoXY(25, 22); printf("Rank     Player                 Score            Level          Time"); Sleep(300);
            TextColor(11);
            for(i = 0; i < n; i++) {
                gotoXY(28, 24 + 2*i); printf("%d", i+1);
                gotoXY(34, 24 + 2*i); printf("%s", List[i].name);
                gotoXY(57, 24 + 2*i); printf("%d", List[i].score);
                gotoXY(76, 24 + 2*i); printf("%d", List[i].level);
                gotoXY(89, 24 + 2*i); printf("%d%d:%d%d", (List[i].time/60)/10, (List[i].time/60)%10,
                                                        (List[i].time%60)/10, (List[i].time%60)%10) ;
                Sleep(200);
            }
            _getch();
            return;
        }
        else if(c == 27) return;
    }
}
