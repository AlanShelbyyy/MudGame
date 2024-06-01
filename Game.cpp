#include"Game.h"
#include<iostream>
#include<fstream>
#include<string>
#include"Equipment.h"
#include"map.h"
#include"Bag.h"
#include"fight_part.h"
#include<windows.h>
#include<conio.h>
using namespace std;

enum {
    start_menu,
    adv,
    fighstu,
    fightea,
    rest,
    bag,
    store
} gamestate;

extern vector<Equipment*> equipment_bag;
extern ouc_map Ouc_map[19];

int count_win=0;

void showMap();
void showInColor(string, int color, HANDLE console);
int GetInput();
int GetInput(int, int);
int SelectItem(int&);

MUDGame::MUDGame() {
    _Run = true;
}
int temp_cc = 0;

void Action(Player& player) //�ж����趨
{
    if (player.get_p()->Player_Action_Points == 0)
    {
        cout << "���Ѿ����ľ�ƣ�� ��Ҫ�ص����Ჹ������ ׼��ӭ����һ��� " << endl;
        player.changep_m(0);
        player.get_p()->Player_Action_Points = 12;
        player.get_p()->DateCount += 1;
        temp_cc = 0;
    }
    if (player.get_p()->DateCount == 24)
    {
        cout << "��ע�⣡���ʣһ��ʱ��������У�ڻ 7d��������ѧ���գ�";
    }
    if (player.get_p()->DateCount == 31)
    {
        cout << "���ź� ���ڹ涨ѧ��������30d����δ��������ѧ��Ҫ�� �����ѱ���ѧ ! " << endl;
        gamestate = start_menu;
    } //������Ϸ ʧ��

    if (player.getMap_id()==19 && temp_cc==0)
    {
        cout << "�������˶��򿨣� ��������4�㣡" << endl;
        player.get_p()->Player_Action_Points += 4;
        system("pause>nul");
        temp_cc = 1;
    }
    if (player.getMap_id() == 19 && temp_cc == 1)
    {
        cout << "�����ڲ��ɹ��ȶ����� ��ת������" << endl;
        system("pause>nul");
    }
}

void MUDGame::LoadNpc() {
    fstream infile;
    npc tmp;
    infile.open("data\\npc.dat", ios::in);
    if (!infile) {
        cout << "��ʧ��" << endl;
        exit(1);
    }
    while (!infile.eof()) {
        infile >> tmp.Name;
        infile >> tmp.Description;

        infile >> tmp.GiveMat;//cout<<tmp.GiveMat;
        infile >> tmp.GiveLog;//cout<<tmp.GiveLog;
        infile >> tmp.GiveProg;//cout<<tmp.GiveProg;
        infile >> tmp.GivePrac;//cout<<tmp.GivePrac;
        infile >> tmp.GiveLearnPinit;//cout<<tmp.GiveLearnPinit;
        infile >> tmp.hardlvl;
        //cout<<"##"<<endl;
        NPCs.push_back(tmp);
    }
    return;
}

void MUDGame::LoadSkill() {
    fstream infile;
    Skill tmp;
    string argus;
    infile.open("data\\normskill.dat", ios::in);
    if (!infile) {
        cout << "��ʧ��" << endl;
        exit(1);
    }
    while (!infile.eof()) {
        infile >> tmp.name;
        infile >> tmp.description;
        infile >> tmp.choices;
        infile >> tmp.answer;
        infile >> tmp.hardlvl;
        skills.push_back(tmp);
    }
    return;
}

void MUDGame::LoadBoss() {
    fstream infile;
    npc tmp;
    infile.open("data\\boss.dat", ios::in);
    if (!infile) {
        cout << "��ʧ��" << endl;
        exit(1);
    }
    while (!infile.eof()) {
        infile >> tmp.Name;
        infile >> tmp.Description;
        infile >> tmp.GiveMat;
        infile >> tmp.GiveLog;
        infile >> tmp.GiveProg;
        infile >> tmp.GivePrac;
        infile >> tmp.GiveLearnPinit;
        infile >> tmp.hardlvl;
        Boss.push_back(tmp);
    }
    return;
}
void MUDGame::LoadBossSkill() {
    fstream infile;
    Skill tmp;
    string argus;
    infile.open("data\\bossskill.dat", ios::in);
    if (!infile) {
        cout << "��ʧ��" << endl;
        exit(1);
    }
    while (!infile.eof()) {
        infile >> tmp.name;
        infile >> tmp.description;
        infile >> tmp.choices;
        infile >> tmp.answer;
        infile >> tmp.hardlvl;
        bossSkills.push_back(tmp);
    }
    return;
}
//����ͼ�ļ�������Ouc_map������
void MUDGame::LoadMap() {
    for (int i = 0; i < 19; i++) {
        ouc_map map(i + 1);
        Ouc_map[i] = map;
    }
}
void MUDGame::ShowNpcList() {
    for (int i = 0; i < NPCs.size(); i++) {
        cout << NPCs[i].Name << endl;
        cout << NPCs[i].Description << endl;
        cout << NPCs[i].GiveLearnPinit << endl;
        cout << NPCs[i].GiveLog << endl;
        cout << NPCs[i].GiveMat << endl;
        cout << NPCs[i].GivePrac << endl;
        cout << NPCs[i].GiveProg << endl;
    }

}


