// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from intnums:msg/IntData.idl
// generated code does not contain a copyright notice

#ifndef INTNUMS__MSG__DETAIL__INT_DATA__STRUCT_H_
#define INTNUMS__MSG__DETAIL__INT_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/IntData in the package intnums.
typedef struct intnums__msg__IntData
{
  int64_t num_a;
  int64_t num_b;
} intnums__msg__IntData;

// Struct for a sequence of intnums__msg__IntData.
typedef struct intnums__msg__IntData__Sequence
{
  intnums__msg__IntData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} intnums__msg__IntData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTNUMS__MSG__DETAIL__INT_DATA__STRUCT_H_
