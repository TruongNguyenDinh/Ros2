// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from intnums:msg/IntData.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "intnums/msg/detail/int_data__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace intnums
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void IntData_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) intnums::msg::IntData(_init);
}

void IntData_fini_function(void * message_memory)
{
  auto typed_message = static_cast<intnums::msg::IntData *>(message_memory);
  typed_message->~IntData();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember IntData_message_member_array[2] = {
  {
    "num_a",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(intnums::msg::IntData, num_a),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "num_b",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(intnums::msg::IntData, num_b),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers IntData_message_members = {
  "intnums::msg",  // message namespace
  "IntData",  // message name
  2,  // number of fields
  sizeof(intnums::msg::IntData),
  IntData_message_member_array,  // message members
  IntData_init_function,  // function to initialize message memory (memory has to be allocated)
  IntData_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t IntData_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &IntData_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace intnums


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<intnums::msg::IntData>()
{
  return &::intnums::msg::rosidl_typesupport_introspection_cpp::IntData_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, intnums, msg, IntData)() {
  return &::intnums::msg::rosidl_typesupport_introspection_cpp::IntData_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
