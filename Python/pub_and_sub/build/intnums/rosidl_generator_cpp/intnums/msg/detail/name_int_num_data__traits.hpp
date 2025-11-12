// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from intnums:msg/NameIntNumData.idl
// generated code does not contain a copyright notice

#ifndef INTNUMS__MSG__DETAIL__NAME_INT_NUM_DATA__TRAITS_HPP_
#define INTNUMS__MSG__DETAIL__NAME_INT_NUM_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "intnums/msg/detail/name_int_num_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'int_num_data'
#include "intnums/msg/detail/int_num_data__traits.hpp"

namespace intnums
{

namespace msg
{

inline void to_flow_style_yaml(
  const NameIntNumData & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: int_num_data
  {
    out << "int_num_data: ";
    to_flow_style_yaml(msg.int_num_data, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NameIntNumData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

  // member: int_num_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "int_num_data:\n";
    to_block_style_yaml(msg.int_num_data, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NameIntNumData & msg, bool use_flow_style = false)
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
  const intnums::msg::NameIntNumData & msg,
  std::ostream & out, size_t indentation = 0)
{
  intnums::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use intnums::msg::to_yaml() instead")]]
inline std::string to_yaml(const intnums::msg::NameIntNumData & msg)
{
  return intnums::msg::to_yaml(msg);
}

template<>
inline const char * data_type<intnums::msg::NameIntNumData>()
{
  return "intnums::msg::NameIntNumData";
}

template<>
inline const char * name<intnums::msg::NameIntNumData>()
{
  return "intnums/msg/NameIntNumData";
}

template<>
struct has_fixed_size<intnums::msg::NameIntNumData>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<intnums::msg::NameIntNumData>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<intnums::msg::NameIntNumData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INTNUMS__MSG__DETAIL__NAME_INT_NUM_DATA__TRAITS_HPP_
