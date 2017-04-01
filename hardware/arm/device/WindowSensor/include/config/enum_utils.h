#ifndef CONFIG_ENUM_UTILS_H_
#define CONFIG_ENUM_UTILS_H_

#define __enum__or__operator__(type) inline type operator|(type a, type b) { return static_cast<type>(static_cast<int>(a) | static_cast<int>(b)); }

#endif
