// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from tnsy_interfaces:msg/TnsyController.idl
// generated code does not contain a copyright notice

#ifndef TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__STRUCT_H_
#define TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/TnsyController in the package tnsy_interfaces.
typedef struct tnsy_interfaces__msg__TnsyController
{
  float translation_magnitude;
  float translation_angle;
  float pointing_magnitude;
  float pointing_angle;
  float rotation_speed;
  bool enable_switch;
} tnsy_interfaces__msg__TnsyController;

// Struct for a sequence of tnsy_interfaces__msg__TnsyController.
typedef struct tnsy_interfaces__msg__TnsyController__Sequence
{
  tnsy_interfaces__msg__TnsyController * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} tnsy_interfaces__msg__TnsyController__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__STRUCT_H_
