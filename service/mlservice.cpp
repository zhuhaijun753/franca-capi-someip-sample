#include "mlservice.hpp"

using ::v1::ford::rnd::ML;
using ::v1::ford::rnd::MLTypes;

MLService::MLService() {
}
MLService::~MLService() {
}

void MLService::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
                         std::string _name, sayHelloReply_t _reply) {
  std::stringstream messageStream;
  messageStream << "Hello " << _name << "!";
  std::cout << "sayHello('" << _name << "'): '" << messageStream.str() << "'\n";

  clients_[_client->hashCode()] = _name;

  setNameAttribute(_name);

  _reply(messageStream.str());
}

void MLService::howMuch(const std::shared_ptr<CommonAPI::ClientId> _client,
                        howMuchReply_t _reply) {
  std::cout << "howMuch()\n";

  if (getNameAttribute() == "Kate") {
    _reply(0);
  } else {
    fireGetOutEvent("Bye!!!");
    _reply(300);
  }
}

void MLService::getDeviceType(
    const std::shared_ptr<CommonAPI::ClientId> _client,
    getDeviceTypeReply_t _reply) {
  std::cout << "getDeviceType()\n";
  ClientList::iterator i = clients_.find(_client->hashCode());
  if (i != clients_.end() && i->second == "Kate") {
    _reply(ML::DeviceType(ML::DeviceType::LAPTOP));
  } else {
    _reply(ML::DeviceType());
  }
}

void MLService::getConnectionType(
    const std::shared_ptr<CommonAPI::ClientId> _client,
    getConnectionTypeReply_t _reply) {
  std::cout << "getConnectionType()\n";
  ClientList::iterator i = clients_.find(_client->hashCode());
  if (i != clients_.end() && i->second == "Kate") {
    _reply(MLTypes::ConnectionType(MLTypes::ConnectionType::USB));
  } else {
    _reply(MLTypes::ConnectionType());
  }
}

void MLService::getLastPerson(
    const std::shared_ptr<CommonAPI::ClientId> _client,
    getLastPersonReply_t _reply) {
  std::cout << "getLastPerson()\n";
 _reply(MLTypes::Person("Tereza", 3));
}
