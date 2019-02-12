#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include "console.h"
#include "Func.h"
#include "Gameplay.h"

/* ----- IN RA THÔNG TIN VỀ GAME ----- */

void About() {
    AddBorder();
    char s[][100] = {"NGUYEN THANH LUAN",
                     "University of Information and Technology - VNU HCMC",
                     "Product: TETRIS - Game Console",
                     "Date Created: 23/01/2017",
                     "Instructor: Nguyen Trung Thanh (Abcxyz tcit)"};
    int i, j;
    TextColor(11);
    for(i = 0; i < strlen(s[0]); i++) {gotoXY(24 + i, 22); printf("%c", s[0][i]); Sleep(30);}
    TextColor(13);
    for(i = 0; i < strlen(s[1]); i++) {gotoXY(24 + i, 23); printf("%c", s[1][i]); Sleep(30);}
    for(i = 2; i < 5; i++) {
        j = 0;
        while(j == 0 || (j > 0 && s[i][j-1] != ':')) {
            TextColor(12);
            gotoXY(24 + j, 23 + i); printf("%c", s[i][j]); Sleep(25);
            j++;
        }
        TextColor(10);
        while(j < strlen(s[i])) {
            gotoXY(24 + j, 23 + i); printf("%c", s[i][j]); Sleep(25);
            j++;
        }
    }
    TextColor(14); gotoXY(50, 38); printf("HAPPY LUNAR NEWYEAR!");
    _getch();
    EraseBorder();
}

/* ----- IN RA BẢNG XẾP HẠNG ĐIỂM ----- */

void HighScore() {
    Player List[7];
    FILE *f = fopen("HighScore.txt", "rt");
    int i = 0, n = 0;
    fscanf(f, "%d ", &n);
    for(i = 0; i < n; i++) {
        fgets(List[i].name, 100, f);
        if(List[i].name[strlen(List[i].name) - 1] == '\n') List[i].name[strlen(List[i].name) - 1] = '\0';
        fscanf(f, "%d %d %d ", &List[i].score, &List[i].level, &List[i].time);
    }
    fclose(f);
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
        Sleep(150);
    }
    _getch();
    EraseBorder();
}

/* ----- IN RA HƯỚNG DẪN GAME ----- */

void Tutorial() {
    AddBorder();
    Sleep(500);
    TextColor(11); gotoXY(24, 22); printf("Su dung cac phim dieu huong {Up, Right, Left, Down}"); Sleep(1000);
                   gotoXY(24, 23); printf("              hoac cac phim {W, D, A, S} de di chuyen va xoay khoi gach:"); Sleep(500);
    TextColor(10); gotoXY(24, 24); printf("    Key ( Up = W ): Xoay khoi gach theo chieu kim dong ho;"); Sleep(500);
                   gotoXY(24, 25); printf("    Key ( Right = D ): Dich chuyen khoi gach qua ben phai;"); Sleep(500);
                   gotoXY(24, 26); printf("    Key ( Left = A ): Dich chuyen khoi gach qua ben trai;"); Sleep(500);
                   gotoXY(24, 27); printf("    Key ( Down = S ): Dich chuyen khoi gach ve phia duoi."); Sleep(1000);
    TextColor(11); gotoXY(24, 29); printf("Game duoc chia lam 3 level:"); Sleep(500);
    TextColor(10); gotoXY(24, 30); printf("    Level 1: NORMAL"); Sleep(500);
                   gotoXY(24, 31); printf("    Level 2: SPEED"); Sleep(500);
                   gotoXY(24, 32); printf("    Level 3: REVERSE"); Sleep(500);
    TextColor(12); gotoXY(24, 33); printf("Co gang de dat duoc nhieu diem nhat co the!"); Sleep(1000);
    TextColor(11); gotoXY(24, 35); printf("Cach tinh diem :"); Sleep(1000);
    TextColor(13); gotoXY(41, 35); printf("Diem = 10 * Level * (So hang gach an duoc)^2"); Sleep(1000);
    TextColor(14); gotoXY(43, 38); printf("\"Be careful with the REVERSE level\"");

    _getch();
    EraseBorder();
}

