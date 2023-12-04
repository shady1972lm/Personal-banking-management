#pragma once
/*������ͷ�ļ�*/
#ifndef _DATE_H_
#define _DATE_H_
#include <iostream>

//������
class Date {
private:
    int year;  //��
    int month; //��
    int day;  //��
    int totalDays; //�������Ǵӹ�ԪԪ��1��1�տ�ʼ�ĵڼ���
public:
    Date(int year = 1, int month = 1, int day = 1); //���꣬�£��չ�������

    int getYear() const{ //��ȡDate�������
        return year;
    }

    int getMonth() const{ //��ȡDate�����·�
        return month;
    }

    int getDay() const{ //��ȡDate������
        return day;
    }

    int getMaxDay() const; //��ȡDate���µ�����

    bool isLeapYear() const { //�ж��Ƿ�Ϊ����
        return year % 4 == 0 && year * 100 != 0 || year % 400 == 0;
    }

    void show() const; //���Date����

    int distance(const Date& date) const{ //���Data�ӹ�ԪԪ��1��1�յ�Ŀǰdate������
        return totalDays - date.totalDays;
    }
    
    int operator-(const Date& date) const{ //����Date֮ǰ�ġ�-���ţ��ù�ԪԪ�굽Ŀǰ���������
        return totalDays - date.totalDays;
    }
    
    bool operator<(const Date& date) const{ //����Date֮��ġ�<"�ţ�����ԶԪ�굽Ŀǰdate�����ڼ���
        return totalDays < date.totalDays;
    }
};

std::istream& operator >>(std::istream& in, Date& date); //����Date�����룬��ʽ�����ڸ�ʽ��year-month-day
std::ostream& operator<<(std::ostream& out, const Date& date); //����Date�����,��ʽ�����ڸ�ʽ��year-month-day
#endif // !_DATE_H_