#ifndef NOTIFICATION_QUEUE_H
#define NOTIFICATION_QUEUE_H

#include <string>
using namespace std;

const int maxNotif = 10;

struct NotifQueue {
   int top;
   string isi[maxNotif];
};

extern NotifQueue notif;

void createQueue();
int isEmptyQueue();
int isFullQueue();
void insertQueue(string data);
void deleteQueue();
void displayQueue();

#endif