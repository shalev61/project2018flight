#include "DataServer.h"

#include <iostream>
#include <cmath>
#include <netinet/in.h>
#include <string.h>
#include <list>
#include <sys/fcntl.h>


int createServer(int port) {
    int sockfd;
    struct sockaddr_in serv_addr;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        return -1;
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        return -1;
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    if (listen(sockfd, 5) < 0) {
        perror("ERROR on listening.");
        return -1;
    }

    return sockfd;
}

int connectClient(int sockfd) {
    int clientfd = accept(sockfd, NULL, 0);

    if (clientfd < 0) {
        perror("ERROR accepting client.");
        return -1;
    }

    return clientfd;
}

// /controls/flight/rudder
// get . ==> value
// set . a ==> . = a

list<string> paths{
        "/instrumentation/airspeed-indicator/indicated-speed-kt",
        "/instrumentation/altimeter/indicated-altitude-ft",
        "/instrumentation/altimeter/pressure-alt-ft",
        "/instrumentation/attitude-indicator/indicated-pitch-deg",
        "/instrumentation/attitude-indicator/indicated-roll-deg",
        "/instrumentation/attitude-indicator/internal-pitch-deg",
        "/instrumentation/attitude-indicator/internal-roll-deg",
        "/instrumentation/encoder/indicated-altitude-ft",
        "/instrumentation/encoder/pressure-alt-ft",
        "/instrumentation/gps/indicated-altitude-ft",
        "/instrumentation/gps/indicated-ground-speed-kt",
        "/instrumentation/gps/indicated-vertical-speed",
        "/instrumentation/heading-indicator/indicated-heading-deg",
        "/instrumentation/magnetic-compass/indicated-heading-deg",
        "/instrumentation/slip-skid-ball/indicated-slip-skid",
        "/instrumentation/turn-indicator/indicated-turn-rate",
        "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
        "/controls/flight/aileron",
        "/controls/flight/elevator",
        "/controls/flight/rudder",
        "/controls/flight/flaps",
        "/controls/engines/engine/throttle",
        "/engines/engine/rpm"
};

// 0.000,1.000001\n

double readVar(int clientfd) {
    char c;
    string varstring;

    while ((read(clientfd, &c, 1) > 0) && c != '\n' && c != ',') {
        varstring += c;
    }

    try {
        return stod(varstring);
    }
    catch (invalid_argument e) {
        return NAN;
    }
}

void readVariables(int clientfd, ValuesMap& map) {
    //cout << "attempts reading" << endl;
    for (const string& path : paths) {
        map[path] = readVar(clientfd);

        //cout << "path: " << path << ", value:" << map[path] << endl;
    }
}

struct Parallel {
    int clientfd;
    int hz;
    ValuesMap* values;
};

void* workInParallel(void* args) {
    Parallel* p = (Parallel*) args;

    milliseconds millisBetweenOperations(convertIntToMilliseconds( 1000 / p->hz ));
    //milliseconds millisBetweenOperations = 1000 / p->hz;

    //unsigned long timeBefore, timeAfter, timeDiff;
    while (fcntl(p->clientfd, F_GETFD) >= 0) {
        // get current timestamp (in millis)
        milliseconds timeBefore(theTimeNowInMillis());

        readVariables(p->clientfd, *(p->values));

        // get current timestamp (millis)
        milliseconds timeAfter(theTimeNowInMillis());

        milliseconds timeDiff = timeAfter - timeBefore;
        this_thread::sleep_for(millisBetweenOperations - timeDiff);
        // sleep(millisBetweenOperations - timeDiff);


    }

    delete p;
}

bool DataServer::openServer() {
    serverfd = createServer(port);

    if (serverfd < 0) {
        return false;
    }

    clientfd = connectClient(serverfd);

    if (clientfd < 0) {
        close(serverfd);
        return false;
    }

    // read data from client
    readVariables(clientfd, values);

    // after reading, continue reading on another thread.
    Parallel* p = new Parallel { clientfd, hz, &values };

    if (pthread_create(&threadId, NULL, workInParallel, p)) {
        // error on creating thread
        close(clientfd);
        close(serverfd);

        perror("error on creating thread");
    }

    isOpen = true;

    return true;
}

/**
*
*   CLASS DataClient ::
*
**/

void DataClient::send(const string &way, double data) {
    stringstream strStream;

    //send the info to the client stream
    strStream << "set " << way << " " << data << "\r\n";
    string sendStr = strStream.str();

    //check if the send not get problem
    if (::send(sockfd, sendStr.c_str(), sendStr.length(), 0) < 0) {

        perror("the info don't send to the socket\n");

    }
}

void DataClient::openClient() {

    hostent* myServer;
    sockaddr_in myAddress;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //check if the socket open ok
    if (sockfd < 0) {
        throw "can't open the socket client";
    }

    fdClients.addFd(sockfd);
    myServer = gethostbyname(strFd.c_str());

    //initilize the the side of the most singificant with 0's
    bzero((char *) &myAddress, sizeof(myAddress));
    myAddress.sin_family = AF_INET;
    bcopy(myServer->h_addr, (char *)&myAddress.sin_addr.s_addr, myServer->h_length);

    myAddress.sin_port = htons(clientPort);

    //check if the connect goes ok
    if (connect(sockfd, (sockaddr*) &myAddress, sizeof(myAddress)) < 0) {
        fdClients.closeFds();
        throw "can't connect the socket client to our server";
    }

}

bool DataClient::areYouOpen() {
    return fdClients.count();
}

void DataClient::close() {
    fdClients.closeFds();
}


/**
*
*   CLASS UserData ::
*
**/

void UserData::openDataServer(int myPort, int myHz) {
    //if it was open close it
    closeTheServer();

    //initilize members of the class
    serverFileDescription = new DataServer(myPort, myHz);
    serverFileDescription->openServer();
}

void UserData::closeTheServer() {
    //free memory
    delete serverFileDescription;
    serverFileDescription = nullptr;
}

void UserData::openDataClient(int port, const string &remoteIp) {
    //if it was open close it for beening safe
    closeTheClient();

    //initilize the mebers of the class
    clientFileDescription = new DataClient(port, remoteIp);
    clientFileDescription->openClient();
}

void UserData::closeTheClient() {
    //free memory
    delete clientFileDescription;
    clientFileDescription = nullptr;
}

void UserData::closeAllMembers() {
    //close the members
    closeTheServer();
    closeTheClient();
}
