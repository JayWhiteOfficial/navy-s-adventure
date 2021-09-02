#pragma once
//特别提醒：如果提示编译失败请将sprintf_s换成sprintf
#ifndef SNAKE_LEVIOSTREAM_H
#define SNAKE_LEVIOSTREAM_H

#include <cstdio>
#include <windows.h>
#include <cstdlib>
#include <string>
#define COL 120
#define LIN 30
#define DEFAULT_COLOR 15
#define RAW 1
#define MAP 0
#define LEFT -1
#define MID -2
#define RIGHT -3
#define GREEN_BLACK 10
#define WHITE_BLACK 15
#define RED_BLACK 12
#define GRAY_BLACK 0x8
#define PURPLE_BLACK 0x5
#define BLUE_BLACK 0x3
#define YELLOW_BLACK 0x6
#define CYAN_BLACK 0xB
using namespace std;
void gotoxy(int x, int y) //x,y分别代表小黑窗的横坐标，纵坐标
{
    if (x % 2 != 0)return;
    COORD pos = { (short)x,(short)y };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

void putchar2xy(int x, int y, char ch, WORD Color = DEFAULT_COLOR) {
    if (x * 2 >= COL) return;
    if (y >= LIN) return;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(2 * x, y);
    SetConsoleTextAttribute(hOut, Color);
    putchar(ch);
    SetConsoleTextAttribute(hOut, 15);
}

void putchar2raw(int x, int y, char ch, WORD Color = DEFAULT_COLOR) {
    if (x >= COL) return;
    if (y >= LIN) return;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(x, y);
    SetConsoleTextAttribute(hOut, Color);
    putchar(ch);
    SetConsoleTextAttribute(hOut, 15);
}
void PutSentence(int x, int y, string str, WORD Color = DEFAULT_COLOR)
{
    if (x * 2 >= COL) return;
    if (y >= LIN) return;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(2 * x, y);
    SetConsoleTextAttribute(hOut, Color);
    cout << str << endl;
    SetConsoleTextAttribute(hOut, 15);
}
void PutSentence(int x, int y, int num, WORD Color = DEFAULT_COLOR)
{
    if (x * 2 >= COL) return;
    if (y >= LIN) return;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(2 * x, y);
    SetConsoleTextAttribute(hOut, Color);
    cout << num << endl;
    SetConsoleTextAttribute(hOut, 15);
}
class ostreamL {
private:
    int x, y; // Actual xy
    WORD color;
public:
    ostreamL() :x(0), y(0), color(DEFAULT_COLOR) {}
    ostreamL& operator()(int, int, WORD, int);
    ostreamL& operator<<(const char*);
    ostreamL& operator<<(long long);
    ostreamL& operator<<(char);
    ostreamL& operator<<(double);
    ostreamL& paint(int, int, const char*, WORD);
};

ostreamL& ostreamL::operator()(int a, int b, WORD Color = DEFAULT_COLOR, int mode = MAP) {
    color = Color;
    if (mode == MAP) { x = a * 2, y = b; return *this; }
    else { x = a, y = b; return *this; }
}

ostreamL& ostreamL::operator<<(const char* str) {
    int len = strlen(str);
    for (int i = 0;i < len;i++) {
        if (x >= COL) return *this;
        putchar2raw(x, y, str[i], color);
        x++;
    }return *this;
}

ostreamL& ostreamL::operator<<(long long tmp) {
    char tmpc[200] = { 0 }; int len = 0;
    for (len = 0;tmp > 0;len++) {
        tmpc[len] = (char)(tmp % 10);
        tmp /= 10;
    }
    while (len > 0) {
        len--;
        putchar2raw(x, y, tmpc[len] + '0');
        x++;
    }

    return *this;
}

ostreamL& ostreamL::operator<<(char ctmp) {
    putchar2raw(x, y, ctmp);
    x++;
    return *this << ctmp;
}

ostreamL& ostreamL::operator<<(double dtmp) {
    char tmpc[200] = { 0 };
    sprintf_s(tmpc, "%lf", dtmp);
    return *this << tmpc;
}

/*ostreamL& ostreamL::paint(int x, int y, const char* str, WORD Color = DEFAULT_COLOR) {

}
*/
ostreamL coutL;

#endif //SNAKE_LEVIOSTREAM_H
