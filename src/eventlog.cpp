#include "eventlog.h"
#include <string>
#include<ostream>
#include<istream>
/**
 * @brief EventLog::EventLog 构造函数
 * @param ID事件ID
 */
EventLog::EventLog(int ID)
{
    this->eventID = ID;
    this->classType = 0;
    this->eventRecordID = 0;
    this->keyWord = 0;
    this->logName = NULL;
    this->sourceID = 0;
    this->occurTime = 0;
    this->taskType = 0;
    this->User = NULL;
    this->description = NULL;
    this->tag = 0;
}
/**
 * @brief 构造函数
 * @param logName 日志名称
 * @param sourceID 发生进程的ID
 * @param occurTime 发生时间
 * @param eventID 事件ID
 * @param taskType任务类型
 * @param classType任务等级
 * @param User 使用者
 * @param eventRecordID 事件记录ID
 * @param keyWord 关键字
 * @param description 描述
 */
EventLog::EventLog(string logName,int sourceID,time_t occurTime,
         int eventID,int taskType,int classType,string User,
                   int eventRecordID,int keyWord,string description){
    this->eventID = eventID;
    this->classType = classType;
    this->eventRecordID = eventRecordID;
    this->keyWord = keyWord;
    this->logName = new string(logName.data());
    this->sourceID = sourceID;
    this->occurTime = occurTime;
    this->taskType = taskType;
    this->User = new string(User.data());
    this->description = new string(description.data());
    this->tag = 0;
}

/**
 * @brief EventLog::~EventLog 析构函数
 *                              将所分配的空间都释放
 */
EventLog::~EventLog(){
    if(this->logName!=NULL) delete this->logName;
    if(this->logName!=NULL) delete this->User;
    if(this->logName!=NULL) delete this->description;
}

std::ostream & operator<<(std::ostream & out  , EventLog & log ){
     out << *log.logName <<' '<< log.sourceID<<' '<<log.occurTime<<' '<<log.eventID<<' '<<
           ' '<<log.taskType<<' '<<log.classType<<' '<<*log.User<<' '
        <<log.eventRecordID<<' '<<log.keyWord<<' '<<*log.description<<' ';
     return out;
}

std::istream &operator>>(std::istream & input , EventLog &log){
    string * logname = new string();
    string * User = new string();
    string * Description = new string();
    input >> *logname>>log.sourceID>>log.occurTime>>log.eventID>>log.taskType
            >>log.classType>>*User>>log.eventRecordID>>
            log.keyWord>>*Description;
    log.logName = logname;
    log.User = User;
    log.description = Description;
    return input;
}














































