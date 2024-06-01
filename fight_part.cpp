#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<random>
#include<cstdlib>
#include<ctime>
#include<cstring>
using namespace std;


#include"fight_part.h"

npc::npc() {//构造
    _isBoss = false;
    strcpy(Name, "nobody");
    strcpy(Description, "a normal student");
}


void npc::Debug_show() {//debug用
    cout << "<!#!>" << GiveProg << GiveMat << GiveLog << GivePrac << GiveLearnPinit;
}
bool npc::IsBoss() {
    return _isBoss;
}

int npc::Useskill(vector<Skill>& skills) {//npc 使用技能

    int choice;

    srand(time(0));
    
    choice = (rand() % skills.size());

    cout << choice << '#' << endl;

    cout << skills[choice].name << endl;
    cout << skills[choice].description << endl;


    cout << "选择你的回答" << endl;
    cout << skills[choice].choices << endl;
    return choice;
   


}

bool npc::Check(int skill_index, int choice, vector<Skill>& skills) {//技能检查是否对应
    if (skills[skill_index].answer == choice) return true;
    else return false;
}

bool npc::CheckEquip(int skill, int item_class, vector<Skill>& BossSkills) {
    if (BossSkills[skill].answer == item_class)return true;
    else return false;

}

void npc::be_attack(bool right_item) {//受攻击
    if (right_item) {
        hardlvl -= 50;
    }
    else {
        hardlvl -= 1;
    }

    return;


}

int npc::Getter_hardlvl() {//返回数值
    return hardlvl;
}
void npc::GivePoint(Player& player) {
    
    player.GetReward(GiveProg, GiveMat, GiveLog, GivePrac, GiveLearnPinit);
    

}
int npc::UseBossSkill() {

    return 0;
}




