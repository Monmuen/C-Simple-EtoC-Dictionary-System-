#include <windows.h>
#include <iostream>
#include <iomanip>  //��������õ� 
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;
map<string, string> dictionary;//���ڴ洢���ʺͷ���Ĺ�����
map<string, bool> favoritesSet;//�ж��ղؼ��Ƿ����õ��ʡ�
int number;           //ȫ�ֱ�����������
void menu();          //������
void translation_e(); //Ӣ�뺺
void view();          //�鿴[�г�]ȫ������
void remove_();       //ɾ������
void add();           //���ӵ���
void back_t_e();      //Ӣ�뺺 ���ؽ���
void back_v();        //�鿴[�г�]ȫ������ ���ؽ���
void back_r();        //ɾ������ ���ؽ���
void back_a();        //���ӵ��� ���ؽ���
int CheckNum(int& n);  //�ж�������ַ����Ƿ�Ϊ�����������ǣ���Ϲ淵����ֵ �����������ʾ 
int main()
{
    menu();
    return 0;
}
void loadDictionary(const string& filename) {
    ifstream file(filename);//���ļ�
    if (!file.is_open()) {
        cerr << "�ļ���ʧ�ܡ�" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);//����ÿһ�У���ȡ���ʺͷ���
        string word, translation;
        if (getline(ss, word, ',') && getline(ss, translation)) {
            // ȥ��csv�ļ��е��ʺͷ����˫����
            word = word.substr(1, word.size() - 2);//ȥ�����ǵ���β�ַ�
            translation = translation.substr(1, translation.size() - 2);
            // ����Ƿ��ж���ķ��벿��
            while (ss.good()) {//��������ss������Ч����ʱִ��ѭ�����ڵĲ���
                string temp;
                getline(ss, temp, ',');//���ڴ洢ÿ�δ��������ж�ȡ������
                translation += "," + temp.substr(1, temp.size() - 2);
            }//�����ź�ȥ����β�ַ����temp������ӵ�translation��ĩβ
            dictionary[word] = translation;
        }
    }
    file.close();
}
void menu()//������
{
    loadDictionary("word_translation.csv");
    int l;
    cout << "\t��ӭʹ��Ӣ���ʵ�\t\n";
    cout << "\t     1.���ʲ��� \t\n";
    cout << "\t     2.�鿴�ղ� \t\n";
    cout << "\t     3.ɾ������ \t\n";
    cout << "\t     4.���ӵ��� \t\n";
    cout << "\t     5.�˳�   \n";
    cout << "=================================\n";
    //������������� 
    int m;
    while (true) {
        cout << "������ѡ��ı��: ";
        l = CheckNum(m);
        if (l >= 1 && l <= 5) //�����ǺϹ��ѡ�� 
        {
            break;
        }
    }
    switch (l) {
    case 1:
        system("cls");
        translation_e();
        break;
    case 2:
        system("cls");
        view();
        break;
    case 3:
        system("cls");
        remove_();
        break;
    case 4:
        system("cls");
        add();
        break;
    case 5:
        cout << "��л����ʹ�ã����˳���\n";
        exit(0);
    }
}
//�ж�������ַ����Ƿ�Ϊ�����������ǣ���Ϲ淵����ֵ �����������ʾ 
int CheckNum(int& n)
{
    int i;
    string x;  //������������
    bool flag = false;
    while (cin >> x) {
        for (i = 0; i < x.size(); ++i) {
            //�ж��Ƿ�Ϊ����
            if (x[i] & 0x80) {
                cout << "\n�������������������ȷ������: ";
                break;
            }
            //�ж��Ƿ�Ϊ��ĸ���������ַ�
            if (!isdigit(x[i])) {
                cout << "\n�������������������ȷ������: ";
                break;
            }
        }
        if (i == x.size()) {
            break;   //����ַ����������ַ����Ϸ������˳�whileѭ��
        }
    }
    n = atoi(x.c_str()); //���������ֵ�string�ַ���ת��Ϊ������
    return n; //����ֵ 
}
void addToFavorites(const string& word, const string& translation) {
    if (favoritesSet[word]) {
        cout << "���ղع��õ��ʡ�" << endl;
        return;
    }
    ofstream favoritesFile("favorites.txt", ios::app);//����򿪣����򴴽�
    if (favoritesFile.is_open()) {
        favoritesFile << word << "," << translation << endl;
        favoritesFile.close();
        favoritesSet[word] = true;//���˵��ʵ�ֵ��Ϊtrue
        cout << "�ѽ�����������ղأ�" << endl;
    }
    else {
        cerr << "���ղؼ�ʧ�ܣ�" << endl;
    }
}
void searchAndDisplayDefinition(const string& wordToSearch) {
    if (dictionary.find(wordToSearch) != dictionary.end()) {//�鵽���һλ
        cout << "����: " << wordToSearch << endl;
        cout << "����: " << dictionary[wordToSearch] << endl;
        char addToFavoritesChoice;
        cout << "Ҫ�ѵ��ʼ����ղؼ���(Y/N): ";
        cin >> addToFavoritesChoice;
        if (addToFavoritesChoice == 'Y' || addToFavoritesChoice == 'y') {
            addToFavorites(wordToSearch, dictionary[wordToSearch]);
        }
    }
    else {
        cout << "��Ǹ���ʵ�����δ��¼�ôʡ�" << endl;
    }
    back_t_e();
}
void translation_e()
{
    string searchWord;
    cout << "������Ҫ��ѯ�ĵ���: ";
    cin >> searchWord;
    searchAndDisplayDefinition(searchWord);
}
void back_t_e()  //Ӣ�뺺(��ѯ����)���ؽ���
{
    int l;
    cout << "\n1.����";
    cout << "\n2.����";
    cout << "\n=========================";
    cout << "\n������Ҫִ�еĲ���: ";
    //������������� 
    int m;
    while (true) {
        cout << "������ѡ��ı��: ";
        l = CheckNum(m);
        if (l >= 1 && l <= 2) //�����ǺϹ��ѡ�� 
        {
            break;
        }
    }
    switch (l) {
    case 1:
        system("cls");
        translation_e();
        break;
    case 2:
        system("cls");
        menu();
        break;
    }
}
void add()    //���ӵ���
{
    string word, translation;
    cout << "����������ӵĵ���: ";
    cin >> word;
    cout << "���뵥�ʵ�����: ";
    cin.ignore(); //��������뻺�����е��κ�ʣ���ַ�
    getline(cin, translation);//��ȡ�û������һ���ַ�����������洢��translation�����С���������Ŀ����ȷ��getline()�ܹ���ȡ�û����������һ�У�������֮ǰ�����Ӱ�졣
    addToFavorites(word, translation);
    back_a();
}
void back_a()  //���ӵ��� ���ؽ���
{
    int l;
    cout << "\n1.����";
    cout << "\n2.����";
    cout << "\n=========================";
    cout << "\n������Ҫִ�еĲ���: ";
    //������������� 
    int m;
    while (true) {
        cout << "������ѡ��ı��: ";
        l = CheckNum(m);
        if (l >= 0 && l <= 2) //�����ǺϹ��ѡ�� 
        {
            break;
        }
    }
    switch (l) {
    case 1:
        system("cls");
        add();
        break;
    case 2:
        system("cls");
        menu();
        break;
    }
}
void view() {
    ifstream favoritesFile("favorites.txt");
    if (favoritesFile.is_open()) {
        string line;
        while (getline(favoritesFile, line)) {
            stringstream ss(line);
            string word, translation;
            getline(ss, word, ',');
            getline(ss, translation);
            cout << "����: " << word << endl << "����: " << translation << endl;
        }
        favoritesFile.close();
    }
    else {
        cerr << "���ļ�ʧ�ܣ�" << endl;
    }
    back_v();
}
void back_v()  //�鿴[�г�]ȫ������ ���ؽ���
{
    int l;
    cout << "1.ɾ������";
    cout << "\n2.����";
    cout << "\n=========================";
    cout << "\n������Ҫִ�еĲ���: ";
    //cin >>l
    //������������� 
    int m;
    while (true) {
        cout << "������ѡ��ı��: ";
        l = CheckNum(m);
        if (l >= 0 && l <= 2) //�����ǺϹ��ѡ�� 
        {
            break;
        }
    }
    switch (l) {
    case 1:
        system("cls");
        remove_();
        break;
    case 2:
        system("cls");
        menu();
        break;
    default:
        cout << "[�������]������������Ч����!\n";
        Sleep(3000);
        back_v();
        break;
    }
}
void remove_() //ɾ������
{
    int flag = 1;
    string deleteWord;
    cout << "��������ɾ���ĵ��ʣ�(����0�˳�): ";
    cin >> deleteWord;
    if (deleteWord == "0") {
        system("cls");
        menu();
    }
        if (deleteWord != "0" && (favoritesSet.find(deleteWord) != favoritesSet.end())) {
            favoritesSet.erase(deleteWord);
            ofstream tempFile("temp.txt");
            ifstream favoritesFile("favorites.txt");
            if (favoritesFile.is_open() && tempFile.is_open()) {
                string line;
                while (getline(favoritesFile, line)) {
                    stringstream ss(line);//��һ���ַ���lineת��Ϊһ����������һ������������������Ķ���
                    string word, translation;//ͨ��ʹ��stringstream�������ǿ��Է���ض��ַ������зָ��ȡ�͸�ʽ���Ȳ�������������������һ��������
                    getline(ss, word, ','); //��������line�ַ����е����ݣ������ն��ŷָ���ȡ�����ʺͷ��벿�֡���ȡ�����ݴ洢��word�ַ����У�ֱ����������Ϊֹ
                    getline(ss, translation);
                    if (word != deleteWord) {
                        tempFile << word << "," << translation << endl;
                    }
                }
                favoritesFile.close();
                tempFile.close();
                remove("favorites.txt");
                rename("temp.txt", "favorites.txt");
                cout << "�����Ѵ��ղؼ���ɾ����" << endl;
                flag = 0;
            }
        }
    else
    {
        cout << "�ղؼ���û�иôʡ�" << endl;
    }
    back_r();
}
void back_r() //ɾ������ ���ؽ���
{
    int l;
    cout << "\n1.����";
    cout << "\n2.����";
    cout << "\n=========================";
    cout << "\n������Ҫִ�еĲ���: ";
    //������������� 
    int m;
    while (true) {
        cout << "������ѡ��ı��: ";
        l = CheckNum(m);
        if (l >= 0 && l <= 2) //�����ǺϹ��ѡ�� 
        {
            break;
        }
    }
    switch (l) {
    case 1:
        system("cls");
        remove_();
        break;
    case 2:
        system("cls");
        menu();
        break;
    }
}