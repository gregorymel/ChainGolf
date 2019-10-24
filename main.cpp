#include <cstdio>
#include <filesystem>
#include <iostream>
#include <thread>

#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>

class TemplateServer : public jsonrpc::AbstractServer<TemplateServer> {
 public:
  TemplateServer(jsonrpc::AbstractServerConnector &conn,
                 jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2)
      : jsonrpc::AbstractServer<TemplateServer>(conn, type) {
    bindAndAddMethod(
        jsonrpc::Procedure("balance", jsonrpc::PARAMS_BY_NAME,
                           jsonrpc::JSON_INTEGER, "address",
                           jsonrpc::JSON_STRING, NULL),
        &TemplateServer::balanceI);
    bindAndAddMethod(
        jsonrpc::Procedure(
            "transaction", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING,
            "amount", jsonrpc::JSON_INTEGER, "from_address",
            jsonrpc::JSON_STRING, "to_address", jsonrpc::JSON_STRING, NULL),
        &TemplateServer::transactionI);
  }

  virtual void balanceI(const Json::Value &request,
                               Json::Value &response) {
    response = balance(request["address"].asString());
  }
  virtual void transactionI(const Json::Value &request,
                                   Json::Value &response) {
    response = transaction(request["amount"].asInt(),
                                 request["from_address"].asString(),
                                 request["to_address"].asString());
  }
  virtual int balance(const std::string &address) = 0;
  virtual std::string transaction(int amount, const std::string &from_address,
                                  const std::string &to_address) = 0;
};

class MyServer : public TemplateServer {
 public:
  MyServer(jsonrpc::AbstractServerConnector &connector,
               jsonrpc::serverVersion_t type);

  int balance(const std::string &address) override;
  std::string transaction(int amount, const std::string &from_address,
                                  const std::string &to_address) override;
};

MyServer::MyServer(jsonrpc::AbstractServerConnector &connector,
                           jsonrpc::serverVersion_t type)
    : TemplateServer(connector, type) {}

int MyServer::balance(const std::string &address) {
  std::cout << "SERVER | Received in balance: address[" << address << "]"
            << std::endl;
  return 1;
}

std::string MyServer::transaction(int amount,
                                      const std::string &from_address,
                                      const std::string &to_address) {
  std::cout << "SERVER | Received in transaction: from_address[" << from_address
            << "], to_address[" << to_address << "], amount[" << amount << "]"
            << std::endl;
  return "transaction block hash";
}

int main() {
  jsonrpc::HttpServer httpserver(10001);
  MyServer s(httpserver, jsonrpc::JSONRPC_SERVER_V1V2);
  s.StartListening();
  std::cout << "welcome to UTON HACK!" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(45));
  s.StopListening();
  return 0;
}
