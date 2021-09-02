#pragma once
//#include"weapon.h"
#include"map.h"
#include"string"
#define MAX_WEAPON  2
using namespace std;
class LazerGun;
class Spirit
{
public:
    void Init(int x1 = 10, int y1 = 10, int MoveSpeed = 70, int Movedirection = 4)
    {
        this->MoveSpeed = MoveSpeed;
        this->MoveDirection = Movedirection;
        x = x1;
        y = y1;
    }
    void SleepTime();//两帧之间停顿一下
    void ChangeSpeed(int speed);
    bool IfFood(int x, int y);//是否吃到了食物？
    bool MoveControlled(char, map);//键盘响应下的下一步移动方向
    virtual bool IfCrash(map Map) = 0;//是否撞了？
    virtual bool MoveNotControlled(map) = 0;//无键盘响应下的下一步位置
    virtual void Paint(map) = 0;//画出
    friend class weapon;
    friend class Pistol;
    friend class LazerGun;

protected:
    int MoveSpeed;  //运动速度
    int MoveDirection;  //运动方向
    int x;              //位置
    int y;
    int RL; //0左右，1上下
};
void Spirit::SleepTime()
{
    Sleep(MoveSpeed);
}
void Spirit::ChangeSpeed(int speed)
{
    MoveSpeed = speed;
}
/*bool Spirit::IfCrash(map Map)		//x代表行，y代表列
{
    return Map.GetMap(x, y) == '*' || Map.GetMap(x, y) == '#';
}
*/
bool Spirit::MoveControlled(char Direction, map Map)
{
    //该函数旨在通过键盘所输入的方向来更新spirit的方向
    if (Direction == 'a')
    {
        MoveDirection = 3;
        return MoveNotControlled(Map);
    }
    else if (Direction == 'd')
    {
        MoveDirection = 4;
        return MoveNotControlled(Map);
    }
    else if (Direction == 'w')
    {
        MoveDirection = 1;
        return MoveNotControlled(Map);
    }
    else if (Direction == 's')
    {
        MoveDirection = 2;
        return MoveNotControlled(Map);
    }
    else
        return false;
}

class pistol_bullet;
class bullet;
class NPC :public Spirit
{
public:
    friend class LazerGun;
    friend class ShotGun;
    friend class Scattershot;
    friend class Lazer;
    friend class pistol_bullet;
    NPC(int x0, int y0, char direction, char Style = '%')
    {
        Direction = direction;
        if (direction == 'a' || direction == 'd')
            RL = 0;
        else
            RL = 1;
        style = Style;
        x = x0;
        y = y0;
        live = true;
    }
    bool MoveNotControlled(map Map);
    void Paint(map);
    bool IfCrash(map Map);
    void SetDirection(char Direction) { this->Direction = Direction; }
    void dead(map Map);
    bool live;
private:
    char Direction;
    char style;
};
class Havy :public Spirit
{
public:
    friend class Pistol;
    friend class pistol_bullet;
    friend class LazerGun;
    friend class Lazer;
    friend class ShotGun;
    friend class Scattershot;
    Havy(string name = "Havy", int money = 0) { Name = name;Money = money; Current_weapon = 0; }
    void PaintMessage(int BulletNum, int NumOfNPC)
    {
        PutSentence((25 - 1) * 2, 2 - 1, Name, WHITE_BLACK);
        PutSentence((25 - 1) * 2, 3 - 1, "NPC:          ", WHITE_BLACK);
        PutSentence((28 - 1) * 2, 3 - 1, NumOfNPC, RED_BLACK);
        PutSentence((25 - 1) * 2, 4 - 1, "子弹:            ", WHITE_BLACK);
        PutSentence((28 - 1) * 2, 4 - 1, BulletNum, RED_BLACK);
        PutSentence((25 - 1) * 2, 5 - 1, "武器:             ", WHITE_BLACK);
        switch (Current_weapon)
        {
        case 0:
            PutSentence((28 - 1) * 2, 5 - 1, "手枪", RED_BLACK);
            break;
        case 1:
            PutSentence((28 - 1) * 2, 5 - 1, "激光枪", RED_BLACK);
        }
    }
    int GetX() { return x; }
    int GetY() { return y; }
    int GetWeapon() { return Current_weapon; }
    void Paint(map);
    bool IfCrash(map Map);
    bool MoveNotControlled(map Map);
    bool Flash(map Map);
    void ChangeWeapon() { Current_weapon = (Current_weapon + 1) % MAX_WEAPON; }
private:
    string Name;
    int Money;
    int Current_weapon;
};

/*—————————————————成员实现———————————————————————*/
void NPC::Paint(map Map)
{
    if (Map.GetMap(x, y) != '#')
        putchar2raw((y - 1) * 2, x - 1, this->style, BLUE_BLACK);
}
bool NPC::IfCrash(map Map)		//x代表行，y代表列
{
    return Map.GetMap(x, y) == '*' || Map.GetMap(x, y) == '#' || x < 1 || x>29 || y < 1 || y>59;
}
bool NPC::MoveNotControlled(map Map)
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
    int x1 = x;
    int y1 = y;
    //通过蛇头方向判断蛇的下一步位置
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
        SetDirection(Direction == 'a' ? 'd' : (Direction == 'w' ? 's' : (Direction == 'd' ? 'a' : 'w')));
        //     return false;
    }
    Paint(Map);
    if (Map.GetMap(x1, y1) != '#')
        putchar2raw((y1 - 1) * 2, x1 - 1, ' ', 14);
}
void Havy::Paint(map Map)
{
    if (Map.GetMap(x, y) != '#')
        putchar2raw((y - 1) * 2, x - 1, '*', 14);
}
bool Havy::Flash(map Map)
{
    int x1 = x;
    int y1 = y;
    if (MoveDirection == 1)
    {
        x = x - 2;
        y = y;
    }
    else if (MoveDirection == 2)
    {
        x = x + 2;
        y = y;
    }
    else if (MoveDirection == 3)
    {
        x = x;
        y = y - 2;
    }
    else if (MoveDirection == 4)
    {
        x = x;
        y = y + 2;
    }
    if (IfCrash(Map))	//撞到自己或者撞墙直接Gameover
    {
        x = x1;
        y = y1;
        return false;
    }
    Paint(Map);
    if (Map.GetMap(x, y) != '#')
        putchar2raw((y1 - 1) * 2, x1 - 1, ' ', 14);
}
bool Havy::IfCrash(map Map)		//x代表行，y代表列
{
    return Map.GetMap(x, y) == '*' || Map.GetMap(x, y) == '#' || x < 1 || x>29 || y < 1 || y>59;
}
bool Havy::MoveNotControlled(map Map)
{
    if (MoveDirection == 0)
        return true;
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
        x = x1;
        y = y1;
        return false;
    }
    Paint(Map);
    if (Map.GetMap(x, y) != '#')
        putchar2raw((y1 - 1) * 2, x1 - 1, ' ', 14);
}