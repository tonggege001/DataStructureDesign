#ifndef MANAGELOG_H
#define MANAGELOG_H
#include"eventlog.h"
#include"tools/linkedlist.h"
#include<queue>
using std::queue;

namespace LOG {
    class manageLog;
}
class manageLog
{   
public:
    static const int INIT_SIZE = 100;
    static const int INCREMENT = 50;
    int logNumber;
    int size;
    int prime;
    EventLog **logs;

    manageLog();
    ~manageLog();

    bool AddLog(EventLog *e);

    bool DeleteLog(int eventID);
    bool DeleteLog(string logName);
    bool DeleteLogbySourceID(int sourceID);
    bool DeleteLogbyRecordID(int eventRecordID);

    int searchByID(int index);
    queue<int> & searchByTime(time_t time);
    queue<int> & searchByTime(time_t low,time_t high);
    queue<int> & searchByUser(string User);
    queue<int> & searchByRecordID(int id);
    queue<int> & searchByTaskType(int task);

    bool modifyLog(int eventId);

    bool LoadData();
    bool SaveData();
};

#endif // MANAGELOG_H
