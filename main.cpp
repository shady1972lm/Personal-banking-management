#include "account.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//释放空间结构体，用于析构函数
struct deleter {
    template<class T>void operator() (T* p) {
        delete p;
    }
};

//建立类，用来存储账户列表和处理命令
class Controller {
private:
    Date date;  //当前日期
    vector<Account*>accounts; //账户列表
    bool end;  //用户是够输入了退出命令
public:
    //存储用户数据，参数:Date时间
    Controller(const Date& date) :date(date), end(false) {}
    //析构函数
    ~Controller();
    //返回当前的时间
    const Date& getDate() const {
        return date;
    }
    //bool值，返回是否结束
    bool isEnd() const {
        return end;
    }
    //执行一条命令，返回该命令是否改变了当前状态(即是否需要保存该命令)
    bool runCommand(const string& cmdLine);
};

//释放从账户开始到结束的所有内存
Controller::~Controller()
{
    //for_each遍历:开始，结束，执行
    //按照顺序应用给定的函数对象f到接引到范围[first,last]中每个迭代器的结果
    for_each(accounts.begin(), accounts.end(), deleter());
}
bool Controller::runCommand(const string& cmdLine)
{
    //读取是有顺序要求的，根据指针向后，异常赋值
    //第一个赋值给cmd判断进入那个case开面
    //后面根据不同case依次赋值
    istringstream str(cmdLine);
    char cmd, type;
    int index, day;
    double amount, credit, rate, fee;
    string id, desc;
    Account* account;
    Date date1, date2;
    str >> cmd;
    switch (cmd) {
    case 'a':   //增加账户
        str >> type >> id;
        if (type == 's') {
            str >> rate;
            account = new SavingsAccount(date, id, rate);
        }
        else {
            str >> credit >> rate >> fee;
            account = new CreditAccount(date, id, credit, rate, fee);
        }
        accounts.push_back(account);
        return true;
    case 'd':   //存入现金
        str >> index >> amount;
        getline(str, desc);
        accounts[index]->deposit(date, amount, desc);
        return true;
    case 'w':   //取出现金
        str >> index >> amount;
        getline(str, desc);
        accounts[index]->withdraw(date, amount, desc);
        return true;
    case 's':   //查询各账户信息
        for (size_t i = 0; i < accounts.size(); i++)
            cout << "[" << i << "] " << *accounts[i] << endl;
        return false;
    case 'c':   //改变日期
        str >> day;
        if (day < date.getDay())
            cout << "You cannot specify a previous day";
        else if (day > date.getMaxDay())
            cout << "Invalid day";
        else
            date = Date(date.getYear(), date.getMonth(), day);
        return true;
    case 'n':   //进入下个月
        if (date.getMonth() == 12)
            date = Date(date.getYear() + 1, 1, 1);
        else
            date = Date(date.getYear(), date.getMonth() + 1, 1);
        for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
            (*iter)->settle(date);
        return true;
    case 'q':   //查询一段时间内的账目
        str >> date1 >> date2;
        Account::query(date1, date2);
        return false;
    case 'e':   //退出
        end = true;
        return false;
    }
    cout << "Inavlid command: " << cmdLine << endl;
    return false;
}

int main(void) {
    Date date(2008, 11, 1); //起始日期
    //  初始化命令
    Controller controller(date);
    string cmdLine;
    //打开文件名称
    const char* FILE_NAME = "commands.txt";
    ifstream fileIn(FILE_NAME); //以读模式打开文件

    if (fileIn) { //直到执行到没有指令
        while (getline(fileIn, cmdLine)) {
            try {
                controller.runCommand(cmdLine);
            }
            catch (exception& e) {
                cout << "Bad line in" << FILE_NAME << ":" << cmdLine << endl;
                cout << "Error:" << e.what() << endl;
                return 1;
            }
        }

        fileIn.close(); //关闭文件
    }
    //初始化指令结束

    //追加模式写入
    ofstream fileOut(FILE_NAME, ios_base::app); //以追加模式
    cout << "(a) add acount  (d) deposit  (w) withdrow  (s) show  (c) change day  (n) next month  (q) query  (e) exit" << endl;
    while (!controller.isEnd()) {   //从标准输入读入命令并执行，直到退出
        cout << controller.getDate() << "\tTotal: " << Account::getTotal() << "\tcommand> ";
        string cmdLine;
        //读入命令，和文件存储格式相同
        getline(cin, cmdLine);
        try {
            //执行命令
            if (controller.runCommand(cmdLine))
                //并记录文件内容
                fileOut << cmdLine << endl; //将命令写入文件
        }
        catch (AccountException& e) {
            cout << "Erroe(#" << e.getAccount()->getId() << "):" << e.what() << endl;
        }
        catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    }
    return 0;
}