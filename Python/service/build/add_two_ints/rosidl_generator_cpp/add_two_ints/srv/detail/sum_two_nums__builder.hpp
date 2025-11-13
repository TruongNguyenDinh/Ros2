// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from add_two_ints:srv/SumTwoNums.idl
// generated code does not contain a copyright notice

#ifndef ADD_TWO_INTS__SRV__DETAIL__SUM_TWO_NUMS__BUILDER_HPP_
#define ADD_TWO_INTS__SRV__DETAIL__SUM_TWO_NUMS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "add_two_ints/srv/detail/sum_two_nums__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace add_two_ints
{

namespace srv
{

namespace builder
{

class Init_SumTwoNums_Request_b
{
public:
  explicit Init_SumTwoNums_Request_b(::add_two_ints::srv::SumTwoNums_Request & msg)
  : msg_(msg)
  {}
  ::add_two_ints::srv::SumTwoNums_Request b(::add_two_ints::srv::SumTwoNums_Request::_b_type arg)
  {
    msg_.b = std::move(arg);
    return std::move(msg_);
  }

private:
  ::add_two_ints::srv::SumTwoNums_Request msg_;
};

class Init_SumTwoNums_Request_a
{
public:
  Init_SumTwoNums_Request_a()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SumTwoNums_Request_b a(::add_two_ints::srv::SumTwoNums_Request::_a_type arg)
  {
    msg_.a = std::move(arg);
    return Init_SumTwoNums_Request_b(msg_);
  }

private:
  ::add_two_ints::srv::SumTwoNums_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::add_two_ints::srv::SumTwoNums_Request>()
{
  return add_two_ints::srv::builder::Init_SumTwoNums_Request_a();
}

}  // namespace add_two_ints


namespace add_two_ints
{

namespace srv
{

namespace builder
{

class Init_SumTwoNums_Response_sum
{
public:
  Init_SumTwoNums_Response_sum()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::add_two_ints::srv::SumTwoNums_Response sum(::add_two_ints::srv::SumTwoNums_Response::_sum_type arg)
  {
    msg_.sum = std::move(arg);
    return std::move(msg_);
  }

private:
  ::add_two_ints::srv::SumTwoNums_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::add_two_ints::srv::SumTwoNums_Response>()
{
  return add_two_ints::srv::builder::Init_SumTwoNums_Response_sum();
}

}  // namespace add_two_ints

#endif  // ADD_TWO_INTS__SRV__DETAIL__SUM_TWO_NUMS__BUILDER_HPP_
