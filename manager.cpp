#include "manager.h"

//构造函数
Manager :: Manager(int id,string name,int dId){
this->m_Id=id;
this->m_Name=name;
this->m_DeptId=dId;
}

//显示个人信息
void Manager :: ShowInfro(){
cout<<"DeptId: "<<this->m_Id
        <<"\tName: "<<this->m_Name
        <<"\tPosition: "<<this->getDeptName()
        <<"\tPositionDuty: Fnish job of Boss and distribute job to employee "<<endl;
}

//获取岗位名称
string Manager :: getDeptName(){
    return string ("Manager");
}