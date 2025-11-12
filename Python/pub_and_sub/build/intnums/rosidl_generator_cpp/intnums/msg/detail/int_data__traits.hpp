// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from intnums:msg/IntData.idl
// generated code does not contain a copyright notice

#ifndef INTNUMS__MSG__DETAIL__INT_DATA__TRAITS_HPP_
#define INTNUMS__MSG__DETAIL__INT_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "intnums/msg/detail/int_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace intnums
{

namespace msg
{

inline void to_flow_style_yaml(
  const IntData & msg,
  std::ostream & out)
{
  out << "{";
  // member: num_a
  {
    out << "num_a: ";
    rosidl_generator_traits::value_to_yaml(msg.num_a, out);
    out << ", ";
  }

  // member: num_b
  {
    out << "num_b: ";
    rosidl_generator_traits::value_to_yaml(msg.num_b, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const IntData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: num_a
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_a: ";
    rosidl_generator_traits::value_to_yaml(msg.num_a, out);
    out << "\n";
  }

  // member: num_b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_b: ";
    rosidl_generator_traits::value_to_yaml(msg.num_b, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const IntData & msg, bool use_flow_style = false)
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

}  // namespace intnums

namespace rosidl_generator_traits
{

[[deprecated("use intnums::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const intnums::msg::IntData & msg,
  std::ostream & out, size_t indentation = 0)
{
  intnums::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use intnums::msg::to_yaml() instead")]]
inline std::string to_yaml(const intnums::msg::IntData & msg)
{
  return intnums::msg::to_yaml(msg);
}

template<>
inline const char * data_type<intnums::msg::IntData>()
{
  return "intnums::msg::IntData";
}

template<>
inline const char * name<intnums::msg::IntData>()
{
  return "intnums/msg/IntData";
}

template<>
struct has_fixed_size<intnums::msg::IntData>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<intnums::msg::IntData>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<intnums::msg::IntData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INTNUMS__MSG__DETAIL__INT_DATA__TRAITS_HPP_
