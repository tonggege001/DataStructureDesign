#include "managelog.h"
#include "tools/tool.h"
#include <queue>
#include <string>
#include<fstream>


manageLog::manageLog(){
    this->logNumber = 0;
    this->size = INIT_SIZE;
    this->prime = MinPrime(this->size);
    this->logs = (EventLog ** )malloc(sizeof(EventLog*)*INIT_SIZE);
    for(int i = 0;i<INIT_SIZE-1;i++) logs[i] = nullptr;
    LoadData();
}
manageLog::~manageLog(){
    SaveData();
    for(int i = 0;i<this->size;i++){
        if(logs[i]!=nullptr){
            delete logs[i];
        }
    }
    free(this->logs);
}
/**
 * @brief manageLog::AddLog 增加事件
 * @param e 事件指针e
 * @return 状态码
 */
bool manageLog::AddLog(EventLog *e){
    //如果空间还有地址，那么对哈希表进行重排
    //哈希表采用线性探测再散列方式
    if(size>logNumber){
        int index = e->getID();
        index %= prime;
        while(logs[index]!=nullptr){
            if(logs[index]->getID()==e->getID()) return false;
            index++;
            index %= prime;
        }
        logs[index] = e;
        logNumber++;
    }
    else{
        //否则先重新分配内存，然后重排哈希表，再加入元素
        EventLog ** oldlogs = this->logs;
        EventLog ** newlogs;
        //重新分配内存
        newlogs = (EventLog **)malloc((this->size+INCREMENT)*sizeof(EventLog*));
        if(!newlogs) return false;
        for(int i = 0;i<size+INCREMENT;i++) newlogs[i] = nullptr;
        this->logs = newlogs;
        //产生最接近空间大小的素数
        this->prime = MinPrime(size+INCREMENT);
        //把Log从旧内存迁移到新内存
        for(int i = 0;i<size;i++){
            if(oldlogs[i]==nullptr) continue;
            int id = oldlogs[i]->getID();
            id %= prime;
            while(newlogs[id]){
                if(newlogs[id]->getID()==e->getID()) return false;
                id++;
                id %= prime;
            }
            newlogs[id] = oldlogs[i];
        }
        free(oldlogs);//释放原有的空间
        size += INCREMENT;//空间大小增加
        //进行插入元素
        int id = e->getID();
        id %= prime;
        while(newlogs[id]){
            id++;
            id = id % prime;
        }
        newlogs[id] = e;
        logNumber++;
    }
    return true;
}
/**
 * @brief manageLog::DeleteLog删除LOG
 * @param eventID 事件ID
 * @return 状态码
 */
bool manageLog::DeleteLog(int eventID){
    int id = eventID%prime;
    id = searchByID(id);//查找id
    //如果是空指针
    if(id==-1) return false;
    else{
        delete this->logs[id];
        this->logs[id] = nullptr;
        logNumber--;
        return true;
    }
}
bool manageLog::DeleteLog(string logName){
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=nullptr&&
                this->logs[i]->getLogName()==logName){
            if(!DeleteLog(this->logs[i]->getID())){
                return false;
            }
            else{
                logNumber--;
            }
        }
    }
    return true;
}
bool manageLog::DeleteLogbySourceID(int sourceID){
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]->getSourceID()==sourceID){
            if(!DeleteLog(logs[i]->getID())){
                return false;
            }
            else{
                logNumber--;
            }
        }
    }
    return true;
}
bool DeleteLogbyRecordID(int eventRecordID);

int manageLog::searchByID(int index){
    int id = index%prime;
    do{
        if(this->logs[id]==nullptr) return -1;
        if(this->logs[id]->getID()==index) return id;
        id++;
        id %= prime;
    }while(true);
    return -1;
}
/**
 * @brief 通过时间查询
 * @param 输入时间点
 * @return 返回一个log的队列
 */
queue<int> & manageLog::searchByTime(time_t time){
    queue<int> & Q = *new queue<int>();
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=nullptr&&this->logs[i]->getTime()==time){
           Q.push(i);
        }
    }
    return Q;
}
/**
 * @brief 通过时间查询
 * @param low 时间下界
 * @param high上界
 * @return 消息队列
 */
queue<int> & manageLog::searchByTime(time_t low,time_t high){
    queue<int> & Q = *new queue<int>();
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=nullptr&&this->logs[i]->getTime()>=low
                &&this->logs[i]->getTime()<=high){
            Q.push(i);
        }
    }
    return Q;
}
/**
 * @brief 通过使用者查询
 * @param User 使用者字符串
 * @return 消息队列
 */
queue<int> & manageLog::searchByUser(string User){
    queue<int> & Q = *new queue<int>();
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=nullptr&&this->logs[i]->getUser()==User){
            Q.push(i);
        }
    }
    return Q;
}
queue<int> & manageLog::searchByRecordID(int id){
    queue<int> & Q = *new queue<int>();
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=nullptr&&this->logs[i]->getEventRecordID()==id){
            Q.push(i);
        }
    }
    return Q;
}
queue<int> & manageLog::searchByTaskType(int task){
    queue<int> & Q = *new queue<int>();
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=nullptr&&this->logs[i]->getTaskType()==task){
            Q.push(i);
        }
    }
    return Q;
}


bool modifyLog(int eventId){
    int a = eventId;
    return true;
}

bool manageLog::LoadData(){
    std::ifstream infile("EventLog");
    if(!infile.is_open()) return false;
    EventLog * newlog;
    do{
        newlog = new EventLog(1);
        infile >> *newlog;
        if(infile.eof()) {
            delete newlog;
            break;
        }
        else{
            this->AddLog(newlog);
        }
    }while(true);
    infile.close();
    return true;
}

bool manageLog::SaveData(){
    std::ofstream outfile("EventLog");
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=nullptr&&this->logs[i]->tag==1){
            outfile << *logs[i];
        }
    }
    outfile.close();
    return true;
}

