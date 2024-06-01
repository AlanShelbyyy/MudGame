#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<iomanip>
#include<windows.h>
#include<cstdlib>
#include<algorithm>
#include"Player.h"
#include<vector>
#include<ctime>
#include"Equipment.h"
#include "map.h"
#include<fstream>
#include"Bag.h"
#include<string>
#include<conio.h>

using namespace std;
extern vector<Equipment*> equipment_bag;
extern ouc_map Ouc_map[19];

int inputch() {
	char str[2];
	str[0] = _getch();
	return atoi(str);
}
int inputch(int min, int max) {
	short n = inputch();
	while (n<min || n>max) {
		n = inputch();
	}
	return n;
}

//输入检查
int GetInput1() {
	char str[2];
	str[0] = _getch();
	return atoi(str);
}
int GetInput1(int min, int max) {
	short n = GetInput1();
	while (n<min || n>max) {
		n = GetInput1();
	}
	return n;
}

void Player::changep_m(int num) {
	p_m = &Ouc_map[num];
};//移动位置
short Player::getMap_id() {
	return p_m->getId();
}
ouc_map* Player::get_map() {
	return p_m;
}

Player you;    //实例化一个 you
Bag mybag;




Player::Player() {//测试用例
	p = (struct Player_Stats*)new struct Player_Stats;
	p_m = &Ouc_map[0];

}

void Player::setting_player() {
	ifstream ifs("data/Player/player.dat", ios::in | ios::binary);
	int n1 = 0;
	cout << "开始读取" << endl;
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	p->DateCount = n1;
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	if (n1 == 1) {
		strcpy(p->Major, "计算机科学与技术");
		flag_major = 1;
	}
	else if (n1 == 2) {
		strcpy(p->Major, "智能科学与技术");
		flag_major = 2;
	}
	else if (n1 == 3) {
		strcpy(p->Major, "网络空间安全");
		flag_major = 3;
	}
	else if (n1 == 4) {
		strcpy(p->Major, "软件工程");
		flag_major = 4;
	}
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	p->Player_AbilityofLearn = n1;
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	p->Player_AbilityofLogic = n1;
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	p->Player_AbilityofMath = n1;
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	p->Player_AbilityofPractice = n1;
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	p->Player_AbilityofProgramming = n1;
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	p->Player_Action_Points = n1;
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	p->Warning = n1;
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	p_m = &Ouc_map[n1 - 1];
	cout << "renwu" << endl;
}

void Player::saver() {
	cout << "开始存档" << endl;
	ofstream ofs("data/Player/player.dat", ios::out | ios::binary);
	if (!ofs)
		cout << "您的存档喝了孟婆汤，请快去开始新的游戏吧！" << endl;
	int n2 = 0;
	n2 = p->DateCount;
	ofs.write(reinterpret_cast<char*>(&n2), sizeof(n2));
	n2 = flag_major;
	ofs.write(reinterpret_cast<char*>(&n2), sizeof(n2));
	n2 = p->Player_AbilityofLearn;
	ofs.write(reinterpret_cast<char*>(&n2), sizeof(n2));
	n2 = p->Player_AbilityofLogic;
	ofs.write(reinterpret_cast<char*>(&n2), sizeof(n2));
	n2 = p->Player_AbilityofMath;
	ofs.write(reinterpret_cast<char*>(&n2), sizeof(n2));
	n2 = p->Player_AbilityofPractice;
	ofs.write(reinterpret_cast<char*>(&n2), sizeof(n2));
	n2 = p->Player_AbilityofProgramming;
	ofs.write(reinterpret_cast<char*>(&n2), sizeof(n2));
	n2 = p->Player_Action_Points;
	ofs.write(reinterpret_cast<char*>(&n2), sizeof(n2));
	n2 = p->Warning;
	ofs.write(reinterpret_cast<char*>(&n2), sizeof(n2));
	n2 = p_m->getId();
	ofs.write(reinterpret_cast<char*>(&n2), sizeof(n2));
	cout << "存档成功" << endl;
	ofs.close();
}


void Player::GetReward(int pro, int mat, int log, int pra, int lnp) {
	p->Player_AbilityofLearn += lnp;
	p->Player_AbilityofLogic += log;
	p->Player_AbilityofMath += mat;
	p->Player_AbilityofPractice += pra;
	p->Player_AbilityofProgramming += pro;
}