// Trả về 0 nếu không tìm thấy dữ liệu game, trả về 1 nếu tải game thành công
// Dùng khi người dùng chọn RESUME GAME

bool isResume() {
    int c;
    bool found;
    FILE *f = fopen("SavedGame.txt", "rt");
    fscanf(f, "%d", &c);
    fclose(f);
    c == 1 ? found = 1 : found = 0;
    AddBorder();
    TextColor(12);
    if(found){
        gotoXY(48, 28); printf("LOAD GAME COMPLETELY !!!"); Sleep(2000); EraseBorder(); return 1;
    } else {
        gotoXY(49, 28); printf("GAME DATA NOT FOUND !!!"); Sleep(2000); EraseBorder(); return 0;
    }
}


/* ----- RESUME GAME ----- */
// Xử lí tương tự như hàm New Game ở dưới, có một số khác biệt lúc đầu khi mà lấy thông tin từ file txt, tạo người chơi mới
// và gán thông tin cũ vào người chơi mới, vẽ giao diện game cũ ...

void Resume() {
    //mciSendStringA("stop Greeting.wav", NULL, 0, NULL);

    // Lấy thông tin người chơi cũ
    Player PL;
    GetInfo(&PL);

    float LVtime[] = {0.4, 0.2, 0.3};
    float time = LVtime[PL.level-1];
    clock_t Begin, End, TimeCnt_start, TimeCnt_end;
    int ID, color, nextID = BlockType(), nextcolor = 10 + rand() % 6;
    block *BL, *nextBL;
    int jump;

    DrawBorder();
    AddInfo(&PL, 0, 0);
    PL.level <= 2 ? Display() : ReverseDisplay();
    CountDown();
    AddInfo(&PL, 0, 0);

    // Nếu level = 1 hoặc level = 2
    if(PL.level <= 2) {
        PL.level == 1 ? jump = 1 : jump = 3;
        ID = BlockType(); BL = BlockBuilding(ID); color = 10 + rand() % 6;
        nextID = BlockType(); nextcolor = 10 + rand() % 6; nextBL = BlockBuilding(nextID);
        DrawNextBlock(nextBL, nextcolor);

        while(1) {
            TimeCnt_start = clock();
            do {
                Display();
                DrawBlock(BL, color);
                Begin = clock();
                do {
                    if(_kbhit()) {
                        EraseBlock(BL);
                        char c = _getch();
                        if(c == 224) c = _getch();
                        if(c == 72 || c == 'W' || c == 'w') BlockTurning(BL);
                        else if(c == 80 || c == 'S' || c == 's') DownMove(BL);
                        else if(c == 77 || c == 'D' || c == 'd') RightMove(BL);
                        else if(c == 75 || c == 'A' || c == 'a') LeftMove(BL);
                        else if(c == 32) {gotoXY(85, 38); TextColor(15); printf("Press any key to Continue"); _getch(); AddInfo(&PL, 0, 0);}
                        else if(c == 27) {if(ESC_handle(&PL)) return; else AddInfo(&PL, 0, 0);}
                        DrawBlock(BL, color);
                    }
                    End = clock();
                } while(float(End - Begin) / CLK_TCK <= time);
                if(!DownMove(BL)) {
                    Update(BL, color);
                    if(!GameChecking(BL, &PL)) {EndGame(&PL); return;}
                    BlockDeleting(BL);
                    EraseNextBlock(nextBL);
                    if(PL.level == 2 && jump == 2) {jump++; time = LVtime[PL.level-1]; AddInfo(&PL, 0, 1);}
                    else if(PL.level == 3 && jump == 4) {time = LVtime[PL.level-1]; AddInfo(&PL, 0, 1);
                                                         ReverseMatrix(); ReverseDisplay(); goto reverse;}
                    ID = nextID; BL = nextBL; color = nextcolor;
                    nextID = BlockType();
                    nextBL = BlockBuilding(nextID);
                    nextcolor = 10 + rand() % 6;
                    DrawNextBlock(nextBL, nextcolor);
                }
                TimeCnt_end = clock();
            } while(float(TimeCnt_end - TimeCnt_start) / CLK_TCK <= (1 - time/2.0)) ;
            AddTime(&PL);
            if(PL.time == 100) {PL.level = 2; jump++;}
            if(PL.time == 200) {PL.level = 3; jump++;}
        }
    }

// Xử lí level 3
reverse:    ID = nextID; BL = ReverseBlockBuilding(ID); color = nextcolor;
            nextID = BlockType(); nextBL = ReverseBlockBuilding(nextID); nextcolor = 10 + rand() % 6;
            DrawNextBlock(nextBL, nextcolor);
        while(1) {
            TimeCnt_start = clock();
            do {
                ReverseDisplay();
                ReverseDrawBlock(BL, color);
                Begin = clock();
                do {
                    if(_kbhit()) {
                        ReverseEraseBlock(BL);
                        char c = _getch();
                        if(c == 224) c = _getch();
                        if(c == 72 || c == 'W' || c == 'w') ReverseDownMove(BL);
                        else if(c == 80 || c == 'S' || c == 's') BlockTurning(BL);
                        else if(c == 77 || c == 'D' || c == 'd') LeftMove(BL);
                        else if(c == 75 || c == 'A' || c == 'a') RightMove(BL);
                        else if(c == 32) {gotoXY(85, 38); TextColor(15); printf("Press any key to Continue"); _getch(); AddInfo(&PL, 0, 0);}
                        else if(c == 27) {if(ESC_handle(&PL)) return; else AddInfo(&PL, 0, 0);}
                        ReverseDrawBlock(BL, color);
                    }
                    End = clock();
                } while(float(End - Begin) / CLK_TCK <= time);
                if(!ReverseDownMove(BL)) {
                    Update(BL, color);
                    if(!ReverseGameChecking(BL, &PL)) {EndGame(&PL); return;}
                    BlockDeleting(BL);
                    EraseNextBlock(nextBL);
                    ID = nextID; BL = nextBL; color = nextcolor;
                    nextID = BlockType();
                    nextBL = ReverseBlockBuilding(nextID);
                    nextcolor = 10 + rand() % 6;
                    DrawNextBlock(nextBL, nextcolor);
                }
                TimeCnt_end = clock();
            } while(float(TimeCnt_end - TimeCnt_start) / CLK_TCK <= (1 - time/2.0));
            AddTime(&PL);
        }
}

