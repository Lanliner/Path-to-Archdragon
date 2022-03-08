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
#pragma comment(lib,"winmm.lib")

using namespace std;

///���ֲ�������
class Music
{
    //�����ַ�����Ŀ��Ŀ¼
    private:
        MCI_OPEN_PARMS OpenParms;
        MCI_PLAY_PARMS PlayParms;
        MCI_STATUS_PARMS StatusParms;
        MCI_GENERIC_PARMS GenericParms;

    public:
        void Load(string s) //��������
        {
            char path[100];
            int length=s.copy(path,99);
            path[length] = '\0';
            OpenParms.lpstrDeviceType = NULL;
            OpenParms.lpstrElementName = path;
            OpenParms.wDeviceID = 0;
            mciSendCommand (OpenParms.wDeviceID, MCI_OPEN,MCI_OPEN_ELEMENT, (DWORD)&OpenParms);
            PlayParms.dwFrom = 0;
        }
        void Play() //��������
        {
            mciSendCommand (OpenParms.wDeviceID, MCI_PLAY, MCI_FROM, (DWORD)&PlayParms);
        }
        int End()   //�Ƿ񲥷Ž���
        {
            StatusParms.dwItem = MCI_STATUS_POSITION;
            mciSendCommand (OpenParms.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&StatusParms);
            DWORD music_timing = StatusParms.dwReturn / 1000;

            StatusParms.dwItem = MCI_STATUS_LENGTH;
            mciSendCommand (OpenParms.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&StatusParms);
            DWORD music_length = StatusParms.dwReturn / 1000;

            return music_timing >= music_length;
        }
        void Close() //�ر�����
        {
            mciSendCommand(OpenParms.wDeviceID, MCI_CLOSE, 0, (DWORD)&GenericParms);
        }
}music;

///��ռ��̻��������ȡ����
char GetInput()
{
    while(kbhit())
        getch();
    return getch();
}

///�õ����λ��
void GetXY(int &x,int &y)
{
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &pBuffer);
	x=pBuffer.dwCursorPosition.X;
	y=pBuffer.dwCursorPosition.Y;
}

///����ƶ�
void GotoXY(int x,int y)
{
    CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
    HANDLE    hConsoleOut;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
    csbiInfo.dwCursorPosition.X = x;
    csbiInfo.dwCursorPosition.Y = y;
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

///���ɼ�
void CursorVisible(int vsb)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = vsb;
	SetConsoleCursorInfo(handle, &CursorInfo);
}

///����������ɫ
void Color(int x)
{
    if(x>=0 && x<=15)//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                BACKGROUND_INTENSITY | //��������
                                BACKGROUND_RED |
                                BACKGROUND_GREEN |
                                BACKGROUND_BLUE
                                |x);
    else//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                BACKGROUND_INTENSITY |
                                BACKGROUND_RED |
                                BACKGROUND_GREEN |
                                BACKGROUND_BLUE );
}
