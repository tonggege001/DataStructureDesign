#include "eventlog.h"
#include <string>
/**
 * @brief EventLog::EventLog
 * @param ID事件ID
 */
EventLog::EventLog(int ID)
{
    this->eventID = ID;
    this->classType = 0;
    this->eventRecordID = -1;
    this->keyWord = 0;
    this->logName = nullptr;
    this->sourceID = 0;
    this->occurTime = 0;
    this->taskType = 0;
    this->User = nullptr;
    this->description = nullptr;
}
EventLog::EventLog(string logName,int sourceID,time_t occurTime,
         int eventID,int taskType,int classType,string User,
                   int eventRecordID,int keyWord,string description){
    this->eventID = eventID;
    this->classType = classType;
    this->eventRecordID = eventRecordID;
    this->keyWord = keyWord;
    this->logName = *new string(logName.data());
    this->sourceID = sourceID;
    this->occurTime = occurTime;
    this->taskType = taskType;
    this->User = *new string(User.data());
    this->description = *new string(description.data());
}

EventLog::~EventLog(){
    delete &this->logName;
    delete &this->User;
    delete &this->description;
}
















































