#pragma once

// - - - - - -
// shared includes and definitions
// - - - - - -

#include <cstdlib>
#include <cstring>

#define intern static
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

#define FlagSet(mask, flag) ((mask) |= (flag))
#define FlagClear(mask, flag) ((mask) &= ~(flag))
#define FlagTest(mask, flag) (((mask) & (flag)) == (flag))

#include "Assert.hpp"
#include "Math.hpp"
#include "Console.hpp"
#include "Logger/Logger.hpp"
#include "IO.hpp"