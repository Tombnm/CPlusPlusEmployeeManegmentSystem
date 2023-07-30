using namespace std;
#include "employee.h"

//构造函数
Employee :: Employee(int Id,string Name,int DId){
    this->m_Id=Id;
    this->m_Name=Name;
    this->m_DeptId=DId;
}

//显示个人信息
void Employee :: ShowInfro(){
    cout<<"DeptId: "<<this->m_Id
        <<"\tName: "<<this->m_Name
        <<"\tPosition: "<<this->getDeptName()
        <<"\tPositionDuty: Fnish job of manager"<<endl;
}

//获取岗位名称
string Employee :: getDeptName(){
    return string ("Worker");
}