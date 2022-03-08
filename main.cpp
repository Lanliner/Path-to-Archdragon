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
#include "body.cpp"

using namespace std;

int main()
{
    system("color F0");
    Color(16);
    CursorVisible(0);
    LoadTips();
    LoadConversation();
    LoadDescription();
    LoadMonster();
    mapinput();

    while(true)
    {
        Title();
        player.atk=80;
        player.def=8;
        player.skill[3]=10;
        player.skill[4]=3;
        srand(time(NULL));
        PlayMapInit();
        BuildMap(1);
        Play(3);
        mapdecide();
    }
    return 0;
}
