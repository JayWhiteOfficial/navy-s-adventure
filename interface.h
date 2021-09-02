#pragma once
#include<stdio.h>
#include<iostream>
#include<sstream>
#include"painting.h"
#include<string>
#include <fstream>
#include<vector>
#include<conio.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cassert>
#include"map.h"
#include<math.h>
#include"painting.h"
#include<windows.h>
#include"hero.h"
#include"weapon.h"
#include<list>
#include"Havy.h"
#define ROW 30
#define COL 60
#define ESC 0x1b
#pragma comment (lib,"Winmm.lib")
const int sleeptime = 70;
using namespace std;
int BulletNum;
int NumOfNPC = 0;
char current_direction = 0;
class Interface
{
public:
	void LoadInterface(string);
	void LoadShop(string);
	void ShowInterface();
	void ShowShop();
	void GotoShop();
	bool StartGame();
	void Exit();
	void ShowMyWord();
	bool GetOrder(char);
	void Setting();
	Interface()
	{
		x = 10;
		y = 5;
		//PutSentence(x, y, "->", BLUE_BLACK);
	}
protected:
	char name[20];
	int money;
	int current_level;
	char mainface[31][61];
	char shop[31][61];
	int x;
	int y;
};
void Interface::Exit()
{
    exit(0);
}
void Interface::ShowMyWord()
{
    system("cls");
    gotoxy(1, 1);
    cout << " 你好，欢迎体验本游戏。我是本游戏的作者ZCH，说起写这个游戏的灵感，其实还是想仿照一下LOL，创建一些角色和"
         <<"技能做成MOBA类的游戏。但是写着写着就更像一个二维的CF。本来想用PYTHON来实现我的设想，但是在实现的过程中存在一些小问题。毕竟本人的专业不是计算机编程，PYTHON"
         <<"是本人自学的编程语言，用起来不那么灵活。所以我选择了学习将近半年的C++来实现这一游戏。这样在写代码的过程中不用担心调试的问题"
         <<"可以把更多的精力放在游戏设计上。\n";
    cout <<"  你可能会问：为什么我不用图形库来做游戏呢？而是要用C++传统字符窗口来做游戏呢？因为我比(fei)较(chang)怀(lan)旧(duo)。"
        <<"用字符窗口（也就是控制台）写起来会比较方便。从打第一行代码到可以运行游戏用了三天都不到的时间。后面十几天都在修复BUG"
        <<"没有图形，全是字符的游戏做起来其实也不比有图形的游戏容易，挺考验我这个制作者想象力的。但是我觉得你应该能看的懂。"
        <<"但是限制也挺多的，有时候想加点东西但是找不到合适的符号来表示它，它只支持键盘上的字符。"
        <<"比如我一直想加一把散弹枪，可是真找不到长得像散弹枪的字符。所以就暂且叫他v1.0版本吧！等v1.1版本会用图形库的。\n"
        <<"接下来说一说游戏，没开始写之前，脑袋：我这里已经蹦出几十条剧情线了。写的时候，手：我一条也实现不了啊。"
        <<"虽然写不出来，但是一个游戏"
        << "  可能你觉得我这个游戏比4399小游戏还Low，还没有用图形库，是不是也就几十行啊？但事实上本程序将近2000行。"
        <<"其中1000行的代码都在构建环境。我把能封装的游戏属性都封装成了类，显示类、地图类、界面类、人物类、枪类、子弹类"
        <<"这样虽然整体看上去比较臃肿，但是更新起来非常方便。比如说我想再填一把新武器，直接从枪类继承就可以了，分分钟的事。"
        <<"<<<<<按P键退出>>>>>>";
    char key = _getch();
    ShowInterface();
    return;
}
void Interface::Setting()
{

}
bool Interface::GetOrder(char key)
{
    PutSentence(2 * (y - 1), x - 1, "    ", BLUE_BLACK);
	if (key == 'w')
	{
		x -= 1;
        if (x < 11)
            x = 15;
		PutSentence(2 * (y - 1), x - 1, "->", BLUE_BLACK);
	}
	if (key == 's')
	{
		x += 1;
        if (x > 15)
            x = 11;
		PutSentence(2 * (y - 1), x - 1, "->", BLUE_BLACK);
	}
	if (key == ' ')
	{
		if (x == 11)
			StartGame();
		else if (x == 12)
			ShowMyWord();
        else if (x == 13)
        {
            ShowShop();
            GotoShop();
        }
		else if (x == 14)
			Setting();
		else if (x == 15)
			return false;
	}
	return true;
}
void Interface::LoadInterface(string filename)
{
	ifstream is;
	is.open(filename);
	for (int i = 1; i <= ROW; i++) {
		for (int j = 1; j <= COL; j++) {
			is >> mainface[i][j];
		}
	}
}
void Interface::LoadShop(string filename)
{
	ifstream is;
	is.open(filename);
	for (int i = 1; i <= ROW; i++) {
		for (int j = 1; j <= COL; j++) {
			is >> shop[i][j];
		}
	}
}
void Interface::GotoShop()
{
	
	while (_getch())
	{

	}
}
void Interface::ShowInterface()
{
	for (int i = 1;i <= ROW;i++)
	{
		for (int j = 1;j <= COL;j++)
		{
			if (mainface[i][j] == '0')
				continue;
			putchar2raw((j - 1) * 2, i - 1, mainface[i][j] == '1' ? ' ' : mainface[i][j], GRAY_BLACK);
		}
	}
	PutSentence(10, 10, "继续游戏", RED_BLACK);
	PutSentence(10, 11, "编者的话", RED_BLACK);
	PutSentence(10, 12, "武器商店", RED_BLACK);
	PutSentence(10, 13, "游戏设置", RED_BLACK);
	PutSentence(10, 14, "退出游戏", RED_BLACK);
}
void Interface::ShowShop()
{
	for (int i = 1;i <= ROW;i++)
	{
		for (int j = 1;j <= COL;j++)
		{
			if (shop[i][j] == '0')
				continue;
			putchar2raw((j - 1) * 2, i - 1, shop[i][j] == '1' ? ' ' : shop[i][j], GRAY_BLACK);
		}
	}
}
bool Interface::StartGame()
{
    system("cls");
    srand(time(0));
    map main_map;
    Havy Q;
    Pistol pistol;
    LazerGun lazergun;
    gun* weapon[2];
    weapon[0] = &pistol;
    weapon[1] = &lazergun;
    pistol_bullet Bullet;
    Lazer lazer;
    std::list<bullet*> Bullets;
    std::list<NPC*> Monsters;
    NPC* npc1 = new NPC(2, 2, 'a');
    NPC* npc2 = new NPC(2, 2, 'w');
    Monsters.push_back(npc1);
    Monsters.push_back(npc2);
    main_map.GetMap("map2.txt");
    main_map.PaintMap();
    Q.Init();
    Q.Paint(main_map);
    bool Pause = false;
    mciSendString(L"open background_music.mp3 alias back", NULL, 0, NULL);
    mciSendString(L"open lazer.mp3 alias lazer", NULL, 0, NULL);
    mciSendString(L"open pistol_bullet.mp3 alias pistol_bullet", NULL, 0, NULL);
    mciSendString(L"open change_weapon.mp3 alias change_weapon", NULL, 0, NULL);
    mciSendString(L"open killed.mp3 alias killed", NULL, 0, NULL);
    mciSendString(L"play back repeat", NULL, 0, NULL);
    while (1)
    {
        char key = 0;
        key = _getch();
        do
        {
            if (key == 'a' || key == 'w' || key == 's' || key == 'd')
            {
                current_direction = key;
                Q.MoveControlled(key, main_map);
            }
            if (key == 'j' || lazer.Isflying())
            {
                if (key == 'j' && weapon[Q.GetWeapon()]->GetBulletNum() > 0)
                {
                    weapon[Q.GetWeapon()]->Fire();
                    if (Q.GetWeapon() == 1)
                    {
                        Lazer* lazer = new Lazer();
                        mciSendString(L"play lazer FROM 0 to 1000", NULL, 0, NULL);
                        lazer->Init(weapon[Q.GetWeapon()]);
                        lazer->ChangeFlying(true);
                        lazer->SetDirection(current_direction);
                        Bullets.push_back(lazer);
                    }
                    else
                    {
                        pistol_bullet* pisbul = new pistol_bullet();
                        mciSendString(L"play pistol_bullet FROM 0 to 1000", NULL, 0, NULL);
                        pisbul->Init(weapon[Q.GetWeapon()]);
                        pisbul->ChangeFlying(true);
                        pisbul->SetDirection(current_direction);
                        Bullets.push_back(pisbul);
                    }

                }
            }
            if (key == 'k')
            {
                mciSendString(L"seek change_weapon to start", NULL, 0, NULL);
                mciSendString(L"play change_weapon", NULL, 0, NULL);
                Q.ChangeWeapon();
            }
            if (key == ' ')
            {
                Q.Flash(main_map);
            }
            list<bullet*>::iterator it;
            list<NPC*>::iterator itr;
            NumOfNPC = 0;
            for (itr = Monsters.begin();itr != Monsters.end();)
            {
                (*itr)->MoveNotControlled(main_map);
                for (it = Bullets.begin();it != Bullets.end();it++)
                {
                    if (((*it))->IfKill((*itr)))
                    {
                        (*itr)->live = false;
                        (*itr)->dead(main_map);
                        int randx;int randy;
                        while (1)
                        {
                            randx = rand() % 30 + 1;
                            randy = rand() % 60 + 1;
                            if (main_map.GetMap(randx, randy) != '#' && (randx - Q.GetX()) * (randx - Q.GetY()) > 4)
                                break;
                        }
                        NPC* npc = new NPC(randx, randy, rand() % 2 == 1 ? 'w' : 'a');
                        Monsters.push_back(npc);
                    }
                }
                if ((*itr)->live == false)
                {
                    delete* itr;
                    mciSendString(L"seek killed to start", NULL, 0, NULL);
                    mciSendString(L"play killed", NULL, 0, NULL);
                    itr = Monsters.erase(itr);
                }
                else
                    itr++;
                NumOfNPC++;
            }
            for (it = Bullets.begin();it != Bullets.end();)
            {
                (*it)->MoveNotControlled(main_map);
                if ((*it)->IfCrash(main_map))
                {
                    delete* it;
                    it = Bullets.erase(it);
                }
                else
                {
                    it++;
                }
            }
            weapon[Q.GetWeapon()]->print(Q, main_map);
            Q.PaintMessage(weapon[Q.GetWeapon()]->GetBulletNum(), NumOfNPC);
            key = 0;
            Sleep(sleeptime);
        } while (!_kbhit());


        if (Pause)//死亡即退出主循环
            break;
    }
    system("pause");
    mciSendString(L"close pistol_bullet", NULL, 0, NULL);
    mciSendString(L"close lazer", NULL, 0, NULL);
    return true;
}
