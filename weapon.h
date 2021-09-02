#pragma once
#include"hero.h"
#include<cstring>
#include<string>
#include<stdio.h>
#include<iostream>
using namespace std;
class gun
{
public:
    friend class pistol_bullet;
    friend class Lazer;
    virtual void print(Havy npc, map Map) = 0;
    void clear(map Map)
    {
        if (Map.GetMap(x, y) != '#')
            putchar2raw((y - 1) * 2, x - 1, ' ', 14);
    }
    int GetBulletNum() { return BulletNum; }
    void SetBulletNum(int x) { BulletNum = x; }
    void Fire() { BulletNum--; }
protected:
    char current;
    int price;
    int BulletNum;
    int x;
    int y;
};
class Pistol: public gun
{
public:
    friend class pistol_bullet;
    void print(Havy npc, map Map);
    Pistol()
    {
        x = 0;y = 0; BulletNum = 50;
    }
protected:
    char style[4] = { 'A','V','<','>' };
    char name[20];
    int attack;
};
class LazerGun :public gun
{
public:
    friend class Lazer;
    void print(Havy, map);
    LazerGun()
    {
        x = 0; y = 0; BulletNum = 10000;
    }
protected:
    char style[2] = { '|','-' };
    char name[20];
    int attack;
};
class ShotGun :public gun
{
public:
    friend class Scattershot;
    void print(Havy, map);
    ShotGun()
    {
        x = 0; y = 0; BulletNum = 10;
    }
protected:
    char style[4] = { 'W','M','=','=' };
    char name[20];
    int attack;
};
class bullet :public Spirit
{
public:
    friend class NPC;
    using Spirit::Init;
    virtual void Init(gun*) = 0;
    virtual bool IfCrash(map Map) = 0;
    virtual bool IfKill(NPC* npc) = 0;
    bool Isflying() { return this->flying; }
    void ChangeFlying(bool Bool) { flying = Bool; }
    //void Paint(map Map);
    void SetDirection(char Direction) 
    { 
        this->Direction = Direction; 
        if (Direction == 'a' || Direction == 'd')
            RL = 0;
        else
            RL = 1;
    }
    char GetDirection() { return this->Direction; }
protected:
    char style;
    bool flying;
    char Direction;
};
class pistol_bullet :public bullet
{
public:
    friend class NPC;
    pistol_bullet() { flying = false; }
    void Init(gun*);
    bool MoveNotControlled(map Map);
    void Paint(map Map);
    bool IfCrash(map Map);
    bool IfKill(NPC*);
protected:
};

class Lazer :public pistol_bullet
{
public:
    Lazer() { flying = false; }
    bool MoveNotControlled(map Map);
    void Init(gun*);
    void Paint(map Map);
    bool IfCrash(map) { return (x < 2 || y < 2 || x >29 || y > 59); }
    bool IfKill(NPC*);
};

class Scattershot :public pistol_bullet
{
public:
    Scattershot() { flying = false; }
    bool MoveNotControlled(map Map);
    void Init(gun*);
    void Paint(map Map);
    bool IfCrash(map) { return (x < 2 || y < 2 || x >29 || y > 59); }
};


