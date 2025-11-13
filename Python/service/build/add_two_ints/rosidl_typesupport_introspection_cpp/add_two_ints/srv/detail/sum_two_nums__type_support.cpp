// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from add_two_ints:srv/SumTwoNums.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "add_two_ints/srv/detail/sum_two_nums__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace add_two_ints
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void SumTwoNums_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) add_two_ints::srv::SumTwoNums_Request(_init);
}

void SumTwoNums_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<add_two_ints::srv::SumTwoNums_Request *>(message_memory);
  typed_message->~SumTwoNums_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SumTwoNums_Request_message_member_array[2] = {
  {
    "a",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(add_two_ints::srv::SumTwoNums_Request, a),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "b",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(add_two_ints::srv::SumTwoNums_Request, b),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SumTwoNums_Request_message_members = {
  "add_two_ints::srv",  // message namespace
  "SumTwoNums_Request",  // message name
  2,  // number of fields
  sizeof(add_two_ints::srv::SumTwoNums_Request),
  SumTwoNums_Request_message_member_array,  // message members
  SumTwoNums_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  SumTwoNums_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SumTwoNums_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SumTwoNums_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace add_two_ints


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<add_two_ints::srv::SumTwoNums_Request>()
{
  return &::add_two_ints::srv::rosidl_typesupport_introspection_cpp::SumTwoNums_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, add_two_ints, srv, SumTwoNums_Request)() {
  return &::add_two_ints::srv::rosidl_typesupport_introspection_cpp::SumTwoNums_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "add_two_ints/srv/detail/sum_two_nums__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace add_two_ints
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void SumTwoNums_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) add_two_ints::srv::SumTwoNums_Response(_init);
}

void SumTwoNums_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<add_two_ints::srv::SumTwoNums_Response *>(message_memory);
  typed_message->~SumTwoNums_Response();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SumTwoNums_Response_message_member_array[1] = {
  {
    "sum",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(add_two_ints::srv::SumTwoNums_Response, sum),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SumTwoNums_Response_message_members = {
  "add_two_ints::srv",  // message namespace
  "SumTwoNums_Response",  // message name
  1,  // number of fields
  sizeof(add_two_ints::srv::SumTwoNums_Response),
  SumTwoNums_Response_message_member_array,  // message members
  SumTwoNums_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  SumTwoNums_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SumTwoNums_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SumTwoNums_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace add_two_ints


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<add_two_ints::srv::SumTwoNums_Response>()
{
  return &::add_two_ints::srv::rosidl_typesupport_introspection_cpp::SumTwoNums_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, add_two_ints, srv, SumTwoNums_Response)() {
  return &::add_two_ints::srv::rosidl_typesupport_introspection_cpp::SumTwoNums_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "add_two_ints/srv/detail/sum_two_nums__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace add_two_ints
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers SumTwoNums_service_members = {
  "add_two_ints::srv",  // service namespace
  "SumTwoNums",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<add_two_ints::srv::SumTwoNums>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t SumTwoNums_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SumTwoNums_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace add_two_ints


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<add_two_ints::srv::SumTwoNums>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::add_two_ints::srv::rosidl_typesupport_introspection_cpp::SumTwoNums_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::add_two_ints::srv::SumTwoNums_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::add_two_ints::srv::SumTwoNums_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, add_two_ints, srv, SumTwoNums)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<add_two_ints::srv::SumTwoNums>();
}

#ifdef __cplusplus
}
#endif
