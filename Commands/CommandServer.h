/**
 * class for create and run server thread.
 *
 * @author Yehonatan Sofri
 * @date 12.26.19
 */

#ifndef COMMANDSERVER_H
#define COMMANDSERVER_H

#include "Command.h"

class CommandServer : public Command {
public:
    void runServer();
    int execute(int);
    /*void createSocket();
    void bindSocket();
    void listenAndAccept();*/
    string convertToString(char*);
    void handleCSV(string);
    CommandServer() = default;
    ~CommandServer() = default;
private:
    int _port;
};


#endif //COMMANDSERVER_H
