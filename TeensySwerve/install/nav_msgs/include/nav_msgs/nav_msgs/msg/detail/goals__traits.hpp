// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from nav_msgs:msg/Goals.idl
// generated code does not contain a copyright notice

#ifndef NAV_MSGS__MSG__DETAIL__GOALS__TRAITS_HPP_
#define NAV_MSGS__MSG__DETAIL__GOALS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "nav_msgs/msg/detail/goals__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'goals'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace nav_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Goals & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: goals
  {
    if (msg.goals.size() == 0) {
      out << "goals: []";
    } else {
      out << "goals: [";
      size_t pending_items = msg.goals.size();
      for (auto item : msg.goals) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Goals & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: goals
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.goals.size() == 0) {
      out << "goals: []\n";
    } else {
      out << "goals:\n";
      for (auto item : msg.goals) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Goals & msg, bool use_flow_style = false)
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

}  // namespace nav_msgs

namespace rosidl_generator_traits
{

[[deprecated("use nav_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const nav_msgs::msg::Goals & msg,
  std::ostream & out, size_t indentation = 0)
{
  nav_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use nav_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const nav_msgs::msg::Goals & msg)
{
  return nav_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<nav_msgs::msg::Goals>()
{
  return "nav_msgs::msg::Goals";
}

template<>
inline const char * name<nav_msgs::msg::Goals>()
{
  return "nav_msgs/msg/Goals";
}

template<>
struct has_fixed_size<nav_msgs::msg::Goals>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<nav_msgs::msg::Goals>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<nav_msgs::msg::Goals>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // NAV_MSGS__MSG__DETAIL__GOALS__TRAITS_HPP_
