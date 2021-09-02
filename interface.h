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
    cout << "  ��GZTͬѧ:\n  ��ã���ӭ���鱾��Ϸ�����Ǳ���Ϸ������ZCH��˵��д�����Ϸ����У���ʵ���������һ��LOL������һЩ��ɫ��"
         <<"��������MOBA�����Ϸ������д��д�ž͸���һ����ά��CF����������PYTHON��ʵ���ҵ����룬������ʵ�ֵĹ����д���һЩС���⡣�Ͼ����˵�רҵ���Ǽ������̣�PYTHON"
         <<"�Ǳ�����ѧ�ı�����ԣ�����������ô��������ѡ����ѧϰ���������C++��ʵ����һ��Ϸ��������д����Ĺ����в��õ��ĵ��Ե�����"
         <<"���԰Ѹ���ľ���������Ϸ����ϡ�\n";
    cout <<"  ����ܻ��ʣ�Ϊʲô�Ҳ���ͼ�ο�������Ϸ�أ�����Ҫ��C++��ͳ�ַ�����������Ϸ�أ���Ϊ�ұ�(fei)��(chang)��(lan)��(duo)��"
        <<"���ַ����ڣ�Ҳ���ǿ���̨��д������ȽϷ��㡣�Ӵ��һ�д��뵽����������Ϸ�������춼������ʱ�䡣����ʮ���춼���޸�BUG"
        <<"û��ͼ�Σ�ȫ���ַ�����Ϸ��������ʵҲ������ͼ�ε���Ϸ���ף�ͦ����������������������ġ������Ҿ�����Ӧ���ܿ��Ķ���"
        <<"��������Ҳͦ��ģ���ʱ����ӵ㶫�������Ҳ������ʵķ�������ʾ������ֻ֧�ּ����ϵ��ַ���"
        <<"������һֱ���һ��ɢ��ǹ���������Ҳ���������ɢ��ǹ���ַ������Ծ����ҽ���v1.0�汾�ɣ���v1.1�汾����ͼ�ο�ġ�\n"
        <<"������˵һ˵��Ϸ��û��ʼд֮ǰ���Դ����������Ѿ��ĳ���ʮ���������ˡ�д��ʱ���֣���һ��Ҳʵ�ֲ��˰���"
        <<"��Ȼд������������һ����Ϸ"
        << "  ����������������Ϸ��4399С��Ϸ��Low����û����ͼ�ο⣬�ǲ���Ҳ�ͼ�ʮ�а�������ʵ�ϱ����򽫽�2000�С�"
        <<"����1000�еĴ��붼�ڹ����������Ұ��ܷ�װ����Ϸ���Զ���װ�����࣬��ʾ�ࡢ��ͼ�ࡢ�����ࡢ�����ࡢǹ�ࡢ�ӵ���"
        <<"������Ȼ���忴��ȥ�Ƚ�ӷ�ף����Ǹ��������ǳ����㡣����˵��������һ����������ֱ�Ӵ�ǹ��̳оͿ����ˣ��ַ��ӵ��¡�"
        <<"<<<<<��P���˳�>>>>>>";
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
	PutSentence(10, 10, "������Ϸ", RED_BLACK);
	PutSentence(10, 11, "���ߵĻ�", RED_BLACK);
	PutSentence(10, 12, "�����̵�", RED_BLACK);
	PutSentence(10, 13, "��Ϸ����", RED_BLACK);
	PutSentence(10, 14, "�˳���Ϸ", RED_BLACK);
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


        if (Pause)//�������˳���ѭ��
            break;
    }
    system("pause");
    mciSendString(L"close pistol_bullet", NULL, 0, NULL);
    mciSendString(L"close lazer", NULL, 0, NULL);
    return true;
}