/*************************************************************************
MYPYGAME 最近更新于 2020年6月14日23:54:11
1.空投包
2.主可以上线
3.剧情可以开始
4.测试DEV上能否运行
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