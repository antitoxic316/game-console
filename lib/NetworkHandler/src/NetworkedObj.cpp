#include "NetworkedObj.h"

#include <memory>
#include <unordered_map>
#include <any>

#include <Arduino.h>
#include <ArduinoJson.h>

//c++ has no reflection lol
std::map<std::string, FieldDescription> NetworkedObj::makeFieldMapFromObj(std::shared_ptr<Obj> obj){
  std::map<std::string, FieldDescription> map;
  
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

void NetworkedObj::registerField(std::string name, FieldDescription fd){
  fieldMap_[name] = fd;
}

std::string NetworkedObj::serializeObjInfo(){
  JsonDocument j;
  size_t nbuff = 256;
  char buff[nbuff] = {'\0', };

  j["type"] = "obj_register";
  j["packet"]["obj_name"] = baseObj_->getName();

  int i = 0;
  for(const auto &field : fieldMap_){
    j["packet"]["interpol_fields"][i] = field.first;
    i++;
  }

  j["echo"] = false;
  j["server_processed"] = true;

  serializeJson(j, buff, nbuff);

  if(buff[nbuff-1] != '\0'){
    // buffer overflow
    return nullptr;
  }

  return std::string(buff);
}

std::string NetworkedObj::serializeData(){
  JsonDocument j;
  size_t nbuff = 256;
  char buff[nbuff] = {'\0', };

  j["type"] = "obj_update";
  if(!strcmp(baseObj_->getName(), "player1")){
    j["packet"]["obj_name"] = "player2";
  } else {
    j["packet"]["obj_name"] = baseObj_->getName();
  }
  int i = 0;
  for(const auto &field : fieldMap_){
    std::string attr_label = field.first;
    auto getter_cb = field.second.getter;
    j["packet"]["interpol_fields"][i] = attr_label;
    j["packet"]["interpol_values"][i] = std::any_cast<int>(getter_cb());
  }

  j["echo"] = true;
  j["server_processed"] = true;

  serializeJson(j, buff, nbuff);

  if(buff[nbuff-1] != '\0'){
    // buffer overflow
    return nullptr;
  }

  return std::string(buff);
}

void NetworkedObj::handlePacket(char *str){
  JsonDocument j;
  DeserializationError err;

  err = deserializeJson(j, str);
  
  if(err){
    Serial.println(err.c_str());
    return;
  } 
  
  if(!strcmp(j["type"], "obj_update")){
    if(!j.containsKey("packet")) return;
    JsonObject packet = j["packet"].as<JsonObject>();

    if(!packet.containsKey("obj_name")) return;
    if(strcmp(packet["obj_name"], baseObj_->getName())){
      return; 
    }

    if(!packet.containsKey("interpol_fields")) return;
    if(!packet.containsKey("interpol_values")) return;
    JsonArray fields_arr = j["packet"]["interpol_fields"];
    JsonArray vals_arr = j["packet"]["interpol_values"]; 

    if(fields_arr.size() != vals_arr.size()) return;

    for (int i = 0; i < fields_arr.size(); i++) {
      const char *field = fields_arr[i];
      int val = vals_arr[i];
    
      auto setter_cb = fieldMap_[field].setter;
      setter_cb(std::any(val));
    }
  } else if (!strcmp(j["type"], "event")){
    if(!j.containsKey("packet")) return;
    JsonObject packet = j["packet"].as<JsonObject>();

    if(!packet.containsKey("ev_name")) return;
    if(!packet.containsKey("ev_data")) return;
    std::string ev_name = packet["ev_name"].as<std::string>();
    void *ev_data = (void *)packet["ev_data"].as<const char*>();

    baseObj_->emitEvent(ev_name, ev_data);
  }
}