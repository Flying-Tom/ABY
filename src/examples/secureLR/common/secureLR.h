#ifndef SECURELR_H
#define SECURELR_H
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>
#include <math.h>

#include <cassert>
#include <iostream>

#define DLLEXPORT __declspec(dllexport)

inline static uint32_t secparam = 128, nthreads = 1;
inline static uint16_t port = 7766;
inline static std::string address = "127.0.0.1";

#define DEBUG

#ifdef DEBUG
#define Log(...) color_print(__VA_ARGS__);
#define INFO(format, arg...) \
  printf("\033[0m\033[1;36m[INFO] \033[0m" format, ##arg);
#define WARNING(format, arg...) \
  printf("\033[0m\033[1;33m[WARNING] \033[0m" format, ##arg);
#define ERROR(format, arg...) \
  printf("\033[0m\033[1;31m[ERROR] \033[0m" format, ##arg);
#else
#define INFO(...)
#define WARNING(...)
#define ERROR(...)
#endif

// inline void color_print(const char* level, const char* msg) {
//   if (strcmp(level, "INFO") == 0) {
//     printf("\033[0m\033[1;36m[INFO] \033[0m%s\n", msg);
//   } else if (strcmp(level, "WARNING") == 0) {
//     printf("\033[0m\033[1;33m[WARNING] \033[0m%s\n", msg);
//   } else if (strcmp(level, "ERROR") == 0) {
//     printf("\033[0m\033[1;31m[ERROR] \033[0m%s\n", msg);
//   } else {
//     printf("%s\n", msg);
//   }
// };

#endif