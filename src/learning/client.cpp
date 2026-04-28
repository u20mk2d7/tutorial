// #include "network/client.hpp"
#include <arpa/inet.h>   // inet_pton(), htons(), inet_addr()
#include <netdb.h>       // getaddrinfo
#include <netinet/in.h>  // sockaddr_in, AF_INET, INADDR_ANY
#include <sys/socket.h>  // socket(), bind(), connect(), send(), recv()
#include <unistd.h>      // close(), sockaddr_in, ip/port defines

#include <cstring>  // memset(), strlen()
#include <iostream>
#include <string>
#include <vector>

int client() {
  struct addrinfo* servinfo;
  struct addrinfo hints = {0};
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;      // IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;  // TCP

  // getaddrinfo of server, resolve
  // Hostname/IP
  int status = getaddrinfo("127.0.0.1", "8080", &hints, &servinfo);
  if (status != 0) {
    std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
    return -1;
  }

  struct addrinfo* p;
  int socket_fd = 0;
  for (p = servinfo; p != nullptr; p = p->ai_next) {
    socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (socket_fd == -1) continue;

    if (connect(socket_fd, p->ai_addr, p->ai_addrlen) == -1) {
      perror("client: connect");
      close(socket_fd);
      continue;
    }
    break;
  }

  if (p == nullptr) {
    std::cerr << "client: failed to "
                 "connect\n"
              << std::endl;
    freeaddrinfo(servinfo);
    return -1;
  }

  // 4. Send/Receive Data
  const char* msg =
      "GET / HTTP/1.1\r\nHost: "
      "localhost\r\n\r\n";
  send(socket_fd, msg, strlen(msg), 0);

  char buffer[4096];
  int bytes_received = recv(socket_fd, buffer, sizeof(buffer) - 1, 0);
  if (bytes_received > 0) {
    buffer[bytes_received] = '\0';
    std::cout << "Server said: " << buffer << std::endl;
  }

  // 5. Close
  close(socket_fd);
  return 1;
}

// int network::Client::connect_to_server_udp(const std::string &hostname, const
// std::string &port) {}
int connect_to_server_udp(const std::string& hostname,
                          const std::string& port) {
  return 0;
}
