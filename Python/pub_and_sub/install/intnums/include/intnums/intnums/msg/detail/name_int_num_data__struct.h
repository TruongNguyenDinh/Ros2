// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from intnums:msg/NameIntNumData.idl
// generated code does not contain a copyright notice

#ifndef INTNUMS__MSG__DETAIL__NAME_INT_NUM_DATA__STRUCT_H_
#define INTNUMS__MSG__DETAIL__NAME_INT_NUM_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"
// Member 'int_num_data'
#include "intnums/msg/detail/int_num_data__struct.h"

/// Struct defined in msg/NameIntNumData in the package intnums.
typedef struct intnums__msg__NameIntNumData
{
  rosidl_runtime_c__String name;
  intnums__msg__IntNumData int_num_data;
} intnums__msg__NameIntNumData;

// Struct for a sequence of intnums__msg__NameIntNumData.
typedef struct intnums__msg__NameIntNumData__Sequence
{
  intnums__msg__NameIntNumData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} intnums__msg__NameIntNumData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTNUMS__MSG__DETAIL__NAME_INT_NUM_DATA__STRUCT_H_
