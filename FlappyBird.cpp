#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fstream>

using namespace std;

int x = 400;
int y = 50;
int score = 21;
int s = 0;

// upper pipe
int speed = 5;
int pipeX = 700;
int pipeW = 60;
int pipeY = 0;
int pipeYe = 200;

// lower pipe
int pipeXd = 700;
int pipeWd = 60;
int pipeYd = 400;
int pipeYed = 600;

// upper pipe 2
int pipeX2 = 700;
int pipeW2 = 60;
int pipeY2 = 0;
int pipeYe2 = 300;

// lower pipe 2
int pipeXd2 = 700;
int pipeWd2 = 60;
int pipeYd2 = 500;
int pipeYed2 = 600;

// Upper grass
int grassX = 0;
int grassY = 0;
int grassXT = 30;
int grassYT = 30; //[14];
int grassX_C = 60;
int grassY_C = 0;

// Bottom grass
int grassXD = 0;
int grassYD = 600;
int grassXTD = 30;
int grassYTD = 570; //[14];
int grassX_CD = 60;
int grassY_CD = 600;

int GapX_G = 0;
int grassC = 0;

int GapX = 350;
int GapY = 150;
char sc[10];

char key;
bool flag = false;
bool namefound = false;
string name;
int fscore=0;

bool gameover();
void bird();
void pipes();
bool start();
void ScoreT();
void background();
void drawGrass();
void intro();
void info();
void updatefile();
void fileout();

int main()
{
    srand(time(NULL));

    // for (int i = 0; i < 14; i++)
    // {
    //     grassYT[i] = rand() % 31 + 5;
    // }

    // int x1 = 800, y1 = 600;
    // setcolor(BLUE);
    // initwindow(x1, y1);
    // setfillstyle(SOLID_FILL, BLUE);
    // floodfill(x1, y1, BLUE); // x, y inside

    int x1 = 800, y1 = 600;

    initwindow(x1, y1);
    background();

    drawGrass();
    pipes();
    bird();

    intro();

    if (key == 'G' || key == 'g')
    {
        cleardevice();
        background();
        drawGrass();
        info();
        setcolor(WHITE);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        outtextxy(140, 500, (char *)"PRESS ANY KEY TO START");

        if (start())
        {
            while (!gameover())
            {
                // setactivepage(page);
                // setvisualpage(page);
                cleardevice();

                background();
                drawGrass();
                pipes();
                bird();

                // grassXT = rand() % 31;

                ScoreT();
                y += 11;
                delay(30);

                if (kbhit())
                {
                    char k = getch(); // reads key without stopping
                    if (k == ' ')
                    {
                        y -= 50;
                    }
                }

                // page = 1 - page;
                grassC++;
            }
        }

        cleardevice();
        background();
        drawGrass();
        setcolor(WHITE);

        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
        outtextxy(220, 100, (char *)"+++++++++++");
        setcolor(RED);
        outtextxy(230, 150, (char *)"GAME OVER");
        setcolor(WHITE);
        outtextxy(220, 200, (char *)"+++++++++++");
        outtextxy(280, 300, (char *)"SCORE:");
        outtextxy(460, 300, sc);
        updatefile();
        getch();
    }

    else if (key == 'L' || key == 'l')
    {
        cleardevice();
        background();
        setcolor(YELLOW);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
        outtextxy(163, 100, (char *)"*LEADERBOARD*");
        fileout();
        getch(); // wait for user to press a key
    }

    else if (key == 'Q' || key == 'q')
    {
        closegraph();
    }
    closegraph();
    return 0;
}

