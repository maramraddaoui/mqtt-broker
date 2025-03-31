#include "client_simulation.h"


/*void Client::send() {
    // Print a message indicating the server is waiting for connections
    std::cout << "MQTT Server waiting for connections on port " << port << "..." << std::endl;

    while (true) {  // Infinite loop to accept client connections
        struct sockaddr_in clientAddr;
        int addrLen = sizeof(clientAddr);

        // Wait for a client connection
        SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (clientSocket == INVALID_SOCKET) {  // If accepting the connection fails
            std::cerr << "Connection acceptance error!" << std::endl;
            continue;  // Continue waiting for other connections
        }

        // Create a new thread to handle the client connection
        std::thread clientThread(&Server::handleClient, this, clientSocket);
        clientThread.detach();  // The thread is detached and runs independently
    }
}*/


Client::Client() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed!" << std::endl;
        return;
    }

    // Create the socket for the client
    _clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
        WSACleanup();
        return;
    }

    // Setup the server address (localhost)
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Localhost
    serverAddr.sin_port = htons(1883);  // Port for the server

    // Connect to the server
    if (connect(_clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed!" << std::endl;
        closesocket(_clientSocket);
        WSACleanup();
        return;
    }
}

Client::~Client() {
    // Clean up and close the client socket
    closesocket(_clientSocket);
    WSACleanup();
    std::cout << "Client disconnected." << std::endl;
    
}

void Client::send_message(const char* message) {
    // Send a message to the server
    send(_clientSocket, message, strlen(message), 0);
    std::cout << "Message sent to the server." << std::endl;
}