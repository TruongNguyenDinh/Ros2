// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from add_two_ints:srv/SumTwoNums.idl
// generated code does not contain a copyright notice

#ifndef ADD_TWO_INTS__SRV__DETAIL__SUM_TWO_NUMS__STRUCT_H_
#define ADD_TWO_INTS__SRV__DETAIL__SUM_TWO_NUMS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SumTwoNums in the package add_two_ints.
typedef struct add_two_ints__srv__SumTwoNums_Request
{
  int64_t a;
  int64_t b;
} add_two_ints__srv__SumTwoNums_Request;

// Struct for a sequence of add_two_ints__srv__SumTwoNums_Request.
typedef struct add_two_ints__srv__SumTwoNums_Request__Sequence
{
  add_two_ints__srv__SumTwoNums_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} add_two_ints__srv__SumTwoNums_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/SumTwoNums in the package add_two_ints.
typedef struct add_two_ints__srv__SumTwoNums_Response
{
  int64_t sum;
} add_two_ints__srv__SumTwoNums_Response;

// Struct for a sequence of add_two_ints__srv__SumTwoNums_Response.
typedef struct add_two_ints__srv__SumTwoNums_Response__Sequence
{
  add_two_ints__srv__SumTwoNums_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} add_two_ints__srv__SumTwoNums_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ADD_TWO_INTS__SRV__DETAIL__SUM_TWO_NUMS__STRUCT_H_
