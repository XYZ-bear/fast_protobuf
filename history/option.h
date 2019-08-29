#pragma once

//#define USE_SET_GET
#define USE_TAG
#define GENERATE_CODE

#ifdef GENERATE_CODE
#include "collector.h"
#else
#include "proto_base10.h"
#endif // GENERATE_CODE