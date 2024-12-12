#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#pragma warning (disable : 4996)

#define ESC 27
#define MAXENEMY 1
#define MAXBALL 1

int fx;
int bx, by;
int Score;
int Strike;
int base1 = 0;
int base2 = 0;
int base3 = 0;
int random;
int a1 = 0;
int a2 = 0;
int a3 = 0;
int a4 = 0;
int a5 = 0;

void gotoxy(int x, int y)
{
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


void CursorView(char show)//커서숨기기
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}


struct tag_Enemy
{
    BOOL exist;
    int Type;
    int x, y;
    int Delta;
    int nFrame;
    int nStay;
}
Enemy[MAXENEMY];


struct tag_Ball
{
    BOOL exist;
    int x, y;
    int nFrame;
    int nStay;
}
Ball[MAXBALL];

const char* arEnemy[] = { " oO@Oo " };
//const char* arEnem[] = { " oO@Oo " };
//const char* arEne[] = { " oO@Oo " };

BOOL IsKeyDown(int Key)
{
    return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}



void main()
{
intro:
    system("cls");
    gotoxy(35, 4);
    printf("■■■■■■■■■■■■");
    gotoxy(35, 5);
    printf("■운빨야구겜■");
    gotoxy(35, 6);
    printf("■■■■■■■■■■■■");
    gotoxy(30, 10);
    printf("게임시작[F1]");
    gotoxy(30, 15);
    printf("게임설명[F2]");
    gotoxy(30, 20);
    printf("제작자[F3]");
    while (1) {
        if (IsKeyDown(VK_F1)) {
            goto game;
            break;
        }

        else if (IsKeyDown(VK_F2)) {
            goto induc;
            break;
        }

        else if (IsKeyDown(VK_F3)) {
            goto me;
            break;
        }
    }

game:
    system("cls");
    printf("asdf");
    Score = 0;
    Strike = 0;
    int ch;
    int i, j;
    base1 = 0;
    base2 = 0;
    base3 = 0;
    random;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    a4 = 0;
    a5 = 0;
    BOOL bFound;
    int count;

    //SetConsoleOutputCP(CP_UTF8);

    srand((unsigned)time(NULL));
    system("cls");
    CursorView(0);//커서 숨기기

    fx = 60;
    bx = -1;
    Score = 0;

    for (count = 0;; count++) {

        // 키 입력 처리
        if (kbhit())
        {
            ch = getch();
            if (ch == 0xE0 || ch == 0)
            {
                getch();
            }
            else
            {
                switch (ch)
                {
                case ' '://Space
                    if (bx == -1)
                    {
                        bx = fx;
                        by = 23;
                    }
                    break;
                case ESC:
                    goto end;
                }
            }
        }

        // 적군 생성
        if (rand() % 50 == 0)
        {
            for (i = 0; i < MAXENEMY && Enemy[i].exist == TRUE; i++) { ; }
            if (i != MAXENEMY)
            {
                Enemy[i].x = 60;
                Enemy[i].Delta = 0;

                for (;;)
                {
                    Enemy[i].y = i + 1;
                    for (bFound = FALSE, j = 0; j < MAXENEMY; j++)
                    {
                        if (Enemy[j].exist == TRUE && Enemy[j].y == Enemy[i].y)
                        {
                            bFound = TRUE;
                            break;
                        }
                    }
                    if (bFound == FALSE)
                    {
                        break;
                    }
                }
                Enemy[i].nFrame = Enemy[i].nStay = rand() % 1 + 1;
                Enemy[i].Type = rand() % (sizeof(arEnemy) / sizeof(arEnemy[0])); //random(sizeof(arEnemy) / sizeof(arEnemy[0]));
                Enemy[i].exist = TRUE;
            }
        }

        // 아군 총알 이동 및 출력


        // 적군과 아군 총알의 충돌 판정
        for (i = 0; i < MAXENEMY; i++)
        {
            if (Enemy[i].exist == FALSE)
                continue;

            if (Enemy[i].y == by && abs(Enemy[i].x - bx) <= 2)
            {
                gotoxy(bx, by); putch(' ');
                bx = -1;
                Enemy[i].exist = FALSE;
                gotoxy(Enemy[i].x - 3, Enemy[i].y);
                puts("       ");
                Score += 7 - Enemy[i].nFrame;
                break;
            }
        }

        // 적군 총알 이동
        for (i = 0; i < MAXBALL; i++)
        {
            if (Ball[i].exist == FALSE)
                continue;

            if (--Ball[i].nStay == 0)
            {
                Ball[i].nStay = Ball[i].nFrame;
                gotoxy(Ball[i].x, Ball[i].y); putch(' ');

                if (Ball[i].y >= 23)
                {
                    Ball[i].exist = FALSE;
                }
                else
                {
                    Ball[i].y++;
                    gotoxy(Ball[i].x, Ball[i].y); putch('♪');
                }
            }
        }

        // 적군 총알과 아군의 충돌 판정
        for (i = 0; i < MAXBALL; i++) {
            if (Ball[i].exist == FALSE) continue;
            if (Ball[i].y == 23 && abs(Ball[i].x - fx) <= 2) {

                if (IsKeyDown(VK_SPACE)) {
                    // Score += 1;
                    int temp = rand() % 10000;
                    int runner = 0;
                    if (temp == 0) {
                        goto bat;
                    }
                    if (temp >= 1 && temp <= 9) {
                        //장외홈런, 123루 주자들이랑 +1 합쳐 두배로 스코어 변수에 플러스 일
                        a5 += 1;
                        Score += (base1 + base2 + base3 + 1) * 2;
                        base1 = 0;
                        base2 = 0;
                        base3 = 0;
                        gotoxy(2, 28);
                        puts("          ");
                        printf("\033[0;31m장외홈런\033[0m\n");
                    }
                    if (temp >= 10 && temp <= 499) {
                        //홈런, 123루 주자들이랑 +1 합쳐 스코어에 1
                        a4 += 1;
                        Score += base1 + base2 + base3 + 1;
                        base1 = 0;
                        base2 = 0;
                        base3 = 0;
                        gotoxy(2, 28);
                        puts("          ");
                        printf("\033[0;31m홈런\033[0m\n");
                    }
                    if (temp >= 500 && temp <= 1199) {
                        //3루타, 타자를 3루로 옮긴뒤 주자들 합쳐 +1
                        a3 += 1;
                        Score += base1 + base2 + base3;
                        base1 = 0;
                        base2 = 0;
                        base3 = 1;
                        gotoxy(2, 28);
                        puts("          ");
                        printf("\033[0;31m3루타\033[0m\n");
                    }
                    if (temp >= 1200 && temp <= 2499) {
                        //2루타, 알아서 하셈 
                        a2 += 1;
                        if (base3 == 1) {
                            Score += 1;
                            base3 = 0;

                        }
                        if (base2 == 1) {
                            Score += 1;
                            base2 = 0;
                        }
                        if (base1 == 1) {
                            base3 = 1;
                            base1 = 0;
                        }
                        base2 = 1;
                        gotoxy(2, 28);
                        puts("          ");
                        printf("\033[0;31m2루타\033[0m\n");
                    }
                    if (temp >= 2500 && temp <= 9999) {
                        //1루타, 알아서 하셈
                        a1 += 1;
                        if (base3 == 1) {
                            Score += 1;
                            base3 = 0;
                        }
                        if (base2 == 1) {
                            base3 = 1;
                            base2 = 0;
                        }
                        if (base1 == 1) {
                            base2 = 1;
                            base1 = 0;
                        }
                        gotoxy(2, 28);
                        puts("          ");
                        printf("\033[0;31m안타\033[0m\n");
                        base1 = 1;
                    }

                    Ball[i].exist == FALSE;
                }
            }
            else if (IsKeyDown(VK_SPACE)) {
                Strike += 1;
                Ball[i].exist == FALSE;

                if (Strike == 50) {
                    goto end;
                }
            }
        }
        // 적군 이동 및 출력
        for (i = 0; i < MAXENEMY; i++) {
            if (Enemy[i].exist == FALSE) continue;
            if (--Enemy[i].nStay == 0) {
                Enemy[i].nStay = Enemy[i].nFrame;
                if (Enemy[i].x >= 76 || Enemy[i].x <= 4) { // 적이 사람 눈에 안보이는 경우
                    Enemy[i].exist = FALSE;                      // 적이 사라지도록 함
                    gotoxy(Enemy[i].x - 3, Enemy[i].y);
                    puts("       ");
                }
                else
                {
                    Enemy[i].x += Enemy[i].Delta;
                    gotoxy(Enemy[i].x - 3, Enemy[i].y);
                    puts(arEnemy[Enemy[i].Type]);
                    // 총알 발사
                    if (rand() % 20 == 0) {
                        for (j = 0; j < MAXBALL && Ball[j].exist == TRUE; j++) { ; }
                        if (j != MAXBALL) {
                            Ball[j].x = Enemy[i].x + 2;
                            Ball[j].y = Enemy[i].y + 1;
                            Ball[j].nFrame = Ball[j].nStay = Enemy[i].nFrame * 1;
                            Ball[j].exist = TRUE;
                        }
                    }
                }
            }
        }

        // 파이터 및 점수 출력
        gotoxy(57, 23);
        puts(" <<A>> ");
        gotoxy(0, 24);
        printf("점수=%d", Score);
        printf("스트라이크 = % d", Strike);
        if (base1 == 1) {
            gotoxy(6, 27);
            printf("◆");
        }
        else {
            gotoxy(6, 27);
            printf("◇");
        }
        if (base2 == 1) {
            gotoxy(4, 26);
            printf("◆");
        }
        else {
            gotoxy(4, 26);
            printf("◇");
        }
        if (base3 == 1) {
            gotoxy(2, 27);
            printf("◆");
        }
        else {
            gotoxy(2, 27);
            printf("◇");
        }
        //printf("1루 : %d  ㅁ", base1);
        //printf("2루 : %d   ", base2);
        //printf("3루 : %d   ", base3);
        gotoxy(0, 25);

        // 초당 10 프레임
        Sleep(10);
    }




induc:
    system("cls");
    gotoxy(30, 10);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    gotoxy(30, 11);
    printf("■스페이스바를 눌러 날라오는 공을 칠수있다!!             ■\n");
    gotoxy(30, 12);
    printf("■스트라이크 지속시간이이 50이 되면 게임이 강제종료된다!!■\n");
    gotoxy(30, 13);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    gotoxy(30, 14);
    printf("돌아가기[스페이스바]");
    gotoxy(30, 16);
    printf("안타 : 70%%");
    gotoxy(30, 17);
    printf("2루타 : 13%%");
    gotoxy(30, 18);
    printf("3루타 : 7%%");
    gotoxy(30, 19);
    printf("홈런 : 4.9%%");
    gotoxy(30, 20);
    printf("장외홈런 : 0.09%% (홈런의 2배)");
    gotoxy(30, 21);
    printf("배트 부숴짐 : 0.01%%");

    while (1) {
        if (IsKeyDown(VK_SPACE)) {
            goto intro;
            break;
        }
    }

me:
    system("cls");
    gotoxy(30, 15);
    printf("\033[0;33m지존짱짱코딩박사준성이\033[0m\n");
    gotoxy(30, 16);
    printf("돌아가기[스페이스바]");
    while (1) {
        if (IsKeyDown(VK_SPACE)) {
            goto intro;
            break;
        }
    }

bat:
    gotoxy(5, 15);
    printf("배트가 부셔졌군요... 당신은 이게임의 이스터에그를 찾으셨습니다... 축하드립니다.");
    gotoxy(5, 16);
    printf("이화면을 찍고 지존짱짱준성이에게 오세요....");
    gotoxy(20, 18);
    printf("-지존짱짱코딩박사준성이-");
end:
    system("cls");
    gotoxy(30, 10);
    printf("==========================GAMEOVER==========================\n\n");
    gotoxy(58, 15);
    printf("점수=%d\n\n\n\n\n\n\n\n\n\n\n\n", Score);
    gotoxy(10, 20);
    printf("안타 : %d번  |  2루타 : %d번  |  3루타 : %d번  |  홈런 : %d번  |  장외홈런 : %d번", a1, a2, a3, a4, a5);
    Sleep(5000);
    goto intro;
}
