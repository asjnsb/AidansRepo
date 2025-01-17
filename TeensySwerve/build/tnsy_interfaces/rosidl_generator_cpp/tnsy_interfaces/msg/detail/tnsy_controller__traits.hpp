// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from tnsy_interfaces:msg/TnsyController.idl
// generated code does not contain a copyright notice

#ifndef TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__TRAITS_HPP_
#define TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "tnsy_interfaces/msg/detail/tnsy_controller__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace tnsy_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TnsyController & msg,
  std::ostream & out)
{
  out << "{";
  // member: translation_magnitude
  {
    out << "translation_magnitude: ";
    rosidl_generator_traits::value_to_yaml(msg.translation_magnitude, out);
    out << ", ";
  }

  // member: translation_angle
  {
    out << "translation_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.translation_angle, out);
    out << ", ";
  }

  // member: rotation_speed
  {
    out << "rotation_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.rotation_speed, out);
    out << ", ";
  }

  // member: pointing_magnitude
  {
    out << "pointing_magnitude: ";
    rosidl_generator_traits::value_to_yaml(msg.pointing_magnitude, out);
    out << ", ";
  }

  // member: pointing_angle
  {
    out << "pointing_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.pointing_angle, out);
    out << ", ";
  }

  // member: enable_switch
  {
    out << "enable_switch: ";
    rosidl_generator_traits::value_to_yaml(msg.enable_switch, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TnsyController & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: translation_magnitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "translation_magnitude: ";
    rosidl_generator_traits::value_to_yaml(msg.translation_magnitude, out);
    out << "\n";
  }

  // member: translation_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "translation_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.translation_angle, out);
    out << "\n";
  }

  // member: rotation_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rotation_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.rotation_speed, out);
    out << "\n";
  }

  // member: pointing_magnitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pointing_magnitude: ";
    rosidl_generator_traits::value_to_yaml(msg.pointing_magnitude, out);
    out << "\n";
  }

  // member: pointing_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pointing_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.pointing_angle, out);
    out << "\n";
  }

  // member: enable_switch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enable_switch: ";
    rosidl_generator_traits::value_to_yaml(msg.enable_switch, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TnsyController & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace tnsy_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use tnsy_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const tnsy_interfaces::msg::TnsyController & msg,
  std::ostream & out, size_t indentation = 0)
{
  tnsy_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use tnsy_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const tnsy_interfaces::msg::TnsyController & msg)
{
  return tnsy_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<tnsy_interfaces::msg::TnsyController>()
{
  return "tnsy_interfaces::msg::TnsyController";
}

template<>
inline const char * name<tnsy_interfaces::msg::TnsyController>()
{
  return "tnsy_interfaces/msg/TnsyController";
}

template<>
struct has_fixed_size<tnsy_interfaces::msg::TnsyController>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<tnsy_interfaces::msg::TnsyController>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<tnsy_interfaces::msg::TnsyController>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__TRAITS_HPP_
