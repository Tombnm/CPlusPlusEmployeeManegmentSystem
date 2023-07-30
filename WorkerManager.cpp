#include "Workermanager.h"
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"

WorkerManager::WorkerManager(){
    
    //文件不存在
    ifstream ifs;
    ifs.open(FILENAME,ios :: in);
    //判断是否打开成功
    if(!ifs.is_open()){
        cout<<"Files is not exit"<<endl;
        //初始化人数
        this->m_EmpNum=0;
        //初始化数组指针
        this->m_EmpArray=NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    
    //文件存在，数据为空
    char ch;
    //向右读入一个字符
    ifs >> ch;
    if(ifs.eof()){
        //文件为空
        cout<<"Files is empty"<<endl;
        //初始化人数
        this->m_EmpNum=0;
        //初始化数组指针
        this->m_EmpArray=NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件存在且保存职工数据
    int num = this->get_EmpNum();
    cout<<"There are "<<num<<" workers"<<endl;
    this->m_EmpNum=num;

    //开辟空间
    this->m_EmpArray = new Worker*[this->m_EmpNum];
    //将文件中的数据存到数组中
    this->init_Emp();

    //初始化文件是否为空
    this->m_FileIsEmpty = false;

    for(int i = 0;i < this->m_EmpNum;i++){
        cout<<" worker id "<<this->m_EmpArray[i]->m_Id
            <<" worker name "<<this->m_EmpArray[i]->m_Name
            <<" worker dId "<<this->m_EmpArray[i]->m_DeptId<<endl;
    }
}

//展示菜单
void WorkerManager::Show_Menu(){
    cout<<"**************************************************"<<endl;
    cout<<"*********Welcome to WorkerManager system**********"<<endl;
    cout<<"************0 Exit system*************************"<<endl;
    cout<<"************1 Add worker information**************"<<endl;
    cout<<"************2 Show worker information*************"<<endl;
    cout<<"************3 Delete worker information***********"<<endl;
    cout<<"************4 Change worker information***********"<<endl;
    cout<<"************5 Search worker information***********"<<endl;
    cout<<"************6 Sort by number of worker************"<<endl;
    cout<<"************7 Clean system************************"<<endl;
    cout<<"**************************************************"<<endl;
    cout<<endl;
}

//退出系统
void WorkerManager::ExitSystem(){
    cout<<"Welcome next use"<<endl;
    system("pause");
    exit(0);
}

//添加职工
void WorkerManager :: Add_emp(){
    cout<<"The number of employees added"<<endl;
    int AddNum = 0;
    cin>>AddNum;

    if(AddNum>0){
        //开始添加
        //计算新添加空间大小
        //空间大小等于原来的人数加添加的人数
        int NewSize = this -> m_EmpNum + AddNum;

        //开辟新空间
        Worker ** NewSpace = new Worker*[NewSize];

        //将原来空间下的数据拷贝到新空间下
        if(this -> m_EmpArray != NULL){
            for(int i = 0;i < this -> m_EmpNum;i++){
                NewSpace[i] = this -> m_EmpArray[i];
            }
        }
    //批量添加数据
    for(int i = 0;i < AddNum;i++){
        int id; //职工编号
        string name; //职工姓名
        int dSelect; //部门选择

        cout<<"Input the department number of "<< i+1 <<" worker"<<endl;
        cin>>id;
        cout<<"Input the name of "<< i+1 << " worker"<<endl;
        cin>>name;
        while(true){
            cout<<"Chose the position of "<< i+1 <<" worker"<<endl;
            cout<<"1 : worker"<<endl;
            cout<<"2 : manager"<<endl;
            cout<<"3 : boss"<<endl;
            cin>>dSelect;
            if(dSelect == 1 || dSelect == 2 || dSelect == 3){
                break;
            }
            else{
                cout<<"Input again"<<endl;
            }
        }
        Worker *worker = NULL;
        switch(dSelect){
            case 1:
            worker = new Employee(id,name,1);
            case 2:
            worker = new Manager(id,name,2);
            case 3:
            worker = new Boss(id,name,3);
        }
        
        //将创建的职工指针保存到数组中
        NewSpace[this -> m_EmpNum+i] = worker;
    }
    //释放原有的空间
    delete[] this->m_EmpArray;

    //更改新空间的指向
    this->m_EmpArray = NewSpace;

    //更新新的职工人数
    this->m_EmpNum = NewSize;

    //更新职工不为空的标志
    this->m_FileIsEmpty = false;

    //提示新添加成功
    cout<<"Successful added "<<AddNum<<" workers"<<endl;

     //保存文件
    this->Save();
    }
    else{
        cout<<"Error:The number of employees"<<endl;
    }

    //按任意键后清屏，回到上级目录
    system("pause");
    system("cls");
}

//保存文件
void WorkerManager :: Save(){
    ofstream ofs;
    ofs.open(FILENAME,ios :: out); //用输出的模式打开文件,写文件
    //将每个人的数据写入到文件中
    for(int i = 0;i < this->m_EmpNum;i++){
        ofs <<this->m_EmpArray[i]->m_Id<<" "
           <<this->m_EmpArray[i]->m_Name<<" "
           <<this->m_EmpArray[i]->m_DeptId<<" "<<endl;
    }
    //关闭文件
    ofs.close();
}

//统计文件中的人数
int WorkerManager :: get_EmpNum(){
    ifstream ifs;
    ifs.open(FILENAME,ios::in);//打开文件
    int id;
    string name;
    int dId;
    int num = 0;
    while(ifs >> id && ifs >> name && ifs >> dId){
        //统计人数变量
        num++;
    }
    return num;
}

//初始化员工
void WorkerManager :: init_Emp(){
    ifstream ifs;
    ifs.open(FILENAME,ios :: in);

    int  id;
    string name;
    int dId;
    int index = 0;
    while(ifs >> id && ifs >> name && ifs >> dId){
        Worker * worker =NULL;
        //普通职工
        if(dId == 1){
            worker = new Employee(id,name,dId);
        }
        //经理
        else if(dId == 2){
            worker = new Manager(id,name,dId);
        }
        //老板
        else{
            worker = new Boss(id,name,dId);
        }
        this->m_EmpArray[index]=worker;
        index++;
    }
    //关闭文件
    ifs.close();
}

//显示职工
void WorkerManager :: Show_Emp(){
    //判断文件是否为空
    if(this->m_FileIsEmpty){
        cout<<"File is not exist or empty"<<endl;
    }
    else{
        for(int i = 0;i < this->m_EmpNum;i++){
            //利用多态调用程序的接口
            this->m_EmpArray[i]->ShowInfro();
        }
    }
    //按任意键清屏
    system("pause");
    system("cls");
}

//判断职工是否存在,存在返回职工数组中所在位置，不存在返回-1
int WorkerManager :: IsExist_Emp(int id){
    int index = -1;
    for(int i = 0;i < this->m_EmpNum;i++){
        if(this->m_EmpArray[i]->m_Id == id){
            //找到职工
            index = i;
            break;
        }
    }
    return index;
}

//删除职工
void WorkerManager :: Del_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"File is not exist or empty"<<endl;
    }
    else{
        //按照职工编号删除职工
        cout<<"input id of delete worker"<<endl;
        int id = 0;
        cin >> id;
        int index = this->IsExist_Emp(id);
        if(index != -1){
            //职工存在且需要删除掉index位置的职工
            for(int i = index;i < this->m_EmpNum-1;i++){
                this->m_EmpArray[i]=this->m_EmpArray[i+1];
            }
            //更新数组中人员的个数
            this->m_EmpNum--;
            //同步更新到文件中
            this->Save();
            cout<<"delete successful"<<endl;
        }
        else{
            cout<<"This worker is not exist"<<endl;
        }
    }
    //按任意键清屏
    system("pause");
    system("cls");
}

