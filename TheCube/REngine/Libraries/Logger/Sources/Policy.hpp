#pragma once

////////////////////////////////////////////////////////////////////////////////
// Logger library
////////////////////////////////////////////////////////////////////////////////
#include "Macros/UtilityMacros.hpp"
////////////////////////////////////////////////////////////////////////////////
// C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <string>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_BEGIN (ReLogger::Policy::Properties)
////////////////////////////////////////////////////////////////////////////////

enum class Color
{
  Black,
  Blue,
  BlueDark,
  Cyan,
  CyanDark,
  Gray,
  GrayDark,
  Green,
  GreenDark,
  Magenta,
  MagentaDark,
  Red,
  RedDark,
  White,
  Yellow,
  YellowDark
};

struct Label
{
  Color Error = Color::Red;
  Color Info = Color::Blue;
  Color Warning = Color::Yellow;
};

struct Text
{
  Color Error = Color::Red;
  Color Info = Color::Blue;
  Color Warning = Color::Yellow;
};

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_END (ReLogger::Policy::Properties)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_BEGIN (ReLogger::Policy)
////////////////////////////////////////////////////////////////////////////////

struct Console
{
  bool CreateConsole = false;

  Properties::Label labelColors;
  Properties::Text textColors;
};

struct File
{
  std::string Filename;
};

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_END (ReLogger::Policy)
////////////////////////////////////////////////////////////////////////////////