void MUDGame::ShowSkillList() {
    for (int i = 0; i < skills.size(); i++) {
        cout << "��ӡ��";
        cout << skills[i].name << endl;
        cout << skills[i].description << endl;
        cout << skills[i].choices << endl;
        cout << skills[i].answer << endl;
        cout << skills[i].hardlvl << endl;
    }
    return;


}
// void MUDGame::GetMapNpc(){
//     vector<int> npcs = player.get_map()->getNpc_id();
//     for(int i =0;i < npcs.size();i++){
//         npcindex.push_back(npcs[i]);
//     }
// }
void MUDGame::RunGame() {
    LoadLogo();
    LoadSkill();
    //ShowSkillList();
    LoadBoss();
    LoadBossSkill();
    LoadNpc();
    LoadMap();
    ShowNpcList();
    //cout<<"load end"<<endl;
    Bag bagsaver;
    thewindow = GetStdHandle(STD_OUTPUT_HANDLE);
    int choice = 0;
    int operate;

    gamestate = start_menu;
    while (RunOrNot()) {
        system("cls");

        switch (gamestate) {
        case start_menu:cout << "��ʼ����" << endl;//������Ϸ״̬

            ShowLogo();
            cout << endl;
            cout << "һ������ĺ���ѧ��" << endl;
            cout << "1. �µĿ�ʼ 2. ����ѧҵ 3.�˳���Ϸ" << endl;
            operate = GetInput(1, 3);
            if (operate == 1) {
                system("cls");
                player.ChooseMajor();
                player.State();
                system("pause>nul");

                //cout<<"��ٵ�ѡרҵ"<<endl;
                gamestate = adv;
            }
            else if (operate == 2) {
                cout << "����/������ȡ" << endl;
                bagsaver.bag_read();
                player.setting_player();
                gamestate = adv;
                break;
            }
            else if (operate == 3) {

                break;
            }

            //thisgame.ToffGame();
            break;
        case adv: {cout << "ð����" << endl;
            player.get_map()->show();//չʾ��ͼ��Ϣ,����е�ͼ����
            //չʾboss

            //չʾ����npc������ɫ
            //cout << player.get_map()->getNpc_id().size() << "##";
            for (int i = 0; i < player.get_map()->getNpc_id().size(); i++) {
                //cout<<player.get_map()->getNpc_id()[i];
                showInColor(NPCs[player.get_map()->getNpc_id()[i]].Name, 1, thewindow);
                cout << endl;
            }
            if (player.getMap_id() == 6 || player.getMap_id() == 9 || player.getMap_id() == 17) {
                showInColor(Boss[player.get_map()->getBoss_id()].Name, 2, thewindow);
                cout << endl;
            }
            //

            cout << "��Ҫ������ʲô : " << endl;
            cout << endl;
            cout << "1. �鿴״̬  2.����  3. ̽��  4. ѧϰ����/���뿼��  5.�ƶ�  6. �Է�/˯��  7. ��ͼ 8.ϵͳ" << endl;
            cout << endl;
            int opt;
            opt = GetInput(1, 8);
            if (opt == 1)
            {
                cout << "���״̬ : " << endl;
                player.State();
                system("pause>nul");
                break;
            }
            else if (opt == 2)
            {
                if (!equipment_bag.size()) //����Ϊ��
                {
                    cout << "��ı����� �տ���Ҳ " << endl;
                }
                else
                {
                    cout << "�������㱳���е���Ʒ : " << endl;
                    player.Backpack();
                }
                system("pause>nul");
                break;

            }
            else if (opt == 3)
            {
                map_explore(player);//̽����ͼ
                player.get_p()->Player_Action_Points -= 1;
                Action(player);
                system("pause>nul");
                break;

            }
            else if (opt == 4)
            {
                //cout<<"ȥ��ĵط�������"<<endl;
                cout << "������" << endl;
                if (player.get_map()->getNpc_id().empty() && (player.getMap_id() != 6 && player.getMap_id() != 9 && player.getMap_id() != 17))//�÷���û��NPC
                {
                    cout << "������ò�ƿ���һ��" << endl;
                }
                else
                {
                    //�ж��Ƿ�����ʦ
                    if (player.getMap_id() == 6 || player.getMap_id() == 9 || player.getMap_id() == 17)
                    {

                        cout << "1. " << Boss[player.get_map()->getBoss_id()].Name << endl;

                        for (int i = 0; i < player.get_map()->getNpc_id().size(); i++)
                        {
                            cout << i + 2 << ". " << NPCs[player.get_map()->getNpc_id()[i]].Name << endl;
                        }

                        int choice;
                        choice = GetInput(1, player.get_map()->getNpc_id().size() + 1);


                        if (choice != 1) { //ѧ��
                            cout << "������ѧ������/���ԵĶ����� " << NPCs[player.get_map()->getNpc_id()[choice - 2]].Name << endl;
                            npcchoice = player.get_map()->getNpc_id()[choice - 2];
                            gamestate = fighstu;
                        }

                        else {
                             if (!player.canTest_or_not()||(player.get_p()->Player_AbilityofLearn<=0)) {
                                cout << "��ѧ�����֪ʶ�ٿ��԰�(��ͬѧ����ѧ������)" << endl;
                                system("pause>nul");
                                break;
                            }
                            cout << "�����ڽ��п��ԵĶ����� " << Boss[player.get_map()->getBoss_id()].Name << endl;
                            bossindex = player.get_map()->getBoss_id();
                            gamestate = fightea;
                        }
                    }//û����ʦ�Ļ�
                    else {
                        //���δ�ӡ����
                        cout << "ѡ����˭����" << endl;
                        for (int dz = 0; dz < player.get_map()->getNpc_id().size(); dz++)
                        {
                            cout << dz + 1 << ' ' << NPCs[player.get_map()->getNpc_id()[dz]].Name;
                        }
                        //ѡ��npc
                        cout << endl;
                        int temp_dz2;
                        temp_dz2 = GetInput(1, player.get_map()->getNpc_id().size());

                        cout << "������ѧ�������Ķ����� " << NPCs[player.get_map()->getNpc_id()[temp_dz2 - 1]].Name;
                        npcchoice = player.get_map()->getNpc_id()[temp_dz2 - 1];
                        gamestate = fighstu;
                    }
                }


            }
            else if (opt == 5)
            {
                // cout << endl;
                // cout << "�㵱ǰ���ڵر�ż�����Ϊ ";
                // player.get_map()->show();
               // cout<<"�����ȥ�ĵط�:"<<endl;
                //��ӡ
                //ѡ��
                //�ƶ�
                move(player);
                player.get_p()->Player_Action_Points -= 1;
                Action(player);
            }
            else if (opt == 6)
            {
                player.Eat_orSleep();
                system("pause>nul");
            }
            else if (opt == 7)
            {
                showMap();
                system("pause>nul");
            }
            else if (opt == 8) {
                system("cls");
                ShowLogo();
                cout << endl;
                cout << "1. ������Ϸ 2. ������� 3. �˳���Ϸ" << endl;
                int localOpt = 0;

                //����Ӽ��
                localOpt = GetInput(1, 3);
                switch (localOpt) {
                case 1:
                case 2://����
                    bagsaver.bag_write();
                    player.saver();

                case 3:ToffGame(); break;
                default: break;
                }
                cout << "ʩ����" << endl;

            }
            break;
        }
        case fighstu: {
            cout << "�����غ�" << endl;
            // system("pause");

            int skillindex = NPCs[npcchoice].Useskill(skills);
            choice = GetInput(1, 4);
            if (NPCs[npcchoice].Check(skillindex, choice, skills)) {
                // NPCs[npcchoice].Debug_show();
                NPCs[npcchoice].GivePoint(player);
                cout << "��Ӣ������������������Ļش�" << endl;
            }
            else {
                cout << "�ش����" << endl;
            }


            cout << "������ 1. ȥð�� 2.��������" << endl;
            operate = GetInput(1, 2);
            if (operate == 1) {
                gamestate = adv;
            }
            break; }
        case fightea: {

            //��ʾѪ��

            cout << "�������ʣ��: ";
            showInColor(to_string(Boss[bossindex].hardlvl) + "/100-------------", 4, thewindow);
            cout << endl;
            cout << "���ѧϰ��: ";
            showInColor(to_string(player.Getter_learn()) + "/100-------------", 4, thewindow);
            cout << endl;

            //cout << "���Իغ�";
            //system("pause");
            //BOSS��ӡ����
            int bossskill = Boss[bossindex].Useskill(bossSkills);

            //���ʹ�ü���

            cout << "ѡ���ж�" << endl << "1.��ͨ����hello world 2.ʹ����Ʒ" << endl;

            choice = GetInput(1, 2);

            if (choice == 1) {
                Sleep(1000);
                cout << "��ʹ����hello world" << endl;
                Sleep(1000);
                cout << "����������ѧϰ�������Խ�����__1__" << endl;
                Sleep(1000);
                Boss[bossindex].be_attack(false);
                player.be_attack(2);
            }
            else if (choice == 2) {
                int localindex;
                int item_class = SelectItem(localindex);
                Sleep(1000);
                cout << "��ʹ����: " << equipment_bag[localindex]->get_name() << endl;
                Sleep(1000);
                bool right = Boss[bossindex].CheckEquip(bossskill, item_class, bossSkills);
                if (right) {

                    Boss[bossindex].be_attack(Boss[bossindex].CheckEquip(bossskill, item_class, bossSkills));
                    cout << "����ȫ��  " << "���Խ�����__50__" << endl;
                    Sleep(1000);
                }
                else {
                    player.be_attack(20);
                    cout << "�ƺ�������";
                    Sleep(100);
                    cout << "û�гɹ��Ľ������" << endl;
                    Sleep(1000);
                }
            }


            if (player.Getter_learn() < 0) {
                cout << "������յ���һ��ѧҵ��ʾ";
                player.setwarn();
                Sleep(1000);
                gamestate = adv;
                Boss[bossindex].hardlvl = 50;
                if (player.get_p()->Warning >= 3) {
                    system("cls");
                    cout << "��Ϊ�յ�����ѧҵ��ʾ���㱻��ѧ��" << endl;
                    Sleep(2000);
                    gamestate = start_menu;
                }
                //player.GetWarning();
            }
            else if (Boss[bossindex].Getter_hardlvl() < 0) {
                system("cls");
                cout << "��ͨ���˿���";
                Sleep(1000);
                Boss[bossindex].hardlvl = 50;
                count_win++;
                if (count_win >= 6) {
                    system("cls");
                    cout << "̫���ˣ���ͨ����" << endl;
                    Sleep(3000);
                    gamestate = start_menu;
                    break;
                }
                gamestate = adv;
            }
            break; }
        case rest:; break;
        case bag:; break;
        case store:; break;
        default: this->ToffGame();
            cout << "esc unexpected";
            break;
        }
    }
}