//修改职工
void WorkerManager :: Mod_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"File is not exist or empty"<<endl;
    }
    else{
        cout<<"Input id of modify worker"<<endl;
        int id;
        cin >> id;
        int ret = this->IsExist_Emp(id);
        if(ret != -1){
            //查找到职工
            delete this->m_EmpArray[ret];

            int newId = 0;
            string newName="";
            int newdId = 0;

            cout<<"Find the worker id is : "<<id<<endl;

            cout<<"Input new id of the worker"<<endl;
            cin >>newId;
            cout<<"Input new name of the worker"<<endl;
            cin >>newName;
            cout<<"Input new Department number of the worker"<<endl;
            cout<<"1: worker  2: manager  3: boss"<<endl;
            cin >> newdId;

            Worker * worker = NULL;
            switch(newdId){
                case 1:
                worker = new Employee(newId,newName,newdId);
                break;
                case 2:
                worker = new Manager(newId,newName,newdId);
                break;
                case 3:
                worker = new Boss(newId,newName,newdId);
                break;
                default:
                break;
            }
            //更新数据，更新到数组中
            this->m_EmpArray[ret] = worker;

            cout<<"Modify successful"<<endl;

            //保存文件
            this->Save();
        }
        else{
            cout<<"Modify failed, this worker is not exist"<<endl;
        }
    }
    //任意键清屏
    system("pause");
    system("cls");
}

