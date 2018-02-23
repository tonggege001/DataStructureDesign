#include "managelog.h"
#include "tools/tool.h"
#include <vector>
#include <string>
#include<fstream>


manageLog::manageLog(){
    this->logNumber = 0;
    this->size = INIT_SIZE;
    this->prime = MinPrime(this->size);
    this->logs = (EventLog ** )malloc(sizeof(EventLog*)*INIT_SIZE);
    for(int i = 0;i<this->size;i++) logs[i] = NULL;
    LoadData();
}
manageLog::~manageLog(){
    for(int i = 0;i<this->size;i++){
        if(logs[i]!=NULL){
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
        while(logs[index]!=NULL){
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
        for(int i = 0;i<size+INCREMENT;i++) newlogs[i] = NULL;
        this->logs = newlogs;
        //产生最接近空间大小的素数
        this->prime = MinPrime(size+INCREMENT);
        //把Log从旧内存迁移到新内存
        for(int i = 0;i<size;i++){
            if(oldlogs[i]==NULL) continue;
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

EventLog * manageLog::getLog(int index){
    int id = index%prime;
    do{
        if(this->logs[id]==NULL){
            return NULL;
        }
        if(this->logs[id]->getID()==index){
            return this->logs[id];
        }
        id++;
        id %= prime;
    }while(true);
    return NULL;
}


/**
 * @brief manageLog::DeleteLog删除LOG
 * @param eventID 事件ID
 * @return 状态码
 */
bool manageLog::DeleteLog(int eventID){
    int id = eventID%prime;
    vector<int> *V;
    V = searchByID(id);//查找id
    //查找失败
    if(V==NULL) return false;
    id = V->back();
    delete V;//释放内存
    delete this->logs[id];
    this->logs[id] = NULL;
    logNumber--;
    return true;
}
bool manageLog::DeleteLog(string logName){
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=NULL&&
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
bool manageLog::DeleteLogbyRecordID(int eventRecordID){
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]->getEventRecordID()==eventRecordID){
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

vector<int> * manageLog::searchByID(int index){
    vector<int> * V = new vector<int>();
    int id = index%prime;
    do{
        if(this->logs[id]==NULL){
            delete V;
            return NULL;
        }
        if(this->logs[id]->getID()==index){
            V->push_back(id);
            return V;
        }
        id++;
        id %= prime;
    }while(true);
    return NULL;
}
/**
 * @brief 通过时间查询
 * @param 输入时间点
 * @return 返回一个log的队列
 */
vector<int> * manageLog::searchByTime(time_t time){
    vector<int> * V = new vector<int>();
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=NULL&&this->logs[i]->getTime()==time){
            V->push_back(i);
        }
    }
    return V;
}
/**
 * @brief 通过时间查询
 * @param low 时间下界
 * @param high上界
 * @return 消息队列
 */
vector<int> * manageLog::searchByTime(time_t low,time_t high){
    vector<int> * Q = new vector<int>();
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=NULL&&this->logs[i]->getTime()>=low
                &&this->logs[i]->getTime()<=high){
            Q->push_back(i);
        }
    }
    return Q;
}
/**
 * @brief 通过使用者查询
 * @param User 使用者字符串
 * @return 消息队列
 */
vector<int> * manageLog::searchByUser(string User){
    vector<int> * Q = new vector<int>();
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=NULL&&this->logs[i]->getUser()==User){
            Q->push_back(i);
        }
    }
    return Q;
}
vector<int> * manageLog::searchByRecordID(int id){
    vector<int> * Q = new vector<int>();
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=NULL&&this->logs[i]->getEventRecordID()==id){
            Q->push_back(i);
        }
    }
    return Q;
}
vector<int> * manageLog::searchByTaskType(int task){
    vector<int> * Q = new vector<int>();
    for(int i = 0;i<this->size;i++){
        if(this->logs[i]!=NULL&&this->logs[i]->getTaskType()==task){
            Q->push_back(i);
        }
    }
    return Q;
}


bool manageLog::modifyLog(int eventId,string logName,int sourceID,time_t occurTime,
                          int taskType,int classType,string User,
                                    int eventRecordID,int keyWord,string description){
    vector<int> * result;
    result = this->searchByID(eventId);
    int id = result->back();delete result;
    this->logs[id]->setLogName(logName);
    this->logs[id]->setSourceID(sourceID);
    this->logs[id]->setTime(occurTime);
    this->logs[id]->setTaskType(taskType);
    this->logs[id]->setClassType(classType);
    this->logs[id]->setUser(User);
    this->logs[id]->setEventRecordID(eventRecordID);
    this->logs[id]->setKeyWord(keyWord);
    this->logs[id]->setDescription(description);
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
        if(this->logs[i]!=NULL){
            outfile << *logs[i];
        }
    }
    outfile.close();
    return true;
}