/* ----- TRÒ CHƠI MỚI ----- */

void Gameplay() {
    // Lưu vô mảng mức tốc độ của mỗi level để dễ quản lí
    float LVtime[] = {0.4, 0.2, 0.3};
    // Biến dùng để tính toán, xác định mức level của người chơi
    int jump = 1;
    float time = LVtime[0];

    // Khởi tạo người chơi
    Player PL;
    initPlayer(&PL);
    if(!EnterName(&PL)) return;

    // Khởi tạo trò chơi
    clock_t Begin, End, TimeCnt_start, TimeCnt_end;
    int ID, color, nextID, nextcolor;
    block *BL, *nextBL;
    ID = BlockType(); BL = BlockBuilding(ID); color = 10 + rand() % 6;
    nextID = BlockType(); nextcolor = 10 + rand() % 6; nextBL = BlockBuilding(nextID);

    // Vẽ giao diện chính (khung viền, thông tin người chơi và khối gạch kế tiếp
    DrawBorder();
    AddInfo(&PL, 0, 0);
    DrawNextBlock(nextBL, nextcolor);

    // Vòng lặp xử lí mỗi bước di chuyển của mỗi viên gạch
    while(1) {
        TimeCnt_start = clock();
        do {
            // Thể hiện giao diện game hiện tại
            Display();
            DrawBlock(BL, color);

            /*
                Để có thể tính được thời gian của người chơi, em đã "ước lượng" thời gian thực hiện
                các thao tác (di chuyển gạch, xoay, vẽ giao diện...) của máy cho mỗi bước di chuyển của
                khối gạch, cho nó bằng môt khoảng T. Thì mỗi giây thực tế sẽ xấp xỉ bằng
                (T + thời gian không nhấn phím trong 1 giây).
                Nhưng em thấy rằng trong khoảng T đó người chơi có thể sẽ ẤN GIỮ phím, nghĩa là
                có rất nhiều thao tác cần xử lí, việc quá giới hạn T được qui định trong 1s sẽ không thể
                tránh khỏi. Vì vậy vòng lặp do while thứ 2 dưới đây dùng để xử lí những trường hợp như thế.
            */
            Begin = clock();
            do {
                if(_kbhit()) {
                    // Xoá khối gạch cũ ở vị trí hiện tại
                    EraseBlock(BL);
                    // Xử lí nhấn phím
                    char c = _getch();
                    if(c == 224) c = _getch();
                    if(c == 72 || c == 'W' || c == 'w') BlockTurning(BL); // Xoay khối gạch
                    else if(c == 80 || c == 'S' || c == 's') DownMove(BL); // Rơi xuống
                    else if(c == 77 || c == 'D' || c == 'd') RightMove(BL); // Dịch phải
                    else if(c == 75 || c == 'A' || c == 'a') LeftMove(BL); // Dịch trái
                    // Pause game
                    else if(c == 32) {gotoXY(85, 38); TextColor(15); printf("Press any key to Continue"); _getch(); AddInfo(&PL, 0, 0);}
                    // Thoát game
                    else if(c == 27) {if(ESC_handle(&PL)) return; else AddInfo(&PL, 0, 0);}
                    // Vẽ khối gạch ở vị trí mới
                    DrawBlock(BL, color);
                }
                End = clock();
            } while(float(End - Begin) / CLK_TCK <= time);

            // Kiểm tra va chạm
            if(!DownMove(BL)) {
                // Cập nhật thông tin vào ma trận toạ độ
                Update(BL, color);
                // Nếu người chơi thua, in ra highscore và kết thúc
                if(!GameChecking(BL, &PL)) {EndGame(&PL); return;}
                // Huỷ vùng nhớ lúc khởi tạo khối gạch
                BlockDeleting(BL);
                // Xoá hình ảnh khối gạch kế tiếp
                EraseNextBlock(nextBL);
                // Kiểm tra qua level và Cập nhật lại thông tin người chơi
                if(PL.level == 2 && jump == 2) {jump++; time = LVtime[PL.level-1]; AddInfo(&PL, 0, 1);} // LV2
                else if(PL.level == 3 && jump == 4) {time = LVtime[PL.level-1]; goto reverse;}  // LV3
                // Khởi tạo khối gạch mới
                ID = nextID; BL = nextBL; color = nextcolor;
                nextID = BlockType();
                nextBL = BlockBuilding(nextID);
                nextcolor = 10 + rand() % 6;
                DrawNextBlock(nextBL, nextcolor);
            }
            TimeCnt_end = clock();
        } while(float(TimeCnt_end - TimeCnt_start) / CLK_TCK <= (1 - time/2.0)) ;
        AddTime(&PL);

        // Xử lí thời gian chơi để lên level (100s == level 2, 200s == level 3
        if(PL.time == 100) {PL.level = 2; jump++;}
        if(PL.time == 200) {PL.level = 3; jump++;}
    }

// Xử lí level 3: Reverse Game (vòng lặp xử lí tương tự như 2 level trước nhưng sử dụng các hàm tương ứng cho level reverse này)
// Em hoàn toàn có thể thu gọn code, gọi ít hàm hơn để xử lí cả 3 level chỉ thông qua 1 do while chính, nhưng tại hồi đó em code
// trâu để hoàn thành, giờ fix lại em nản quá, chịu luôn anh ạ :'(
reverse:    AddInfo(&PL, 0, 1);
            ReverseMatrix();
            ReverseDisplay();
            ID = nextID; BL = ReverseBlockBuilding(ID); color = nextcolor;
            nextID = BlockType(); nextBL = ReverseBlockBuilding(nextID); nextcolor = 10 + rand() % 6;
            DrawNextBlock(nextBL, nextcolor);
        while(1) {
            TimeCnt_start = clock();
            do {
                ReverseDisplay();
                ReverseDrawBlock(BL, color);
                Begin = clock();
                do {
                    if(_kbhit()) {
                        ReverseEraseBlock(BL);
                        char c = _getch();
                        if(c == 224) c = _getch();
                        if(c == 72 || c == 'W' || c == 'w') ReverseDownMove(BL);
                        else if(c == 80 || c == 'S' || c == 's') BlockTurning(BL);
                        else if(c == 77 || c == 'D' || c == 'd') LeftMove(BL);
                        else if(c == 75 || c == 'A' || c == 'a') RightMove(BL);
                        else if(c == 32) {gotoXY(85, 38); TextColor(15); printf("Press any key to Continue"); _getch(); AddInfo(&PL, 0, 0);}
                        else if(c == 27) {if(ESC_handle(&PL)) return; else AddInfo(&PL, 0, 0);}
                        ReverseDrawBlock(BL, color);
                    }
                    End = clock();
                } while(float(End - Begin) / CLK_TCK <= time);
                if(!ReverseDownMove(BL)) {
                    Update(BL, color);
                    if(!ReverseGameChecking(BL, &PL)) {EndGame(&PL); return;}
                    BlockDeleting(BL);
                    EraseNextBlock(nextBL);
                    ID = nextID; BL = nextBL; color = nextcolor;
                    nextID = BlockType();
                    nextBL = ReverseBlockBuilding(nextID);
                    nextcolor = 10 + rand() % 6;
                    DrawNextBlock(nextBL, nextcolor);
                }
                TimeCnt_end = clock();
            } while(float(TimeCnt_end - TimeCnt_start) / CLK_TCK <= (1 - time/2.0));
            AddTime(&PL);
        }
}

