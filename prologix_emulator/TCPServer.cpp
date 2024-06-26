//
//  TCPServer.cpp
//
//
//  Created by drMrstheMonarch on 28.04.24.
//

#include "TCPServer.hpp"
#include "Functions.hpp"

////Server class to start the server.
// TCPServer::TCPServer(io_service& service, short port, Command& cmd,
// SharedVector& sharedVec)
//     : acceptor_(service, ip::tcp::endpoint(ip::tcp::v4(), port)),
//       socket_(service),
//       command_(cmd),
//       sharedVec_(sharedVec) { // Initialize SharedVector
//     accept();
// }

// void TCPServer::accept() {
//     acceptor_.async_accept(socket_,
//         [this](boost::system::error_code ec) {
//             if (!ec) {
//                 //std::cout << "Connection established." << std::endl;
//                 {
//                     std::lock_guard<std::mutex> lock(sharedVec_.vecMutex);
//                     sharedVec_.vec.push_back("Connection established." );
//                 }
//                 std::make_shared<TCPSession>(std::move(socket_), command_,
//                 sharedVec_)->start(); // Pass SharedVector
//             }
//             accept(); // Accept new connections
//         });
// }
//  Server class to start the server.
TCPServer::TCPServer(boost::asio::io_service& service,
                     short port,
                     Command& cmd,
                     SharedVector& sharedVec,
                     SharedVector& clientVec)
    : acceptor_(service, ip::tcp::endpoint(ip::tcp::v4(), port)),
      socket_(service),
      command_(cmd),
      sharedVec_(sharedVec),
      clientVec_(clientVec) {
  accept();
}

void TCPServer::accept() {
  acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
    if (!ec) {
      std::string remote_ip = socket_.remote_endpoint().address().to_string();
      {
        std::lock_guard<std::mutex> lock(sharedVec_.vecMutex);
        sharedVec_.vec.push_back("Connection established from " + remote_ip +
                                 ".");
      }
      std::make_shared<TCPSession>(std::move(socket_), command_, sharedVec_,
                                   clientVec_)
          ->start();
    }
    accept();  // Accept new connections
  });
}
