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

//������
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
};//�ƶ�λ��
short Player::getMap_id() {
	return p_m->getId();
}
ouc_map* Player::get_map() {
	return p_m;
}

Player you;    //ʵ����һ�� you
Bag mybag;




Player::Player() {//��������
	p = (struct Player_Stats*)new struct Player_Stats;
	p_m = &Ouc_map[0];

}

void Player::setting_player() {
	ifstream ifs("data/Player/player.dat", ios::in | ios::binary);
	int n1 = 0;
	cout << "��ʼ��ȡ" << endl;
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	p->DateCount = n1;
	ifs.read(reinterpret_cast<char*>(&n1), sizeof(n1));
	if (n1 == 1) {
		strcpy(p->Major, "�������ѧ�뼼��");
		flag_major = 1;
	}
	else if (n1 == 2) {
		strcpy(p->Major, "���ܿ�ѧ�뼼��");
		flag_major = 2;
	}
	else if (n1 == 3) {
		strcpy(p->Major, "����ռ䰲ȫ");
		flag_major = 3;
	}
	else if (n1 == 4) {
		strcpy(p->Major, "�������");
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
	cout << "��ʼ�浵" << endl;
	ofstream ofs("data/Player/player.dat", ios::out | ios::binary);
	if (!ofs)
		cout << "���Ĵ浵���������������ȥ��ʼ�µ���Ϸ�ɣ�" << endl;
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
	cout << "�浵�ɹ�" << endl;
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
	cout << "��ӭ������ OUC �Ų� ��"; Sleep(400);
	cout << "��ü������������רҵȥ����ô�� �������ĸ�����רҵ������ѡ : " << endl;
	cout << "1. �������ѧ�뼼��" << endl;
	cout << "2. ���ܿ�ѧ�뼼��" << endl;
	cout << "3. ����ռ䰲ȫ" << endl;
	cout << "4. �������" << endl;
	cout << endl;
	cout << "��ѡ��һ���ʺ���ķ���רҵ : " << endl;
	flag_major = inputch(1,4);
	if (flag_major == 1)
	{
		cout << "���ѳ�Ϊ [�������ѧ�뼼��] רҵ��ѧ��  " << endl;
		Sleep(300);
		cout << "��ȥ̽��У԰ ���Ͻ���ѧϰ ����������� ��ȡ˳����ҵ�� " << endl;
		p->Player_AbilityofLearn = 1;
		p->Player_AbilityofProgramming = 4;
		p->Player_AbilityofMath = 2;
		p->Player_AbilityofLogic = 2;
		p->Player_AbilityofPractice = 2;
		p->Player_Action_Points = 8;
		strcpy(p->Major, "�������ѧ�뼼��");
	}
	else if (flag_major == 2)
	{
		cout << "���ѳ�Ϊ [���ܿ�ѧ�뼼��] רҵ��ѧ��  " << endl;
		Sleep(300);
		cout << "��ȥ̽��У԰ ���Ͻ���ѧϰ ����������� ��ȡ˳����ҵ�� " << endl;
		p->Player_AbilityofLearn = 1;
		p->Player_AbilityofProgramming = 2;
		p->Player_AbilityofMath = 2;
		p->Player_AbilityofLogic = 4;
		p->Player_AbilityofPractice = 2;
		p->Player_Action_Points = 8;
		strcpy(p->Major, "���ܿ�ѧ�뼼��");
	}
	else if (flag_major == 3)
	{
		cout << "���ѳ�Ϊ ������ռ䰲ȫ] רҵ��ѧ��  " << endl;
		Sleep(300);
		cout << "��ȥ̽��У԰ ���Ͻ���ѧϰ ����������� ��ȡ˳����ҵ�� " << endl;
		p->Player_AbilityofLearn = 1;
		p->Player_AbilityofProgramming = 2;
		p->Player_AbilityofMath = 2;
		p->Player_AbilityofLogic = 3;
		p->Player_AbilityofPractice = 3;
		p->Player_Action_Points = 8;
		strcpy(p->Major, "����ռ䰲ȫ");
	}
	else if (flag_major == 4)
	{
		cout << "���ѳ�Ϊ [�������] רҵ��ѧ��  " << endl;
		Sleep(300);
		cout << "��ȥ̽��У԰ ���Ͻ���ѧϰ ����������� ��ȡ˳����ҵ�� " << endl;
		p->Player_AbilityofLearn = 1;
		p->Player_AbilityofProgramming = 4;
		p->Player_AbilityofMath = 2;
		p->Player_AbilityofLogic = 2;
		p->Player_AbilityofPractice = 2;
		p->Player_Action_Points = 8;
		strcpy(p->Major, "�������");
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
	cout << "��10��������λ�ڣ�ͨ����ͬѧ [����ѧϰ] �� [̽��У԰] �����Լ���ѧϰ�������������ֵ" << endl;
	cout << "�������ŵİ����£����ʦ���� [����] �����ۻ���6��ѧ�ַ���˳����ҵ" << endl;
}

void Player::State() const //չʾ��ҵ�ǰ״̬ 
{
	cout << endl;
	cout << "���רҵ [" << p->Major << ']' << endl;
	cout << "ѧϰ�� : " << p->Player_AbilityofLearn << endl;
	cout << "�ж��� : " << p->Player_Action_Points << endl;
	cout << "�������ֵ : " << p->Player_AbilityofProgramming << endl;
	cout << "��ѧ����ֵ : " << p->Player_AbilityofMath << endl;
	cout << "�߼�����ֵ : " << p->Player_AbilityofLogic << endl;
	cout << "ʵ������ֵ : " << p->Player_AbilityofPractice << endl;
	cout << "��У��ѧϰ���� : " << p->DateCount <<"     "<<"ѧҵ��ʾ��"<<p->Warning<<  endl;
}

void Player::Equip_equipments(int num_eq)
{
	Equipment player_equ;
	cout << endl;
	cout << " ���� [" << equipment_bag[num_eq - 1]->get_name() << "] ����� :" << endl;
	cout << "1. ʹ�ø���Ʒ" << endl;
	cout << "2. �鿴����Ʒ����" << endl;
	cout << "3. ж�¸�װ��" << endl;
	cout << "4. ��������Ʒ " << endl;
	int flag_eq;
	cin >> flag_eq;
	if (flag_eq == 1)
	{
		cout << "װ������Ʒ�����״̬ : " << endl;
		p->Player_AbilityofLearn += equipment_bag[num_eq - 1]->get_AbilityofLearn();  //ѧϰ�� 
		this->p->Player_AbilityofProgramming += equipment_bag[num_eq - 1]->get_AbilityofProgramming();  //�������ֵ 
		this->p->Player_AbilityofMath += equipment_bag[num_eq - 1]->get_AbilityofMath(); // ��ѧ����ֵ 
		this->p->Player_AbilityofLogic += equipment_bag[num_eq - 1]->get_AbilityofLogic();  //�߼�����ֵ 
		this->p->Player_AbilityofPractice += equipment_bag[num_eq - 1]->get_AbilityofPractice();  //ʵ������ֵ 
		this->p->Player_Action_Points += equipment_bag[num_eq - 1]->get_Action_Points();  //�ж���
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
		if (!equipment_bag[num_eq - 1]->get_on()) //��δʹ��
		{
			cout << "����Ʒ��δʹ�� �޷�ж��" << endl;
		}
		else
		{
			this->p->Player_AbilityofLearn -= equipment_bag[num_eq - 1]->get_AbilityofLearn();  //ѧϰ�� 
			this->p->Player_AbilityofProgramming -= equipment_bag[num_eq - 1]->get_AbilityofProgramming();  //�������ֵ 
			this->p->Player_AbilityofMath -= equipment_bag[num_eq - 1]->get_AbilityofMath(); // ��ѧ����ֵ 
			this->p->Player_AbilityofLogic -= equipment_bag[num_eq - 1]->get_AbilityofLogic();  //�߼�����ֵ 
			this->p->Player_AbilityofPractice -= equipment_bag[num_eq - 1]->get_AbilityofPractice();  //ʵ������ֵ 
			equipment_bag[num_eq - 1]->show();
		}
	}
	else if (flag_eq == 4)
	{
		cout << "ȷ�϶�������Ʒ?" << endl;
		cout << "1. ����" << endl;

		cout << "2. ȡ��" << endl;
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
			//����
		}
	}

}

void Player::Backpack()
{
	if (equipment_bag.empty()) //�� ����
	{
		cout << "��ı����տ���Ҳ " << endl;
	}
	else
	{
		int siz = equipment_bag.size();
		cout << "�㱳���ڵ���Ʒ�� : " << endl;
		for (int i = 0; i < siz; i++)
		{
			cout << i + 1 << '.' << equipment_bag[i]->get_name()<<" "<<equipment_bag[i]->get_num()<<"��" << endl;
		}
		while (true) {
			cout << "������ָ���װ�����в���: " << endl;
			int chose = 0;//ѡ��װ����ʹ��
			cin >> chose;
			if (chose >= 1 && chose <= siz) {
				Equip_equipments(chose);
				break;
			}
			else
				cout << "ָ�����" << endl;
		}
	}
}

void Player::Eat_orSleep() const
{
	int flag_es;
	cout << endl;
	cout << "1. ��ʳ���ò�" << endl;
	cout << "2. ������˯��" << endl;
	cin >> flag_es;
	if (flag_es == 1)
	{
		int flag_eat = 1; //һ����������ò�һ��  ת��flag_eat��עΪ 1 ���ò�  
		srand(time(NULL));
		int temp1_Player_Action_Points = rand() % 4 + 2; //��һ�η������ 2~5�ж���  
		if (p_m->getId() != 2) //����ʳ��
		{
			cout << "�˴������ò� ������ʳ���ò� " << endl;
		}
		else if (!flag_eat)
		{
			cout << endl;
			cout << "ʳ�ù�����  ��ת��������� " << endl;
		}
		else
		{
			cout << endl;
			cout << "�����ò� ";
			Sleep(300);
			for (int i = 0; i < 6; i++)
			{
				cout << ".";
				Sleep(400);
			}
			cout << endl;
			cout << "�òͽ���  ����ж��� " << temp1_Player_Action_Points << ' ' << endl;
			p->Player_Action_Points += temp1_Player_Action_Points;
			flag_eat = 0;
		}
	}
	else if (flag_es == 2)
	{
		if (p_m->getId() != 1)//��������
		{
			cout << endl;
			cout << "������������˯���Ŷ" << endl;
		}
		else if (p->Player_Action_Points >= 5)// ��������ڵ���5 ��ֹ������� ����˯��
		{
			cout << endl;
			cout << "��ľ������� ������ȥ����~" << endl;
		}
		else
		{
			srand(time(NULL));
			int temp2_Player_Action_Points = rand() % 5 + 6; //˯������� 10-16�ж���  
			cout << endl;
			cout << "������˯��";
			Sleep(300);
			for (int i = 0; i < 6; i++)
			{
				cout << ".";
				Sleep(400);
			}
			cout << endl;
			cout << "˯�߽���  ����ж��� " << temp2_Player_Action_Points << ' ' << endl;
			p->Player_Action_Points += temp2_Player_Action_Points;
		}
	}

}



void Player::Explore_items() const
{
	cout << "�Ƿ��һ��̽���ó�������Ʒ��" << endl;
	cout << "1.��\n2.��" << endl;
	int temp_ts;
	cin >> temp_ts;
	if (temp_ts == 1) {
		map_explore(you);
	}
	else if (temp_ts == 2)
	{
		cout << "���þ���~" << endl;
	}
}

void Player::Settings()
{
	cout << endl;
	cout << "������Ϸϵͳ�˵�" << endl;
	cout << endl;
	cout << "1. �洢����  2. ���ر���  3. ���沢�˳���Ϸ  4.������Ϸ " << endl;
	cout << endl;
	int flag_set;
	cin >> flag_set;
	if (flag_set == 1)
	{
		mybag.bag_write();
	}
	else if (flag_set == 2)
	{
		cout << "��ѡ�񷵻ر���ǰ �Ƿ�Ҫ�洢���ȣ�\n1. �洢����\n2. ������ȥ";
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





//������뺯��

int Player_scanf() {
	int a;
	cin >> a;
	return a;
}
//�����ƶ��ĺ���
void quick_move(Player& you, int num) {
	cout << "������ȥ������";
	cout << setfill('=') << setw(25) << "��ͼ�ڵ�" << setfill('=') << setw(25) << "" << endl;
	for (int i = 0; i < 19; i++) {
		Ouc_map[i].show();
	}
	int choice = Player_scanf();
	while (choice < 1 || choice>19) {
		cout << "����ѡ�����������������ô��Ҳ��������" << endl;
		choice = Player_scanf();
	}
	you.changep_m(choice);
}


void move(Player& you) {
	int num;
	short neib[6];

	you.get_map()->getNeib(neib);
	cout << "��ʲô��ȥ�ĵط���" << endl;
	//��ӡ���ƶ����Ľڵ�
	int size = 0;//���ƶ��ڵ������

	for (int i = 0; i < 6; i++) {
		if (neib[i] != 0) {
			cout << i + 1 << ". " << Ouc_map[neib[i] - 1].getName() << endl;
			size++;
		}
		else
			break;
	}
	//�������ѡ���ƶ�
	int choice;
	choice = Player_scanf();
	while (choice < 1 || choice > size) {
		cout << "��Ч���룬������ѡ��" << endl;
		choice = Player_scanf();
	}
	you.changep_m(neib[choice - 1] - 1);
	num = you.get_map()->getId();

	//�ƶ�ʱ���ʻ�ȡװ��
	srand(time(NULL));
	int equip_id;
	int probability;
	equip_id = rand() % 19;
	MofE(equip_id, num, 60, 0, 50, 40, 60, 50, 0);

	//ˢ��0-3��npc 
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
	
	//�̶�ˢ��boss
	if (num = you.get_map()->getId() == 17)
		you.get_map()->getBoss_id() = 0;
	if (num = you.get_map()->getId() == 6)
		you.get_map()->getBoss_id() = 1;
	if (num = you.get_map()->getId() == 9)
		you.get_map()->getBoss_id() = 2;
}

void map_explore(Player& you) {//��ȡ��ǰ��ͼ���ڵ���Ʒ
	srand(time(0));
	int equip_id = rand() % 19;
	bool theBool = 0;
	int num = you.get_map()->getId();
	theBool = MofE(equip_id, num, 90, 0, 75, 80, 90, 75, 0);
	if (!theBool)
		cout << "�������ƺ���û���ҵ�ʲô���õĶ���" << endl;
}