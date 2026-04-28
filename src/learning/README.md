// https://pubs.opengroup.org/onlinepubs/9799919799/

1. C++ Raw Socket Basics

Creating sockets

Binding, listening, and accepting connections

Sending and receiving data via TCP and UDP

2. Working with IP Addresses

IP address formats (IPv4, IPv6)

Converting between string and binary representations of IPs

3. Understanding the OSI Model Layers

TCP (Layer 4) and IP (Layer 3)

Why sockets are key to Layer 4 communication

4. Multithreading and Concurrency

Handling multiple client connections efficiently

Introduction to select() / poll() for non-blocking I/O

5. Raw Sockets and Network Sniffing

Moving to raw sockets

Understanding network sniffing and packet crafting

# The Core Concepts
Socket: An endpoint for communication. Think of it like a physical telephone.

IP Address: The machine's address on the network.

Port: A specific "door" on that machine. A server listens on a specific port (e.g., port 8080) so the OS knows which program to hand the incoming network traffic to.

TCP (Transmission Control Protocol): A reliable, connection-oriented protocol. This is what HTTP (and therefore Boost.Beast) relies on.
