#include <iostream>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <Mmsystem.h>
#include <thread>
#include <mutex>
#include "util.cpp"

#define ABS(x) ((x)>=0?(x):(-(x)))

#define PEACE_MAZE 0
#define COMBAT_MAZE 1
#define COMBAT_CHASE_MAZE 2
#define COLOR_MAZE 3

using namespace std;


///***************************     PART 1

typedef struct
{
    char name[100];
    int lv; //等级
    int hp; //生命值
    int maxhp;  //最大生命值
    int mp; //魔法值
    int maxmp;  //最大魔法值
    int atk;    //攻击力
    int def;    //防御力
    int spd;    //速度
    int skill[10];  //技能组
    int exp;    //经验值
    int maxexp;     //最大经验值
    int skillPoint; //属性点
}PLAYER;

typedef struct
{
    char name[100];
    int lv;
    int hp;
    int maxhp;
    int atk;
    int def;
    int spd;
    int loop[10];
    int expGiven;   //战胜获得的经验值
}MONSTER;

PLAYER player;
int playerDodge;
int enemyDodge;
int attribute[5];
MONSTER monster[100];
char temp[100];
char temp1[100];
int atkPA;  //临时附加值
int defPA;
int spdPA;
int atkMA;
int defMA;
int spdMA;
char tips[100][100];
char hoboName[10][10];
char conversation[10][10][100];
char buffName[20][20]={"空","恢复","流血","聚力","硬化","避矢","暴怒","虚弱","濒死"};
char buffDes[100][100];
char skillName[20][20]={"空","重击(30)","治愈(20)","疾风连击(22)","血刀(5)","吸血术(25)","备战(15)","暴怒(20)","腐蚀(20)","神风(50)","回春(32)","审判(50)"};
char skillDes[100][100];

void LoadPlayer();
void SavePlayer();
void LoadTips();
void LoadConversation();
void LoadDescription();
void LoadMonster();
void Initialization();
void Title();
void Passage(int n);
void CharaCreate();
void Credit();
void HoboChat(int hID);
void HealthBar(int hp,int maxhp);
void MagicBar(int mp,int maxmp);
void Info(MONSTER enemy);
void NormalAttack(int isFromPlayer,MONSTER &enemy);
int MagicSkill(int isFromPlayer,MONSTER &enemy);
void Dodge(int isFromPlayer,MONSTER enemy);
void EnemyIntend(MONSTER enemy,int act);
void EnemyAction(MONSTER &enemy,int &act);
int Fight(int mID);
void FightWin(MONSTER enemy);
void FightLose();
void FightFlee();
void SkillRoll();
void Attributes();
void AttributeDistribute(int distribute[],int n);
void BGM(int mID);

///动作记录类
class Movement
{
    private:
        char text[1000][100];
        int front;
        int rear;
        int maxsize;

    public:
        void Init()
        {
            front=rear=0;
        }
        void Push(char *s)
        {
            strcpy(text[rear++],s);
        }
        void Pop()
        {
            front++;
        }
        int Length()
        {
            return rear-front;
        }
        void Traverse()
        {
            int x=72,y=21;
            for(int i=front;i<rear;i++)
            {
                GotoXY(x,y++);
                printf("%s",text[i]);
            }
        }
}record;

