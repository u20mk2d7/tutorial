// #include "network/server.hpp"
#include <cstring>  // strlen, memset
#include <iostream>

// network library
#include <arpa/inet.h>   // inet_pton, htons, inet_addr
#include <netdb.h>       // getaddrinfo
#include <netinet/in.h>  // sockaddr_in, AF_INET, INADDR_ANY
#include <sys/socket.h>  // socket, bind, connect, send, recv
#include <unistd.h>      // close, sockaddr_in, ip/port defines

#include <string>

// int network::Server::init_tcp() {
int server() {
  const std::string port = "8080";  // const char* port

  struct addrinfo* servinfo;  // point to each hostname reach to null

  struct addrinfo hints = {0};
  memset(&hints, 0, sizeof(hints));  // make sure struct empty
  hints.ai_family = AF_UNSPEC;       // IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;   // TCP stream socket
  hints.ai_flags = AI_PASSIVE;       // fill in my IP for me

  int status = getaddrinfo(nullptr, port.c_str(), &hints, &servinfo);
  if (status != 0) {
    fprintf(stderr, "[ERROR] getaddrinfo: %s\n", gai_strerror(status));
    // throw std::runtime_error(gai_strerror(status));
    return -1;  // Return error instead of exiting the whole app
  }

  // socket -> listen -> bind -> accept -> response -> send
  struct addrinfo* p;
  int socket_fd = 0;
  for (p = servinfo; p != nullptr; p = p->ai_next) {
    socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (socket_fd == -1) {
      continue;
    }

    // (?) why need set socket options
    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(socket_fd, p->ai_addr, p->ai_addrlen) == -1) {
      close(socket_fd);
      perror("Server: Bind");
      continue;
    }

    break;  // Successfully bound! Exit the loop.
  }

  freeaddrinfo(servinfo);  // free the linked-list
  if (p == nullptr) {
    throw std::runtime_error("Could not bind to any address");
  }

  // listen from client
  if (listen(socket_fd, 10) < 0) {
    close(socket_fd);
    throw std::runtime_error("Listen failed");
  }

  std::cout << "Server initialized on port " << port
            << ". Waiting for connections..." << std::endl;

  struct sockaddr_storage client_addr;  // Large enough for IPv4/v6
  socklen_t addr_size = sizeof(client_addr);

  int client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &addr_size);
  if (client_fd < 0) {
    perror("Server: Accept error");
  }

  send(client_fd, "Hello!\n", 7, 0);

  close(socket_fd);
  return 1;
}
// int network::Server::init_udp() {}