void MUDGame::ToffGame() {
    _Run = false;
}
bool MUDGame::RunOrNot() {
    return _Run;
}
void MUDGame::LoadLogo() {

    fstream file;
    file.open("data\\logo.dat", ios::in | ios::binary);
    if (!file) {
        cout << "file open error";
        exit(1);
    }

    int logolength;
    file.seekg(0, ios::end);
    logolength = (int)file.tellg();

    file.seekg(0, ios::beg);
    file.read(GameLogo, logolength);

    file.close();
    return;


}
void MUDGame::ShowLogo() {
    SetConsoleTextAttribute(thewindow, FOREGROUND_BLUE);
    cout << GameLogo;
    SetConsoleTextAttribute(thewindow, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}
void showMap() {
    string line;
    ifstream file("data/map/map.dat");
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "�޷����ļ�" << endl;
    }
}

//����ɫ�����
void showInColor(string str, int color, HANDLE console) {
    SetConsoleTextAttribute(console, color);
    cout << str;
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
//������
int GetInput() {
    char str[2];
    str[0] = _getch();
    return atoi(str);
}
int GetInput(int min, int max) {
    short n = GetInput();
    while (n<min || n>max) {
        n = GetInput();
    }
    return n;
}

int SelectItem(int& index) {
    int choice;
    int j=0;
    for (int i = 0; i < equipment_bag.size(); i++) {

        cout <<  i+1 << ". " << equipment_bag[i]->get_name() << endl;
    }
    cout << endl;
    cout << "ѡ����Ҫ�õ���Ʒ[���]" << endl;

    while (true) {
        cin >> choice;
        if (choice >= 1 && choice <= equipment_bag.size())break;
        else {
            cout << "�������" << endl;
        }
    }
    
    

   /*int i = 0;
   while (j<equipment_bag.size()) {

        for (i = j*9; i < j*9&&i<equipment_bag.size(); i++) {
            
            cout << i-j+1 << ". " << equipment_bag[j+i]->get_name() << endl;
        }

        j += 9;
        cout << endl;
        cout << "ѡ����Ҫ�õ���Ʒ" << endl;
        choice = GetInput(1, 9);

       


    }*/
   





    
    index = choice - 1;

    return equipment_bag[choice - 1]->get_id();
}