void Player::ChooseMajor()
{

	cout << endl;
	cout << "欢迎你来到 OUC 信部 ！"; Sleep(400);
	cout << "想好计算机类分流后的专业去向了么？ 有以下四个分流专业供你挑选 : " << endl;
	cout << "1. 计算机科学与技术" << endl;
	cout << "2. 智能科学与技术" << endl;
	cout << "3. 网络空间安全" << endl;
	cout << "4. 软件工程" << endl;
	cout << endl;
	cout << "请选择一个适合你的分流专业 : " << endl;
	flag_major = inputch(1,4);
	if (flag_major == 1)
	{
		cout << "你已成为 [计算机科学与技术] 专业的学生  " << endl;
		Sleep(300);
		cout << "快去探索校园 不断交流学习 提高自身能力 争取顺利毕业吧 " << endl;
		p->Player_AbilityofLearn = 1;
		p->Player_AbilityofProgramming = 4;
		p->Player_AbilityofMath = 2;
		p->Player_AbilityofLogic = 2;
		p->Player_AbilityofPractice = 2;
		p->Player_Action_Points = 8;
		strcpy(p->Major, "计算机科学与技术");
	}
	else if (flag_major == 2)
	{
		cout << "你已成为 [智能科学与技术] 专业的学生  " << endl;
		Sleep(300);
		cout << "快去探索校园 不断交流学习 提高自身能力 争取顺利毕业吧 " << endl;
		p->Player_AbilityofLearn = 1;
		p->Player_AbilityofProgramming = 2;
		p->Player_AbilityofMath = 2;
		p->Player_AbilityofLogic = 4;
		p->Player_AbilityofPractice = 2;
		p->Player_Action_Points = 8;
		strcpy(p->Major, "智能科学与技术");
	}
	else if (flag_major == 3)
	{
		cout << "你已成为 【网络空间安全] 专业的学生  " << endl;
		Sleep(300);
		cout << "快去探索校园 不断交流学习 提高自身能力 争取顺利毕业吧 " << endl;
		p->Player_AbilityofLearn = 1;
		p->Player_AbilityofProgramming = 2;
		p->Player_AbilityofMath = 2;
		p->Player_AbilityofLogic = 3;
		p->Player_AbilityofPractice = 3;
		p->Player_Action_Points = 8;
		strcpy(p->Major, "网络空间安全");
	}
	else if (flag_major == 4)
	{
		cout << "你已成为 [软件工程] 专业的学生  " << endl;
		Sleep(300);
		cout << "快去探索校园 不断交流学习 提高自身能力 争取顺利毕业吧 " << endl;
		p->Player_AbilityofLearn = 1;
		p->Player_AbilityofProgramming = 4;
		p->Player_AbilityofMath = 2;
		p->Player_AbilityofLogic = 2;
		p->Player_AbilityofPractice = 2;
		p->Player_Action_Points = 8;
		strcpy(p->Major, "软件工程");
	}

}

int Player::Getter_learn() {
	return p->Player_AbilityofLearn;
}

bool Player::canTest_or_not() {
	return p->Player_AbilityofLogic >= 10 && p->Player_AbilityofMath >= 10 && p->Player_AbilityofPractice >= 10 && p->Player_AbilityofProgramming >= 10 && p->Player_Action_Points;
}

void Player::setwarn() {
	p->Warning += 1;
	return;
}

void Player::be_attack(int damage) {
	p->Player_AbilityofLearn -= damage;
}
void Player::Tasks()
{
	cout << "在10个天数单位内，通过与同学 [交流学习] 和 [探索校园] 提升自己的学习力与各方面能力值" << endl;
	cout << "在有自信的把握下，向教师发起 [考试] 请求，累积到6个学分方可顺利毕业" << endl;
}

void Player::State() const //展示玩家当前状态 
{
	cout << endl;
	cout << "你的专业 [" << p->Major << ']' << endl;
	cout << "学习力 : " << p->Player_AbilityofLearn << endl;
	cout << "行动点 : " << p->Player_Action_Points << endl;
	cout << "编程能力值 : " << p->Player_AbilityofProgramming << endl;
	cout << "数学能力值 : " << p->Player_AbilityofMath << endl;
	cout << "逻辑能力值 : " << p->Player_AbilityofLogic << endl;
	cout << "实践能力值 : " << p->Player_AbilityofPractice << endl;
	cout << "在校已学习天数 : " << p->DateCount <<"     "<<"学业警示："<<p->Warning<<  endl;
}

