/*************************************************************************
MYPYGAME ��������� 2020��6��14��23:54:11
1.��Ͷ��
2.����������
3.������Կ�ʼ
4.����DEV���ܷ�����
**************************************************************************/

#include"interface.h"
int main()
{
    Interface mainface;
    mainface.LoadInterface("mainface.txt");
    mainface.LoadShop("shop.txt");
    mainface.ShowInterface();
    while (1)
    {
        mainface.StartGame();
    }
}