/* ----- VÒNG LẶP CHÍNH CỦA CHƯƠNG TRÌNH ----- */

void MainMenu() {
    int i, j, c, pos = 0;
    bool done = 0;

re: clrscr();
    // In ra Menu lựa chọn
    char TAG[7][20] = {"RESUME", "NEW GAME", "TUTORIAL", "HIGH SCORE", "ABOUT", "QUIT"};
    PrintLogo(&done); bool cnt = 0;
    int Status[21][11] = {0};
    int Color[21][11] = {0};

    while (1) {
        gotoXY(53, 20 + 2 * pos); TextColor(10); putchar(175);
        for (i = 0; i < 6; i++) {
            if (i == pos) TextColor(12);
            else TextColor(15);
            gotoXY(55, 20 + 2 * i);
            printf("%s", TAG[i]);
        }
        c = _getch();
        if (c == 13) { // Xử lí thao tác nhấn Enter
            switch (pos) {
                // case 0: Resume Game
                case 0: if(isResume()) {Resume(); goto re;}
                        else break;
                        break;
                // case 1: New Game
                case 1: Gameplay(); goto re;
                // case 2: In ra hướng dẫn game
                case 2: Tutorial(); break;
                // case 3: In ra bảng xếp hạng điểm
                case 3: HighScore(); break;
                // case 4: In ra thông tin về game
                case 4: About(); break;
                // case 5: Quit - Thoát game, kết thúc chương trình
                case 5: return;
            }
            continue;
        }

        // Xử lí thao tác nhấn phím di chuyển
        if (c == 224) c = _getch();
        gotoXY(53, 20 + 2 * pos); TextColor(0); putchar(175);
        if (c == 72 || c == 'W' || c == 'w') {
            pos -= 1;
            if (pos == -1) pos = 5;
        }
        else if (c == 80 || c == 'S' || c == 's') {
            pos += 1;
            if (pos == 6) pos = 0;
        }
    }
}


int main() {
    // Khởi tạo màn hình console
    srand(time(NULL));
    Nocursortype();
    system("mode 119, 42");
    mciSendStringA("play Playing.mp3 repeat", NULL, 0, NULL);

    MainMenu();

    return 0;
}
