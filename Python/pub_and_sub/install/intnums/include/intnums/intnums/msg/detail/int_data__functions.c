// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from intnums:msg/IntData.idl
// generated code does not contain a copyright notice
#include "intnums/msg/detail/int_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
intnums__msg__IntData__init(intnums__msg__IntData * msg)
{
  if (!msg) {
    return false;
  }
  // num_a
  // num_b
  return true;
}

void
intnums__msg__IntData__fini(intnums__msg__IntData * msg)
{
  if (!msg) {
    return;
  }
  // num_a
  // num_b
}

bool
intnums__msg__IntData__are_equal(const intnums__msg__IntData * lhs, const intnums__msg__IntData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // num_a
  if (lhs->num_a != rhs->num_a) {
    return false;
  }
  // num_b
  if (lhs->num_b != rhs->num_b) {
    return false;
  }
  return true;
}

bool
intnums__msg__IntData__copy(
  const intnums__msg__IntData * input,
  intnums__msg__IntData * output)
{
  if (!input || !output) {
    return false;
  }
  // num_a
  output->num_a = input->num_a;
  // num_b
  output->num_b = input->num_b;
  return true;
}

intnums__msg__IntData *
intnums__msg__IntData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  intnums__msg__IntData * msg = (intnums__msg__IntData *)allocator.allocate(sizeof(intnums__msg__IntData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(intnums__msg__IntData));
  bool success = intnums__msg__IntData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
intnums__msg__IntData__destroy(intnums__msg__IntData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    intnums__msg__IntData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
intnums__msg__IntData__Sequence__init(intnums__msg__IntData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  intnums__msg__IntData * data = NULL;

  if (size) {
    data = (intnums__msg__IntData *)allocator.zero_allocate(size, sizeof(intnums__msg__IntData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = intnums__msg__IntData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        intnums__msg__IntData__fini(&data[i - 1]);
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
intnums__msg__IntData__Sequence__fini(intnums__msg__IntData__Sequence * array)
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
      intnums__msg__IntData__fini(&array->data[i]);
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

intnums__msg__IntData__Sequence *
intnums__msg__IntData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  intnums__msg__IntData__Sequence * array = (intnums__msg__IntData__Sequence *)allocator.allocate(sizeof(intnums__msg__IntData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = intnums__msg__IntData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
intnums__msg__IntData__Sequence__destroy(intnums__msg__IntData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    intnums__msg__IntData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
intnums__msg__IntData__Sequence__are_equal(const intnums__msg__IntData__Sequence * lhs, const intnums__msg__IntData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!intnums__msg__IntData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
intnums__msg__IntData__Sequence__copy(
  const intnums__msg__IntData__Sequence * input,
  intnums__msg__IntData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(intnums__msg__IntData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    intnums__msg__IntData * data =
      (intnums__msg__IntData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!intnums__msg__IntData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          intnums__msg__IntData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!intnums__msg__IntData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
