#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

bool isPortOpen(const std::string& ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return false;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(ip.c_str());
    serverAddress.sin_port = htons(port);

    if (connect(sock, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == 0) {
        close(sock);
        return true;
    }

    close(sock);
    return false;
}

int main() {
    std::string targetIP;
    int startPort, endPort;

    std::cout << "Enter the target IP address: ";
    std::cin >> targetIP;

    std::cout << "Enter the range of ports to scan (start port end port): ";
    std::cin >> startPort >> endPort;

    for (int port = startPort; port <= endPort; ++port) {
        if (isPortOpen(targetIP, port)) {
            std::cout << "Port " << port << " is open." << std::endl;
        } else {
            std::cout << "Port " << port << " is closed." << std::endl;
        }
    }

    return 0;
}
