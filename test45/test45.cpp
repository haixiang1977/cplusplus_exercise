// to exercise map[id, task run flag] and map[id, thread]
#include <unistd.h>

#include <iostream>
#include <string>
#include <map>
#include <thread>

std::map<std::string, bool> CmdRunFlag;
std::map<std::string, std::thread> CmdPollingMonitor;

void CmdPollingMonitorTask(std::string id) {
    std::cout << "CmdPollingMonitorTask " << id << " running" << std::endl;

    while (CmdRunFlag[id]) {
        sleep(1);
    }

    std::cout << "CmdPollingMonitorTask " << id << " quit" << std::endl;
    return;
}

void stopPollingMonitor(std::string id) {
    CmdRunFlag[id] = false;
    CmdPollingMonitor[id].join();

    std::cout << "stopPollingMonitor " << id << " stopped" << std::endl;
    return;
}

void startPollingMonitor(std::string id) {
    CmdRunFlag[id] = true;
    CmdPollingMonitor[id] = std::thread(CmdPollingMonitorTask, id);

    std::cout << "startPollingMonitor " << id << " started" << std::endl;
    return;
}

int main() {

    std::string id = "bma-app";

    startPollingMonitor(id);

    sleep(10);

    stopPollingMonitor(id);

    return 0;
}
