#include <iostream>
using namespace std;
#include "WorkerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

int main(){

// //测试代码
// Worker * worker=NULL;
// worker = new Employee(1,"AAA",1);
// worker->ShowInfro();
// delete worker;

// worker = new Manager(2,"BBB",2);
// worker->ShowInfro();
// delete worker;

// worker = new Boss(3,"CCC",3);
// worker->ShowInfro();
// delete worker;



//实例化一个对象
WorkerManager wm;

int choice=0;//用来记录用户的选择



while(true){
    //展示菜单
    wm.Show_Menu();

    cout<<"input your choice"<<endl;
    cin>>choice;//接受用户的选项

    switch(choice){
        case 0: //退出系统
        wm.ExitSystem();
        break;
        case 1: //增加职工
        wm.Add_emp();
        break;
        case 2: //显示职工
        wm.Show_Emp();
        break;
        case 3: //删除职工
        wm.Del_Emp();
        break;
        case 4: //修改职工
        wm.Mod_Emp();
        break;
        case 5: //查找职工
        wm.Find_Emp();
        break;
        case 6: //排序职工
        wm.Sort_Emp();
        break;
        case 7: //清空文档
        wm.Clean_Emp();
        break;
        default:
        system("cls");
        break;
    }
}
    system("pause");
    return 0;
}