void Player::Equip_equipments(int num_eq)
{
	Equipment player_equ;
	cout << endl;
	cout << " 对于 [" << equipment_bag[num_eq - 1]->get_name() << "] 你打算 :" << endl;
	cout << "1. 使用该物品" << endl;
	cout << "2. 查看该物品属性" << endl;
	cout << "3. 卸下该装备" << endl;
	cout << "4. 丢弃该物品 " << endl;
	int flag_eq;
	cin >> flag_eq;
	if (flag_eq == 1)
	{
		cout << "装备该物品后你的状态 : " << endl;
		p->Player_AbilityofLearn += equipment_bag[num_eq - 1]->get_AbilityofLearn();  //学习力 
		this->p->Player_AbilityofProgramming += equipment_bag[num_eq - 1]->get_AbilityofProgramming();  //编程能力值 
		this->p->Player_AbilityofMath += equipment_bag[num_eq - 1]->get_AbilityofMath(); // 数学能力值 
		this->p->Player_AbilityofLogic += equipment_bag[num_eq - 1]->get_AbilityofLogic();  //逻辑能力值 
		this->p->Player_AbilityofPractice += equipment_bag[num_eq - 1]->get_AbilityofPractice();  //实践能力值 
		this->p->Player_Action_Points += equipment_bag[num_eq - 1]->get_Action_Points();  //行动力
		State();
		int number_player = 0;
		number_player = equipment_bag[num_eq - 1]->get_num();
		if (number_player == 1)
			equipment_bag.erase(equipment_bag.begin() + num_eq - 1);
		else
			equipment_bag[num_eq - 1]->num_reduce();
	}
	else if (flag_eq == 2)
	{
		equipment_bag[num_eq - 1]->show();
	}
	else if (flag_eq == 3)
	{
		if (!equipment_bag[num_eq - 1]->get_on()) //还未使用
		{
			cout << "该物品仍未使用 无法卸下" << endl;
		}
		else
		{
			this->p->Player_AbilityofLearn -= equipment_bag[num_eq - 1]->get_AbilityofLearn();  //学习力 
			this->p->Player_AbilityofProgramming -= equipment_bag[num_eq - 1]->get_AbilityofProgramming();  //编程能力值 
			this->p->Player_AbilityofMath -= equipment_bag[num_eq - 1]->get_AbilityofMath(); // 数学能力值 
			this->p->Player_AbilityofLogic -= equipment_bag[num_eq - 1]->get_AbilityofLogic();  //逻辑能力值 
			this->p->Player_AbilityofPractice -= equipment_bag[num_eq - 1]->get_AbilityofPractice();  //实践能力值 
			equipment_bag[num_eq - 1]->show();
		}
	}
	else if (flag_eq == 4)
	{
		cout << "确认丢弃该物品?" << endl;
		cout << "1. 丢弃" << endl;

		cout << "2. 取消" << endl;
		int flag_qr;
		cin >> flag_qr;
		if (flag_qr == 1)
		{
			int temp = num_eq - 1;
			delete equipment_bag[temp];
			equipment_bag.erase(equipment_bag.begin() + temp);
		}
		else
		{
			//返回
		}
	}

}

void Player::Backpack()
{
	if (equipment_bag.empty()) //空 背包
	{
		cout << "你的背包空空如也 " << endl;
	}
	else
	{
		int siz = equipment_bag.size();
		cout << "你背包内的物品有 : " << endl;
		for (int i = 0; i < siz; i++)
		{
			cout << i + 1 << '.' << equipment_bag[i]->get_name()<<" "<<equipment_bag[i]->get_num()<<"个" << endl;
		}
		while (true) {
			cout << "请输入指令对装备进行操作: " << endl;
			int chose = 0;//选择装备的使用
			cin >> chose;
			if (chose >= 1 && chose <= siz) {
				Equip_equipments(chose);
				break;
			}
			else
				cout << "指令错误！" << endl;
		}
	}
}

void Player::Eat_orSleep() const
{
	int flag_es;
	cout << endl;
	cout << "1. 在食堂用餐" << endl;
	cout << "2. 在寝室睡觉" << endl;
	cin >> flag_es;
	if (flag_es == 1)
	{
		int flag_eat = 1; //一天仅仅可以用餐一次  转天flag_eat标注为 1 可用餐  
		srand(time(NULL));
		int temp1_Player_Action_Points = rand() % 4 + 2; //吃一次饭随机加 2~5行动点  
		if (p_m->getId() != 2) //不在食堂
		{
			cout << "此处不可用餐 仅可在食堂用餐 " << endl;
		}
		else if (!flag_eat)
		{
			cout << endl;
			cout << "食堂关门啦  请转天再来光顾 " << endl;
		}
		else
		{
			cout << endl;
			cout << "正在用餐 ";
			Sleep(300);
			for (int i = 0; i < 6; i++)
			{
				cout << ".";
				Sleep(400);
			}
			cout << endl;
			cout << "用餐结束  获得行动点 " << temp1_Player_Action_Points << ' ' << endl;
			p->Player_Action_Points += temp1_Player_Action_Points;
			flag_eat = 0;
		}
	}
	else if (flag_es == 2)
	{
		if (p_m->getId() != 1)//不在宿舍
		{
			cout << endl;
			cout << "仅允许在宿舍睡大觉哦" << endl;
		}
		else if (p->Player_Action_Points >= 5)// 体力点大于等于5 防止摆烂玩家 不可睡觉
		{
			cout << endl;
			cout << "你的精力充沛 不妨多去走走~" << endl;
		}
		else
		{
			srand(time(NULL));
			int temp2_Player_Action_Points = rand() % 5 + 6; //睡觉随机加 10-16行动点  
			cout << endl;
			cout << "呼呼大睡中";
			Sleep(300);
			for (int i = 0; i < 6; i++)
			{
				cout << ".";
				Sleep(400);
			}
			cout << endl;
			cout << "睡眠结束  获得行动点 " << temp2_Player_Action_Points << ' ' << endl;
			p->Player_Action_Points += temp2_Player_Action_Points;
		}
	}

}



