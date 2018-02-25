#ifndef TOOL_H
#define TOOL_H

#endif // TOOL_H

#include<vector>
#include"src/eventlog.h"
#include"src/eventgraph.h"
#include"src/managelog.h"
#include"src/managegraph.h"


bool isPrime(int M);

int MinPrime(int N);

int Value2Hash(int prime,int max,int ID);

vector<EventLog *> similarLog(manageLog * ManageLog,EventLog log);

vector<EventLog *> PriorNode(manageGraph * ManageGraph, manageLog * ManageLog, EventLog log);

vector<EventLog *> NextNode(manageGraph * ManageGraph, manageLog * ManageLog, EventLog log);

QString ResultStr(manageGraph * ManageGraph, manageLog * ManageLog, EventLog * log);