/*—————————————————成员实现———————————————————*/
void pistol_bullet::Init(gun* weapon)
{
    this->x = weapon->x;
    this->y = weapon->y;
    style = weapon->current;
    flying = false;
    if (Direction == 'a' || Direction == 'd')
        RL = 0;
    else
        RL = 1;
}
void pistol_bullet::Paint(map Map)
{
    if (Map.GetMap(x, y) != '#')
        putchar2raw((y - 1) * 2, x - 1, this->style, RED_BLACK);
}
bool pistol_bullet::IfCrash(map Map)		//x代表行，y代表列
{
    return Map.GetMap(x, y) == '*' || Map.GetMap(x, y) == '#' || x < 1 || x>29 || y < 1 || y>59;
}
bool pistol_bullet::IfKill(NPC* npc)
{
    if (npc->x == x && Direction == 'd' && npc->y > y -1 ||
        npc->x == x && Direction == 'a' && npc->y < y + 1||
        npc->y == y && Direction == 'w' && npc->x < x + 1||
        npc->y == y && Direction == 's' && npc->x > x - 1)
    {
            putchar2raw((y - 1) * 2, x - 1, ' ', RED_BLACK);
        x = npc->x;
        y = npc->y;
        return true;
    }
    return false;
}
bool pistol_bullet::MoveNotControlled(map Map)
{
    if (MoveDirection == 0)
        return true;
    if (Direction == 'a')
    {
        MoveDirection = 3;
    }
    else if (Direction == 'd')
    {
        MoveDirection = 4;
    }
    else if (Direction == 'w')
    {
        MoveDirection = 1;
    }
    else if (Direction == 's')
    {
        MoveDirection = 2;
    }
    else
        return false;
    //通过蛇头方向判断蛇的下一步位置
    int x1 = x;
    int y1 = y;
    if (MoveDirection == 1)
    {
        x = x - 3;
        y = y;
    }
    else if (MoveDirection == 2)
    {
        x = x + 3;
        y = y;
    }
    else if (MoveDirection == 3)
    {
        x = x;
        y = y - 3;
    }
    else if (MoveDirection == 4)
    {
        x = x;
        y = y + 3;
    }
    if (IfCrash(Map))	//撞到自己或者撞墙直接Gameover
    {
        if (Map.GetMap(x1, y1) != '#')
            putchar2raw((y1 - 1) * 2, x1 - 1, ' ', 14);
        flying = false;
        return false;
    }
    Paint(Map);
    if (Map.GetMap(x1, y1) != '#')
        putchar2raw((y1 - 1) * 2, x1 - 1, ' ', 14);
}
void Pistol::print(Havy npc, map Map)
{
    //int x1 = x, y1 = y;
    // clear();
    if (x != npc.x || y != npc.y)
        clear(Map);
    if (npc.MoveDirection == 1)
    {
        x = npc.x - 1;
        y = npc.y;
    }
    else if (npc.MoveDirection == 2)
    {
        x = npc.x + 1;
        y = npc.y;
    }
    else if (npc.MoveDirection == 3)
    {
        x = npc.x;
        y = npc.y - 1;
    }
    else if (npc.MoveDirection == 4)
    {
        x = npc.x;
        y = npc.y + 1;
    }
    current = style[npc.MoveDirection - 1];
    if (Map.GetMap(x, y) != '#')
        putchar2raw((y - 1) * 2, x - 1, current, 14);
}
void LazerGun::print(Havy npc,map Map)
{
    //int x1 = x, y1 = y;
    // clear();
    if (x != npc.x || y != npc.y)
        clear(Map);
    if (npc.MoveDirection == 1)
    {
        x = npc.x - 1;
        y = npc.y;
    }
    else if (npc.MoveDirection == 2)
    {
        x = npc.x + 1;
        y = npc.y;
    }
    else if (npc.MoveDirection == 3)
    {
        x = npc.x;
        y = npc.y - 1;
    }
    else if (npc.MoveDirection == 4)
    {
        x = npc.x;
        y = npc.y + 1;
    }
    current = style[npc.MoveDirection > 2 ? 1 : 0];
    if (Map.GetMap(x, y) != '#')
        putchar2raw((y - 1) * 2, x - 1, current, CYAN_BLACK);
}
void ShotGun::print(Havy npc, map Map)
{
    //int x1 = x, y1 = y;
    // clear();
    if (x != npc.x || y != npc.y)
        clear(Map);
    if (npc.MoveDirection == 1)
    {
        x = npc.x - 1;
        y = npc.y;
    }
    else if (npc.MoveDirection == 2)
    {
        x = npc.x + 1;
        y = npc.y;
    }
    else if (npc.MoveDirection == 3)
    {
        x = npc.x;
        y = npc.y - 1;
    }
    else if (npc.MoveDirection == 4)
    {
        x = npc.x;
        y = npc.y + 1;
    }
    current = style[npc.MoveDirection - 1];
    if (Map.GetMap(x, y) != '#')
        putchar2raw((y - 1) * 2, x - 1, current, 14);
}
void Lazer::Init(gun* weapon)
{
    this->x = weapon->x;
    this->y = weapon->y;
    style = weapon->current;
    flying = false;
}
void Lazer::Paint(map Map)
{
    if (Map.GetMap(x, y) != '#')
        putchar2raw((y - 1) * 2, x - 1, this->style, CYAN_BLACK);
}
bool Lazer::IfKill(NPC* npc)
{
    if (npc->x == x && npc->RL + RL == 0 && (npc->y - y) * (npc->y - y) < 30 ||
        npc->y == y && npc->RL + RL == 2 && (npc->x - x) * (npc->x - x) < 30 ||
        npc->x == x && npc->y == y)
    {
        return true;
    }
    return false;
}
bool Lazer::MoveNotControlled(map Map)
{
    if (MoveDirection == 0)
        return true;
    if (Direction == 'a')
    {
        MoveDirection = 3;
    }
    else if (Direction == 'd')
    {
        MoveDirection = 4;
    }
    else if (Direction == 'w')
    {
        MoveDirection = 1;
    }
    else if (Direction == 's')
    {
        MoveDirection = 2;
    }
    else
        return false;
    //通过蛇头方向判断蛇的下一步位置
    int x1 = x;
    int y1 = y;
    if (MoveDirection == 1)
    {
        x = x - 3;
        y = y;
    }
    else if (MoveDirection == 2)
    {
        x = x + 3;
        y = y;
    }
    else if (MoveDirection == 3)
    {
        x = x;
        y = y - 3;
    }
    else if (MoveDirection == 4)
    {
        x = x;
        y = y + 3;
    }
    if (IfCrash(Map))
    {
        if (Map.GetMap(x1, y1) != '#')
            putchar2raw((y1 - 1) * 2, x1 - 1, ' ', 14);
        flying = false;
        return false;
    }
    Paint(Map);
    if (Map.GetMap(x1, y1) != '#')
        putchar2raw((y1 - 1) * 2, x1 - 1, ' ', CYAN_BLACK);
}
/*void Scattershot::Init(gun* weapon)
{
    this->x = weapon->x;
    this->y = weapon->y;
    style = weapon->current;
    flying = false;
    if (Direction == 'a' || Direction == 'd')
        RL = 0;
    else
        RL = 1;
}*/
void Scattershot::Paint(map Map)
{
    if (Map.GetMap(x, y) != '#')
        putchar2raw((y - 1) * 2, x - 1, this->style, RED_BLACK);
}
bool Scattershot::MoveNotControlled(map Map)
{
    if (MoveDirection == 0)
        return true;
    if (Direction == 'a')
    {
        MoveDirection = 3;
    }
    else if (Direction == 'd')
    {
        MoveDirection = 4;
    }
    else if (Direction == 'w')
    {
        MoveDirection = 1;
    }
    else if (Direction == 's')
    {
        MoveDirection = 2;
    }
    else
        return false;
    //通过蛇头方向判断蛇的下一步位置
    int x1 = x;
    int y1 = y;
    if (MoveDirection == 1)
    {
        x = x - 1;
        y = y;
    }
    else if (MoveDirection == 2)
    {
        x = x + 1;
        y = y;
    }
    else if (MoveDirection == 3)
    {
        x = x;
        y = y - 1;
    }
    else if (MoveDirection == 4)
    {
        x = x;
        y = y + 1;
    }
    if (IfCrash(Map))	//撞到自己或者撞墙直接Gameover
    {
        flying = false;
        return false;
    }
    Paint(Map);
    if (Map.GetMap(x1, y1) != '#')
        putchar2raw((y1 - 1) * 2, x1 - 1, ' ', 14);
}
void NPC::dead(map Map)
{
    if(Map.GetMap(x, y) != '#')
        putchar2raw((y - 1) * 2, x - 1, 'X', 12);
}
