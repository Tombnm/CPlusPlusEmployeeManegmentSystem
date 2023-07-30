#include "Boss.h"

//构造函数
Boss :: Boss(int id,string name,int dId){
this->m_Id=id;
this->m_Name=name;
this->m_DeptId=dId;
}

//显示个人信息
void Boss :: ShowInfro(){
cout<<"DeptId: "<<this->m_Id
        <<"\tName: "<<this->m_Name
        <<"\tPosition: "<<this->getDeptName()
        <<"\tPositionDuty: Manage company affairs "<<endl;
}

//获取岗位名称
string Boss :: getDeptName(){
    return string ("Boss");
}