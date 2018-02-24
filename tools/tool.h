#ifndef TOOL_H
#define TOOL_H

#endif // TOOL_H

#include<vector>
#include"src/eventlog.h"
#include"src/managelog.h"
#include"src/managegraph.h"


bool isPrime(int M);

int MinPrime(int N);

int Value2Hash(int prime,int max,int ID);

vector<EventLog *> similarLog(manageLog * ManageLog,EventLog log);

vector<EventLog *> PriorNode(manageGraph * ManageGraph,EventLog log);
