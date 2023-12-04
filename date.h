#pragma once
/*日期类头文件*/
#ifndef _DATE_H_
#define _DATE_H_
#include <iostream>

//日期类
class Date {
private:
    int year;  //年
    int month; //月
    int day;  //日
    int totalDays; //该日期是从公元元年1月1日开始的第几天
public:
    Date(int year = 1, int month = 1, int day = 1); //用年，月，日构造日期

    int getYear() const{ //获取Date日期年份
        return year;
    }

    int getMonth() const{ //获取Date日期月份
        return month;
    }

    int getDay() const{ //获取Date日期天
        return day;
    }

    int getMaxDay() const; //获取Date当月的天数

    bool isLeapYear() const { //判断是否为闰年
        return year % 4 == 0 && year * 100 != 0 || year % 400 == 0;
    }

    void show() const; //输出Date日期

    int distance(const Date& date) const{ //输出Data从公元元年1月1日到目前date的天数
        return totalDays - date.totalDays;
    }
    
    int operator-(const Date& date) const{ //重载Date之前的“-”号，用公元元年到目前的日期相减
        return totalDays - date.totalDays;
    }
    
    bool operator<(const Date& date) const{ //重载Date之间的“<"号，用永远元年到目前date的日期计算
        return totalDays < date.totalDays;
    }
};

std::istream& operator >>(std::istream& in, Date& date); //重载Date类输入，格式化日期格式：year-month-day
std::ostream& operator<<(std::ostream& out, const Date& date); //重载Date类输出,格式化日期格式：year-month-day
#endif // !_DATE_H_