#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include "console.h"
#include "Func.h"

void Nocursortype() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void AddBorder() {
    int i, j;
    for (i = 39; i > 20; i--) {
        TextColor(15);
        gotoXY(20, i); putchar(186);
        gotoXY(100, i); putchar(186);
        TextColor(0);
        for (j = 21; j <= 99; j++) {
            gotoXY(j, i); putchar(219);
        }
        Sleep(5);
    }
    TextColor(15);
    gotoXY(20, 20); putchar(201);
    gotoXY(100, 39); putchar(188);
    for (i = 21; i <= 99; i++) {
        gotoXY(i, 20); putchar(205);
        gotoXY(120-i, 37); putchar(240);
        gotoXY(120-i, 39); putchar(205);
        Sleep(5);
    }
    gotoXY(100, 20); putchar(187);
    gotoXY(20, 39); putchar(200);
}

void EraseBorder()
{
    TextColor(0);
    gotoXY(100, 20); putchar(187);
    int i, j;
    for (i = 99; i >= 21; i--)
    {
        gotoXY(i, 20); putchar(205);
        gotoXY(120-i, 37); putchar(205);
        gotoXY(120-i, 39); putchar(205);
        Sleep(5);
    }
    gotoXY(20, 20); putchar(201);
    for (i = 21; i <= 39; i++)
    {
        gotoXY(20, i); putchar(186);
        gotoXY(100, i); putchar(186);
        for (j = 21; j <= 95; j++)
        {
            gotoXY(j, i);
            putchar(219);
        }
        Sleep(5);
    }
}

void PrintLogo(bool *pdone) {
    int i, j;
    char title[20][200];
    FILE *f = fopen ("logo.txt", "rt");
    for (i = 0; i < 16; i++)
        fgets(title[i], 200, f);
    fclose(f);
    i = 0;
    if(!(*pdone)) {
        while (i++ < 100) {
            int k = rand() % 16;
            int a = 10 + rand() % 6;
            gotoXY(1, k); TextColor(a);
            for (j = 0; title[k][j] != '\0'; j++)
                putchar(title[k][j]);
            Sleep(10);
        }
        clrscr();
    }
    for (i = 0; i < 16; i++) {
        int cnt = 0;
        char last = 'T';
        TextColor(cnt + 10);
        putchar(32);
        for (j = 0; title[i][j] != '\0'; j++) {
            if ('A' <= title[i][j] && title[i][j] <= 'Z' && title[i][j] != last) {
                cnt++;
                TextColor(cnt + 10);
                last = title[i][j];
            }
            putchar(title[i][j]);
        }
        if(!(*pdone)) Sleep(100);
    }
    *pdone = true;
}




