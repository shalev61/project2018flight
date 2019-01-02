#include <mutex>
#include "Clock.h"
#include <unordered_map>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>
#include <list>
#include <sys/ioctl.h>
#include <vector>
#include <netdb.h>
#include <set>
#include <sstream>
#include <cmath>

#include <chrono>
//using namespace std::chrono;
//#include "../time.h"
//#include "../utils.h"

using namespace std;

#ifndef DATASERVER_H
#define DATASERVER_H


typedef unordered_map<string, double> ValuesMap;


/**
*
* list definition
*
**/
class listKey {

    mutex key;
    list<int> filedes;

public:

    void addFd(int numf) {
        key.lock();
        filedes.push_back(numf);
        key.unlock();
    }

    void closeFds() {
        key.lock();
        for (int& num : filedes) {
            close(num);
        }
        filedes.clear();
        key.unlock();
    }

    int count() {
        key.lock();
        int sum = filedes.size();
        key.unlock();
        return sum;
    }

};

class DataServer {
private:
    int serverfd;
    int clientfd;
    pthread_t threadId;

    ValuesMap values;

    bool isOpen;

    int port;
    int hz;
public:
    DataServer(int port, int hz) : port(port), hz(hz), isOpen(false) {
    }

    double getValue(const string& path) {
        return values.at(path);
    }

    bool openServer();

    void closeServer() {
        if (!isOpen) {
            return;
        }

        close(clientfd);
        close(serverfd);
        pthread_join(threadId, NULL);
        isOpen = false;
    }

    ~DataServer() {
        closeServer();
    }
};


class DataClient {
    listKey fdClients;
    string strFd;
    int clientPort;
    int sockfd;

public:

    void openClient();
    void send(const string& way, double data);

    DataClient(int port, const string& remoteIp) : strFd(remoteIp), sockfd(-1), clientPort(port) { }

    bool areYouOpen();
    void close();

    ~DataClient() {
        close();
    }

};



class UserData {
    DataClient* clientFileDescription;
    DataServer* serverFileDescription;

public:

    UserData() : serverFileDescription(nullptr), clientFileDescription(nullptr) { }

    void openDataClient(int port, const string& remoteIp);
    void openDataServer(int port, int hz);
    void closeTheClient();
    void closeTheServer();

    void setValue(const string& way, double val) { clientFileDescription->send(way, val); }

    double getValue(const string& str) const { return serverFileDescription->getValue(str); }

    void closeAllMembers();

    ~UserData() {
        closeAllMembers();
    }

};

#endif