//查找职工
void WorkerManager :: Find_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"File is not exist or empty"<<endl;
    }
    else{
        cout<<"Input the key of finding"<<endl;
        cout<<"1 : id of worker"<<endl;
        cout<<"2 : name of worker"<<endl;
        int select = 0;
        cin >> select;
        if(select == 1){
            //按照编号查找
            cout<<"Input id of worker"<<endl;
            int id = 0 ;
            cin >> id;
            int ret = IsExist_Emp(id);
            if(ret != -1){
                //查找成功
                cout<<"Finding successful, the infromation of worler is here"<<endl;
                this->m_EmpArray[ret]->ShowInfro();
            }
            else{
                cout<<"Finding failed"<<endl;
            }
        }
        else if(select == 2){
            //按照姓名查找
            cout<<"Input name of worker"<<endl;
            string name ="";
            cin >>name;
            //加入判断是否查到的标志
            int flag = false;

            for(int i = 0;i < this->m_EmpNum;i++){
                if(this->m_EmpArray[i]->m_Name == name){
                    cout<<"Finding successful, the infromation of worler is here"<<endl;
                    this->m_EmpArray[i]->ShowInfro();
                    flag = true;
                }
            }
            if(flag == false){
                cout<<"Finding failed"<<endl;
            }
        }
        else{
            cout<<"Error of finding input"<<endl;
        }
    }
    //任意键清屏
    system ("pause");
    system("cls");
}

//排序员工
void WorkerManager :: Sort_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"File is not exist or empty"<<endl;
        //任意键清屏
        system("pause");
        system("cls");
    }
    else{
        cout<<"Chosing the way of sorting"<<endl;
        cout<<"1 : up of id"<<endl;
        cout<<"2 : down of id"<<endl;
        int select = 0;
        cin >> select;
        for(int i = 0;i < this->m_EmpNum;i++){
            //声明最小值或最大值下标
            int minOrmax = i;
            for(int j = i + 1;j < this->m_EmpNum; j++){
                //升序
                if(select == 1){
                    if(this->m_EmpArray[minOrmax]->m_Id > this->m_EmpArray[j]->m_Id){
                        minOrmax = j;
                    }
                }
                //降序
                else{
                    if(this->m_EmpArray[minOrmax]->m_Id < this->m_EmpArray[j]->m_Id){
                        minOrmax = j;
                    }
                }
            }
            if(i != minOrmax){
                Worker *tmp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrmax];
                this->m_EmpArray[minOrmax] = tmp;
            }
        }
    cout<<"Sort successful"<<endl;
    this->Save();
    }
    //展示结果
    this->Show_Emp();
    //任意键清屏
    system("pause");
    system("cls");
}

//清空文件
void WorkerManager :: Clean_Emp(){
    cout<<"Clean file ???"<<endl;
    cout<<"1 : Yes"<<endl;
    cout<<"2 : No"<<endl;

    int select = 0;
    cin >> select;
    if(select == 1){
        ofstream ofs(FILENAME,ios :: trunc);//删除文件后重新创建
        ofs.close();
        //删除堆区的对象
        if(this->m_EmpArray != NULL){
        for(int i = 0;i < this->m_EmpNum;i++){
            if(this->m_EmpArray[i] != NULL){
                delete this->m_EmpArray[i];
                this->m_EmpArray = NULL;
            }
        }
        }
        //删除堆区指针数组
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
        this->m_EmpNum = 0;
        this->m_FileIsEmpty = true;
        cout<<"Clean successful"<<endl;
        system ("pause");
        system("cls");
    }
    else{
        system ("pause");
        system("cls");
        return;
    }
}


//释放堆区开辟的数据
WorkerManager::~WorkerManager(){
    if(this->m_EmpArray != NULL){
        for(int i = 0;i < this->m_EmpNum;i++){
            if(this->m_EmpArray[i] != NULL){
                delete this->m_EmpArray[i];
            }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}