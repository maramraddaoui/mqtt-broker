#include "server.h"

Server::Server(int port) : port(port) {
    // Initialize Winsock (library needed for using sockets on Windows)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {  // Initialize Winsock version 2.2
        std::cerr << "Winsock initialization error!" << std::endl;
        exit(EXIT_FAILURE);  // If initialization fails, print an error and exit the program
    }

    // Create a TCP socket for the server
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {  // Check if the socket was created successfully
        std::cerr << "Socket creation error!" << std::endl;
        WSACleanup();  // Cleanup Winsock resources
        exit(EXIT_FAILURE);  // If creation fails, exit the program
    }

    // Set up the server's address (IPv4, listens on all network interfaces)
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;  // Use IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // The server will listen on all network interfaces
    serverAddr.sin_port = htons(port);  // Convert the port to network byte order

    // Bind the socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {  // If binding fails
        std::cerr << "Socket binding error!" << std::endl;
        closesocket(serverSocket);  // Close the socket
        WSACleanup();  // Cleanup Winsock
        exit(EXIT_FAILURE);  // If binding fails, exit the program
    }

    // Set the socket to listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {  // If listening fails
        std::cerr << "Listening error!" << std::endl;
        closesocket(serverSocket);  // Close the socket
        WSACleanup();  // Cleanup Winsock
        exit(EXIT_FAILURE);  // If listening fails, exit the program
    }
}

void Server::start() {
    // Print a message indicating the server is waiting for connections
    std::cout << "MQTT Server waiting for connections on port " << port << "..." << std::endl;

    // Create a new thread to handle the client connection
    std::thread clientThread(&Server::handleClient, this);
    clientThread.detach();  // The thread is detached and runs independently
}

void Server::handleClient() {
    struct sockaddr_in clientAddr;
    int addrLen = sizeof(clientAddr);

    // Wait for a client connection
    SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
    if (clientSocket == INVALID_SOCKET) {  // If accepting the connection fails
        std::cerr << "Connection acceptance error!" << std::endl;
        //continue;  // Continue waiting for other connections
    }

    // Buffer to receive messages from the client
    char buffer[1024] = { 0 };

    // Print a message indicating a client has connected
    {
        std::lock_guard<std::mutex> lock(coutMutex);  // Lock to access the console safely
        std::cout << "Client connected!" << std::endl;
    }

    while (true) {  // Loop to read messages sent by the client
        int valread = recv(clientSocket, buffer, 1024, 0);  // Read message from client
        if (valread <= 0) {  // If reading fails or the client closes the connection
            {
                std::lock_guard<std::mutex> lock(coutMutex);  // Lock for safe console access
                std::cout << "Client disconnected." << std::endl;
            }
            closesocket(clientSocket);  // Close the client socket
            return;  // Exit the client handling function (ends the thread)
        }

        // Print the received message from the client
        {
            std::lock_guard<std::mutex> lock(coutMutex);  // Lock for safe console access
            std::cout << "Message received: " << buffer << std::endl;
        }
    }
}
