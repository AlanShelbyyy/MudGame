#ifndef FIGHT_H
#define FIGHT_H
#include"Player.h"
#include<vector>

typedef struct Tskill {
    char name[16];
    char description[1024];
    int  hardlvl;
    char choices[32];
    int  answer;

}Skill;

class npc {
public:
    npc();
    int Useskill(vector<Skill>& skills);//使用技能
    int UseBossSkill();
    bool Check(int skill, int choice, vector<Skill>& skills);//检查技能输入
    bool CheckEquip(int skill, int item_class, vector<Skill>& BossSkills);
    int Getter_hardlvl();
    void be_attack(bool right_item);
    void GivePoint(Player& player);//给予玩家属性加成
    void Debug_show();
    bool IsBoss();
    
    int hardlvl;//npc 的姓名介绍等，以及一些数值
    char Name[16];
    char Description[1024];
    int GiveMat;
    int GiveLog;
    int GiveProg;
    int GivePrac;
    int GiveLearnPinit;
private:
    bool _isBoss;
    bool _inround;



};



void FightRound(Player thisPlayer, npc thisNpc);

#endif 