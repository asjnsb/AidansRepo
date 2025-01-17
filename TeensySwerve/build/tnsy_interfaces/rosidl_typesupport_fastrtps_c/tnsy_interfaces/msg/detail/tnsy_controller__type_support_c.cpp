// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from tnsy_interfaces:msg/TnsyController.idl
// generated code does not contain a copyright notice
#include "tnsy_interfaces/msg/detail/tnsy_controller__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "tnsy_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "tnsy_interfaces/msg/detail/tnsy_controller__struct.h"
#include "tnsy_interfaces/msg/detail/tnsy_controller__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _TnsyController__ros_msg_type = tnsy_interfaces__msg__TnsyController;

static bool _TnsyController__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _TnsyController__ros_msg_type * ros_message = static_cast<const _TnsyController__ros_msg_type *>(untyped_ros_message);
  // Field name: translation_magnitude
  {
    cdr << ros_message->translation_magnitude;
  }

  // Field name: translation_angle
  {
    cdr << ros_message->translation_angle;
  }

  // Field name: rotation_speed
  {
    cdr << ros_message->rotation_speed;
  }

  // Field name: pointing_magnitude
  {
    cdr << ros_message->pointing_magnitude;
  }

  // Field name: pointing_angle
  {
    cdr << ros_message->pointing_angle;
  }

  // Field name: enable_switch
  {
    cdr << (ros_message->enable_switch ? true : false);
  }

  return true;
}

static bool _TnsyController__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _TnsyController__ros_msg_type * ros_message = static_cast<_TnsyController__ros_msg_type *>(untyped_ros_message);
  // Field name: translation_magnitude
  {
    cdr >> ros_message->translation_magnitude;
  }

  // Field name: translation_angle
  {
    cdr >> ros_message->translation_angle;
  }

  // Field name: rotation_speed
  {
    cdr >> ros_message->rotation_speed;
  }

  // Field name: pointing_magnitude
  {
    cdr >> ros_message->pointing_magnitude;
  }

  // Field name: pointing_angle
  {
    cdr >> ros_message->pointing_angle;
  }

  // Field name: enable_switch
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->enable_switch = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_tnsy_interfaces
size_t get_serialized_size_tnsy_interfaces__msg__TnsyController(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _TnsyController__ros_msg_type * ros_message = static_cast<const _TnsyController__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name translation_magnitude
  {
    size_t item_size = sizeof(ros_message->translation_magnitude);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name translation_angle
  {
    size_t item_size = sizeof(ros_message->translation_angle);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name rotation_speed
  {
    size_t item_size = sizeof(ros_message->rotation_speed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name pointing_magnitude
  {
    size_t item_size = sizeof(ros_message->pointing_magnitude);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name pointing_angle
  {
    size_t item_size = sizeof(ros_message->pointing_angle);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name enable_switch
  {
    size_t item_size = sizeof(ros_message->enable_switch);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _TnsyController__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_tnsy_interfaces__msg__TnsyController(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_tnsy_interfaces
size_t max_serialized_size_tnsy_interfaces__msg__TnsyController(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: translation_magnitude
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: translation_angle
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: rotation_speed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: pointing_magnitude
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: pointing_angle
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: enable_switch
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = tnsy_interfaces__msg__TnsyController;
    is_plain =
      (
      offsetof(DataType, enable_switch) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _TnsyController__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_tnsy_interfaces__msg__TnsyController(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_TnsyController = {
  "tnsy_interfaces::msg",
  "TnsyController",
  _TnsyController__cdr_serialize,
  _TnsyController__cdr_deserialize,
  _TnsyController__get_serialized_size,
  _TnsyController__max_serialized_size
};

static rosidl_message_type_support_t _TnsyController__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_TnsyController,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, tnsy_interfaces, msg, TnsyController)() {
  return &_TnsyController__type_support;
}

#if defined(__cplusplus)
}
#endif
