#pragma once

// - - - - - -
// math libraries & definitions
// - - - - - - 

#include <cmath>
#include "Shared.hpp"

#undef M_PI	// SDL wants to define this for us? we'll use our own instead
#define M_PI 3.14159265358979323846

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define Clamp(value, lower, upper) (min(max((value), (lower)), (upper)))
#define randf() ((float)(rand()) / (float)(RAND_MAX))

#include "Matrix.hpp"
#include "Vector.hpp"