void info()
{
    setcolor(WHITE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
    outtextxy(220, 100, (char *)"ENTER YOUR NAME:");

    cin >> name;

    bool found = false;
    ifstream file("data.txt");
    string n;
    int lastscore;

    if (file)
    {
        while (file >> n >> lastscore)
        { 
            if (n == name)
            {
                found = true;
                namefound = true;
                fscore = lastscore; 
                char scoreStr[10];
                sprintf(scoreStr, "%d", lastscore);

                outtextxy(240, 270, (char *)"NAME MATCHED!");
                outtextxy(240, 300, (char *)"LAST SCORE:");
                outtextxy(500, 300, scoreStr);
                break;
            }
        }
        file.close();
    }

    if (!found)
    {
        namefound = false;
        fscore = 0;
        outtextxy(290, 150, (char *)name.c_str());
    }

    getch();
}

void updatefile()
{
    ifstream infile("data.txt");
    ofstream outfile("temp.txt");
    bool found = false;

    string n;
    int scfile;
    while (infile >> n >> scfile)
    {
        if (n == name)
        {
            scfile = fscore; 
            found = true;
        }
        outfile << n << " " << scfile << endl;
    }

    if (!found)
    {
        outfile << name << " " << fscore << endl;
    }

    infile.close();
    outfile.close();

    // Replace old file with updated file
    remove("data.txt");
    rename("temp.txt", "data.txt");
}

void fileout()
{
    ifstream file("data.txt");
    if (file)
    {
        string n2;
        int sco;
        setcolor(WHITE);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
        outtextxy(220, 200, (char *)"********************");
        outtextxy(250, 250, (char *)" NAME ");
        outtextxy(400, 250, (char *)" SCORE ");
        int i = 280;
        while (file >> n2 >> sco)
        {
            outtextxy(250, i, (char *)n2.c_str());
            char scoreStr[10];
            sprintf(scoreStr, "%d", sco);
            outtextxy(400, i, scoreStr);
            i += 40; 
        }
    }
    file.close();
}

void intro()
{
    setcolor(WHITE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(163, 100, (char *)"FLAPPY BIRD!");

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(170, 170, (char *)"G");
    outtextxy(172, 230, (char *)"L");
    outtextxy(170, 280, (char *)"Q");

    outtextxy(202, 170, (char *)" - START GAME");
    outtextxy(200, 230, (char *)" - LEADERBOARD");
    outtextxy(202, 280, (char *)" - QUIT");

    key = getch();
}

void background()
{
    setfillstyle(SOLID_FILL, COLOR(135, 206, 235));
    bar(0, 0, 800, 600);
}

void bird()
{
    setcolor(BLACK); // border
    circle(x, y, 20);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(x, y, BLACK); // x, y inside

    // Bird eye
    setcolor(BLACK);
    circle(x + 5, y, 5);
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(x + 5, y, BLACK);

    // Bird beak
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillellipse(x + 25, y, 12, 7);
}

void drawGrass()
{
    // srand(time(NULL));
    //  Set the fill color
    setfillstyle(SOLID_FILL, GREEN);
    int tempX = 0;
    int i = 0;
    for (tempX = 0; tempX < 800; tempX += 60)
    {
        // Define triangle points
        int tri[8] = {
            grassX + tempX, grassY,     // left bottom
            grassXT + tempX, grassYT,   // top point
            grassX_C + tempX, grassY_C, // right bottom
            grassX + tempX, grassY      // repeat first point to close the triangle
        };

        // Draw and fill the triangle

        fillpoly(4, tri);
    }

    for (tempX = 0; tempX < 800; tempX += 60)
    {
        // Define triangle points
        int tri2[8] = {
            grassXD + tempX, grassYD,     // left bottom
            grassXTD + tempX, grassYTD,   // top point
            grassX_CD + tempX, grassY_CD, // right bottom
            grassXD + tempX, grassYD      // repeat first point to close the triangle
        };

        // Draw and fill the triangle

        fillpoly(4, tri2);
    }

    // GapX_G += 60;

    // if (GapX_G > 800)
    // {
    //     GapX_G = 0;
    // }
}

bool start()
{
    while (!kbhit())
    {
        delay(50);
    }
    char k = getch();
    return k;
}

bool gameover()
{
    if (y >= 600 || y <= 0)
    {
        return true;
    }

    if (y - 15 <= grassYT)
    {
        return true;
    }

    if (y + 15 >= grassYTD)
    {
        return true;
    }

    if (x + 20 >= pipeX && x - 20 <= (pipeX + pipeW))
    {
        if (y - 20 <= pipeYe || y + 20 >= pipeYd)
        {
            return true;
        }
        score++;
    }

    if (x + 20 >= (pipeX2 + GapX) && x - 20 <= (pipeX2 + pipeW2 + GapX))
    {
        if (y - 20 <= pipeYe2 || y + 20 >= pipeYd2)
        {
            return true;
        }
        score++;
    }

    return false;
}

bool c, c1;
void ScoreT()
{
    if (x == pipeX + pipeW + 2 || x == pipeXd2 + pipeW2 + 2)
    {
        if (c == 0)
        {
            score += 1;
            c++;
        }
    }

    setcolor(WHITE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(50, 40, (char *)"SCORE = ");
    fscore=1 + (score - 41) / 20;
    sprintf(sc, "%d", fscore);
    outtextxy(210, 40, sc);
    //(70,20,score);
    // cout<<score;
    // outtextxy(70, 20, (char*)score);
}
void pipes()
{
    // cleardevice();
    setcolor(BLACK);
    rectangle((pipeX), pipeY, (pipeX + pipeW), pipeYe);
    setfillstyle(SOLID_FILL, GREEN);
    floodfill((pipeX + 1), (pipeY + 1), BLACK);

    setcolor(BLACK);
    rectangle((pipeXd), pipeYd, (pipeXd + pipeWd), pipeYed);
    setfillstyle(SOLID_FILL, GREEN);
    floodfill((pipeXd + 1), (pipeYd) + 1, BLACK);

    setcolor(BLACK);
    rectangle((pipeX2) + GapX, pipeY2, (pipeX2 + pipeW2) + GapX, pipeYe2);
    setfillstyle(SOLID_FILL, GREEN);
    floodfill((pipeX2 + 1) + GapX, (pipeY2 + 1), BLACK);

    setcolor(BLACK);
    rectangle((pipeXd2) + GapX, pipeYd2, (pipeXd2 + pipeWd2) + GapX, pipeYed2);
    setfillstyle(SOLID_FILL, GREEN);
    floodfill((pipeXd2 + 1) + GapX, (pipeYd2) + 1, BLACK);

    pipeX -= speed;
    pipeXd -= speed;

    if ((pipeX + pipeW) < 0)
    {
        pipeX = 700 + GapX;
        pipeXd = 700 + GapX;
        pipeYe = rand() % 301 + 100;
        pipeYd = pipeYe + GapY;
        pipeYed = 600;
        c = 0;
    }

    pipeX2 -= speed;
    pipeXd2 -= speed;

    if ((pipeX2 + GapX + pipeW2) < 0)
    {
        // if((pipeX2+GapX+10)>(pipeX+pipeW))
        pipeX2 = 700;
        pipeXd2 = 700;
        pipeYe2 = rand() % 301 + 100;
        pipeYd2 = pipeYe2 + GapY;
        pipeYed2 = 600;
        c1 = 0;
    }
}