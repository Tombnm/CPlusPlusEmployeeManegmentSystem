#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
#include <fstream>
#define FILENAME "empFile.txt"

class WorkerManager
{
public:
//构造函数
WorkerManager();

//展示菜单
void Show_Menu();

//退出系统
void ExitSystem();

//记录职工人数
int m_EmpNum;

//职工数组指针
Worker ** m_EmpArray;

//添加职工
void Add_emp();

//保存文件
void Save();

//判断文件是否为空
bool m_FileIsEmpty;

//统计文件中的人数
int get_EmpNum();

//初始化员工
void init_Emp();

//显示职工
void Show_Emp();

//判断职工是否存在,存在返回职工数组中所在位置，不存在返回-1
int IsExist_Emp(int id);

//删除职工
void Del_Emp();

//修改职工
void Mod_Emp();

//查找职工
void Find_Emp();

//排序员工
void Sort_Emp();

//清空文件
void Clean_Emp();

//析构函数
~WorkerManager();

};