void Player::Explore_items() const
{
	cout << "是否进一步探索该场景中物品？" << endl;
	cout << "1.是\n2.否" << endl;
	int temp_ts;
	cin >> temp_ts;
	if (temp_ts == 1) {
		map_explore(you);
	}
	else if (temp_ts == 2)
	{
		cout << "见好就收~" << endl;
	}
}

void Player::Settings()
{
	cout << endl;
	cout << "进入游戏系统菜单" << endl;
	cout << endl;
	cout << "1. 存储进度  2. 返回标题  3. 保存并退出游戏  4.继续游戏 " << endl;
	cout << endl;
	int flag_set;
	cin >> flag_set;
	if (flag_set == 1)
	{
		mybag.bag_write();
	}
	else if (flag_set == 2)
	{
		cout << "请选择返回标题前 是否要存储进度？\n1. 存储进度\n2. 潇洒离去";
		int temp_save;
		cin >> temp_save;
		if (temp_save == 1)
		{
			mybag.bag_write();
			//
		}
		else if (temp_save == 20)
		{
			//
		}
	}
	else if (flag_set == 3)
	{
		mybag.bag_write();
	}
}





//玩家输入函数

int Player_scanf() {
	int a;
	cin >> a;
	return a;
}
//快速移动的函数
void quick_move(Player& you, int num) {
	cout << "是想跑去哪里吗？";
	cout << setfill('=') << setw(25) << "地图节点" << setfill('=') << setw(25) << "" << endl;
	for (int i = 0; i < 19; i++) {
		Ouc_map[i].show();
	}
	int choice = Player_scanf();
	while (choice < 1 || choice>19) {
		cout << "别尝试选项以外的数字啦，怎么想也做不到的" << endl;
		choice = Player_scanf();
	}
	you.changep_m(choice);
}


void move(Player& you) {
	int num;
	short neib[6];

	you.get_map()->getNeib(neib);
	cout << "有什么想去的地方吗？" << endl;
	//打印能移动到的节点
	int size = 0;//能移动节点的数量

	for (int i = 0; i < 6; i++) {
		if (neib[i] != 0) {
			cout << i + 1 << ". " << Ouc_map[neib[i] - 1].getName() << endl;
			size++;
		}
		else
			break;
	}
	//根据玩家选择移动
	int choice;
	choice = Player_scanf();
	while (choice < 1 || choice > size) {
		cout << "无效输入，请重新选择" << endl;
		choice = Player_scanf();
	}
	you.changep_m(neib[choice - 1] - 1);
	num = you.get_map()->getId();

	//移动时概率获取装备
	srand(time(NULL));
	int equip_id;
	int probability;
	equip_id = rand() % 19;
	MofE(equip_id, num, 60, 0, 50, 40, 60, 50, 0);

	//刷新0-3个npc 
	if (you.get_map()->getNpc_id().size() == 0) {
		num = rand() % 4;
		for (int i = 0; i < num; i++) {
			bool isTrue = 0;
			int Npc_id = rand() % 3;
			for (int i = 0; i < you.get_map()->getNpc_id().size(); i++) {
				if (Npc_id == you.get_map()->getNpc_id()[i]) {
					isTrue = 1;
					break;
				}
			}
			if (!isTrue)
				you.get_map()->getNpc_id().push_back(Npc_id);
		}
	}
	
	//固定刷新boss
	if (num = you.get_map()->getId() == 17)
		you.get_map()->getBoss_id() = 0;
	if (num = you.get_map()->getId() == 6)
		you.get_map()->getBoss_id() = 1;
	if (num = you.get_map()->getId() == 9)
		you.get_map()->getBoss_id() = 2;
}

void map_explore(Player& you) {//获取当前地图存在的物品
	srand(time(0));
	int equip_id = rand() % 19;
	bool theBool = 0;
	int num = you.get_map()->getId();
	theBool = MofE(equip_id, num, 90, 0, 75, 80, 90, 75, 0);
	if (!theBool)
		cout << "运气真差，似乎并没有找到什么有用的东西" << endl;
}