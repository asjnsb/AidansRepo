// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from tnsy_interfaces:msg/TnsyController.idl
// generated code does not contain a copyright notice
#include "tnsy_interfaces/msg/detail/tnsy_controller__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
tnsy_interfaces__msg__TnsyController__init(tnsy_interfaces__msg__TnsyController * msg)
{
  if (!msg) {
    return false;
  }
  // translation_magnitude
  msg->translation_magnitude = 0.0f;
  // translation_angle
  msg->translation_angle = 0.0f;
  // rotation_speed
  msg->rotation_speed = 0.0f;
  // pointing_magnitude
  msg->pointing_magnitude = 0.0f;
  // pointing_angle
  msg->pointing_angle = 0.0f;
  // enable_switch
  msg->enable_switch = false;
  return true;
}

void
tnsy_interfaces__msg__TnsyController__fini(tnsy_interfaces__msg__TnsyController * msg)
{
  if (!msg) {
    return;
  }
  // translation_magnitude
  // translation_angle
  // rotation_speed
  // pointing_magnitude
  // pointing_angle
  // enable_switch
}

bool
tnsy_interfaces__msg__TnsyController__are_equal(const tnsy_interfaces__msg__TnsyController * lhs, const tnsy_interfaces__msg__TnsyController * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // translation_magnitude
  if (lhs->translation_magnitude != rhs->translation_magnitude) {
    return false;
  }
  // translation_angle
  if (lhs->translation_angle != rhs->translation_angle) {
    return false;
  }
  // rotation_speed
  if (lhs->rotation_speed != rhs->rotation_speed) {
    return false;
  }
  // pointing_magnitude
  if (lhs->pointing_magnitude != rhs->pointing_magnitude) {
    return false;
  }
  // pointing_angle
  if (lhs->pointing_angle != rhs->pointing_angle) {
    return false;
  }
  // enable_switch
  if (lhs->enable_switch != rhs->enable_switch) {
    return false;
  }
  return true;
}

bool
tnsy_interfaces__msg__TnsyController__copy(
  const tnsy_interfaces__msg__TnsyController * input,
  tnsy_interfaces__msg__TnsyController * output)
{
  if (!input || !output) {
    return false;
  }
  // translation_magnitude
  output->translation_magnitude = input->translation_magnitude;
  // translation_angle
  output->translation_angle = input->translation_angle;
  // rotation_speed
  output->rotation_speed = input->rotation_speed;
  // pointing_magnitude
  output->pointing_magnitude = input->pointing_magnitude;
  // pointing_angle
  output->pointing_angle = input->pointing_angle;
  // enable_switch
  output->enable_switch = input->enable_switch;
  return true;
}

tnsy_interfaces__msg__TnsyController *
tnsy_interfaces__msg__TnsyController__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  tnsy_interfaces__msg__TnsyController * msg = (tnsy_interfaces__msg__TnsyController *)allocator.allocate(sizeof(tnsy_interfaces__msg__TnsyController), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(tnsy_interfaces__msg__TnsyController));
  bool success = tnsy_interfaces__msg__TnsyController__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
tnsy_interfaces__msg__TnsyController__destroy(tnsy_interfaces__msg__TnsyController * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    tnsy_interfaces__msg__TnsyController__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
tnsy_interfaces__msg__TnsyController__Sequence__init(tnsy_interfaces__msg__TnsyController__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  tnsy_interfaces__msg__TnsyController * data = NULL;

  if (size) {
    data = (tnsy_interfaces__msg__TnsyController *)allocator.zero_allocate(size, sizeof(tnsy_interfaces__msg__TnsyController), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = tnsy_interfaces__msg__TnsyController__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        tnsy_interfaces__msg__TnsyController__fini(&data[i - 1]);
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
tnsy_interfaces__msg__TnsyController__Sequence__fini(tnsy_interfaces__msg__TnsyController__Sequence * array)
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
      tnsy_interfaces__msg__TnsyController__fini(&array->data[i]);
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

tnsy_interfaces__msg__TnsyController__Sequence *
tnsy_interfaces__msg__TnsyController__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  tnsy_interfaces__msg__TnsyController__Sequence * array = (tnsy_interfaces__msg__TnsyController__Sequence *)allocator.allocate(sizeof(tnsy_interfaces__msg__TnsyController__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = tnsy_interfaces__msg__TnsyController__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
tnsy_interfaces__msg__TnsyController__Sequence__destroy(tnsy_interfaces__msg__TnsyController__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    tnsy_interfaces__msg__TnsyController__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
tnsy_interfaces__msg__TnsyController__Sequence__are_equal(const tnsy_interfaces__msg__TnsyController__Sequence * lhs, const tnsy_interfaces__msg__TnsyController__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!tnsy_interfaces__msg__TnsyController__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
tnsy_interfaces__msg__TnsyController__Sequence__copy(
  const tnsy_interfaces__msg__TnsyController__Sequence * input,
  tnsy_interfaces__msg__TnsyController__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(tnsy_interfaces__msg__TnsyController);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    tnsy_interfaces__msg__TnsyController * data =
      (tnsy_interfaces__msg__TnsyController *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!tnsy_interfaces__msg__TnsyController__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          tnsy_interfaces__msg__TnsyController__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!tnsy_interfaces__msg__TnsyController__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
