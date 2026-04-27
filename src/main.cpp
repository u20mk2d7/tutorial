#include <boost/asio.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <string>

void f() {
  try {
    // 1. Hire the Foreman
    boost::asio::io_context ioc;

    // 2. Buy the empty Copper Wire (Hand it to the foreman)
    boost::asio::ip::tcp::socket mycable{ioc};

    // 3. Hire the Navigator (Resolver) to find the doors
    boost::asio::ip::tcp::resolver navigator{ioc};
    boost::asio::ip::tcp::resolver::results_type list_of_doors =
        navigator.resolve("stream.binance.com", "443");
    std::cout << "Found the doors! Handing cable to the Smart Plumber...\n";

    // 4. THE SMART PLUMBER (asio::connect)
    // We pass the empty cable, and the list of doors.
    // It does the 3-Way Handshake for us!
    boost::asio::connect(mycable, list_of_doors);

    std::cout << "SUCCESS! The physical TCP highway to Binance is open!\n";

  } catch (std::exception const& e) {
    std::cerr << "The Plumber failed: " << e.what() << "\n";
  }
}

int main() {
  f();
  return 0;
}
