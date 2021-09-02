#pragma once
/*MAP库
TODO LIST
1. 设计主地图
2.设计作战地图
3.显示地图*/
#include<stdio.h>
#include<iostream>
#include<sstream>
#include"painting.h"
#include<string>
#include <fstream>
#include<vector>
using namespace std;
class map
{
private:
    int row;
    int col;
    char mp[40][70];
//    char mp2[40][70];
public:
    map();
    void SetWall();
    int GetRow();
    int GetColumn();
    char GetMap(int x, int y);
    void ChangeMap(int x, int y, char ch);
    void PaintMap();
    void GetMap(string);
};
void map::SetWall()
{
    for (int i = 1;i <= row;i++)
    {
        for (int j = 1;j <= col;j++)
        {
            if (i == 1 || i == row || j == 1 || j == col)
                mp[i][j] = '#';
            else
                mp[i][j] = ' ';
        }
    }
}

void map::PaintMap()
{
    for (int i = 1;i <= row;i++)
    {
        for (int j = 1;j <= col;j++)
        {
            if (mp[i][j] == '0')
                continue;
            putchar2raw((j - 1) * 2, i - 1, mp[i][j] == '1' ? ' ' : mp[i][j], GRAY_BLACK);
        }
    }

}
int map::GetRow()
{
    return row;
}
int map::GetColumn()
{
    return col;
}
char map::GetMap(int x, int y)
{
    return mp[x][y];
}
void map::ChangeMap(int x, int y, char ch)
{
    mp[x][y] = ch;
}
map::map()
{
    row = 30;
    col = 60;
    memset(mp, 0, sizeof * (mp[0]));
}
void map::GetMap(string filename)
{
    ifstream is;
    is.open(filename);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            is >> mp[i][j];
        }
    }

    
}