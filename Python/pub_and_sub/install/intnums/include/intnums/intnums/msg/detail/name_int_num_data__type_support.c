// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from intnums:msg/NameIntNumData.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "intnums/msg/detail/name_int_num_data__rosidl_typesupport_introspection_c.h"
#include "intnums/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "intnums/msg/detail/name_int_num_data__functions.h"
#include "intnums/msg/detail/name_int_num_data__struct.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"
// Member `int_num_data`
#include "intnums/msg/int_num_data.h"
// Member `int_num_data`
#include "intnums/msg/detail/int_num_data__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  intnums__msg__NameIntNumData__init(message_memory);
}

void intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_fini_function(void * message_memory)
{
  intnums__msg__NameIntNumData__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_message_member_array[2] = {
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(intnums__msg__NameIntNumData, name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "int_num_data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(intnums__msg__NameIntNumData, int_num_data),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_message_members = {
  "intnums__msg",  // message namespace
  "NameIntNumData",  // message name
  2,  // number of fields
  sizeof(intnums__msg__NameIntNumData),
  intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_message_member_array,  // message members
  intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_init_function,  // function to initialize message memory (memory has to be allocated)
  intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_message_type_support_handle = {
  0,
  &intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_intnums
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, intnums, msg, NameIntNumData)() {
  intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, intnums, msg, IntNumData)();
  if (!intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_message_type_support_handle.typesupport_identifier) {
    intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &intnums__msg__NameIntNumData__rosidl_typesupport_introspection_c__NameIntNumData_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
