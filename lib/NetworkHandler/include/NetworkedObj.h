#pragma once

#include <Obj.h>
#include "InetMsg.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <any>
#include <memory>

#define OBJ_CLIENT_CONTROLLED 0b1
#define OBJ_SERVER_CONTROLLED 0b10
#define OBJ_PASSIVE           0b100

template<typename F>
std::function<std::any(void)> getter_generic_wrapper(F foo, std::shared_ptr<Obj> obj_p){
  return [foo, obj_p]() -> std::any { return std::any((obj_p.get()->*foo)()); };
};

template<typename F, typename T>
std::function<void(std::any)> setter_generic_wrapper(F foo, std::shared_ptr<Obj> obj_p){
  return [foo, obj_p](std::any val) { (obj_p.get()->*foo)(std::any_cast<T>(val)); };
};


struct FieldDescription{
  std::function<std::any(void)> getter;
  std::function<void(std::any)> setter;
};

class NetworkedObj
{
private:
  std::shared_ptr<Obj> baseObj_;
  std::unordered_map<std::string, FieldDescription> fieldMap_;
  std::unordered_map<std::string, FieldDescription> makeFieldMapFromObj(std::shared_ptr<Obj> obj);
public:
  NetworkedObj(std::shared_ptr<Obj> obj) :
    baseObj_(obj),
    fieldMap_(makeFieldMapFromObj(obj))
  {
  };

  bool operator==(const NetworkedObj &o) const { return o.baseObj_ == baseObj_; };

  void registerField(std::string, FieldDescription);
  void processPacket(InetMsg &mag);
  std::shared_ptr<Obj> getBaseObj(){
    return baseObj_;
  }

  std::string serialize();
};