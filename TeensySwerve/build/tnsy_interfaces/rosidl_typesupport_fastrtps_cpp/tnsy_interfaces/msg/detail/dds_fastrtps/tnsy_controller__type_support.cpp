// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from tnsy_interfaces:msg/TnsyController.idl
// generated code does not contain a copyright notice
#include "tnsy_interfaces/msg/detail/tnsy_controller__rosidl_typesupport_fastrtps_cpp.hpp"
#include "tnsy_interfaces/msg/detail/tnsy_controller__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace tnsy_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tnsy_interfaces
cdr_serialize(
  const tnsy_interfaces::msg::TnsyController & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: translation_magnitude
  cdr << ros_message.translation_magnitude;
  // Member: translation_angle
  cdr << ros_message.translation_angle;
  // Member: pointing_magnitude
  cdr << ros_message.pointing_magnitude;
  // Member: pointing_angle
  cdr << ros_message.pointing_angle;
  // Member: rotation_speed
  cdr << ros_message.rotation_speed;
  // Member: enable_switch
  cdr << (ros_message.enable_switch ? true : false);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tnsy_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  tnsy_interfaces::msg::TnsyController & ros_message)
{
  // Member: translation_magnitude
  cdr >> ros_message.translation_magnitude;

  // Member: translation_angle
  cdr >> ros_message.translation_angle;

  // Member: pointing_magnitude
  cdr >> ros_message.pointing_magnitude;

  // Member: pointing_angle
  cdr >> ros_message.pointing_angle;

  // Member: rotation_speed
  cdr >> ros_message.rotation_speed;

  // Member: enable_switch
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.enable_switch = tmp ? true : false;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tnsy_interfaces
get_serialized_size(
  const tnsy_interfaces::msg::TnsyController & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: translation_magnitude
  {
    size_t item_size = sizeof(ros_message.translation_magnitude);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: translation_angle
  {
    size_t item_size = sizeof(ros_message.translation_angle);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: pointing_magnitude
  {
    size_t item_size = sizeof(ros_message.pointing_magnitude);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: pointing_angle
  {
    size_t item_size = sizeof(ros_message.pointing_angle);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: rotation_speed
  {
    size_t item_size = sizeof(ros_message.rotation_speed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: enable_switch
  {
    size_t item_size = sizeof(ros_message.enable_switch);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tnsy_interfaces
max_serialized_size_TnsyController(
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


  // Member: translation_magnitude
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: translation_angle
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: pointing_magnitude
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: pointing_angle
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: rotation_speed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: enable_switch
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
    using DataType = tnsy_interfaces::msg::TnsyController;
    is_plain =
      (
      offsetof(DataType, enable_switch) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _TnsyController__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const tnsy_interfaces::msg::TnsyController *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _TnsyController__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<tnsy_interfaces::msg::TnsyController *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _TnsyController__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const tnsy_interfaces::msg::TnsyController *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _TnsyController__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_TnsyController(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _TnsyController__callbacks = {
  "tnsy_interfaces::msg",
  "TnsyController",
  _TnsyController__cdr_serialize,
  _TnsyController__cdr_deserialize,
  _TnsyController__get_serialized_size,
  _TnsyController__max_serialized_size
};

static rosidl_message_type_support_t _TnsyController__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_TnsyController__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace tnsy_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_tnsy_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<tnsy_interfaces::msg::TnsyController>()
{
  return &tnsy_interfaces::msg::typesupport_fastrtps_cpp::_TnsyController__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, tnsy_interfaces, msg, TnsyController)() {
  return &tnsy_interfaces::msg::typesupport_fastrtps_cpp::_TnsyController__handle;
}

#ifdef __cplusplus
}
#endif
