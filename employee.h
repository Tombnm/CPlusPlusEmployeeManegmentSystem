//普通员工
#pragma once;
#include <iostream>
using namespace std;
#include "Worker.h"

class Employee:public Worker{
public:

//构造函数
Employee(int Id,string Name,int DId);

//显示个人信息
virtual void ShowInfro();

//获取岗位名称
virtual string getDeptName();

};