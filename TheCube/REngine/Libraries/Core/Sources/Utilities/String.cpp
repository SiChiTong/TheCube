////////////////////////////////////////////////////////////////////////////////
#include "String.hpp"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

// Constructors
String::String ()
  : internal_string {}
{
}

String::String (const char* c_str)
  : internal_string { c_str }
{
}

String::String (const std::string& str)
  : internal_string { str }
{
}

// Copy & Move constructors
String::String
(const String& other)
  : internal_string { other.internal_string }
{
}

String::String (String&& other)
  : internal_string { std::move (other.internal_string) }
  , internal_wstring { std::move (other.internal_wstring) }
{
}

// Copy & Move assignment operators
const String&
String::operator= (const String& other)
{
  this->internal_string = other.internal_string;
  this->internal_wstring = other.internal_wstring;

  return *this;
}

const String&
String::operator= (String&& other)
{
  this->internal_string = std::move (other.internal_string);
  this->internal_wstring = std::move (other.internal_wstring);

  return *this;
}

// Operators
const String&
String::operator= (const char*& c_str)
{
  this->internal_string = c_str;

  return *this;
}

const String&
String::operator= (const std::string& str)
{
  this->internal_string = str;

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core)
////////////////////////////////////////////////////////////////////////////////
