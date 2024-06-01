#include<iostream>
#include<vector>
#include<cstring>
#include"Game.h"
#include"map.h"
#include"Equipment.h"
#include"Player.h"
#include"fight_part.h"
using namespace std;

ouc_map Ouc_map[19];

vector<Equipment*> equipment_bag;

Player player;
npc testene;

int main() {

    MUDGame thisgame;
    //游戏主函数
    thisgame.RunGame();



    cout << '#';
    system("pause");
    return 0;
}
