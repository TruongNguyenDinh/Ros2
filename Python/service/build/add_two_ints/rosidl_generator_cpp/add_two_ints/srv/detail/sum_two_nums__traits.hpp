// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from add_two_ints:srv/SumTwoNums.idl
// generated code does not contain a copyright notice

#ifndef ADD_TWO_INTS__SRV__DETAIL__SUM_TWO_NUMS__TRAITS_HPP_
#define ADD_TWO_INTS__SRV__DETAIL__SUM_TWO_NUMS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "add_two_ints/srv/detail/sum_two_nums__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace add_two_ints
{

namespace srv
{

inline void to_flow_style_yaml(
  const SumTwoNums_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: a
  {
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << ", ";
  }

  // member: b
  {
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SumTwoNums_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: a
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << "\n";
  }

  // member: b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SumTwoNums_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace add_two_ints

namespace rosidl_generator_traits
{

[[deprecated("use add_two_ints::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const add_two_ints::srv::SumTwoNums_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  add_two_ints::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use add_two_ints::srv::to_yaml() instead")]]
inline std::string to_yaml(const add_two_ints::srv::SumTwoNums_Request & msg)
{
  return add_two_ints::srv::to_yaml(msg);
}

template<>
inline const char * data_type<add_two_ints::srv::SumTwoNums_Request>()
{
  return "add_two_ints::srv::SumTwoNums_Request";
}

template<>
inline const char * name<add_two_ints::srv::SumTwoNums_Request>()
{
  return "add_two_ints/srv/SumTwoNums_Request";
}

template<>
struct has_fixed_size<add_two_ints::srv::SumTwoNums_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<add_two_ints::srv::SumTwoNums_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<add_two_ints::srv::SumTwoNums_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace add_two_ints
{

namespace srv
{

inline void to_flow_style_yaml(
  const SumTwoNums_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: sum
  {
    out << "sum: ";
    rosidl_generator_traits::value_to_yaml(msg.sum, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SumTwoNums_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: sum
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sum: ";
    rosidl_generator_traits::value_to_yaml(msg.sum, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SumTwoNums_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace add_two_ints

namespace rosidl_generator_traits
{

[[deprecated("use add_two_ints::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const add_two_ints::srv::SumTwoNums_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  add_two_ints::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use add_two_ints::srv::to_yaml() instead")]]
inline std::string to_yaml(const add_two_ints::srv::SumTwoNums_Response & msg)
{
  return add_two_ints::srv::to_yaml(msg);
}

template<>
inline const char * data_type<add_two_ints::srv::SumTwoNums_Response>()
{
  return "add_two_ints::srv::SumTwoNums_Response";
}

template<>
inline const char * name<add_two_ints::srv::SumTwoNums_Response>()
{
  return "add_two_ints/srv/SumTwoNums_Response";
}

template<>
struct has_fixed_size<add_two_ints::srv::SumTwoNums_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<add_two_ints::srv::SumTwoNums_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<add_two_ints::srv::SumTwoNums_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<add_two_ints::srv::SumTwoNums>()
{
  return "add_two_ints::srv::SumTwoNums";
}

template<>
inline const char * name<add_two_ints::srv::SumTwoNums>()
{
  return "add_two_ints/srv/SumTwoNums";
}

template<>
struct has_fixed_size<add_two_ints::srv::SumTwoNums>
  : std::integral_constant<
    bool,
    has_fixed_size<add_two_ints::srv::SumTwoNums_Request>::value &&
    has_fixed_size<add_two_ints::srv::SumTwoNums_Response>::value
  >
{
};

template<>
struct has_bounded_size<add_two_ints::srv::SumTwoNums>
  : std::integral_constant<
    bool,
    has_bounded_size<add_two_ints::srv::SumTwoNums_Request>::value &&
    has_bounded_size<add_two_ints::srv::SumTwoNums_Response>::value
  >
{
};

template<>
struct is_service<add_two_ints::srv::SumTwoNums>
  : std::true_type
{
};

template<>
struct is_service_request<add_two_ints::srv::SumTwoNums_Request>
  : std::true_type
{
};

template<>
struct is_service_response<add_two_ints::srv::SumTwoNums_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ADD_TWO_INTS__SRV__DETAIL__SUM_TWO_NUMS__TRAITS_HPP_
