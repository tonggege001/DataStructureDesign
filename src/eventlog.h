#ifndef EVENTLOG_H
#define EVENTLOG_H
#include <string>
#include<ctime>
#include<ostream>
#include<istream>

using std::string;

namespace LOG {
class EventLog;
}
class EventLog
{
private:
    string *logName; //日志名称
    int sourceID;//日志来源
    time_t occurTime;//发生时间
    int eventID;//事件ID
    int taskType;//任务类别（客体）
    int classType;//级别
    string *User;//发生事件的用户（主体）
    int eventRecordID;//出现问题的进程ID
    int keyWord;
    string *description;//事件的描述


public:
    int tag=0;//标志域
    EventLog(int ID);
    EventLog(string logName,int sourceID,time_t occurTime,
             int eventID,int taskType,int classType,string User,
             int eventRecordID,int keyWord,string description);
    ~EventLog();
    int getID(){return this->eventID;}

    string getLogName(){return *this->logName;}

    int setLogName(string name){
        if(name.length()!=0){
            delete this->logName;
            this->logName = new string(name.data());
            return 1;
        }
        else{
            return 0;
        }
    }

    bool setLogName(char name[]){
        delete this->logName;
        this->logName = new string(name);
        return true;
    }

    int getSourceID(){return this->sourceID;}

    bool setSourceID(int id){
        this->sourceID = id;
        return true;
    }

    time_t getTime(){return occurTime;}

    bool setTime(time_t time){
        if(time >0){this->occurTime = time; return true;}
        else return false;
    }

    int getTaskType(){return this->taskType;}
    bool setTaskType(int type){
        this->taskType = type;
        return true;
    }

    int getClassType(){return this->classType;}
    bool setClassType(int type){
        this->classType = type;
        return true;
    }

    string getUser(){
        return *this->User;
    }
    bool setUser(string name){
        delete this->User;
        this->User = new string(name.data());
        return true;
    }

    int getEventRecordID(){return this->eventRecordID;}
    bool setEventRecordID(int id){this->eventRecordID = id;return true;}

    int getKeyWord(){return this->keyWord;}
    bool setKeyWord(int key){this->keyWord = key;return true;}

    string getDescription(){
        return *this->description;
    }
    bool setDescription(string des){
        delete this->description;
        this->description = new string(des.data());
        return true;
    }

    friend std::ostream &operator<<(std::ostream & , EventLog &);
    friend std::istream &operator>>(std::istream & , EventLog &);
};

#endif // EVENTLOG_H















