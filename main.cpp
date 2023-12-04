#include "account.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//�ͷſռ�ṹ�壬������������
struct deleter {
    template<class T>void operator() (T* p) {
        delete p;
    }
};

//�����࣬�����洢�˻��б�ʹ�������
class Controller {
private:
    Date date;  //��ǰ����
    vector<Account*>accounts; //�˻��б�
    bool end;  //�û��ǹ��������˳�����
public:
    //�洢�û����ݣ�����:Dateʱ��
    Controller(const Date& date) :date(date), end(false) {}
    //��������
    ~Controller();
    //���ص�ǰ��ʱ��
    const Date& getDate() const {
        return date;
    }
    //boolֵ�������Ƿ����
    bool isEnd() const {
        return end;
    }
    //ִ��һ��������ظ������Ƿ�ı��˵�ǰ״̬(���Ƿ���Ҫ���������)
    bool runCommand(const string& cmdLine);
};

//�ͷŴ��˻���ʼ�������������ڴ�
Controller::~Controller()
{
    //for_each����:��ʼ��������ִ��
    //����˳��Ӧ�ø����ĺ�������f����������Χ[first,last]��ÿ���������Ľ��
    for_each(accounts.begin(), accounts.end(), deleter());
}
bool Controller::runCommand(const string& cmdLine)
{
    //��ȡ����˳��Ҫ��ģ�����ָ������쳣��ֵ
    //��һ����ֵ��cmd�жϽ����Ǹ�case����
    //������ݲ�ͬcase���θ�ֵ
    istringstream str(cmdLine);
    char cmd, type;
    int index, day;
    double amount, credit, rate, fee;
    string id, desc;
    Account* account;
    Date date1, date2;
    str >> cmd;
    switch (cmd) {
    case 'a':   //�����˻�
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
    case 'd':   //�����ֽ�
        str >> index >> amount;
        getline(str, desc);
        accounts[index]->deposit(date, amount, desc);
        return true;
    case 'w':   //ȡ���ֽ�
        str >> index >> amount;
        getline(str, desc);
        accounts[index]->withdraw(date, amount, desc);
        return true;
    case 's':   //��ѯ���˻���Ϣ
        for (size_t i = 0; i < accounts.size(); i++)
            cout << "[" << i << "] " << *accounts[i] << endl;
        return false;
    case 'c':   //�ı�����
        str >> day;
        if (day < date.getDay())
            cout << "You cannot specify a previous day";
        else if (day > date.getMaxDay())
            cout << "Invalid day";
        else
            date = Date(date.getYear(), date.getMonth(), day);
        return true;
    case 'n':   //�����¸���
        if (date.getMonth() == 12)
            date = Date(date.getYear() + 1, 1, 1);
        else
            date = Date(date.getYear(), date.getMonth() + 1, 1);
        for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
            (*iter)->settle(date);
        return true;
    case 'q':   //��ѯһ��ʱ���ڵ���Ŀ
        str >> date1 >> date2;
        Account::query(date1, date2);
        return false;
    case 'e':   //�˳�
        end = true;
        return false;
    }
    cout << "Inavlid command: " << cmdLine << endl;
    return false;
}

int main(void) {
    Date date(2008, 11, 1); //��ʼ����
    //  ��ʼ������
    Controller controller(date);
    string cmdLine;
    //���ļ�����
    const char* FILE_NAME = "commands.txt";
    ifstream fileIn(FILE_NAME); //�Զ�ģʽ���ļ�

    if (fileIn) { //ֱ��ִ�е�û��ָ��
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

        fileIn.close(); //�ر��ļ�
    }
    //��ʼ��ָ�����

    //׷��ģʽд��
    ofstream fileOut(FILE_NAME, ios_base::app); //��׷��ģʽ
    cout << "(a) add acount  (d) deposit  (w) withdrow  (s) show  (c) change day  (n) next month  (q) query  (e) exit" << endl;
    while (!controller.isEnd()) {   //�ӱ�׼����������ִ�У�ֱ���˳�
        cout << controller.getDate() << "\tTotal: " << Account::getTotal() << "\tcommand> ";
        string cmdLine;
        //����������ļ��洢��ʽ��ͬ
        getline(cin, cmdLine);
        try {
            //ִ������
            if (controller.runCommand(cmdLine))
                //����¼�ļ�����
                fileOut << cmdLine << endl; //������д���ļ�
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