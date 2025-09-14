#include "NetworkedObj.h"

#include <memory>
#include <unordered_map>
#include <any>

#include <Arduino.h>

#include <nlohmann/json.hpp>
using namespace nlohmann;

auto j = json::parse(R"({"x": 100, "y": 5})");


//c++ has no reflection lol
std::unordered_map<std::string, FieldDescription> NetworkedObj::makeFieldMapFromObj(std::shared_ptr<Obj> obj){
  std::unordered_map<std::string, FieldDescription> map;
  
  FieldDescription field_x;
  field_x.getter = getter_generic_wrapper(&Obj::getX, obj);
  field_x.setter = setter_generic_wrapper<decltype(&Obj::setX), int>(&Obj::setX, obj);

  FieldDescription field_y;
  field_y.getter = getter_generic_wrapper(&Obj::getY, obj);
  field_y.setter = setter_generic_wrapper<decltype(&Obj::setY), int>(&Obj::setY, obj);


  map["x"] = field_x;
  map["y"] = field_y;

  return map;
};

void NetworkedObj::processPacket(InetMsg &mag){
  /*
  Serial.println("parsed json");
  Serial.println((int)j["x"]);
  delay(10);

  fieldMap_["x"].setter(std::any((int)j["x"]));
  fieldMap_["y"].setter(std::any((int)j["y"]));
  */
}

void NetworkedObj::registerField(std::string name, FieldDescription fd){
  fieldMap_[name] = fd;
}

std::string NetworkedObj::serialize(){
  j["x"] = std::any_cast<int>(fieldMap_["x"].getter());
  j["y"] = std::any_cast<int>(fieldMap_["y"].getter());

  return j.dump();
}