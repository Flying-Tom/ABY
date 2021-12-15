#ifndef SECURELR_H
#define SECURELR_H
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>
#include <cassert>
#include <math.h>

#define DLLEXPORT __declspec(dllexport)

inline static uint32_t secparam = 128, nthreads = 1;
inline static uint16_t port = 7766;
inline static std::string address = "127.0.0.1";

#endif