#ifndef CSPIN_INCLUDE_CSPIN_EXCEPTION_HPP_
#define CSPIN_INCLUDE_CSPIN_EXCEPTION_HPP_

#include <exception>
#include <string>

namespace cspin
{

class RuntimeError : public std::exception
{
public:
  explicit RuntimeError(const char* msg) : msg_(msg) {}
  explicit RuntimeError(const std::string& msg) : msg_(msg) {}
  virtual ~RuntimeError() throw() {}
  virtual const char* what() const throw() { return msg_.c_str(); }

private:
  std::string msg_;
};

class LogicError : public std::exception
{
public:
  explicit LogicError(const char* msg) : msg_(msg) {}
  explicit LogicError(const std::string& msg) : msg_(msg) {}
  virtual ~LogicError() throw() {}
  virtual const char* what() const throw() { return msg_.c_str(); }

private:
  std::string msg_;
};

class NotImplementedError : public std::exception
{
public:
  explicit NotImplementedError(const char* msg) : msg_(msg) {}
  explicit NotImplementedError(const std::string& msg) : msg_(msg) {}
  virtual ~NotImplementedError() throw() {}
  virtual const char* what() const throw() { return msg_.c_str(); }

private:
  std::string msg_;
};

} // namespace cspin

#endif // CSPIN_INCLUDE_CSPIN_EXCEPTION_HPP_