///动画类
class Anime
{
    public:
        static void PlayerAttack()
        {
            GotoXY(0,0);
            Player2();Sleep(100);
        }
        static void PlayerHit()
        {
            GotoXY(0,0);
            Player0();Sleep(400);
        }
        static void PlayerRaise()
        {
            GotoXY(0,0);
            Player4();Sleep(500);
        }
        static void PlayerCombo()
        {
            for(int i=0;i<3;i++)
            {
                GotoXY(0,0);
                Player2();
                Sleep(100);
                GotoXY(0,0);
                Player3();
                Sleep(100);
            }
            GotoXY(0,0);
            Sleep(100);
            Player5();
            Sleep(260);
            GotoXY(0,0);
            Player6();
            Sleep(400);
        }
        static void PlayerDie()
        {
            GotoXY(0,0);
            printf("                                   \n");
            printf("                                   \n");
            printf("                                    \n");
            Color(6);
            printf("     _____                           \n");
            printf("    (_____)                        \n");
            Color(16);
            printf("     -----                         \n");
            printf("    | X X |                         \n");
            printf("    |  o /                          \n");
            printf("    |   |                          \n");
            printf("     \\ /                           \n");
            printf("      V              @              \n");
            printf("     _              @ @             \n");
            printf("     X      @@     @   @            \n");
            printf("      p@  @@@@@@  @     @           \n");
            printf("     X  @@@@@@@@@@@@@    @          \n");
            printf("     -    @@@@@@@@@@@@@@@@@@@@@@    \n");
        }
        static void Player0()
        {
            printf("                                   \n");
            printf("                                   \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                                   \n");
            printf("                                   \n");
            printf("                                   \n");
            printf("          ( X_X)        |           \n");
            printf("             @        \\  /        \n");
            printf("        @@@@@@@@@@@  -     -        \n");
            printf("       @@   @@@    @@ /  \\         \n");
            printf("       @    @@@     @   |           \n");
            printf("           @@@@                    \n");
            printf("           @@  @@                  \n");
            printf("           @@   @@                 \n");
            printf("            @@   @@                \n");
        }
        static void Player1()
        {
            printf("                                   \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("               ( ^_^)               \n");
            printf("                 @                  \n");
            printf("            @@@@@@@@@@@             \n");
            printf("           @@  @@@    @@            \n");
            printf("           @   @@@     @            \n");
            printf("               @@@@                 \n");
            printf("              @@  @@@               \n");
            printf("             @@     @@              \n");
            printf("            @@      @@              \n");
        }
        static void Player2()
        {
            printf("                                   \n");
            printf("                                   \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                         ( ^_^)     \n");
            printf("                           @          \\ /  \n");
            printf("                      @@@@@@@@@@@@@@   \n");
            printf("                     @    @@@         / \\  \n");
            printf("                      @@  @@@              \n");
            printf("                         @@@@              \n");
            printf("                        @@  @@@            \n");
            printf("                       @@     @@           \n");
            printf("                      @@      @@    \n");
        }
        static void Player3()
        {
            printf("                                   \n");
            printf("                                   \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                                    \n");
            printf("                         ( ^_^)            \n");
            printf("                           @               \n");
            printf("                        @@@@@@@@           \n");
            printf("                         @@@@         \\ /  \n");
            printf("                          @@@@@@@@@@   \n");
            printf("                         @@@@         / \\  \n");
            printf("                        @@  @@@     \n");
            printf("                       @@     @@    \n");
            printf("                      @@      @@    \n");
        }
        static void Player4()
        {
            Color(6);
            printf("         |               |         \n");
            printf("         |   |      |    |         \n");
            printf("         |            |  |          \n");
            printf("         |  |    |       |          \n");
            printf("         |          |    |          \n");
            printf("         |    |          |          \n");
            printf("         |   |       |   |          \n");
            printf("         | @   ( ^_^)  @ |          \n");
            printf("         | @@    @    @@ |          \n");
            printf("         |  @@@@@@@@@@@  |          \n");
            printf("         | |    @@@  |   |          \n");
            printf("         |      @@@   |  |          \n");
            printf("         |  |   @@@@     |          \n");
            printf("         | |   @@  @@@ | |          \n");
            printf("       __|    @@     @@ ||__        \n");
            printf("     ----   @@       @@   -----     \n");
            Color(16);
        }
        static void Player5()
        {
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("           @   ( ^_^)  @                   \n");
            printf("           @@    @    @@                   \n");
            printf("            @@@@@@@@@@@                    \n");
            printf("                @@@                        \n");
            printf("                @@@                        \n");
            printf("                @@@@                       \n");
            printf("               @@  @@@                     \n");
            printf("              @@     @@                    \n");
            printf("            @@       @@                    \n");
        }
        static void Player6()
        {
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("                                           \n");
            printf("                         ( ^_^)            \n");
            printf("                   @@@@@@@@@               \n");
            printf("                @@@@@@@@@@@                             |\n");
            printf("                @@@@     @@@                           \\ /\n");
            printf("               @@  @@@     @@                         - X -\n");
            printf("              @@     @@   *@@ *                        / \\\n");
            printf("            @@       @@   \\@@/ w w o o o o o O O O 0 @  |\n");
        }
        static void Monster(int mID)
        {
            int x,y;
            GotoXY(50,0);
            GetXY(x,y);
            switch(mID)
            {
                case 1:
                {
                    printf("    |    ");GotoXY(50,++y);
                    printf("    |    ");GotoXY(50,++y);
                    printf("    |    ");GotoXY(50,++y);
                    printf("    |    ");GotoXY(50,++y);
                    printf("   / \\  ");GotoXY(50,++y);
                    printf("   ---   ");GotoXY(50,++y);
                    printf("  |XXX|  ");GotoXY(50,++y);
                    printf("  |XXX|  ");GotoXY(50,++y);
                    printf("  |XXX|  ");GotoXY(50,++y);
                    printf("  |XXX|  ");GotoXY(50,++y);
                    printf("  |XXX|  ");GotoXY(50,++y);
                    printf("   ---   ");GotoXY(50,++y);
                }break;
                case 2:
                {
                    y=10;
                    GotoXY(50,++y);
                    printf("       .;7      ");GotoXY(50,++y);
                    printf("      DG;7M     ");GotoXY(50,++y);
                    printf("   :l@@@vl@@7   ");GotoXY(50,++y);
                    printf("  .@@@@@@@@@@S  ");GotoXY(50,++y);
                }break;
                case 3:
                {
                    printf("                                   \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("               ___                 \n");GotoXY(50,++y);
                    printf("              (O_O )               \n");GotoXY(50,++y);
                    printf("                @                  \n");GotoXY(50,++y);
                    printf("            @@@@@@@@@@@             \n");GotoXY(50,++y);
                    printf("       -==*======#=V@#@            \n");GotoXY(50,++y);
                    printf("           @   @@@  #@            \n");GotoXY(50,++y);
                    printf("               @@@@                 \n");GotoXY(50,++y);
                    printf("             @@@  @@               \n");GotoXY(50,++y);
                    printf("            @@     @@              \n");GotoXY(50,++y);
                    printf("            @@      @@              \n");GotoXY(50,++y);
                }break;
                case 4:
                {
                    printf("                                   \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("              ######                \n");GotoXY(50,++y);
                    printf("             #(o_o )#              \n");GotoXY(50,++y);
                    printf("                @                  \n");GotoXY(50,++y);
                    printf("            ###@@#@@###             \n");GotoXY(50,++y);
                    printf("      =-==*=####=#=V@#@            \n");GotoXY(50,++y);
                    printf("           @   ###  #@            \n");GotoXY(50,++y);
                    printf("               ###                 \n");GotoXY(50,++y);
                    printf("             #@@  @#               \n");GotoXY(50,++y);
                    printf("            ##     ##              \n");GotoXY(50,++y);
                    printf("            @@      @@              \n");GotoXY(50,++y);
                }break;
                case 5:
                {
                    printf("                                   \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("                                    \n");GotoXY(50,++y);
                    printf("               ___                   \n");GotoXY(50,++y);
                    printf("              /_★_\\                 \n");GotoXY(50,++y);
                    printf("              (-_O )               \n");GotoXY(50,++y);
                    printf("                @                  \n");GotoXY(50,++y);
                    printf("            @@@@@@@@@@@             \n");GotoXY(50,++y);
                    printf("       -==*======#=V@#@            \n");GotoXY(50,++y);
                    printf("           @   @@@  #@            \n");GotoXY(50,++y);
                    printf("               @@@@                 \n");GotoXY(50,++y);
                    printf("             @@@  @@               \n");GotoXY(50,++y);
                    printf("            @@     @@              \n");GotoXY(50,++y);
                    printf("            @@      @@              \n");GotoXY(50,++y);
                }break;
                case 6:
                {
                    Color(12);
                    y=10;
                    GotoXY(50,++y);
                    printf("       .;7      ");GotoXY(50,++y);
                    printf("      DG;7M     ");GotoXY(50,++y);
                    printf("   :l@@@vl@@7   ");GotoXY(50,++y);
                    printf("  .@@@@@@@@@@S  ");GotoXY(50,++y);
                    Color(16);
                }break;
                case 7:
                {
                    Color(1);
                    y=10;
                    GotoXY(50,++y);
                    printf("       .;7      ");GotoXY(50,++y);
                    printf("      DG;7M     ");GotoXY(50,++y);
                    printf("   :l@@@vl@@7   ");GotoXY(50,++y);
                    printf("  .@@@@@@@@@@S  ");GotoXY(50,++y);
                    Color(16);
                }break;
                case 10:
                {
                    printf("     @     @   ");GotoXY(50,++y);
                    printf("    @@ccccc@@  ");GotoXY(50,++y);
                    printf("     \\");
                    Color(12);printf("=====");Color(16);
                    printf("/    ");GotoXY(50,++y);
                    printf("      Y@@@Y     ");GotoXY(50,++y);
                    printf(" A     S@S     A");GotoXY(50,++y);
                    printf("AAA@@@XX@@@@@@AAA");GotoXY(50,++y);
                    printf("@@@@@@@XX@@@@@@@@");GotoXY(50,++y);
                    printf("@@@ @@@@XX@@@ @@@");GotoXY(50,++y);
                    printf("@@  XXXXXXXXX  @@");GotoXY(50,++y);
                    printf("@@   @@@@@@@   @@ ");GotoXY(50,++y);
                    printf("@@   =#=#=#=   @@ ");GotoXY(50,++y);
                    printf(" @@  @@@@@@@  @@");GotoXY(50,++y);
                    printf("    @@@   @@@   ");GotoXY(50,++y);
                    printf("    @@@   @@@    ");GotoXY(50,++y);
                    printf("    @@     @@    ");GotoXY(50,++y);
                    printf("    @@     @@    ");GotoXY(50,++y);
                }break;
                case 11:
                {
                    printf("                          ");GotoXY(50,++y);
                    printf("                          ");GotoXY(50,++y);
                    printf("                          ");GotoXY(50,++y);
                    printf("                          ");GotoXY(50,++y);
                    printf("                          ");GotoXY(50,++y);
                    printf("     @@5                  ");GotoXY(50,++y);
                    printf("    (^o^)                 ");GotoXY(50,++y);
                    printf("  @  O@7                  ");GotoXY(50,++y);
                    printf("  7  @@                   ");GotoXY(50,++y);
                    printf("   7lT8@                  ");GotoXY(50,++y);
                    printf("    0@@@S                 ");GotoXY(50,++y);
                    printf("   9@M#@@7                ");GotoXY(50,++y);
                    printf("   @@MD#d@@               ");GotoXY(50,++y);
                    printf("  Tl@@Md#d8M@8            ");GotoXY(50,++y);
                    printf("  @@@@888@@@@@            ");GotoXY(50,++y);
                    printf("    sXEZUc7               ");GotoXY(50,++y);
                }break;
                case 12:
                case 14:
                {
                    printf("      k       #T,            ");GotoXY(50,++y);
                    printf("     .s77P,, 7@@@@@@@7       ");GotoXY(50,++y);
                    printf("     Z@dM@#Zc,T@@h#@@@@s     ");GotoXY(50,++y);
                    printf("  k,   ZD00@@GX72@bhE@@@@@c  ");GotoXY(50,++y);
                    printf(" FKM   #0MMl1YC#88@M@7       ");GotoXY(50,++y);
                    Color(12);printf(" ￠");Color(16);printf("@@ TUhTUZc7S#MM#OM@      ");GotoXY(50,++y);
                    printf("  TD@@@D,7Plvh@@@@l  s.      ");GotoXY(50,++y);
                    printf("     @@7S7E5@@X5d7           ");GotoXY(50,++y);
                    printf("       5,7Y7M@7              ");GotoXY(50,++y);
                    printf("       *EhS70@@Mh7        ,7 ");GotoXY(50,++y);
                    printf("       #@hhh0@b@P@M@b      ,S");GotoXY(50,++y);
                    printf("      ,@,7Od87@@@@G@@,     M");GotoXY(50,++y);
                    printf("       E7CFPM  77@  @@7,.,@1");GotoXY(50,++y);
                    printf("      ,@GG7b,  DC@   Y@@8P7 ");GotoXY(50,++y);
                    printf("     ,#@@@87  v8@@          ");GotoXY(50,++y);
                    printf("    ,GZ,,7                  ");GotoXY(50,++y);
                }break;
                default:break;
            }
            GotoXY(0,0);
        }
        static void Portrait(int hID)
        {
            int x,y;
            x=10,y=30;
            GotoXY(x,y);
            printf("/------------\\");GotoXY(x,y+1);
            printf("|            |  ");Color(1);printf("%s          ",hoboName[hID]);Color(16);GotoXY(x,y+2);
            printf("|            |----------------------------------------------------------------------------- ");GotoXY(x,y+3);
            printf("|            |                                                                             |");GotoXY(x,y+4);
            printf("|            |                                                                             |");GotoXY(x,y+5);
            printf("|            |                                                                   [Enter]▼ |");GotoXY(x,y+6);
            printf("|            |----------------------------------------------------------------------------- ");GotoXY(x,y+7);
            printf("\\------------/");
            GotoXY(x+1,y+1);
            switch(hID)
            {
                case 1:
                {
                    printf("   @@@@@    ");GotoXY(x+1,y+2);
                    printf(" @@#####@@  ");GotoXY(x+1,y+3);
                    printf("   ( O_O)   ");GotoXY(x+1,y+4);
                    printf("     ##     ");GotoXY(x+1,y+5);
                    printf("  @@@@@@@   ");GotoXY(x+1,y+6);
                    printf(" @@@@@@@@@@ ");GotoXY(x+1,y+7);
                }break;
                case 2:
                {
                    printf("            ");GotoXY(x+1,y+2);
                    printf("            ");GotoXY(x+1,y+3);
                    printf("     ( ._.) ");GotoXY(x+1,y+4);
                    printf("     @@     ");GotoXY(x+1,y+5);
                    printf("  @@@@@@    ");GotoXY(x+1,y+6);
                    printf(" @@@@@@@@   ");GotoXY(x+1,y+7);
                }break;
                case 3:
                {
                    printf("    ***     ");GotoXY(x+1,y+2);
                    printf("  *******   ");GotoXY(x+1,y+3);
                    printf(" *( ^V^ )*  ");GotoXY(x+1,y+4);
                    printf("    @@      ");GotoXY(x+1,y+5);
                    printf("  @@@@@@    ");GotoXY(x+1,y+6);
                    printf(" @@@@@@@@   ");GotoXY(x+1,y+7);
                }break;
                case 4:
                {
                    printf("    @@@@    ");GotoXY(x+1,y+2);
                    printf("  @@@@@@@@  ");GotoXY(x+1,y+3);
                    printf("   ( O O)   ");GotoXY(x+1,y+4);
                    printf("    (/-\\)  ");GotoXY(x+1,y+5);
                    printf("  @@@@@@@@  ");GotoXY(x+1,y+6);
                    printf(" @@@@@@@@@@ ");GotoXY(x+1,y+7);
                }break;
                case 5:
                {
                    printf("    @       ");GotoXY(x+1,y+2);
                    printf("   @@@@     ");GotoXY(x+1,y+3);
                    printf(" @@@@@@@@@  ");GotoXY(x+1,y+4);
                    printf("   ( -_-)   ");GotoXY(x+1,y+5);
                    printf("    @@@@    ");GotoXY(x+1,y+6);
                    printf("   @@@@@@   ");GotoXY(x+1,y+7);
                }break;
                case 6:
                {
                    printf("            ");GotoXY(x+1,y+2);
                    printf("            ");GotoXY(x+1,y+3);
                    printf("     NO     ");GotoXY(x+1,y+4);
                    printf("   SIGNAL   ");GotoXY(x+1,y+5);
                    printf("            ");GotoXY(x+1,y+6);
                    printf("            ");GotoXY(x+1,y+7);
                }break;
                default: break;
            }
        }
        static void ErasePortrait()
        {
            int x,y;
            x=10,y=30;
            GotoXY(x,y);
            printf("                                                                                                ");GotoXY(x,y+1);
            printf("                                                                                                ");GotoXY(x,y+2);
            printf("                                                                                                ");GotoXY(x,y+3);
            printf("                                                                                                ");GotoXY(x,y+4);
            printf("                                                                                                ");GotoXY(x,y+5);
            printf("                                                                                                ");GotoXY(x,y+6);
            printf("                                                                                                ");GotoXY(x,y+7);
            printf("                                                                                                ");
        }
        static void Victory(MONSTER enemy)
        {
            int x,y;
            GotoXY(40,8);
            GetXY(x,y);
            Color(6);
            printf("@M    @E      @;           @@      @         Pd      @F        @Z @; @");GotoXY(x,++y);
            printf("9@    @S     @@7          8@;    ;@@@:       @@      @@@C      5@ @7;@");GotoXY(x,++y);
            printf(" @0  v@    h@Z@c        ;@@     @@Z@X@@     @M8@     @; l@@U    @@@@@.");GotoXY(x,++y);
            printf(" P@  @@    1, @s       0@5      S  @  S    d@  @b    @; T@@G     @@@9 ");GotoXY(x,++y);
            printf(" .@  @T       @c     ,@@          :@:     7@;  :@7   @@MX.       ;@@  ");GotoXY(x,++y);
            printf("  @5;@        @c     ,@@          :@:     7@;  ;@7   @@;          @X  ");GotoXY(x,++y);
            printf("  9@@@        @; 2.    G@5        ;@:      P@  @#    @P@@         @G  ");GotoXY(x,++y);
            printf("  .@@7        @0@@      ;@@       ;@:       @@b@     @; @@;       @0  ");GotoXY(x,++y);
            printf("   @@         @@;         h@7     ,@.        @@      @7  7@X      @O  ");
            Color(16);
            GotoXY(48,++++++++y);
            printf("/-------------------- 战斗胜利 ---------------------\\");GotoXY(48,++++y);
            printf("                  你击败了%s！",enemy.name);GotoXY(48,++++y);
            printf("                  获得了%d经验值",enemy.expGiven);GotoXY(48,++y);
            printf("                 已恢复%d点生命值",(int)(player.maxhp*0.2));GotoXY(48,++++y);
            printf("\\---------------------------------------------------/");
        }
        static void Defeated()
        {
            int x,y;
            GotoXY(28,12);
            GetXY(x,y);
            Color(4);
            printf("P@  @7 E@       @X       M#     @;           Cd             ,@.             O@    @v      ");GotoXY(x,++y);
            printf("1@T @Y @@      ,@@       @@    ,@S           @@E           :@@;            5@M    @@7     ");GotoXY(x,++y);
            printf(" 1@Y@C@@       @@@@      @@    ;@O           @@@@:        8@@@7           @@T     @@@@    ");GotoXY(x,++y);
            printf("  @@@@@7      @@ :@Z     @@    ;@O           @@ 8@F      @@::@7         7@@       @E @@7  ");GotoXY(x,++y);
            printf("  .@@@D      7@U  @@,    @@    :@2           @@  l@@        7@7        X@T        @b  M@Z ");GotoXY(x,++y);
            printf("   5@@       @@    @@    @@    ;@O           @@    @@7      7@7      ,@@@5Z8@#    @@   ;@@");GotoXY(x,++y);
            printf("    @Z       @@    @@    @@    ,@2           @@    @@7      Y@7      .@@@75UhX    @M   ;@@");GotoXY(x,++y);
            printf("    @0       ;@0  @@     @@    .@P           @@  l@@        7@;  .     S@U        @8  8@X ");GotoXY(x,++y);
            printf("    @9        #@ ;@5     @@   5@@c           @@ M@F         Y@:7@h      ;@@,      @Z @@;  ");GotoXY(x,++y);
            printf("   .@h         @@@@      @@:@@@2             @@@@;          7@@@S         @@5     @@@@    ");GotoXY(x,++y);
            printf("    @U          @@       @@@l                @@5            ;@@            7@@    @@;     ");GotoXY(x,++++y);
            Color(16);
            printf("                        /                                     \\                          ");GotoXY(x,++y);
            printf("                         你的最大生命值减少10%%，返回传火祭祀场                            ");GotoXY(x,++y);
            printf("                        \\                                     /                          ");GotoXY(x,++y);
        }
        static void Flee()
        {
            int x,y;
            GotoXY(30,10);
            GetXY(x,y);
            printf("        F@            v@.           c@.    @7            @U                   7@");GotoXY(x,++y);
            printf("       l@@           7@@           7@@    ;@@5           @@@1                7@@");GotoXY(x,++y);
            printf("      @@M           @@@           @@@     7@@@@7        .@@1@@@7            @@@ ");GotoXY(x,++y);
            printf("    ;@@s          .@@U          .@@U      7@S @@@,       @@  ,P@@M,       ,@@O  ");GotoXY(x,++y);
            printf("   5@@.          7@@;          c@@;       7@#  ;@@G      @@   7@@@7      Y@@;   ");GotoXY(x,++y);
            printf("  8@2           P@D           d@@         ;@@@   O@@.    @@:@@@0,       9@P     ");GotoXY(x,++y);
            printf("l@@@XP@@@@.   ,@@@0FEU9#.   :@@T          7@@@@Z  0@7    @@@@7        ,@@@GG@@@b");GotoXY(x,++y);
            printf("s@@@CX#M@@    ,@0P0Ed@@@.   ,@@1          7@U C@@:X@;    @@           .@@@OUdM@d");GotoXY(x,++y);
            printf("  b@U               8@P       h@@         7@b  .@@@@;    @@             P@d     ");GotoXY(x,++y);
            printf("   l@@.           ;@@7         Y@@;       7@8    ;@@;    @@              7@@;   ");GotoXY(x,++y);
            printf("    ;@@l         G@@.           .@@X      7@M     d@;   .@@               .@@U  ");GotoXY(x,++y);
            printf("      @@@       @@D               b@@     7@M     M@;    @@                 b@@ ");GotoXY(x,++y);
            printf("       7@@    .@@:                 ;@@    ;@D     #@:    @@                  ;@@");
            GotoXY(48,++++y);
            printf("/---------------------------------------------\\");GotoXY(48,++++y);
            printf("               你设法逃离了战斗");GotoXY(48,++++y);
            printf("\\---------------------------------------------/");
        }
        static void Promoted()
        {
            int x,y;
            GotoXY(34,8);
            GetXY(x,y);
            Color(6);
            printf("P@             ,@   Z@    @;        @@   @;                    @5   7@   v@,    ");GotoXY(x,++y);
            printf("@@            :@d   c@   ,@.       M@;   @;                    @Z   7@   C@@M;  ");GotoXY(x,++y);
            printf("@@           d@7     @l  @@      :@@    .@7                    @0   l@   Z@ ,M@0");GotoXY(x,++y);
            printf("@@          @@       @@  @X     l@7      @7                    @P   c@   G@ ;@@E");GotoXY(x,++y);
            printf("@@    U;  T@@YsUP    Y@ ,@.    @@h7CP7   @7   7S               @9   T@   F@@@7  ");GotoXY(x,++y);
            printf("@@   @@;  7@@Y7CF     @;O@     @@#;l27   @;  #@X               @E   7@   Z@     ");GotoXY(x,++y);
            printf("@@ 7@8      @@        @@@5      v@c      @. @@,                @G   P@   Z@     ");GotoXY(x,++y);
            printf("@@P@7        Z@l      7@@        ,@@     @9@d                  @S Z@@1   9@     ");GotoXY(x,++y);
            printf("M@0           .@@      @@          X@;   @@                    @@85      O@     ");
            Color(16);
            GotoXY(48,++++++++y);
            printf("/-------------------- ");
            Color(6);
            printf("等级上升");
            Color(16);
            printf(" ---------------------\\");GotoXY(48,++++y);
            printf("                  你已升级至等级%d！",player.lv);GotoXY(48,++++y);
            printf("             获得了可分配的属性点和新技能");GotoXY(48,++++y);
            printf("\\---------------------------------------------------/");
        }
        static void FirelinkShrine()
        {
            system("cls");
            int x=22,y=12;
            GotoXY(x,y);
            printf("cSSSOZWS FM                r@h               F@            OWW@   #M             SM                 ");GotoXY(x,++y);
            printf(" iB                         BW  S@           sB           BO  E@  M@                                ");GotoXY(x,++y);
            printf(" r@      rU   r rs   rii    @B  rF   r rcr   r@  r7       @6      6B rj    r r1  rF   r rYr     iir ");GotoXY(x,++y);
            printf(" rBrr@r  XB  rB@r@7 B#  B1  @@  k@  F@Wr @B  rB r@s        @B6    G@S r@r  @BrWs 6B  FB@r M@  O@  B6");GotoXY(x,++y);
            printf(" r@      S@   @7   r@rrr@@  @M  r@   M   5@  r@W@            m@m  hB   BH  @3    r@   @   5B  @Zrr1B");GotoXY(x,++y);
            printf(" rB      rB   Mi   iB       MB  r@   @   3B  r@ 6@        r    @  P@   @O  @1    rB   B   1@  BT    ");GotoXY(x,++y);
            printf(" i@      r@   @5    @6SBYj  @B  1B  r@   X@  7@  m@       @rJHEB  bB   B6  BG    j@  r@   XB  s@SDDj");GotoXY(x,++y);
            printf("____________________________________________________________________________________________________");GotoXY(x,++y);
            x=30,y++;
            GotoXY(x,y);
            printf("    c@   @r            mB            TB r  rBT       jB  i   i       1B  crrk@  ");GotoXY(x,++y);
            printf("   r@ rr2Br5m          S@  r        5@rM@BSE@         rO BhrFB       r@    k@   ");GotoXY(x,++y);
            printf("  5@B   BX   rr    Z@  @s 1@1      @#1#H  B@       ksrB@ @  i@       UMrrr@Z  rW");GotoXY(x,++y);
            printf("rmS @Yrr@rrriYi     H@ Bb1O       r #XPr r 1@Y       E@T BPY25     r7U@  T@1@XFB");GotoXY(x,++y);
            printf("r   B  DB  X@         r@X@         rBF r31rrTWXi   PEmBrF@           rB  TFYM B ");GotoXY(x,++y);
            printf("   r@  sr iBr         @  S@      r6  r@ @1rc      3r r@  Br    3   rS#Gc@jY#  @ ");GotoXY(x,++y);
            printf("   jB   FHB         3@r   c@i       OW3 Mr r#@r      2B  @S    @   6s  5rOks @r ");GotoXY(x,++y);
            printf("   c@     ZM      c27       @Fr    T   1@            Y#   Scjc1O        s   @U  ");GotoXY(x,++y);
            Sleep(1500);
        }
        static void ADPeak()
        {
            system("cls");
            int x=22,y=11;
            GotoXY(x,y);
            printf("      @@;             7@@7c2MM:                  Y@@7YU@Z     l@87Y7C@h        @@        Y@@.   @@P ");GotoXY(x,++y);
            printf("     S@@@              @@    Z@d                  @b   ;@@     @Z    XE       @h@M        @M   7@7  ");GotoXY(x,++y);
            printf("     @ ,@;             @@     @@;                 @h    @@     @O   ;        ;@ 2@        @E  E@    ");GotoXY(x,++y);
            printf("    @G  @@             @@     7@5                 @8  :@@;     @@7T@@        @;  @h       @@7@@     ");GotoXY(x,++y);
            printf("   ,@;:.P@;            @@     Y@1                 @@sF9l       @# ,5@       C@,,.@@       @d 9@c    ");GotoXY(x,++y);
            printf("   @G777;@@            @@     @@                  @9           @O           @v7v77@9      @0  C@O   ");GotoXY(x,++y);
            printf("  2@     l@;    s7     @@    X@l    ,s;           @d           @X    M@    @@     @@      @#   v@d  ");GotoXY(x,++y);
            printf(" 7@@.    S@@.   @@    ;@M775GU      7@1          Y@@.         Y@E77YS@c   l@0     9@D    7@@    0@d:");GotoXY(x,++y);
            printf("____________________________________________________________________________________________________");GotoXY(x,++y);
            x=35,y++;
            GotoXY(x,y);
            printf("       ..                                                       avvCl ");GotoXY(x,++y);
            printf("       @C               v@  lZ             @b               .7.  ,;   ");GotoXY(x,++y);
            printf("       @;               O@  cF,             h: cT        sG@M7, E@T7; ");GotoXY(x,++y);
            printf("   ...:@;7vCP#;      ;Tv@@@G1          ;Y11l;1@@M.         @;  @OY :@;");GotoXY(x,++y);
            printf("7PMGC78@:;;;77;      .;T@ @ .@;        :F7  s@s            @7  @ 7@ @ ");GotoXY(x,++y);
            printf("      M9               @  T:@Y            ;bS              @7  @ 0l @;");GotoXY(x,++y);
            printf("   ;@sO77G@O          @5 ;@U    ,,    cYU@C              ;s@;  M.@;.#.");GotoXY(x,++y);
            printf("    @7   G@         7@v v#@    :@@    Ps7vcXXS7:   :.     8@  .5@; 8@ ");GotoXY(x,++y);
            printf("    1C7775:        .;     ;2GEPXl            :l8@@Ds.        :7.    sY");GotoXY(x,++y);
            Sleep(1500);
        }
        static void ADClimax()
        {
            system("cls");
            int x=12,y=11;
            GotoXY(x,y);
            printf("      @@Y           ,M@@U9@@@7                  l@@UG@@P  ;@@@:       7@@M,  ;@@@.     7@@@,       G@@       ;@@@,  :@@T");GotoXY(x,++y);
            printf("     @@@@            ,@d    Z@@                @@7    @G   Z@7         #@:    D@@@     @@@,       ,@0@7        @@7  l@, ");GotoXY(x,++y);
            printf("    ;@ 7@Y           :@h     b@5              7@b          F@;         h@:    M9;@7   @X7@:       @T @@         @@;7@   ");GotoXY(x,++y);
            printf("    @7  @@           :@#     7@@              b@7          X@7         d@;    M@ @@  Y@ l@:      F@  v@7         E@@    ");GotoXY(x,++y);
            printf("   E@;;:M@T          :@D     7@b              M@7          U@;         0@:    @@  @U @; Z@;      @P;;7@@         d@@Y   ");GotoXY(x,++y);
            printf("  .@v7vY;@@          :@d     @@7              s@h          U@7    T;   h@:    M@  9@@b  X@:     @@;cv79@7       @M P@S  ");GotoXY(x,++y);
            printf("  @@     C@U   .E5   :@#    M@X   7Z7          @@;    @#   G@;   .@l   #@:    @@   @@   0@;    l@      @@     .@M   9@E ");GotoXY(x,++y);
            printf("7@@@7   ;@@@5  7@@  ,@@@ZdM@b:    8@d           Z@@90@@2  7@@@EhD@@;  7@@@,  7@@v      7@@@:  2@@U    5@@@,  1@@l   S@@9");GotoXY(x,++y);
            printf("________________________________________________________________________________________________________________________");GotoXY(x,++y);
            x=38,y++;
            GotoXY(x,y);
            printf("                                                              ;b      ");GotoXY(x,++y);
            printf("       F@,              b7  c7            bU                   @  Ch  ");GotoXY(x,++y);
            printf("       7@.              @c  1@;           :@l              M@7vX:,@7  ");GotoXY(x,++y);
            printf("       1@    ,,        ,@7YDU            ..;7C@@b          C@; .:;D7l5");GotoXY(x,++y);
            printf(";122OC1@@C0dM@@O    ;hF@h@@  Y        F@@Gv,s@@;         ;Yh@S: ;M@;7 ");GotoXY(x,++y);
            printf(".7l7,  @.              @ 1; @@:            9M;           Y@O,@Y @7. @T");GotoXY(x,++y);
            printf("      :@;;c.          @F 2;@M            C8;              @Y d  @ @ @,");GotoXY(x,++y);
            printf("    @@77:,M@P        @@  @@;     s  ;9X@@l               ;@v7D71@ @ @.");GotoXY(x,++y);
            printf("    h@    @@       7@O 7U@O    ;@@  :F;:;T9d057,  ,;,  7l7@77@7 :d0;c ");GotoXY(x,++y);
            printf("    ;@5ZZP87      ;l.  ,  0@@@@@b7          ;X@@@@@9;   ,X2  ;S;GF Y@@");GotoXY(x,++y);
            printf("                                                        ,      :     ;");GotoXY(x,++y);
            Sleep(1500);
        }
        static void Title(int i)
        {
            int x=18,y=8;
            GotoXY(x,y);
            printf("           .                       :,      ;                                                                  ");GotoXY(x,++y);
            printf("           BBB:                    7BBv   YBv70B5                GB9,                              .B5        ");GotoXY(x,++y);
            printf("           7BB                       O8;   BBc7;.                 8BB;                      ,lU7   ;BD        ");GotoXY(x,++y);
            printf("           ;BF                   :O#bBB    Bs .                     l   .7,             BB0X11BBF  BB19BB;    ");GotoXY(x,++y);
            printf("           vB                    :B  B2.   BClBBY                  :7UEBBBBM            ;Bc   BO  BB  7BB;    ");GotoXY(x,++y);
            printf("       .,:,#BY1GbBBBBBBS        :7BUdBZP;     B7           :OG#BBBBDY,FBBX;              XB :FB; #B1  BZ      ");GotoXY(x,++y);
            printf(" SBBBBBBBB9BB1SCsY7;;;77    ,BBB07      ,BO1SZZ            .SBBl:    BBC                  MBB   vY ;BBD       ");GotoXY(x,++y);
            printf("  .:,      B5                   ,5;cBB   BE;7Y                     bBh                 :   7B;Y,   1B#B9.     ");GotoXY(x,++y);
            printf("          ;B                    .B7 SB   BsYs5;                  hBM                   9BP 7BSS:  BB   BBB5:  ");GotoXY(x,++y);
            printf("      5;;7BB9dBBB97             ;Bv ;B   B77s17                SBZ                      B5 7B   58;    ,UBBBBF");GotoXY(x,++y);
            printf("      MBBv;..   BBB;            EBS7.B   B,;7O7    77    YP8MBBB                        Bv DB5llBBTCEhUMBB    ");GotoXY(x,++y);
            printf("       Bb       BB              BX   B:  BF:;;     bB    7B8Y;YOBBBZ7.               ;SOBBB5,    BB    ,Bv    ");GotoXY(x,++y);
            printf("       BB  :;77BB,             YB. 7ZB;  MB;   ,;lBBB             79BBBBBP5cYlObD,   ;BB7        SB  :;BB     ");GotoXY(x,++y);
            printf("       YBsC2FS5YY,              :   BB    :UMBBBBbC,                   ;EBBBBB97.                 B5lTY;:     ");GotoXY(x,++++y);
            printf("   --------------------------------------------------------------------------------------------------------   ");GotoXY(x,++++y);
            printf("                                  JOURNEY    TO    THE    ANCIENT    DRAGON\n");
            if(i==1)
            {
                GotoXY(64,30);
                printf("< 请 按 任 意 键 >");
            }
        }
        static void Present()
        {
            system("cls");
            Sleep(1000);
            int x,y;
            x=50,y=5;
            GotoXY(x,y);
            printf("  @@@@@      @@@@@@@@       @@@@         @@@@@ ");GotoXY(x,++y);
            printf("@@@@@@@@@   @@@@@@@@@     @@@@@@@@      @@@@@@ ");GotoXY(x,++y);
            printf("@@@@ @@@@   @@@@         @@@@  @@@     @@@@@@@ ");GotoXY(x,++y);
            printf("@@@@ @@@@   @@@@@@@@@    @@@@  @@@    @@@@@@@@ ");GotoXY(x,++y);
            printf(" @@@@@@@    @@@@@@@@@@        @@@@    @@@ @@@@ ");GotoXY(x,++y);
            printf("@@@@@@@@@         @@@@       @@@@    @@@  @@@@ ");GotoXY(x,++y);
            printf("@@@@ @@@@         @@@@      @@@@     @@@@@@@@@@");GotoXY(x,++y);
            printf("@@@@ @@@@   @@@   @@@@     @@@@      @@@@@@@@@@");GotoXY(x,++y);
            printf("@@@@ @@@@   @@@@  @@@@    @@@@  @@        @@@@ ");GotoXY(x,++y);
            printf(" @@@@@@@     @@@@@@@@    @@@@@@@@@        @@@@ ");GotoXY(x,++y);
            Sleep(2000);
            x=33,y=20;
            GotoXY(x,y);
            printf("@@@@@@@@     @@@@@@@@     @@@@@@@    @@@@@@@     @@@@@@@   @@@@  @@@   @@@@@@@@@");GotoXY(x,++y);
            printf("@@@@@@@@@    @@@@@@@@@    @@@@@@@   @@@@ @@@@    @@@@@@@   @@@@  @@@   @@@@@@@@@");GotoXY(x,++y);
            printf("@@@@  @@@    @@@@ @@@@    @@@@      @@@@  @@@    @@@@      @@@@@ @@@      @@@@  ");GotoXY(x,++y);
            printf("@@@@  @@@    @@@@ @@@@    @@@@      @@@@@        @@@@      @@@@@@@@@      @@@@  ");GotoXY(x,++y);
            printf("@@@@@@@@     @@@@@@@@     @@@@@@@     @@@@@@     @@@@@@@   @@@@@@@@@      @@@@  ");GotoXY(x,++y);
            printf("@@@@         @@@@ @@@@    @@@@          @@@@@    @@@@      @@@ @@@@@      @@@@  ");GotoXY(x,++y);
            printf("@@@@         @@@@ @@@@    @@@@      @@@@ @@@@    @@@@      @@@  @@@@      @@@@  ");GotoXY(x,++y);
            printf("@@@@         @@@@ @@@@    @@@@@@@   @@@@ @@@@    @@@@@@@   @@@  @@@@      @@@@  ");GotoXY(x,++y);
            printf("@@@@         @@@@ @@@@    @@@@@@@    @@@@@@@     @@@@@@@   @@@  @@@@      @@@@  ");GotoXY(x,++y);
            Sleep(2000);
            while(kbhit())
                getch();
        }
        static void Load()
        {
            srand(time(NULL));
            int x,y,i;
            GotoXY(34,8);
            GetXY(x,y);
            Color(16);
            printf("O@             @9       @P          8G             @Z       @S    O0          ,@");GotoXY(x,++y);
            printf("@@             @@       @@h         @@s           0@b       @@7   @@         :@M");GotoXY(x,++y);
            printf("@@            @@@@      @@@@2       @@@@        ;@@@@       @@@@  @@        Z@# ");GotoXY(x,++y);
            printf("@@           G@ ,@T     @# ;@@,     @@ @@;      @@ @@       @C @@ M@       @@T  ");GotoXY(x,++y);
            printf("@@          .@#  @@     @@l  0@G    @@  @@l        @@       @Z  @@@@     .@@,   ");GotoXY(x,++y);
            printf("@@    .@;   @@    @@    @@@@. 0@    @@   7@@       @@       @#   U@@    c@@   .Z");GotoXY(x,++y);
            printf("@@   ;@@:   @@    @M    @# 9@U#@    @@   v@@       @@       @@O   @@    7@@   7@");GotoXY(x,++y);
            printf("@@  F@b      @@  @@     @@  ,@@@    @@  @@Y        @@  .    @@@@  @@      @@; :@");GotoXY(x,++y);
            printf("@@ #@c       s@.7@7     @@    @@    @@ @@,         @0 @@    @5 @@ M@       D@Y,@");GotoXY(x,++y);
            printf("@@@@,         @@@@      @@    d@    @@@@           @@@M     @D  M@@@        7@@@");GotoXY(x,++y);
            printf("@@2            @@       @@    #@    @@7            @@:      @G   ;@@          8@");GotoXY(x,++y);
            Color(16);
            GotoXY(----x,++++++y);
            for(i=0;i<42;i++)
                printf("□");
            GotoXY(46,y+2);
            printf("Tips: %s",tips[rand()%10]);
            GotoXY(x,y);
            for(i=0;i<42;i++)
            {
                printf("■");
                GetXY(x,y);
                GotoXY(67,y-1);
                printf("载入中  %d%%",i*100/42);
                GotoXY(x,y);
                Sleep(rand()%250);
            }
        }
};

///状态类
class Status
{
    public:
        //1-恢复：每回合回复定量HP
        static void Recover(int toplayer, MONSTER &enemy)
        {
            if(toplayer)
            {
                sprintf(temp,"[恢复]你的生命值回复10点");
                record.Push(temp);
                player.hp+=10;
            }
            else
            {
                sprintf(temp,"[恢复]%s的生命值回复10点",enemy.name);
                record.Push(temp);
                enemy.hp+=10;
            }
        }
        //2-流血：每回合减少定量HP
        static void Bleed(int toplayer, MONSTER &enemy)
        {
            if(toplayer)
            {
                sprintf(temp,"[流血]你失去10点生命");
                record.Push(temp);
                player.hp-=10;
            }
            else
            {
                sprintf(temp,"[流血]%s失去10点生命",enemy.name);
                record.Push(temp);
                enemy.hp-=10;
            }
        }
        //3-聚力：临时增加ATK
        static void Brace(int toplayer, MONSTER &enemy)
        {
            if(toplayer)
            {
                sprintf(temp,"[聚力]你的攻击力提升至1.25倍");
                record.Push(temp);
                atkPA+=(int)(player.atk*0.25);
            }
            else
            {
                sprintf(temp,"[聚力]%s的攻击力提升至1.25倍",enemy.name);
                record.Push(temp);
                atkMA+=(int)(enemy.atk*0.25);
            }
        }
        //4-硬化：临时增加DEF
        static void Harden(int toplayer, MONSTER &enemy)
        {
            if(toplayer)
            {
                sprintf(temp,"[硬化]你的防御力提升至1.25倍");
                record.Push(temp);
                defPA+=(int)(player.def*0.25);
            }
            else
            {
                sprintf(temp,"[硬化]%s的防御力提升至1.25倍",enemy.name);
                record.Push(temp);
                defMA+=(int)(enemy.def*0.25);
            }
        }
        //5-避矢：临时增加SPD
        static void Evite(int toplayer, MONSTER &enemy)
        {
            if(toplayer)
            {
                sprintf(temp,"[避矢]你的速度提升至2倍");
                record.Push(temp);
                spdPA+=player.spd;
            }
            else
            {
                sprintf(temp,"[避矢]%s的速度提升至2倍",enemy.name);
                record.Push(temp);
                spdMA+=enemy.spd;
            }
        }
        //6-暴怒：ATK翻倍
        static void Rage(int toplayer, MONSTER &enemy)
        {
            if(toplayer)
            {
                sprintf(temp,"[暴怒]你的攻击力提升至2倍");
                record.Push(temp);
                atkPA+=player.atk;
            }
            else
            {
                sprintf(temp,"[暴怒]%s的攻击力提升至2倍",enemy.name);
                record.Push(temp);
                atkMA+=enemy.atk;
            }
        }
        //7-虚弱:ATK减半
        static void Weak(int toplayer, MONSTER &enemy)
        {
            if(toplayer)
            {
                sprintf(temp,"[虚弱]你的攻击力减半");
                record.Push(temp);
                atkPA-=player.atk/2;
            }
            else
            {
                sprintf(temp,"[虚弱]%s的攻击力减半",enemy.name);
                record.Push(temp);
                atkMA-=enemy.atk/2;
            }
        }
        //8-濒死：HP减少至1点
        static void Death(int toplayer, MONSTER &enemy)
        {
            if(toplayer)
            {
                sprintf(temp,"[濒死]你的生命值减至1点");
                record.Push(temp);
                if(player.hp>1)
                    player.hp=1;
            }
            else
            {
                sprintf(temp,"[濒死]%s的生命值减至1点",enemy.name);
                record.Push(temp);
                if(enemy.hp>1)
                    enemy.hp=1;
            }
        }
};


///状态操作类
class Buff
{
    private:
        typedef struct node
        {
            int ID; //Buff ID
            int turn;  //剩余持续时间
            struct node *next;
        }NODE,*LinkList;
        LinkList PList,MList;    //以带头结点的链表存放buff
    public:
        void Init()
        {
            PList=new NODE;
            MList=new NODE;
            PList->next=MList->next=NULL;
        }
        void Insert(int toPlayer, int turn, int bID)    //尾插结点
        {
            NODE *p;
            if(toPlayer)
                p=PList;
            else
                p=MList;
            while(p->next!=NULL)
            {
                if(p->next->ID==bID)
                {
                    p->next->turn+=turn;
                    return;
                }
                p=p->next;
            }
            NODE *tmp=new NODE;
            tmp->ID=bID;
            tmp->turn=turn;
            tmp->next=NULL;
            p->next=tmp;

        }
        void Delete(NODE *p)   //删除结点p的后继结点
        {
            NODE *q=p->next;
            p->next=p->next->next;
            delete q;
        }
        void Destroy()  //销毁链表
        {
            NODE *p=PList;
            NODE *q=p;
            while(p)
            {
                q=p;
                p=p->next;
                delete q;
            }
            p=MList;
            while(p)
            {
                q=p;
                p=p->next;
                delete q;
            }
        }
        void Display(int toPlayer)  //显示buff列表
        {
            NODE *p;
            if(toPlayer)
                p=PList;
            else
                p=MList;
            if(p->next==NULL)
                printf("无状态\n");
            while(p->next!=NULL)
            {
                printf("[%s](%d):",buffName[p->next->ID],p->next->turn);
                Color(0);
                printf("%s",buffDes[p->next->ID]);
                Color(16);
                p=p->next;
            }
            printf("\n (按任意键返回)");
            getch();
        }
        void Exert(int toPlayer, MONSTER &enemy)
        {
            NODE *p;
            if(toPlayer)
                p=PList;
            else
                p=MList;
            while(p->next!=NULL)
            {
                switch(p->next->ID)
                {
                    case 1: Status::Recover(toPlayer,enemy);break;
                    case 2: Status::Bleed(toPlayer,enemy);break;
                    case 3: Status::Brace(toPlayer,enemy);break;
                    case 4: Status::Harden(toPlayer,enemy);break;
                    case 5: Status::Evite(toPlayer,enemy);break;
                    case 6: Status::Rage(toPlayer,enemy);break;
                    case 7: Status::Weak(toPlayer,enemy);break;
                    case 8: Status::Death(toPlayer,enemy);break;
                    default: break;
                }
                p->next->turn--;
                p=p->next;
            }
        }
        void Expire(int toPlayer, MONSTER &enemy)
        {
            NODE *p;
            if(toPlayer)
                p=PList;
            else
                p=MList;
            while(p->next!=NULL)
            {
                if(p->next->turn==0)
                    Delete(p);
                else
                    p=p->next;
            }
        }
}buff;

///技能类
class Skill
{
    public:
        //1-重击(30)：对对方造成1.5倍普攻伤害
        static int HeavyStrike(int isFromPlayer,MONSTER &enemy)
        {
            if(isFromPlayer)
            {
                if(player.mp<30)
                {
                    sprintf(temp,"魔法值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                player.mp-=30;
                sprintf(temp,"你使用了“重击”，");
                if(enemyDodge)
                {
                    sprintf(temp1,"被闪避");
                    PlaySound(TEXT("Dodge.wav"),NULL,SND_FILENAME|SND_ASYNC);
                }
                else
                {
                    int sum=(int)((player.atk+atkPA-enemy.def-defMA)*1.5);
                    if(sum<0)
                        sum=0;
                    enemy.hp-=sum;
                    sprintf(temp1,"对%s造成了%.d点伤害",enemy.name,sum);
                    PlaySound(TEXT("Skill_HeavyAttack.wav"),NULL,SND_FILENAME|SND_ASYNC);
                }
                Anime::PlayerAttack();
            }
            else
            {
                sprintf(temp,"%s使用了“重击”，",enemy.name);
                if(playerDodge)
                {
                    sprintf(temp1,"被闪避");
                    PlaySound(TEXT("Dodge.wav"),NULL,SND_FILENAME|SND_ASYNC);
                }
                else
                {
                    int sum=(int)((enemy.atk+atkMA-player.def-defPA)*1.5);
                    if(sum<0)
                        sum=0;
                    player.hp-=sum;
                    sprintf(temp1,"对你造成了%d点伤害",sum);
                    PlaySound(TEXT("Skill_HeavyAttack.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    Anime::PlayerHit();
                }
            }
            strcat(temp,temp1);
            record.Push(temp);
            return 1;
        }
        //2-治愈(20)：回复自身(20+LV*2)的HP
        static int Heal(int isFromPlayer,MONSTER &enemy)
        {
            if(isFromPlayer)
            {
                if(player.mp<20)
                {
                    sprintf(temp,"魔法值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                player.mp-=20;
                player.hp+=20+player.lv*2;
                sprintf(temp,"你使用了“治愈”，回复了%d点生命",20+player.lv*2);
                PlaySound(TEXT("Skill_Heal.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerRaise();
            }
            else
            {
                enemy.hp+=20+enemy.lv*2;
                sprintf(temp,"%s使用了“治愈”，回复了%d点生命",enemy.name,20+enemy.lv*2);
                PlaySound(TEXT("Skill_Heal.wav"),NULL,SND_FILENAME|SND_ASYNC);
            }
            record.Push(temp);
            return 1;
        }
        //3-疾风连击(22)：必中，对对方造成(普攻+速度*6)伤害
        static int ComboAttack(int isFromPlayer,MONSTER &enemy)
        {
            if(isFromPlayer)
            {
                if(player.mp<22)
                {
                    sprintf(temp,"魔法值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                player.mp-=22;
                sprintf(temp,"你使用了“疾风连击”，");
                int sum=player.atk+atkPA-enemy.def-defMA+(player.spd+spdPA)*6;
                if(sum<0)
                    sum=0;
                enemy.hp-=sum;
                sprintf(temp1,"对%s造成了%d点伤害",enemy.name,sum);
                PlaySound(TEXT("Skill_ComboAttack.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerCombo();
            }
            else
            {
                sprintf(temp,"%s使用了“疾风连击”，",enemy.name);
                int sum=enemy.atk+atkMA-player.def-defPA+(enemy.spd+spdMA)*6;
                if(sum<0)
                    sum=0;
                player.hp-=sum;
                sprintf(temp1,"对你造成了%d点伤害",sum);
                PlaySound(TEXT("Skill_ComboAttack.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerHit();
            }
            strcat(temp,temp1);
            record.Push(temp);
            return 1;
        }
        //4-血刀(5)：必中，消耗自身(10+LV*2)的HP，对对方造成等量伤害并给予对方2层[流血]
        static int BloodBlade(int isFromPlayer,MONSTER &enemy)
        {
            if(isFromPlayer)
            {
                if(player.hp<=10+player.lv*2)
                {
                    sprintf(temp,"生命值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                else if(player.mp<5)
                {
                    sprintf(temp,"魔法值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                player.hp-=10+player.lv*2;
                player.mp-=5;
                sprintf(temp,"你使用了“血刀”，消耗了%d点生命，",10+player.lv*2);
                enemy.hp-=10+player.lv*2;
                buff.Insert(0,2,2);
                sprintf(temp1,"对%s造成了%.d点伤害",enemy.name,10+player.lv*2);
                strcat(temp,temp1);
                record.Push(temp);
                sprintf(temp,"给予%s2层[流血]",enemy.name);
                record.Push(temp);
                PlaySound(TEXT("Skill_BloodBlade.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerAttack();
            }
            return 1;
        }
        //5-吸血术(25)：必中，给予自身3层[恢复]3回合、对方3层[流血]
        static int SoulDraw(int isFromPlayer,MONSTER &enemy)
        {
            if(isFromPlayer)
            {
                if(player.mp<25)
                {
                    sprintf(temp,"魔法值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                player.mp-=25;
                buff.Insert(1,3,1);
                buff.Insert(0,3,2);
                sprintf(temp,"你使用了“吸血术”");
                record.Push(temp);
                sprintf(temp,"给予自身3层[恢复]，给予%s3层[流血]",enemy.name);
                record.Push(temp);
                PlaySound(TEXT("Skill_SoulDraw.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerAttack();
            }
            else
            {
                buff.Insert(0,3,1);
                buff.Insert(1,3,2);
                sprintf(temp,"%s使用了“吸血术”",enemy.name);
                record.Push(temp);
                sprintf(temp,"给予自身3层[恢复]，给予你3层[流血]");
                record.Push(temp);
                PlaySound(TEXT("Skill_SoulDraw.wav"),NULL,SND_FILENAME|SND_ASYNC);
            }
            return 1;
        }
        //6-备战(15)：尝试闪避，下回合给予自身1层[聚力]、[硬化]
        static int Parabellum(int isFromPlayer,MONSTER &enemy)
        {
            if(isFromPlayer)
            {
                if(player.mp<15)
                {
                    sprintf(temp,"魔法值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                player.mp-=15;
                Dodge(1,enemy);
                buff.Insert(1,1,3);
                buff.Insert(1,1,4);
                sprintf(temp,"你使用了“备战”");
                record.Push(temp);
                sprintf(temp,"下回合给予自身[聚力]、[硬化]");
                record.Push(temp);
                PlaySound(TEXT("Skill_Heal.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerRaise();
            }
            else
            {
                Dodge(0,enemy);
                buff.Insert(0,1,3);
                sprintf(temp,"%s使用了“备战”",enemy.name);
                record.Push(temp);
                sprintf(temp,"下回合给予自身[聚力]");
                record.Push(temp);
                PlaySound(TEXT("Skill_Heal.wav"),NULL,SND_FILENAME|SND_ASYNC);
            }
            return 1;
        }
        //7-狂怒(30)：下回合给予自身1层[暴怒]
        static int Fury(int isFromPlayer,MONSTER &enemy)
        {
            if(isFromPlayer)
            {
                if(player.mp<20)
                {
                    sprintf(temp,"魔法值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                player.mp-=20;
                buff.Insert(1,1,6);
                sprintf(temp,"你使用了“狂怒”");
                record.Push(temp);
                sprintf(temp,"下回合给予自身[暴怒]");
                record.Push(temp);
                PlaySound(TEXT("Skill_Fury.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerRaise();
            }
            else
            {
                buff.Insert(0,1,6);
                sprintf(temp,"%s使用了“狂怒”",enemy.name);
                record.Push(temp);
                sprintf(temp,"下回合给予自身[暴怒]");
                record.Push(temp);
                PlaySound(TEXT("Skill_Fury.wav"),NULL,SND_FILENAME|SND_ASYNC);
            }
            return 1;
        }
        //8-腐蚀（20）：给予对方2层[虚弱]
        static int Corrode(int isFromPlayer,MONSTER &enemy)
        {
            if(isFromPlayer)
            {
                if(player.mp<20)
                {
                    sprintf(temp,"魔法值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                player.mp-=20;
                buff.Insert(0,2,7);
                sprintf(temp,"你使用了“腐蚀”");
                record.Push(temp);
                sprintf(temp,"给予%s2层[虚弱]",enemy.name);
                record.Push(temp);
                PlaySound(TEXT("Skill_Corrode.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerAttack();
            }
            else
            {
                buff.Insert(1,2,7);
                sprintf(temp,"%s使用了“腐蚀”",enemy.name);
                record.Push(temp);
                sprintf(temp,"给予你2层[虚弱]");
                record.Push(temp);
                PlaySound(TEXT("Skill_Corrode.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerHit();
            }
            return 1;
        }
        //9-神风（50）：自身HP减少至1点，对对方造成与减少量等量的伤害
        static int Kamikaze(int isFromPlayer,MONSTER &enemy)
        {
            if(isFromPlayer)
            {
                if(player.mp<50)
                {
                    sprintf(temp,"魔法值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                player.mp-=50;
                int sum=player.hp-1;
                enemy.hp-=sum;
                player.hp=1;
                sprintf(temp,"你使用了“神风”");
                record.Push(temp);
                sprintf(temp,"自身生命值减少至1点，对%s造成了%d点伤害",enemy.name,sum);
                record.Push(temp);
                PlaySound(TEXT("Skill_Kamikaze.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerRaise();
            }
            else
            {
                int sum=enemy.hp-1;
                player.hp-=sum;
                enemy.hp=1;
                sprintf(temp,"%s使用了“神风”",enemy.name);
                record.Push(temp);
                sprintf(temp,"自身生命值减少至1点，对你造成了%d点伤害",sum);
                record.Push(temp);
                PlaySound(TEXT("Skill_Kamikaze.wav"),NULL,SND_FILENAME|SND_ASYNC);
            }
            return 1;
        }
        //10-回春(32)：回复自身20点HP，给予自身3层[恢复]
        static int Rejuvenate(int isFromPlayer,MONSTER &enemy)
        {
            if(isFromPlayer)
            {
                if(player.mp<32)
                {
                    sprintf(temp,"魔法值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                player.mp-=32;
                player.hp+=20;
                buff.Insert(1,2,1);
                sprintf(temp,"你使用了“回春”");
                record.Push(temp);
                sprintf(temp,"回复20点生命值，给予自身2层[恢复]");
                record.Push(temp);
                PlaySound(TEXT("Skill_Heal.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerRaise();
            }
            else
            {
                enemy.hp+=20;
                buff.Insert(0,2,1);
                sprintf(temp,"%s使用了“回春”",enemy.name);
                record.Push(temp);
                sprintf(temp,"回复20点生命值，给予自身2层[恢复]");
                record.Push(temp);
                PlaySound(TEXT("Skill_Heal.wav"),NULL,SND_FILENAME|SND_ASYNC);
            }
            return 1;
        }
        //11-审判(50)：给予对方99层[濒死]
        static int Judgement(int isFromPlayer,MONSTER &enemy)
        {
            if(isFromPlayer)
            {
                if(player.mp<50)
                {
                    sprintf(temp,"魔法值不足");
                    PlaySound(TEXT("Deny.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    return 0;
                }
                player.mp-=50;
                buff.Insert(0,99,8);
                sprintf(temp,"你使用了“审判”");
                record.Push(temp);
                sprintf(temp,"给予%s99层[濒死]",enemy.name);
                record.Push(temp);
                PlaySound(TEXT("Skill_Judgement.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerRaise();
            }
            else
            {
                buff.Insert(1,99,8);
                sprintf(temp,"%s使用了“审判”",enemy.name);
                record.Push(temp);
                sprintf(temp,"给予你99层[濒死]");
                record.Push(temp);
                PlaySound(TEXT("Skill_Judgement.wav"),NULL,SND_FILENAME|SND_ASYNC);
            }
            return 1;
        }

        //以下为怪物特有技能
        static int Shoot(MONSTER &enemy)
        {
            sprintf(temp,"%s使用了“射击”，",enemy.name);
            if(playerDodge)
            {
                sprintf(temp1,"被闪避");
                PlaySound(TEXT("51_Shoot.wav"),NULL,SND_FILENAME|SND_ASYNC);
                PlaySound(TEXT("Dodge.wav"),NULL,SND_FILENAME|SND_ASYNC);
            }
            else
            {
                int sum=(int)((enemy.atk+atkMA-player.def-defPA));
                if(sum<0)
                    sum=0;
                player.hp-=sum;
                sprintf(temp1,"对你造成了%d点伤害",sum);
                PlaySound(TEXT("51_Shoot.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerHit();
            }
            strcat(temp,temp1);
            record.Push(temp);
            return 1;
        }
        static int Reload(MONSTER &enemy)
        {
            sprintf(temp,"%s使用了“上弹”",enemy.name);
            record.Push(temp);
            PlaySound(TEXT("52_Reload.wav"),NULL,SND_FILENAME|SND_ASYNC);
            return 1;
        }
        static int Firespit(MONSTER &enemy)
        {
            sprintf(temp,"%s使用了“烈焰”，",enemy.name);
            if(playerDodge)
            {
                sprintf(temp1,"被闪避");
                PlaySound(TEXT("53_Firespit.wav"),NULL,SND_FILENAME|SND_ASYNC);
                PlaySound(TEXT("Dodge.wav"),NULL,SND_FILENAME|SND_ASYNC);
            }
            else
            {
                int sum=(int)((enemy.atk+atkMA-player.def-defPA)*1.1);
                if(sum<0)
                    sum=0;
                player.hp-=sum;
                player.mp-=5;
                if(player.mp<0)
                    player.mp=0;
                sprintf(temp1,"对你造成了%d点伤害，你的魔法值减少5",sum);
                PlaySound(TEXT("53_Firespit.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Anime::PlayerHit();
            }
            strcat(temp,temp1);
            record.Push(temp);
            return 1;
        }
        static int Awake(MONSTER &enemy)
        {
            if(enemy.hp<500)
            {
                strcpy(enemy.name,"觉醒古龙\0");
                enemy.hp+=100;
                enemy.atk+=5;
                enemy.def+=3;
                enemy.loop[0]=1;
                enemy.loop[1]=6;
                enemy.loop[2]=0;
                enemy.loop[3]=55;
                enemy.loop[4]=7;
                enemy.loop[5]=0;
                enemy.loop[6]=55;
                enemy.loop[7]=6;
                enemy.loop[8]=0;
                enemy.loop[9]=0;
                enemy.loop[10]=55;
                enemy.loop[11]=-1;
                sprintf(temp,"古龙的力量已经觉醒……");
                record.Push(temp);
                sprintf(temp,"古龙的生命值回复100点");
                record.Push(temp);
                sprintf(temp,"古龙的攻击力增加3点");
                record.Push(temp);
                sprintf(temp,"古龙的防御力增加3点");
                record.Push(temp);
                PlaySound(TEXT("54_Awake.wav"),NULL,SND_FILENAME|SND_ASYNC);
                Sleep(2000);
                music.Close();
                music.Load("AncientDragon2.wav");
                music.Play();
            }
            else
                NormalAttack(0,enemy);
            return 1;
        }
        static int Storm(MONSTER &enemy)
        {
            player.hp-=1;
            buff.Insert(1,3,2);
            sprintf(temp,"%s使用了“沙尘暴”",enemy.name);
            record.Push(temp);
            sprintf(temp,"对你造成1点伤害,给予你3层[流血]");
            record.Push(temp);
            PlaySound(TEXT("55_Storm.wav"),NULL,SND_FILENAME|SND_ASYNC);
            return 1;
        }
};

void Initialization()
{
    strcpy(player.name,"勇者");
    player.lv=50;
    player.hp=player.maxhp=150;
    player.mp=player.maxmp=40;
    player.atk=40;
    player.def=5;
    player.spd=0;
    player.skill[1]=1;
    player.skill[2]=2;
    player.skill[3]=4;
    player.skill[4]=6;
    player.exp=0;
    player.maxexp=100;
}

///标题界面
void Title()
{
    system("cls");
    Anime::Title(1);
    getch();
    PlaySound(TEXT("Gong.wav"),NULL,SND_FILENAME|SND_ASYNC);
    music.Load("Menu.wav");
    music.Play();
    Anime::Title(0);
    int x=46,y=30;
    GotoXY(x,y);
    printf("                                                        ");
    GotoXY(x,y);
    printf("新的游戏        继续游戏        制作人员        退出游戏");
    int select=0;
    char sel[5][10]={"新的游戏","继续游戏","制作人员","退出游戏"};
    char sel2[5][10]={"--------","--------","--------","--------"};
    char c;
    while(true)
    {
        GotoXY(x+select*16,y);
        Color(1);
        printf("%s",sel[select]);
        GotoXY(x+select*16,y+1);
        printf("%s",sel2[select]);
        Color(16);
        c=GetInput();
        switch(c)
        {
            case 'a':
            case 'A':
            {
                GotoXY(x+select*16,y);
                Color(16);
                printf("%s",sel[select]);
                GotoXY(x+select*16,y+1);
                printf("          ");
                select--;
                select=(select+4)%4;
            }break;
            case 'd':
            case 'D':
            {
                GotoXY(x+select*16,y);
                Color(16);
                printf("%s",sel[select]);
                GotoXY(x+select*16,y+1);
                printf("          ");
                select++;
                select=(select+4)%4;
            }break;
            default: break;
        }
        if(c=='\r')
        {
            PlaySound(TEXT("Click.wav"),NULL,SND_FILENAME|SND_ASYNC);
            switch(select)
            {
                case 0:
                {
                    music.Close();
                    music.Load("Preface.wav");
                    music.Play();
                    Anime::Present();
                    Passage(1);
                    Initialization();
                    Fight(14);
                    system("cls");
                    HoboChat(6);
                    CharaCreate();
                    SavePlayer();
                    return;
                }
                case 1:
                {
                    music.Close();
                    LoadPlayer();
                    return;
                }break;
                case 2:
                {
                    Credit();
                    Anime::Title(0);
                    x=46,y=30;
                    GotoXY(x,y);
                    printf("新的游戏        继续游戏        制作人员        退出游戏");
                    select=0;
                }break;
                case 3:
                {
                    music.Close();
                    exit(0);
                }break;
                default:
                    break;
            }
        }
    }
}

///长段文字
void Passage(int n)
{
    FILE *fp;
    switch(n)
    {
        case 1: fp=fopen("Preface.txt","r");break;
        case 2: fp=fopen("NTR.txt","r");break;
        case 3: fp=fopen("NTRbeat.txt","r");break;
        case 4: fp=fopen("princess.txt","r");break;
        case 5: fp=fopen("princessbeat.txt","r");break;
        case 6: fp=fopen("dragon.txt","r");break;
        case 7: fp=fopen("dragonbeat.txt","r");break;
        default: break;
    }

    system("cls");
    char s[20000];
    memset(s,'\0',sizeof(s));
    fgets(s,10000,fp);
    int i=0,j=0,x,y;
    x=20,y=5;
    j=4;
    GotoXY(x+4,y);
    while(s[i]!='\0')
    {
        if(s[i]=='&')
        {
            GotoXY(x+4,++++y);
            i++;
            j=4;
            continue;
        }
        if(('a'<=s[i]&&s[i]<='z')||('A'<=s[i]&&s[i]<='A'))
        {
            printf("%c",s[i]);
            i++;
            j++;
            Sleep(40);
            continue;
        }
        if(s[i]=='_')
        {
            printf(" ");
            i++;
            j++;
            Sleep(40);
            continue;
        }
        printf("%c%c",s[i],s[i+1]);
        Sleep(40);
        if(kbhit())
        {
            if(getch()=='\r')
                goto End;
        }
        i+=2;
        j+=2;
        if(j>=104)
        {
            j=0;
            GotoXY(x,++y);
        }
    }
    Sleep(1000);
    GotoXY(66,28);
    Color(1);
    printf("请按任意键继续......");
    Color(16);
    GetInput();
    End:
    PlaySound(TEXT("Click.wav"),NULL,SND_FILENAME|SND_ASYNC);
    fclose(fp);
}

///角色创建界面
void CharaCreate()
{
    system("cls");
    int x,y;
    char c,temp[30];
    while(true)
    {
        system("cls");
        x=65,y=12;
        GotoXY(x,y);
        printf("年轻的勇者啊");GotoXY(x,++++y);
        printf(" 你的名字是");GotoXY(x,++++++++y);
        printf("------------");GotoXY(x,--y);
        scanf("%s",temp);
        PlaySound(TEXT("Click.wav"),NULL,SND_FILENAME|SND_ASYNC);
        x=51,y=20;
        GotoXY(x,y);
        printf("  ┌--------------------------------┐");GotoXY(x,++++y);
        printf("        %s, 你确定吗？",temp);GotoXY(x,++++y);
        printf("     [回车]是的     [空格]不，等等");GotoXY(x,++++y);
        printf("  └--------------------------------┘");
        do
        {
            c=GetInput();
            PlaySound(TEXT("Click.wav"),NULL,SND_FILENAME|SND_ASYNC);
        }while(c!='\r'&&c!=' ');
        if(c=='\r')
            break;
    }
    Sleep(100);
    strcpy(player.name,temp);

    player.lv=1;
    player.hp=player.maxhp=100;
    player.mp=player.maxmp=40;
    player.atk=10;
    player.def=0;
    player.spd=1;
    player.skill[1]=1;
    player.skill[2]=2;
    player.skill[3]=0;
    player.skill[4]=0;
    player.exp=0;
    player.maxexp=100;
    player.skillPoint+=16;
    Attributes();

    SavePlayer();

    system("cls");
    Anime::Load();
    music.Close();
}

///鸣谢界面
void Credit()
{
    system("cls");
    int x=64,y=14;
    GotoXY(x,y);
    printf("---- 制作人员 ----");GotoXY(x,++++y);
    printf(" 软工一班  徐梓皓 ");GotoXY(x,++++y);
    printf(" 软工一班  余嘉祺 ");GotoXY(x,++++y);
    printf(" 软工一班  余宇桐 ");GotoXY(x,++++y);
    printf(" 软工一班   张鹏  ");GotoXY(x,++++y);
    GetInput();
    system("cls");
}

///祭祀场对话
void HoboChat(int hID)
{
    Anime::Portrait(hID);
    int i=0,x,y;
    x=25,y=33;
    while(conversation[hID][i][0]!='\0')
    {
        GotoXY(x,y);
        printf("                                                                           ");
        GotoXY(x,y);
        printf("%s",conversation[hID][i]);
        while(getch()!='\r');
        PlaySound(TEXT("Click.wav"),NULL,SND_FILENAME|SND_ASYNC);
        i++;
    }
    Anime::ErasePortrait();
}

///载入角色文件
void LoadPlayer()
{
    FILE *fp;
    fp=fopen("PlayerInfo.txt","r");
    fscanf(fp,"%s",player.name);
    fscanf(fp,"%d",&player.lv);
    fscanf(fp,"%d/%d",&player.hp,&player.maxhp);
    fscanf(fp,"%d/%d",&player.mp,&player.maxmp);
    fscanf(fp,"%d/%d/%d",&player.atk,&player.def,&player.spd);
    for(int i=1;i<=4;i++)
        fscanf(fp,"%d",&player.skill[i]);
    fscanf(fp,"%d/%d",&player.exp,&player.maxexp);
    fscanf(fp,"%d",&player.skillPoint);
    fclose(fp);
}

///导出角色文件
void SavePlayer()
{
    FILE *fp;
    fp=fopen("PlayerInfo.txt","w");
    fprintf(fp,"%s\n",player.name);
    fprintf(fp,"%d\n",player.lv);
    fprintf(fp,"%d/%d\n",player.hp,player.maxhp);
    fprintf(fp,"%d/%d\n",player.mp,player.maxmp);
    fprintf(fp,"%d/%d/%d\n",player.atk,player.def,player.spd);
    for(int i=1;i<=4;i++)
        fprintf(fp,"%d ",player.skill[i]);
    fprintf(fp,"\n");
    fprintf(fp,"%d/%d\n",player.exp,player.maxexp);
    fprintf(fp,"%d\n",player.skillPoint);
    fclose(fp);
}

///载入提示文件
void LoadTips()
{
    FILE *fp;
    char s[256];
    int i=0;
    fp=fopen("Tips.txt","r");
    while(fgets(s,255,fp))
        strcpy(tips[i++],s);
    fclose(fp);
}

///载入对话文件
void LoadConversation()
{
    FILE *fp;
    char s[256];
    int i=1,j,len;
    fp=fopen("Conversation.txt","r");
    while(fscanf(fp,"%d",&i)>0)
    {
        fscanf(fp,"%s",hoboName[i]);
        fscanf(fp,"%d",&len);
        for(j=0;j<len;j++)
        {
            fscanf(fp,"%s",s);
            strcpy(conversation[i][j],s);
        }
    }
    fclose(fp);
}

///载入描述文件
void LoadDescription()
{
    FILE *fp;
    char s[256];
    int i=1;
    fp=fopen("SkillDescription.txt","r");
    while(fgets(s,255,fp))
        strcpy(skillDes[i++],s);
    fclose(fp);
    i=1;
    fp=fopen("BuffDescription.txt","r");
    while(fgets(s,255,fp))
        strcpy(buffDes[i++],s);
    fclose(fp);
}

///载入怪物文件
void LoadMonster()
{

    FILE *fp;
    int mID,i;
    fp=fopen("Monster.txt","r");
    while(fscanf(fp,"%d",&mID)>0)
    {
        fscanf(fp,"%s",monster[mID].name);
        fscanf(fp,"%d",&monster[mID].lv);
        fscanf(fp,"%d/%d",&monster[mID].hp,&monster[mID].maxhp);
        fscanf(fp,"%d/%d/%d",&monster[mID].atk,&monster[mID].def,&monster[mID].spd);
        for(i=0;;i++)
        {
            fscanf(fp,"%d",&monster[mID].loop[i]);
            if(monster[mID].loop[i]==-1)
                break;
        }
        fscanf(fp,"%d",&monster[mID].expGiven);
    }
    fclose(fp);
}

///健康条
void HealthBar(int hp,int maxhp)
{
    int i,length;
    if(hp<0)
        hp=0;
    length=(double)hp/maxhp*20;
    printf(" HP ");
    for(i=1;i<=length;i++)
        printf("■");
    while(i<=20)
    {
        printf("□");
        i++;
    }
    printf(" %d/%d\n",hp,maxhp);
}

///魔法条
void MagicBar(int mp,int maxmp)
{
    int i,length;
    length=(double)mp/maxmp*10;
    printf(" MP ");
    for(i=1;i<=length;i++)
        printf("■");
    while(i<=10)
    {
        printf("□");
        i++;
    }
    printf(" %d/%d\n\n",mp,maxmp);
}

///状态条
void Info(MONSTER enemy)
{
    printf("{ %s }  lv.%d\n",player.name,player.lv);
    Color(10);
    HealthBar(player.hp,player.maxhp);
    Color(3);
    MagicBar(player.mp,player.maxmp);
    Color(16);
    printf("{ %s }  lv.%d\n",enemy.name,enemy.lv);
    Color(4);
    HealthBar(enemy.hp,enemy.maxhp);
    Color(16);
}

///显示动作记录
void RecordDisplay()
{
    int x,y;
    GetXY(x,y);
    GotoXY(70,20);
    Color(0);
    printf("/----------------------- 战斗记录 -----------------------\\\n");
    while(record.Length()>14)
        record.Pop();
    record.Traverse();
    GotoXY(70,35);
    printf("\\--------------------------------------------------------/\n");
    Color(16);
    GotoXY(x,y);
}

///普通攻击
void NormalAttack(int isFromPlayer,MONSTER &enemy)
{
    if(isFromPlayer)
    {
        sprintf(temp,"你对%s使用了普通攻击，",enemy.name);
        if(enemyDodge)
        {
            sprintf(temp1,"被闪避");
            PlaySound(TEXT("Dodge.wav"),NULL,SND_FILENAME|SND_ASYNC);
        }
        else
        {
            int sum=player.atk+atkPA-enemy.def-defMA;
            if(sum<0)
                sum=0;
            enemy.hp-=sum;
            sprintf(temp1,"造成了%d点伤害",sum);
            PlaySound(TEXT("NormalAttack.wav"),NULL,SND_FILENAME|SND_ASYNC);
            Anime::PlayerAttack();
        }

    }
    else
    {
        sprintf(temp,"%s对你使用了普通攻击，",enemy.name);
        if(playerDodge)
        {
            sprintf(temp1,"被闪避");
            PlaySound(TEXT("Dodge.wav"),NULL,SND_FILENAME|SND_ASYNC);
        }
        else
        {
            int sum=enemy.atk+atkMA-player.def-defPA;
            if(sum<0)
                sum=0;
            player.hp-=sum;
            sprintf(temp1,"造成了%d点伤害",sum);
            PlaySound(TEXT("NormalAttack.wav"),NULL,SND_FILENAME|SND_ASYNC);
            Anime::PlayerHit();
        }
    }
    strcat(temp,temp1);
    record.Push(temp);
}

///魔法攻击
int MagicSkill(int isFromPlayer,MONSTER &enemy,int sID)
{
    int choice,result;
    if(isFromPlayer)
    {
        printf("施放技能：                                       \n");
        for(int i=1;i<=4;i++)
            printf("[%d]%s  ",i,skillName[player.skill[i]]);
        printf("[其他]取消\n\n");
        Color(0);
        for(int i=1;i<=4;i++)
        {
            if(player.skill[i]>0)
                printf("%s",skillDes[player.skill[i]]);
        }
        Color(16);
        choice=getch()-'0';
        sID=player.skill[choice];
        if(choice<1||choice>4||sID==0)
            return 0;
    }
    switch(sID)
    {
        case 1: result=Skill::HeavyStrike(isFromPlayer,enemy);break;
        case 2: result=Skill::Heal(isFromPlayer,enemy);break;
        case 3: result=Skill::ComboAttack(isFromPlayer,enemy);break;
        case 4: result=Skill::BloodBlade(isFromPlayer,enemy);break;
        case 5: result=Skill::SoulDraw(isFromPlayer,enemy);break;
        case 6: result=Skill::Parabellum(isFromPlayer,enemy);break;
        case 7: result=Skill::Fury(isFromPlayer,enemy);break;
        case 8: result=Skill::Corrode(isFromPlayer,enemy);break;
        case 9: result=Skill::Kamikaze(isFromPlayer,enemy);break;
        case 10:result=Skill::Rejuvenate(isFromPlayer,enemy);break;
        case 11:result=Skill::Judgement(isFromPlayer,enemy);break;

        case 51:result=Skill::Shoot(enemy);break;
        case 52:result=Skill::Reload(enemy);break;
        case 53:result=Skill::Firespit(enemy);break;
        case 54:result=Skill::Awake(enemy);break;
        case 55:result=Skill::Storm(enemy);break;
        default: return 0;
    }
    return result;
}

///闪避、逃跑判定
void Dodge(int isFromPlayer,MONSTER enemy)
{
    int rate;
    srand(time(NULL));
    if(isFromPlayer)
    {
        rate=rand()%50+(player.spd-enemy.spd);
        if(rate>30)
            playerDodge=1;
        else
        {
            if(isFromPlayer>0)
                strcpy(temp,"闪避失败\0");
            else
                strcpy(temp,"逃跑失败\0");
            record.Push(temp);
        }
    }
    else
    {
        rate=rand()%50+(enemy.spd-player.spd);
        if(rate>25)
            enemyDodge=1;
    }
}

///敌方行动
void EnemyAction(MONSTER &enemy,int &act)
{
    for(int i=0; i<6; i++)
    {
        printf(". ");
        Sleep(250);
    }
    if(enemy.loop[act]<0)
        act=0;
    if(enemy.loop[act]==100)
        Dodge(0,enemy);
    else if(enemy.loop[act]==0)
        NormalAttack(0,enemy);
    else
        MagicSkill(0,enemy,enemy.loop[act]);
}

///战斗
int Fight(int mID)
{
    //播放bgm
    BGM(mID);

    MONSTER enemy = monster[mID];
    int x,y;
    int turn;
    int select;
    int act;
    turn=act=0;
    buff.Init();
    player.mp=player.maxmp;
    atkPA=defPA=spdPA=0;
    atkMA=defMA=spdMA=0;
    record.Init();
    while(1)
    {
        if(music.End()) //循环播放音乐
            music.Play();

        turn++;
        sprintf(temp,"<第%d回合>",turn);
        record.Push(temp);

        //玩家回合
        playerDodge=enemyDodge=0;
        atkPA=defPA=spdPA=0;
        buff.Expire(1,enemy);
        buff.Exert(1,enemy);
        while(1)
        {

            player.mp+=5;
            PlayerTurn:
            if(player.hp>=player.maxhp)
                player.hp=player.maxhp;
            if(player.mp>=player.maxmp)
                player.mp=player.maxmp;
            if(enemy.hp>=enemy.maxhp)
                enemy.hp=enemy.maxhp;
            system("cls");
            Anime::Monster(mID);
            Anime::Player1();
            printf("\n\n[第 %d 回合]\n\n",turn);
            Info(enemy);
            RecordDisplay();
            if(player.hp<=0)
            {
                Anime::PlayerDie();
                Sleep(3000);
                FightLose();
                buff.Destroy();
                return 0;
            }
            Sleep(500);
            printf("\n<你的回合>           \n\n");
            printf("[1]行动  [2]充能  [3]查看状态  [0]逃跑\n");
            GetXY(x,y);
            GotoXY(x,y-1);
            switch(GetInput())
            {
                case '1':   //行动
                {
                    printf("选择： [1]攻击  [2]技能  [3]闪避  [0]取消       \n");
                    select=0;
                    while(!('0'<=select&&select<='3'))
                    {
                        switch(select=getch())
                        {
                            case '1':   NormalAttack(1,enemy);goto EnemyTurn;
                            case '2':
                            {
                                GetXY(x,y);
                                GotoXY(x,y-1);
                                printf("                                                \n");
                                GetXY(x,y);
                                GotoXY(x,y-1);
                                if(MagicSkill(1,enemy,0))
                                    goto EnemyTurn;
                                else
                                    goto PlayerTurn;
                            }
                            case '3':   Dodge(1,enemy);goto EnemyTurn;
                            default:    break;
                        }
                    }
                }break;
                case '2':;  //充能
                {
                    sprintf(temp,"你回复了%d点魔法值\n",20+player.lv*2);
                    player.mp+=20+player.lv*2;
                    PlaySound(TEXT("Standby.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    record.Push(temp);
                    goto EnemyTurn;
                }
                case '3':   //查看属性
                {
                    printf("查看： [1]我的状态  [2]怪物状态                       \n");
                    GetXY(x,y);
                    GotoXY(x,y-1);
                    select=getch();
                    while(!(select=='1'||select=='2'))
                        select=getch();
                    switch(select)
                    {
                        case '1':
                        {
                            printf("我的状态:                                 \n");
                            buff.Display(1);
                        }break;
                        case '2':
                        {
                            printf("怪物状态:                                 \n");
                            buff.Display(0);
                        }break;
                        default:    break;
                    }
                    goto PlayerTurn;
                }break;
                case '0':   //逃跑
                {
                    Dodge(-1,enemy);
                    if(playerDodge)
                    {
                        FightFlee();
                        buff.Destroy();
                        return -1;
                    }
                    goto EnemyTurn;
                }
            }
        }

        //怪物回合
        EnemyTurn:
        atkMA=defMA=spdMA=0;
        buff.Expire(0,enemy);
        buff.Exert(0,enemy);
        if(player.hp>=player.maxhp)
            player.hp=player.maxhp;
        if(player.mp>=player.maxmp)
            player.mp=player.maxmp;
        if(enemy.hp>=enemy.maxhp)
            enemy.hp=enemy.maxhp;
        if(enemy.hp<=0)
        {
            sprintf(temp,"%s死亡",enemy.name);
            record.Push(temp);
            system("cls");
            Anime::Player1();
            printf("\n\n[第 %d 回合]\n\n",turn);
            Info(enemy);
            printf("\n<你的回合>           \n");
            RecordDisplay();
            Sleep(4000);
            FightWin(enemy);
            buff.Destroy();
            return 1;
        }
        system("cls");
        Anime::Monster(mID);
        Anime::Player1();
        printf("\n\n[第 %d 回合]\n\n",turn);
        Info(enemy);
        printf("\n<敌方回合>\n");
        RecordDisplay();
        EnemyAction(enemy,act);
        act++;

        sprintf(temp,"------------------------------------------------------");
        record.Push(temp);
    }
}

///战斗胜利
void FightWin(MONSTER enemy)
{
    music.Close();
    PlaySound(TEXT("Win.wav"),NULL,SND_FILENAME|SND_ASYNC);
    system("cls");
    Anime::Victory(enemy);
    player.exp+=enemy.expGiven;
    GetInput();
    if(player.exp>=player.maxexp)
    {
        player.lv++;
        player.exp-=player.maxexp;
        player.maxexp+=100;

        PlaySound(TEXT("LevelUp.wav"),NULL,SND_FILENAME|SND_ASYNC);
        system("cls");
        Anime::Promoted();
        getch();
        player.hp+=(int)(player.maxhp*0.2);
        if(player.hp>player.maxhp)
            player.hp=player.maxhp;
        player.skillPoint+=4;
        Attributes();
        SkillRoll();
    }
}

///战斗失败
void FightLose()
{
    music.Close();
    PlaySound(TEXT("Lose.wav"),NULL,SND_FILENAME|SND_ASYNC);
    system("cls");
    Anime::Defeated();
    player.maxhp-=player.maxhp*0.1;
    player.hp=player.maxhp;
    SavePlayer();
    GetInput();
}

///战斗逃跑
void FightFlee()
{
    music.Close();
    PlaySound(TEXT("Flee.wav"),NULL,SND_FILENAME|SND_ASYNC);
    system("cls");
    Anime::Flee();
    GetInput();
}

///获得技能
void SkillRoll()
{
    system("cls");
    srand(time(NULL));
    int n,select=0,input,flag,x,y;
    int alternative[5]={0};
    char c;
    for(int i=0;i<3;i++)
    {
        n=rand()%10+1;
        flag=0;
        for(int j=1;j<=4;j++)
        {
            if(player.skill[j]==n||alternative[j-1]==n)
                flag++;
        }
        if(!flag)
            alternative[i]=n;
        else
            i--;
    }
    x=63,y=5;
    GotoXY(x,y);
    printf("/----------------------\\");GotoXY(x,++y);
    printf("        选择技能        ");GotoXY(x,++y);
    printf("\\----------------------/");GotoXY(x,++++y);
    for(int i=0;i<3;i++)
    {
        printf("  ┌-----------------┐");GotoXY(x,++y);
        printf("       %s            ",skillName[alternative[i]]);GotoXY(x,++y);
        printf("  └-----------------┘");GotoXY(x,++++y);
    }
    while(true)
    {
        y=9+select*4;
        GotoXY(63,y);
        Color(1);
        printf("  ┌-----------------┐");GotoXY(x,++y);
        printf("       %s            ",skillName[alternative[select]]);GotoXY(x,++y);
        printf("  └-----------------┘");GotoXY(x,++++y);
        Color(16);
        x=38;y=22;
        GotoXY(x,y);
        printf("/-----效果-----------------------------------------------------------------\\");GotoXY(x,++++y);
        printf("                                                                             ");GotoXY(x,y);
        printf("  %s",skillDes[alternative[select]]);GotoXY(x,++++y);
        printf("\\--------------------------------------------------------------------------/");GotoXY(x,++++y);
        x=63;
        printf("                      [W][S]移动      [回车]选择");
        c=getch();
        PlaySound(TEXT("Click.wav"),NULL,SND_FILENAME|SND_ASYNC);
        switch(c)
        {
            case 'w':
            case 'W':
            {
                y=9+select*4;
                GotoXY(63,y);
                printf("  ┌-----------------┐");GotoXY(x,++y);
                printf("       %s            ",skillName[alternative[select]]);GotoXY(x,++y);
                printf("  └-----------------┘");GotoXY(x,++++y);
                select--;
                select=(select+3)%3;
            }break;
            case 's':
            case 'S':
            {
                y=9+select*4;
                GotoXY(63,y);
                printf("  ┌-----------------┐");GotoXY(x,++y);
                printf("       %s            ",skillName[alternative[select]]);GotoXY(x,++y);
                printf("  └-----------------┘");GotoXY(x,++++y);
                select++;
                select=(select+3)%3;
            }break;
            default:break;
        }
        if(c=='\r')
        {
            x=38;y=22;
            GotoXY(x,y);
            printf("/-----选择技能槽位---------------------------------------------------------\\");GotoXY(x,++++y);
            printf("                                                                             ");GotoXY(x,y);
            printf(" ");
            for(int i=1;i<=4;i++)
            printf("[%d]%s   ",i,skillName[player.skill[i]]);
            printf("[其他]取消");GotoXY(x,++++y);
            printf("\\--------------------------------------------------------------------------/");GotoXY(x,++++y);
            x=63;
            printf("                                                   ");
            input=GetInput()-'0';
            PlaySound(TEXT("Click.wav"),NULL,SND_FILENAME|SND_ASYNC);
            if(input>=1&&input<=4)
            {
                player.skill[input]=alternative[select];
                Sleep(100);
                break;
            }
        }
    }
}

///人物属性
void Attributes()
{
    system("cls");
    int x=63,y=5;
    GotoXY(x,y);
    printf("/----------------------\\");GotoXY(x,++y);
    printf("        人物属性        ");GotoXY(x,++y);
    printf("\\----------------------/");
    int select=0;
    int distribute[5]={0};
    char c;
    while(true)
    {
        AttributeDistribute(distribute,select);
        c=getch();
        PlaySound(TEXT("Click.wav"),NULL,SND_FILENAME|SND_ASYNC);
        switch(c)
        {
            case 'w':
            case 'W':
            {
                select--;
                select=(select+5)%5;
            }break;
            case 's':
            case 'S':
            {
                select++;
                select=(select+5)%5;
            }break;
            case 'a':
            case 'A':
            {
                if(distribute[select]>0)
                {
                    distribute[select]--;
                    player.skillPoint++;
                }
            }break;
            case 'd':
            case 'D':
            {
                if(player.skillPoint>0&&distribute[select]<24)
                {
                    player.skillPoint--;
                    distribute[select]++;
                }
            }break;
            default:break;
        }
        if(c=='\r')
        {
            player.maxhp+=distribute[0]*5;
            player.hp+=distribute[0]*5;
            player.maxmp+=distribute[1]*4;
            player.mp+=distribute[1]*4;
            player.atk+=distribute[2]*2;
            player.def+=distribute[3];
            player.spd+=distribute[4];
            for(int i=0;i<5;i++)
            {
                attribute[i]+=distribute[i];
                distribute[i]=0;
            }
            AttributeDistribute(distribute,-1);
            Sleep(1000);
            break;
        }
    }
}

///属性分配(不单独使用)
void AttributeDistribute(int distribute[],int select)
{
    int x,y,i;
    x=62,y=20;
    GotoXY(x,y);
    printf("你有");
    Color(6);
    printf("%2d",player.skillPoint);
    Color(16);
    printf("点属性点待分配");
    x=55,y=22;
    GotoXY(x,y);
    Color(0);
    printf("[W][S]移动    [A][D]调整    [回车]确认");

    x=40,y=10;
    GotoXY(x,y);
    Color(16);
    if(select==0)    Color(10);
    printf("最大生命值  ");
    for(i=0;i<attribute[0];i++)
        printf("■");
    Color(10);
    for(i=attribute[0];i<attribute[0]+distribute[0];i++)
        printf("■");
    Color(8);
    for(i=attribute[0]+distribute[0];i<24;i++)
        printf("□");
    Color(16);
    printf("%3d ",player.maxhp);
    if(distribute[0]>0)
    {
        Color(10);
        printf("+");
        printf("%3d",distribute[0]*5);
    }
    else
        printf("          ");
    GotoXY(x,++++y);

    Color(16);
    if(select==1)    Color(3);
    printf("最大魔法值  ");
    for(i=0;i<attribute[1];i++)
        printf("■");
    Color(3);
    for(i=attribute[1];i<attribute[1]+distribute[1];i++)
        printf("■");
    Color(8);
    for(i=attribute[1]+distribute[1];i<24;i++)
        printf("□");
    Color(16);
    printf("%3d ",player.maxmp);
    if(distribute[1]>0)
    {
        Color(3);
        printf("+");
        printf("%3d",distribute[1]*4);
    }
    else
        printf("          ");
    GotoXY(x,++++y);

    Color(16);
    if(select==2)    Color(4);
    printf("  攻击力    ");
    for(i=0;i<attribute[2];i++)
        printf("■");
    Color(4);
    for(i=attribute[2];i<attribute[2]+distribute[2];i++)
        printf("■");
    Color(8);
    for(i=attribute[2]+distribute[2];i<24;i++)
        printf("□");
    Color(16);
    printf("%3d ",player.atk);
    if(distribute[2]>0)
    {
        Color(4);
        printf("+");
        printf("%3d",distribute[2]*2);
    }
    else
        printf("          ");
    GotoXY(x,++++y);

    Color(16);
    if(select==3)    Color(6);
    printf("  防御力    ");
    for(i=0;i<attribute[3];i++)
        printf("■");
    Color(6);
    for(i=attribute[3];i<attribute[3]+distribute[3];i++)
        printf("■");
    Color(8);
    for(i=attribute[3]+distribute[3];i<24;i++)
        printf("□");
    Color(16);
    printf("%3d ",player.def);
    if(distribute[3]>0)
    {
        Color(6);
        printf("+");
        printf("%3d",distribute[3]);
    }
    else
        printf("          ");
    GotoXY(x,++++y);

    Color(16);
    if(select==4)    Color(13);
    printf("   速度     ");
    for(i=0;i<attribute[4];i++)
        printf("■");
    Color(13);
    for(i=attribute[4];i<attribute[4]+distribute[4];i++)
        printf("■");
    Color(8);
    for(i=attribute[4]+distribute[4];i<24;i++)
        printf("□");
    Color(16);
    printf("%3d ",player.spd);
    if(distribute[4]>0)
    {
        Color(13);
        printf("+");
        printf("%3d",distribute[4]);
    }
    else
        printf("          ");
    GotoXY(x,++++y);

    Color(16);
}

///根据怪物ID播放BGM
void BGM(int mID)
{
    music.Close();
    if(mID==10)    //Boss 1:弥诺陶洛斯
        music.Load("Minotaur.wav");
    else if(mID==11)    //Boss 2:瓦凯诺
        music.Load("Valcano.wav");
    else if(mID==12||mID==14)    //Boss 3：古龙
        music.Load("AncientDragon.wav");
    else    //普通怪物
    {
        srand(time(NULL));
        if(rand()%2)
            music.Load("Battle1.wav");
        else
            music.Load("Battle2.wav");
    }
    music.Play();
}



///***************************     PART 2

char mapname[50][40];

int smapcnt=1;
int randmapcnt=0;
int smapl=0;
int randmapl=0;
int aside;
int bside;

int choose();
void mapdecide();
void mapinput();
void BuildMap(int mazeType);
int Play(int playType);
void PlayMapInit();
void GetRandom(int low,int high,int &num);

struct smap{
    //MAZE    mapsize[100][100];
    char Cmapname[20];
    char Emapname[20];
}randmap[50],smap[50];

int  choose(){
     // new version of getch()
	int c2 ;
	int x=0;
    int p=0;
	while(c2 = _getch()){
        switch (c2)
        {
        case 72: // up
		// do something
            break;
        case 80: // down
		// do something
            p=1;
            break;
        case 75: // left
            // do something
            x--;
            break;
        case 77: // right
            // do something
            x++;
            break;
        default:
            // do something
            break;
        }
        if(p==1)
            break;
        if(x<0) x++;
        if(x>2) x--;
        else{
            if(x==0){
                randmapcnt-=2;
                int x,y;
                GetXY(x,y);
                GotoXY(35,11);
                Color(1);
                cout<<smap[smapcnt].Cmapname;
                Color(0);
                GotoXY(59,11);
                cout<<randmap[aside].Cmapname;
                randmapcnt++;
                GotoXY(86,11);
                cout<<randmap[bside].Cmapname;
                randmapcnt++;
                GotoXY(1,20);
            }
            else if(x==1){
                randmapcnt-=2;
                int x,y;
                GetXY(x,y);
                GotoXY(35,11);
                cout<<smap[smapcnt].Cmapname;
                GotoXY(59,11);
                Color(1);
                cout<<randmap[aside].Cmapname;
                randmapcnt++;
                Color(0);
                GotoXY(86,11);
                cout<<randmap[bside].Cmapname;
                randmapcnt++;
                GotoXY(1,20);
            }
            else if(x==2){
                randmapcnt-=2;
                int x,y;
                GetXY(x,y);
                GotoXY(35,11);
                cout<<smap[smapcnt].Cmapname;
                GotoXY(59,11);
                cout<<randmap[aside].Cmapname;
                randmapcnt++;
                GotoXY(86,11);
                Color(1);
                cout<<randmap[bside].Cmapname;
                Color(0);
                randmapcnt++;
                GotoXY(1,20);
            }
        }
    }
    return x;
}


void mapinput(){
    FILE *fp;
    fp=fopen("smapname.txt","r");
    char str[100];
    int i=0;
    while(fgets(str,100,fp)){
        if(i%2==0)  strcpy(smap[smapl].Cmapname,str);
        else{
             strcpy(smap[smapl].Emapname,str);
             smapl++;
        }
        i++;
    }
    fclose(fp);
    fp=fopen("randmapname.txt","r");
    i=0;
     while(fgets(str,100,fp)){
        if(i%2==0)  strcpy(randmap[randmapl].Cmapname,str);
        else{
             strcpy(randmap[randmapl].Emapname,str);
             randmapl++;
        }
        i++;
    }
}

void mapdecide(){
    system("cls");
    Color(0);
    cout<<"\n\n\n\n\n\n\n\n 		                                      请选择你接下来要前往的地方："<<endl;
    cout<<"                              ";
    cout<<"#####################	#####################	   #####################"<<endl;
    for(int i=0;i<3;i++){
        cout<<"                              ";
        cout<<"#                   #	#		    #	   #		       #"<<endl;
    }
    cout<<"                              ";
    cout<<"#####################	#####################	   #####################"<<endl;
    for(int i=0;i<2;i++)    cout<<endl;
    cout<<" 		                                       请按←和→选择目标地图"<<endl;
    cout<<" 		                                         请按↓确认所选地图"<<endl;
    int x,y;
    GetXY(x,y);
    GotoXY(35,11);
    Color(1);
    cout<<smap[smapcnt].Cmapname;
    Color(0);
    GotoXY(59,11);
    aside=rand()%8;
    while((bside=rand()%8)==aside){
    }
    cout<<randmap[aside].Cmapname;
    randmapcnt++;
    GotoXY(86,11);
    cout<<randmap[bside].Cmapname;
    randmapcnt++;
     x=choose();
     if(x==0){
        smapcnt++;
        if(smapcnt==2){
            PlayMapInit();
            BuildMap(COMBAT_MAZE);// 0 or 1
            if(Play(COMBAT_MAZE)) // 0 1 2 3
            mapdecide();
        }
        else if(smapcnt==3){
            Passage(2);
            Fight(10);
            Passage(3);
            mapdecide();
        }
        else if(smapcnt==4){
            Anime::ADPeak();
            Passage(4);
            Fight(11);
            Passage(5);
            Passage(6);
            Anime::ADClimax();
            Fight(12);
            Passage(7);
            Credit();
            system("cls");
            SavePlayer();
            int x=56,y=16;
            GotoXY(x,y);
            printf("       已可进行多周目游戏");GotoXY(x,++++y);
            printf("“继续游戏”将进入下周目游戏世界");
            GetInput();
            smapcnt=0;
        }
     }
     else if(x==1){
        PlayMapInit();
        BuildMap(COMBAT_MAZE);// 0 or 1
        if(Play(1))// 0 1 2 3
            mapdecide();
     }
     else{
        PlayMapInit();
        BuildMap(COMBAT_MAZE);// 0 or 1
        int playType;
        GetRandom(2,3,playType);
        if(Play(playType))// 0 1 2 3
            mapdecide();
     }
}


///***************************     PART 3

typedef struct
{
    int r;
    int c;
    int lastR;
    int lastC;
    int defeated;
} Coordinate;

typedef struct
{
    int r;
    int c;
    int step;
} QUEUE;

typedef struct
{
    int cell;//储存迷宫单元格基本信息
    int condition;//在单元格为墙时，0表示横墙,1竖墙,2为横竖交叉墙,
}MAZE;

typedef struct pos
{
    int r;
    int c;
    int pre;
    pos():r(),c(),pre(){}
    pos(int a,int b,int c):r(a),c(b),pre(c){}
}POS;

mutex myLock;
MAZE maze[500][500];
Coordinate playerPos,player2Pos;
Coordinate monsterPos[100];
Coordinate crystal[50];

int thEnd=0;
int playerBombLeft=3;
int minute,second;
int nMonster=0;
int nCrystal=0;
int mazeRow=0,mazeCol=0,mazeMoveRow=0,mazeMoveCol=0;

void BuildBasicMap(FILE *fp);//生成基本地图
int FindClosestWall(int _r,int _c);//找最近的墙
void BuildRandomWall();//随机墙壁
void BuildRandomMonster();//随机怪物


void WallRevision(int r,int c);//修正十字墙
void PlayBasicMap();//打印基本地图
void PlayerMove();
void PlayerMove2();
void MonsterMove(int moveType);
void MazeFirelinkShrine();
void PlayerMonsterMovePack();
int Contact();
void GetRandom(int low,int high,int &num);

class MonsterToPlayer
{
    private:
    queue<POS> Q;
    int i;
    POS close[10000];
    int rec[500][500];

    void Init()
    {
        i=0;
        memset(rec,0,sizeof(rec));
        while(!Q.empty())
            Q.pop();
    }

    public:
    int BFS(Coordinate m,int type) //返回怪物移动的结果：上1下2左3右4停0
    {
        POS cur;
        Init();
        Q.push(pos(m.r,m.c,0));
        while(!Q.empty())
        {
            cur=Q.front();
            close[i++]=cur;
            if(cur.r==playerPos.r&&cur.c==playerPos.c)
            {
                i--;
                while(close[i].pre)
                    i=close[i].pre;
                if(close[i].r==m.r-1&&close[i].c==m.c)
                    return 1;
                else if(close[i].r==m.r+1&&close[i].c==m.c)
                    return 2;
                else if(close[i].r==m.r&&close[i].c==m.c-1)
                    return 3;
                else if(close[i].r==m.r&&close[i].c==m.c+1)
                    return 4;
                else
                    return 0;
            }
            if(maze[cur.r-1][cur.c].cell==0&&!rec[cur.r-1][cur.c])
            {
                Q.push(pos(cur.r-1,cur.c,i-1));
                rec[cur.r-1][cur.c]=1;
            }
            if(maze[cur.r+1][cur.c].cell==0&&!rec[cur.r+1][cur.c])
            {
                Q.push(pos(cur.r+1,cur.c,i-1));
                rec[cur.r+1][cur.c]=1;
            }
            if(maze[cur.r][cur.c-1].cell==0&&!rec[cur.r][cur.c-1])
            {
                Q.push(pos(cur.r,cur.c-1,i-1));
                rec[cur.r][cur.c-1]=1;
            }
            if(maze[cur.r][cur.c+1].cell==0&&!rec[cur.r][cur.c+1])
            {
                Q.push(pos(cur.r,cur.c+1,i-1));
                rec[cur.r][cur.c+1]=1;
            }
            Q.pop();
        }
        return 0;
    }
}mtp;

void PlayMapInit()
{
    for(int i=0;i<300;i++)
    {
        for(int j=0;j<300;j++)
        {
            maze[i][j].cell=0;
            maze[i][j].condition=-1;
        }
    }
    nMonster=0;
    nCrystal=0;
    mazeRow=0;
    mazeCol=0;
    mazeMoveRow=0;
    mazeMoveCol=0;
    playerBombLeft=3;
    thEnd=1;
}

void GetRandom(int low,int high,int &num)
{
    num=(rand()%(high-low+1))+low;
}

void BuildRandomMonster()//用于生成地图
{
    int monsterNum;
    int monsterType;
    int monsterCaps;
    GetRandom(3,5,monsterNum);
    for(int i=0; i<monsterNum; i++)
    {
        int r,c;
        GetRandom(1,mazeRow-2,r);
        GetRandom(1,mazeCol-2,c);
        GetRandom(1,10,monsterCaps);
        if(monsterCaps>=7)
            GetRandom('A','Z',monsterType);
        else
            GetRandom('a','z',monsterType);
        if(maze[r][c].cell==0&&r!=playerPos.r&&c!=playerPos.c)
        {
            maze[r][c].cell=monsterType;
            monsterPos[nMonster].r=r;
            monsterPos[nMonster].lastR=r;
            monsterPos[nMonster].c=c;
            monsterPos[nMonster].lastC=c;
            nMonster++;
        }
    }
}
int FindClosestWall(int _r,int _c)//找最近的墙
{
    int head=0,tail=0;
    int record[mazeRow+5][mazeCol+5];
    int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
    QUEUE _queue[mazeRow*mazeCol+5];

    for(int i=0;i<mazeRow;i++)
        for(int j=0;j<mazeCol;j++)
                record[i][j]=0;

    _queue[tail].r=_r;
    _queue[tail].c=_c;
    _queue[tail].step=0;
    record[_r][_c]=1;
    tail++;
    while(head!=tail&&_queue[head].step<=1.0/5*mazeCol)
    {
        if(maze[_queue[head].r][_queue[head].c].cell==1)
        {
            if(maze[_queue[head].r][_queue[head].c].condition==1)//竖直墙壁
                return 1;
            else
                return 2;
        }
        for(int i=0;i<4;i++)
        {
            int x=_queue[head].r+dir[i][0];
            int y=_queue[head].c+dir[i][1];
            if(x>=0&&x<=mazeRow&&y>=0&&y<=mazeCol&&record[x][y]==0)
            {
                _queue[tail].r=x;
                _queue[tail].c=y;
                _queue[tail].step=_queue[head].step+1;
                record[x][y]=1;
                tail++;
            }
        }
        head++;
    }
    return 0;
}

void BuildRandomWall()//随机墙壁
{
    int r,c,rand,wallType;
    for(int i=1; i<=2; i++)
    {
        for(int j=1; j<=3; j++)
        {
            GetRandom(-2,2,rand);
            c=(double)j/4*mazeCol+rand;
            if(!(c>0&&c<mazeCol))
                c-=rand;
            GetRandom(-2,2,rand);
            r=(double)i/3*mazeRow+rand;
            if(!(r>0&&r<mazeRow))
                r-=rand;
            //int rt=r,ct=c;

            int flag=FindClosestWall(r,c);//找最近的墙
            if(flag==1)//最近的墙为竖墙
                GetRandom(2,3,wallType);//建横墙
            else if(flag==2)//横墙
                GetRandom(0,1,wallType);//建竖墙
            else//没有墙
                GetRandom(0,3,wallType);//横竖都可

            while(r>=0&&r<mazeRow&&c>=0&&c<mazeCol)
            {
                if(r!=playerPos.r&&c!=playerPos.c&&maze[r][c].cell==0)
                    maze[r][c].cell=1;
                switch(wallType)
                {
                case 0://up
                    maze[r][c].condition=1;
                    r--;
                    break;
                case 1://down
                    maze[r][c].condition=1;
                    r++;
                    break;
                case 2://left
                    maze[r][c].condition=0;
                    c--;
                    break;
                case 3://right
                    maze[r][c].condition=0;
                    c++;
                    break;
                }
            }
            //maze[rt][ct].cell=3;
        }
    }
}

void BuildBasicMap(FILE *fp)
{
    int i=0;
    int firstRow=1;
    char mazeLine[500];
    while(fgets(mazeLine,500,fp)!=NULL)
    {
        /*
        if(strcmp(mazeLine,"-1\n")<=0)//mazeLine=="-1"或"-1\n"
            break;*/
        if(firstRow)
        {
            mazeCol=strlen(mazeLine)-1;
            firstRow=0;
        }
        for(int j=0; j<mazeCol; j++)
        {
            if(mazeLine[j]==' '||mazeLine[j]=='1')
            {
                if(mazeLine[j]==' ')
                    maze[i][j].cell=mazeLine[j]-32;
                else
                    maze[i][j].cell=mazeLine[j]-48;
            }
            else if((mazeLine[j]>='a'&&mazeLine[j]<='z')||(mazeLine[j]>='A'&&mazeLine[j]<='Z'))
            {
                maze[i][j].cell=(int)mazeLine[j];
                monsterPos[nMonster].r=i;
                monsterPos[nMonster].lastR=i;
                monsterPos[nMonster].c=j;
                monsterPos[nMonster].lastC=j;
                monsterPos[nMonster].defeated=0;
                nMonster++;
            }
            else if(mazeLine[j]=='2')
            {
                playerPos.r=i;
                playerPos.c=j;
                maze[i][j].cell=0;
            }
            else if(mazeLine[j]=='*')
            {
                maze[i][j].cell=(int)mazeLine[j];
                crystal[nCrystal].r=i;
                crystal[nCrystal].c=j;
                nCrystal++;
            }
        }
        i++;
    }
    mazeRow=i;
}
void BuildPeaceWallCondition()
{
    system("cls");
    GotoXY(0,0);
    FILE *fp;
    if((fp=fopen("FireLinkShrine_WallCondition.txt","r"))==NULL)
    {
        printf("读取地图文件错误\n");
        return;
    }

    int i=0;
    char mazeLine[500];
    while(fgets(mazeLine,500,fp)!=NULL)
    {
        for(int j=0; j<mazeCol; j++)
        {
            if(mazeLine[j]>='0'&&mazeLine[j]<='7')
            {
                maze[i][j].condition=mazeLine[j]-48;
                //GotoXY(j,i);cout<<maze[i][j].condition;
            }
        }
        i++;
    }
    //getch();
    fclose(fp);
}
void BuildMap(int mazeType)
{
    FILE *fp;
    if(mazeType==0)
        fp=fopen("FireLinkShrine.txt","r");
    else
        fp=fopen("maze.txt","r");
    if(fp==NULL)
    {
        printf("读取地图文件错误\n");
        return;
    }
    nMonster=0;
    fscanf(fp,"%d%d\n",&mazeMoveRow,&mazeMoveCol);//'\n'吞掉回车，防止被fgets读到

    BuildBasicMap(fp);//生成基本地图
    fclose(fp);

    switch(mazeType)//生成详细地图
    {
    case 0://和平地图
        BuildPeaceWallCondition();
        break;
    case 1://战斗地图
        BuildRandomWall();//随机墙壁
        BuildRandomMonster();//随机怪物
        //保证地图边沿的横墙或竖墙
        for(int j=0; j<mazeRow; j++)
        {
            maze[j][0].condition=1;
            maze[j][mazeCol-1].condition=1;
        }
        for(int j=0; j<mazeCol; j++)
        {
            maze[0][j].condition=0;
            maze[mazeRow-1][j].condition=0;
        }
        break;
    }
}
int Contact()
{
    if((maze[playerPos.r][playerPos.c].cell>='a'&&maze[playerPos.r][playerPos.c].cell<='z')
       ||(maze[playerPos.r][playerPos.c].cell>='A'&&maze[playerPos.r][playerPos.c].cell<='Z'))
   {
       for(int i=0;i<nMonster;i++)
        if(monsterPos[i].defeated==0&&monsterPos[i].r==playerPos.r&&monsterPos[i].c==playerPos.c)
            return i;
   }
    else
        return -1;
    return -1;
}
void MonsterMoveRandom()
{
    while(thEnd!=1)
    {
        for(int i=0; i<nMonster; i++)
        {
            if(monsterPos[i].defeated==1)
                continue;
            monsterPos[i].lastR=monsterPos[i].r;
            monsterPos[i].lastC=monsterPos[i].c;
            int num=0,choice=0;
            GetRandom(-1,1,num);//x+=num或者y+=num
            GetRandom(0,1,choice);//移动x还是y
            if(choice==1)
                monsterPos[i].r+=num;
            else
                monsterPos[i].c+=num;

            if(maze[monsterPos[i].r][monsterPos[i].c].cell==0)
            {
                maze[monsterPos[i].r][monsterPos[i].c].cell=maze[monsterPos[i].lastR][monsterPos[i].lastC].cell;
                maze[monsterPos[i].lastR][monsterPos[i].lastC].cell=0;
            }
            else
            {
                monsterPos[i].r=monsterPos[i].lastR;
                monsterPos[i].c=monsterPos[i].lastC;
            }
        }
        Sleep(700);
    }
}
void MonsterMoveChasePlayer()
{
    while(thEnd!=1)
    {
        for(int i=0; i<nMonster; i++)
        {
            if(monsterPos[i].defeated==1)
                continue;
            monsterPos[i].lastR=monsterPos[i].r;
            monsterPos[i].lastC=monsterPos[i].c;

            int dir=mtp.BFS(monsterPos[i],1);
            switch(dir)
            {
                case 1: monsterPos[i].r--;break;
                case 2: monsterPos[i].r++;break;
                case 3: monsterPos[i].c--;break;
                case 4: monsterPos[i].c++;break;
                default: break;
            }
            if(maze[monsterPos[i].r][monsterPos[i].c].cell==0)
            {
                maze[monsterPos[i].r][monsterPos[i].c].cell=maze[monsterPos[i].lastR][monsterPos[i].lastC].cell;
                maze[monsterPos[i].lastR][monsterPos[i].lastC].cell=0;
            }
            else
            {
                monsterPos[i].r=monsterPos[i].lastR;
                monsterPos[i].c=monsterPos[i].lastC;
            }
        }
        Sleep(300);
    }
}

void BombWall(int r,int c)//r,c处存在墙
{
    if(r==0||r==mazeRow-1||c==0||c==mazeCol)
        return;
    Color(4);
    GotoXY(c+mazeMoveCol,r+mazeMoveRow);
    switch(maze[r][c].condition)
    {
    case 0:printf("━");break;
    case 1:printf("┃");break;
    case 3:printf("┳");break;
    case 4:printf("┻");break;
    case 5:printf("┫");break;
    case 6:printf("┣");break;
    }
    Sleep(500);
    PlaySound(TEXT("Blast.wav"),NULL,SND_FILENAME|SND_ASYNC);
    GotoXY(c+mazeMoveCol,r+mazeMoveRow);
    printf(" ");
    Color(16);
    maze[r][c].cell=0;
    maze[r][c].condition=-1;
}
void PlayerBombWall()
{
    char ch=getch();
    switch(ch)
    {
    case'w':
        if(maze[playerPos.r-1][playerPos.c].cell==1)
            BombWall(playerPos.r-1,playerPos.c);
        break;
    case's':
        if(maze[playerPos.r+1][playerPos.c].cell==1)
            BombWall(playerPos.r+1,playerPos.c);
        break;
    case'a':
        if(maze[playerPos.r][playerPos.c-1].cell==1)
            BombWall(playerPos.r,playerPos.c-1);
        break;
    case'd':
        if(maze[playerPos.r][playerPos.c+1].cell==1)
            BombWall(playerPos.r,playerPos.c+1);
        break;
    default:
        return;
    }
}
void PlayerMove()
{
    char ch;
    ch=getch();
    switch(ch)
    {
    case'w':
        playerPos.r--;
        if(maze[playerPos.r][playerPos.c].cell==1)
            playerPos.r++;
        break;
    case's':
        playerPos.r++;
        if(maze[playerPos.r][playerPos.c].cell==1)
            playerPos.r--;
        break;
    case'a':
        playerPos.c--;
        if(maze[playerPos.r][playerPos.c].cell==1)
            playerPos.c++;
        break;
    case'd':
        playerPos.c++;
        if(maze[playerPos.r][playerPos.c].cell==1)
            playerPos.c--;
        break;
    case' ':
        if(playerBombLeft>0)
        {
            playerBombLeft--;
            Color(1);
            GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
            printf("e");
            PlayerBombWall();
        }
        break;
    default:
        ch=getch();
        break;
    }
}
void WallRevision(int r,int c)//检查墙r,c的周围有无墙，什么墙，修正十字墙
{
    //r,c前提是墙
    if(maze[r][c].condition==1)//竖墙
    {
        if(c-1>0&&c-1<mazeCol&&c+1<mazeCol&&maze[r][c-1].cell==1&&maze[r][c+1].cell==1)
                maze[r][c].condition=2;

        else if(c-1>0&&c-1<mazeCol&&maze[r][c-1].cell==1)
                maze[r][c].condition=5;

        else if(c+1<mazeCol&&maze[r][c+1].cell==1)
                maze[r][c].condition=6;
    }
    else if(maze[r][c].condition==0)//横墙
    {
        if(r-1>0&&r-1<mazeRow&&r+1<mazeRow&&maze[r-1][c].cell==1&&maze[r+1][c].cell==1)
                maze[r][c].condition=2;
        else if(r-1>0&&r-1<mazeRow&&maze[r-1][c].cell==1)
                maze[r][c].condition=4;
        else if(r+1<mazeRow&&maze[r+1][c].cell==1)
                maze[r][c].condition=3;
    }
}
void PlayBasicMap(int playType)
{
    GotoXY(mazeMoveCol,mazeMoveRow);
    for(int i=0; i<mazeRow; i++)
    {
        for(int j=0; j<mazeCol; j++)
        {
            if(maze[i][j].cell==1)
            {
                if(playType!=0)//非和平地图，随机墙壁后，进行十字墙修正
                    WallRevision(i,j);
                GotoXY(j+mazeMoveCol,i+mazeMoveRow);
                //printf("%d",maze[i][j].condition);
                switch(maze[i][j].condition)
                {
                case 0:printf("━");break;
                case 1:printf("┃");break;
                case 2:printf("╋");break;
                case 3:printf("┳");break;
                case 4:printf("┻");break;
                case 5:printf("┫");break;
                case 6:printf("┣");break;
                case 7:printf("┏");break;
                default:printf("#");break;
                }
            }
        }
    }
    //四个角
    GotoXY(mazeMoveCol,mazeMoveRow);printf("┏");
    GotoXY(mazeCol-1+mazeMoveCol,mazeMoveRow);printf("┓");
    GotoXY(mazeMoveCol,mazeRow-1+mazeMoveRow);printf("┗");
    GotoXY(mazeCol-1+mazeMoveCol,mazeRow-1+mazeMoveRow);printf("┛");
}

void ColorGameResult()
{
    system("cls");
    //计算颜色格子数
    int player1=0,player2Pos=0;
    for(int i=0;i<mazeRow;i++)
    {
        for(int j=0;j<mazeCol;j++)
        {
            if(maze[i][j].cell==2)
                player1++;
            else if(maze[i][j].cell==3)
                player2Pos++;
        }
    }
    //打印边框
    Color(16);
    int x=48;
    int y=10;
    GotoXY(x,y);printf("┏");
    for(int i=1;i<=33;i++)
        printf("━");
    printf("┓");
    for(int i=1;i<=15;i++)
    {
        GotoXY(x,y+i);printf("┃");
        GotoXY(x+34,y+i);printf("┃");
    }
    GotoXY(x,y+16);printf("┗");
    for(int i=1;i<=33;i++)
        printf("━");
    printf("┛");

    GotoXY(55,15);Color(1);printf("player1");
    GotoXY(65,15);Color(2);printf("VS");
    GotoXY(70,15);Color(4);printf("player2");

    int i=0,j=0;
    while(i<=player1&&j<=player2Pos)
    {
        GotoXY(58,20);Color(1);printf("%d",i++);
        GotoXY(73,20);Color(4);printf("%d",j++);
        Sleep(50);
    }
    while(i<=player1)//代码1
    {
        GotoXY(58,20);Color(1);printf("%d",i++);
        Sleep(50);
    }
    while(j<=player2Pos)//代码2。代码1和代码2只发生其中一个
    {
        GotoXY(73,20);Color(4);printf("%d",j++);
        Sleep(50);
    }
    Color(6);
    if(player1>player2Pos)
    {
        GotoXY(57,23);printf("WIN!");
    }
    else if(player1<player2Pos)
    {
        GotoXY(72,23);printf("WIN!");
    }
    else
    {
        GotoXY(64,23);printf("EVEN!");
    }
}
void PlayerMove2()
{
    char ch;
    ch=getch();
    switch(ch)
    {
    case'w':
        playerPos.r--;
        if(maze[playerPos.r][playerPos.c].cell==1)
            playerPos.r++;
        break;
    case's':
        playerPos.r++;
        if(maze[playerPos.r][playerPos.c].cell==1)
            playerPos.r--;
        break;
    case'a':
        playerPos.c--;
        if(maze[playerPos.r][playerPos.c].cell==1)
            playerPos.c++;
        break;
    case'd':
        playerPos.c++;
        if(maze[playerPos.r][playerPos.c].cell==1)
            playerPos.c--;
        break;

    case'8':
        player2Pos.r--;
        if(maze[player2Pos.r][player2Pos.c].cell==1)
            player2Pos.r++;
        break;
    case'5':
        player2Pos.r++;
        if(maze[player2Pos.r][player2Pos.c].cell==1)
            player2Pos.r--;
        break;
    case'4':
        player2Pos.c--;
        if(maze[player2Pos.r][player2Pos.c].cell==1)
            player2Pos.c++;
        break;
    case'6':
        player2Pos.c++;
        if(maze[player2Pos.r][player2Pos.c].cell==1)
            player2Pos.c--;
        break;
    default:
        ch=getch();
        break;
    }
}

void CountDown()//倒计时
{
    while(minute>=0)
    {
        while(second>0)
        {
            second--;
            Sleep(1000);
        }
        minute--;
        second=60;
    }
    minute=0;
    second=-1;
}
void CountDownON(int _min,int _sec)
{
    minute=_min;
    second=_sec;
    thread th(CountDown);//倒计时,min,sec不断减少
    th.detach();
    Color(16);
    GotoXY(64,1);printf("倒计时");
    GotoXY(62,3);printf("<");
    GotoXY(70,3);printf(">");
}
void CountDownDisplay()
{
    //倒计时,不断读取min和sec,最后10s颜色变红
    GotoXY(64,3);
    Color(2);
    if(minute==0&&second<=10)
        Color(4);
    if(second<0)
        printf("%02d:%02d",minute,0);
    printf("%02d:%02d",minute,second);
    Color(16);
}
int CountDownEnd()
{
    if(minute*60+second>=0)
        return 1;
    else
        return 0;
}
int PlayColorGame()
{
    music.Load("CombatMaze.wav");
    music.Play();

    player2Pos.r=mazeRow-playerPos.r;
    player2Pos.c=mazeCol-playerPos.c;
    maze[player2Pos.r][player2Pos.c].cell=3;
    maze[playerPos.r][playerPos.c].cell=2;

    GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
    Color(1);printf("e");Color(16);
    GotoXY(player2Pos.c+mazeMoveCol,player2Pos.r+mazeMoveRow);
    Color(4);printf("f");Color(16);

    thEnd=0;
    thread thMonster(MonsterMoveRandom);
    thMonster.detach();

    int rand;
    CountDownON(0,40);
    while(CountDownEnd())
    {
        CountDownDisplay();
        for(int k=0; k<nMonster; k++)
        {
            GotoXY(monsterPos[k].lastC+mazeMoveCol,monsterPos[k].lastR+mazeMoveRow);
            printf(" ");
            GotoXY(monsterPos[k].c+mazeMoveCol,monsterPos[k].r+mazeMoveRow);
            printf("%c",maze[monsterPos[k].r][monsterPos[k].c].cell);
        }
        if(kbhit())
        {
            GetRandom(0,9,rand);

            Color(1);
            GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
            printf("%d",rand);
            maze[playerPos.r][playerPos.c].cell=2;

            Color(4);
            GotoXY(player2Pos.c+mazeMoveCol,player2Pos.r+mazeMoveRow);
            printf("%d",rand);
            maze[player2Pos.r][player2Pos.c].cell=3;

            PlayerMove2();

            Color(4);
            GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
            maze[playerPos.r][playerPos.c].cell=2;
            printf("e");

            Color(1);
            GotoXY(player2Pos.c+mazeMoveCol,player2Pos.r+mazeMoveRow);
            maze[player2Pos.r][player2Pos.c].cell=3;
            printf("f");
            Color(16);
        }
        if(music.End())
        {
            music.Load("CombatMaze.wav");
            music.Play();
        }
    }
    thEnd=1;
    //结算
    ColorGameResult();
    GetInput();
    music.Close();
    FightWin(monster[13]);
    return 1;
}
void PlayerMonsterMovePack(int playerColor,int monsterColor)
{
    Color(monsterColor);
    for(int k=0; k<nMonster; k++)
    {
        if(monsterPos[k].defeated==1)
            continue;
        GotoXY(monsterPos[k].lastC+mazeMoveCol,monsterPos[k].lastR+mazeMoveRow);
        printf(" ");
        GotoXY(monsterPos[k].c+mazeMoveCol,monsterPos[k].r+mazeMoveRow);
        printf("%c",maze[monsterPos[k].r][monsterPos[k].c].cell);
    }
    if(kbhit())
    {
        Color(playerColor);
        GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
        printf(" ");

        PlayerMove();
        GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
        printf("e");
    }
    Color(16);
}
void PlayerFlick()
{
    int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
    for(int i=0; i<4; i++)
    {
        int _r=playerPos.r+dir[i][0];
        int _c=playerPos.c+dir[i][1];
        if(maze[_r][_c].cell==0)
        {
            playerPos.r=_r;
            playerPos.c=_c;
        }
    }
}
int PlayCombatGame()
{
    music.Load("CombatMaze.wav");
    music.Play();

    GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
    Color(1);printf("e");Color(16);

    thEnd=0;
    thread thMonster(MonsterMoveRandom);
    thMonster.detach();

    int exitR=mazeRow-playerPos.r;
    int exitC=mazeCol-playerPos.c;
    GotoXY(exitC+mazeMoveCol,exitR+mazeMoveRow);
    Color(2);printf("#");Color(16);

    int monsterIndex;
    int monsterId;

    while(1)
    {
        GotoXY(63,3);
        printf("炸弹数：");
        if(playerBombLeft>0)
            Color(2);
        else
            Color(4);
        printf("%d",playerBombLeft);
        Color(16);

        if(playerPos.r==exitR&&playerPos.c==exitC)
        {
            music.Close();
            thEnd=1;
            return 1;
        }
        if((monsterIndex=Contact())!=-1)
        {
            GetRandom(2,7,monsterId);
            int fightResult=Fight(monsterId);
            //int fightResult=-1;
            if(fightResult==1)//胜利
                monsterPos[monsterIndex].defeated=1;
            else if(fightResult==0)//失败，直接返回标题界面
            {
                music.Close();
                thEnd=1;
                return 0;
            }
            else//Fight(monsterId)==-1 player逃跑
            {
                PlayerFlick();
            }
            system("cls");
            PlayBasicMap(1);
            GotoXY(exitC+mazeMoveCol,exitR+mazeMoveRow);
            Color(2);printf("#");
            GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
            Color(1);printf("e");Color(16);
        }
        PlayerMonsterMovePack(1,12);
        if(music.End())
        {
            music.Load("CombatMaze.wav");
            music.Play();
        }
    }
}
int PlayChaseGame()
{
    music.Load("CombatMaze.wav");
    music.Play();

    GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
    Color(1);printf("e");Color(16);

    thEnd=0;
    thread thMonster(MonsterMoveChasePlayer);
    thMonster.detach();

    CountDownON(0,20);
    while(CountDownEnd())
    {
        CountDownDisplay();

        GotoXY(75,3);
        printf("炸弹数：");
        if(playerBombLeft>0)
            Color(2);
        else
            Color(4);
        printf("%d",playerBombLeft);
        Color(16);

        if(Contact()!=-1)
        {
            FightLose();
            return 0;
        }
        PlayerMonsterMovePack(1,12);
        if(music.End())
        {
            music.Load("CombatMaze.wav");
            music.Play();
        }
    }
    thEnd=1;
    Sleep(2000);
    FightWin(monster[13]);
    music.Close();
    return 1;
}
int PlayPeaceGame()
{
    music.Load("PeacefulMaze.wav");
    music.Play();


    GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
    Color(1);printf("e");Color(16);

    Color(4);
    for(int k=0;k<nCrystal;k++)
    {
        GotoXY(crystal[k].c+mazeMoveCol,crystal[k].r+mazeMoveRow);
        printf("*");
    }
    Color(16);

    LoadConversation();

    while(1)
    {
        if(maze[playerPos.r][playerPos.c].cell==(int)'*')
        {
            music.Close();
            return 1;
        }
        if(Contact()!=-1)
        {
            switch((char)maze[playerPos.r][playerPos.c].cell)
            {
            case 'P': HoboChat(1);break;
            case 'B': HoboChat(2);break;
            case 'L': HoboChat(3);break;
            case 'G': HoboChat(4);break;
            case 'W': HoboChat(5);break;
            }
            PlayerFlick();
        }
        for(int k=0; k<nMonster; k++)//Npc使用怪物模组
        {
            Color(2);
            GotoXY(monsterPos[k].c+mazeMoveCol,monsterPos[k].r+mazeMoveRow);
            printf("%c",maze[monsterPos[k].r][monsterPos[k].c].cell);
        }
        if(kbhit())
        {
            Color(1);
            GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
            printf(" ");

            PlayerMove();
            GotoXY(playerPos.c+mazeMoveCol,playerPos.r+mazeMoveRow);
            printf("e");
        }
        Color(4);
        for(int k=0;k<nCrystal;k++)
        {
            GotoXY(crystal[k].c+mazeMoveCol,crystal[k].r+mazeMoveRow);
            printf("*");
        }
        Color(16);

        if(music.End())
        {
            music.Load("PeacefulMaze.wav");
            music.Play();
        }
    }
    music.Close();
}

int Play(int playType)
{
    //system("cls");
    /*
    cout<<"mazeType="<<mazeType<<endl;
    cout<<"mazeRow="<<mazeRow<<" mazeCol="<<mazeCol<<endl;
    cout<<"mazeMoveRow="<<mazeMoveRow<<" mazeMoveCol="<<mazeMoveCol<<endl;
    cout<<"Nmonster="<<nMonster<<endl;
    */
    if(playType==0)
        Anime::FirelinkShrine();
    system("cls");

    int result;

    //打印基本地图
    PlayBasicMap(playType);
    switch(playType)
    {
    case 0:
        result=PlayPeaceGame();//和平地图
        break;
    case 1:
        result=PlayCombatGame();//战斗迷宫
        break;
    case 2:
        result=PlayChaseGame();//追逐游戏
        break;
    case 3:
        result=PlayColorGame();//填颜色游戏
        break;
    }
    music.Close();
    system("cls");
    return result;
}
