// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from intnums:msg/NameIntNumData.idl
// generated code does not contain a copyright notice
#include "intnums/msg/detail/name_int_num_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"
// Member `int_num_data`
#include "intnums/msg/detail/int_num_data__functions.h"

bool
intnums__msg__NameIntNumData__init(intnums__msg__NameIntNumData * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    intnums__msg__NameIntNumData__fini(msg);
    return false;
  }
  // int_num_data
  if (!intnums__msg__IntNumData__init(&msg->int_num_data)) {
    intnums__msg__NameIntNumData__fini(msg);
    return false;
  }
  return true;
}

void
intnums__msg__NameIntNumData__fini(intnums__msg__NameIntNumData * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // int_num_data
  intnums__msg__IntNumData__fini(&msg->int_num_data);
}

bool
intnums__msg__NameIntNumData__are_equal(const intnums__msg__NameIntNumData * lhs, const intnums__msg__NameIntNumData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->name), &(rhs->name)))
  {
    return false;
  }
  // int_num_data
  if (!intnums__msg__IntNumData__are_equal(
      &(lhs->int_num_data), &(rhs->int_num_data)))
  {
    return false;
  }
  return true;
}

bool
intnums__msg__NameIntNumData__copy(
  const intnums__msg__NameIntNumData * input,
  intnums__msg__NameIntNumData * output)
{
  if (!input || !output) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__copy(
      &(input->name), &(output->name)))
  {
    return false;
  }
  // int_num_data
  if (!intnums__msg__IntNumData__copy(
      &(input->int_num_data), &(output->int_num_data)))
  {
    return false;
  }
  return true;
}

intnums__msg__NameIntNumData *
intnums__msg__NameIntNumData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  intnums__msg__NameIntNumData * msg = (intnums__msg__NameIntNumData *)allocator.allocate(sizeof(intnums__msg__NameIntNumData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(intnums__msg__NameIntNumData));
  bool success = intnums__msg__NameIntNumData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
intnums__msg__NameIntNumData__destroy(intnums__msg__NameIntNumData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    intnums__msg__NameIntNumData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
intnums__msg__NameIntNumData__Sequence__init(intnums__msg__NameIntNumData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  intnums__msg__NameIntNumData * data = NULL;

  if (size) {
    data = (intnums__msg__NameIntNumData *)allocator.zero_allocate(size, sizeof(intnums__msg__NameIntNumData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = intnums__msg__NameIntNumData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        intnums__msg__NameIntNumData__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
intnums__msg__NameIntNumData__Sequence__fini(intnums__msg__NameIntNumData__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      intnums__msg__NameIntNumData__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

intnums__msg__NameIntNumData__Sequence *
intnums__msg__NameIntNumData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  intnums__msg__NameIntNumData__Sequence * array = (intnums__msg__NameIntNumData__Sequence *)allocator.allocate(sizeof(intnums__msg__NameIntNumData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = intnums__msg__NameIntNumData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
intnums__msg__NameIntNumData__Sequence__destroy(intnums__msg__NameIntNumData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    intnums__msg__NameIntNumData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
intnums__msg__NameIntNumData__Sequence__are_equal(const intnums__msg__NameIntNumData__Sequence * lhs, const intnums__msg__NameIntNumData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!intnums__msg__NameIntNumData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
intnums__msg__NameIntNumData__Sequence__copy(
  const intnums__msg__NameIntNumData__Sequence * input,
  intnums__msg__NameIntNumData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(intnums__msg__NameIntNumData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    intnums__msg__NameIntNumData * data =
      (intnums__msg__NameIntNumData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!intnums__msg__NameIntNumData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          intnums__msg__NameIntNumData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!intnums__msg__NameIntNumData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
