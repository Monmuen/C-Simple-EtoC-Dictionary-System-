#include <windows.h>
#include <iostream>
#include <iomanip>  //对齐输出用到 
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;
map<string, string> dictionary;//用于存储单词和翻译的关联。
map<string, bool> favoritesSet;//判断收藏夹是否存过该单词。
int number;           //全局变量单词总数
void menu();          //主界面
void translation_e(); //英译汉
void view();          //查看[列出]全部单词
void remove_();       //删除单词
void add();           //增加单词
void back_t_e();      //英译汉 返回界面
void back_v();        //查看[列出]全部单词 返回界面
void back_r();        //删除单词 返回界面
void back_a();        //增加单词 返回界面
int CheckNum(int& n);  //判断输入的字符串是否为正整数，若是，则合规返归其值 ，否则给出提示 
int main()
{
    menu();
    return 0;
}
void loadDictionary(const string& filename) {
    ifstream file(filename);//打开文件
    if (!file.is_open()) {
        cerr << "文件打开失败。" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);//解析每一行，提取单词和翻译
        string word, translation;
        if (getline(ss, word, ',') && getline(ss, translation)) {
            // 去除csv文件中单词和翻译的双引号
            word = word.substr(1, word.size() - 2);//去掉他们的首尾字符
            translation = translation.substr(1, translation.size() - 2);
            // 检查是否有额外的翻译部分
            while (ss.good()) {//当输入流ss还有有效数据时执行循环体内的操作
                string temp;
                getline(ss, temp, ',');//用于存储每次从输入流中读取的内容
                translation += "," + temp.substr(1, temp.size() - 2);
            }//将逗号和去掉首尾字符后的temp内容添加到translation的末尾
            dictionary[word] = translation;
        }
    }
    file.close();
}
void menu()//主界面
{
    loadDictionary("word_translation.csv");
    int l;
    cout << "\t欢迎使用英汉词典\t\n";
    cout << "\t     1.单词查找 \t\n";
    cout << "\t     2.查看收藏 \t\n";
    cout << "\t     3.删除单词 \t\n";
    cout << "\t     4.增加单词 \t\n";
    cout << "\t     5.退出   \n";
    cout << "=================================\n";
    //处理输入非数字 
    int m;
    while (true) {
        cout << "请输入选择的编号: ";
        l = CheckNum(m);
        if (l >= 1 && l <= 5) //限制是合规的选项 
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
        cout << "感谢您的使用，已退出！\n";
        exit(0);
    }
}
//判断输入的字符串是否为正整数，若是，则合规返归其值 ，否则给出提示 
int CheckNum(int& n)
{
    int i;
    string x;  //用来接受输入
    bool flag = false;
    while (cin >> x) {
        for (i = 0; i < x.size(); ++i) {
            //判断是否为中文
            if (x[i] & 0x80) {
                cout << "\n输入错误，请重新输入正确的数字: ";
                break;
            }
            //判断是否为字母或者其它字符
            if (!isdigit(x[i])) {
                cout << "\n输入错误，请重新输入正确的数字: ";
                break;
            }
        }
        if (i == x.size()) {
            break;   //如果字符串中所有字符都合法，则退出while循环
        }
    }
    n = atoi(x.c_str()); //将仅含数字的string字符串转化为正整数
    return n; //返回值 
}
void addToFavorites(const string& word, const string& translation) {
    if (favoritesSet[word]) {
        cout << "已收藏过该单词。" << endl;
        return;
    }
    ofstream favoritesFile("favorites.txt", ios::app);//有则打开，无则创建
    if (favoritesFile.is_open()) {
        favoritesFile << word << "," << translation << endl;
        favoritesFile.close();
        favoritesSet[word] = true;//将此单词的值设为true
        cout << "已将单词添加至收藏！" << endl;
    }
    else {
        cerr << "打开收藏夹失败！" << endl;
    }
}
void searchAndDisplayDefinition(const string& wordToSearch) {
    if (dictionary.find(wordToSearch) != dictionary.end()) {//查到最后一位
        cout << "单词: " << wordToSearch << endl;
        cout << "释义: " << dictionary[wordToSearch] << endl;
        char addToFavoritesChoice;
        cout << "要把单词加入收藏夹吗？(Y/N): ";
        cin >> addToFavoritesChoice;
        if (addToFavoritesChoice == 'Y' || addToFavoritesChoice == 'y') {
            addToFavorites(wordToSearch, dictionary[wordToSearch]);
        }
    }
    else {
        cout << "抱歉，词典中尚未收录该词。" << endl;
    }
    back_t_e();
}
void translation_e()
{
    string searchWord;
    cout << "请输入要查询的单词: ";
    cin >> searchWord;
    searchAndDisplayDefinition(searchWord);
}
void back_t_e()  //英译汉(查询单词)返回界面
{
    int l;
    cout << "\n1.继续";
    cout << "\n2.返回";
    cout << "\n=========================";
    cout << "\n请输入要执行的操作: ";
    //处理输入非数字 
    int m;
    while (true) {
        cout << "请输入选择的编号: ";
        l = CheckNum(m);
        if (l >= 1 && l <= 2) //限制是合规的选项 
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
void add()    //增加单词
{
    string word, translation;
    cout << "输入你想添加的单词: ";
    cin >> word;
    cout << "输入单词的释义: ";
    cin.ignore(); //会清除输入缓冲区中的任何剩余字符
    getline(cin, translation);//读取用户输入的一行字符串，并将其存储在translation变量中。这样做的目的是确保getline()能够读取用户输入的完整一行，而不受之前输入的影响。
    addToFavorites(word, translation);
    back_a();
}
void back_a()  //增加单词 返回界面
{
    int l;
    cout << "\n1.继续";
    cout << "\n2.返回";
    cout << "\n=========================";
    cout << "\n请输入要执行的操作: ";
    //处理输入非数字 
    int m;
    while (true) {
        cout << "请输入选择的编号: ";
        l = CheckNum(m);
        if (l >= 0 && l <= 2) //限制是合规的选项 
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
            cout << "单词: " << word << endl << "释义: " << translation << endl;
        }
        favoritesFile.close();
    }
    else {
        cerr << "打开文件失败！" << endl;
    }
    back_v();
}
void back_v()  //查看[列出]全部单词 返回界面
{
    int l;
    cout << "1.删除单词";
    cout << "\n2.返回";
    cout << "\n=========================";
    cout << "\n请输入要执行的操作: ";
    //cin >>l
    //处理输入非数字 
    int m;
    while (true) {
        cout << "请输入选择的编号: ";
        l = CheckNum(m);
        if (l >= 0 && l <= 2) //限制是合规的选项 
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
        cout << "[输入错误]请重新输入有效数字!\n";
        Sleep(3000);
        back_v();
        break;
    }
}
void remove_() //删除单词
{
    int flag = 1;
    string deleteWord;
    cout << "输入你想删除的单词：(输入0退出): ";
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
                    stringstream ss(line);//将一个字符串line转换为一个可以像流一样进行输入输出操作的对象。
                    string word, translation;//通过使用stringstream对象，我们可以方便地对字符串进行分割、提取和格式化等操作，就像对输入输出流一样操作。
                    getline(ss, word, ','); //用来解析line字符串中的内容，并按照逗号分隔提取出单词和翻译部分。读取的内容存储到word字符串中，直到遇到逗号为止
                    getline(ss, translation);
                    if (word != deleteWord) {
                        tempFile << word << "," << translation << endl;
                    }
                }
                favoritesFile.close();
                tempFile.close();
                remove("favorites.txt");
                rename("temp.txt", "favorites.txt");
                cout << "单词已从收藏夹中删除。" << endl;
                flag = 0;
            }
        }
    else
    {
        cout << "收藏夹中没有该词。" << endl;
    }
    back_r();
}
void back_r() //删除单词 返回界面
{
    int l;
    cout << "\n1.继续";
    cout << "\n2.返回";
    cout << "\n=========================";
    cout << "\n请输入要执行的操作: ";
    //处理输入非数字 
    int m;
    while (true) {
        cout << "请输入选择的编号: ";
        l = CheckNum(m);
        if (l >= 0 && l <= 2) //限制是合规的选项 
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