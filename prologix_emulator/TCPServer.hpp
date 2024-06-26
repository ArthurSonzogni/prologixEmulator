//
//  TCPServer.hpp
//
//
//  Created by drMrstheMonarch on 28.04.24.
//
#ifndef TCPServer_hpp
#define TCPServer_hpp

#include <atomic>
#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include "Command.hpp"
#include "Functions.hpp"
#include "TCPSession.hpp"

class TCPServer {
 public:
  //        TCPServer(io_service& service, short port, Command& cmd,
  //        SharedVector& sharedVec);
  TCPServer(boost::asio::io_service& service,
            short port,
            Command& cmd,
            SharedVector& sharedVec,
            SharedVector& clientVec);
  //    TCPServer(boost::asio::io_service& service, short port, Command& cmd,
  //    SharedVector& sharedVec);

 private:
  void accept();
  ip::tcp::socket socket_;
  SharedVector& sharedVec_;  // Add SharedVector reference
  SharedVector& clientVec_;
  std::atomic<int> activeSessions_;  // Counter for active sessions
  boost::asio::ip::tcp::acceptor acceptor_;
  Command& command_;
};

#endif /* TCPServer_hpp */
