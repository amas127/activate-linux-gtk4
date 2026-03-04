#ifndef OPTION_OPTION_H_
#define OPTION_OPTION_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} OptionRgba;

typedef struct {
  const char *text1;
  const char *style1;
  const char *font1;

  const char *text2;
  const char *style2;
  const char *font2;

  float scale;
  uint64_t hshift;
  uint64_t vshift;
  OptionRgba rgba;

  bool daemonize;
  bool kill;
} Option;

extern Option parse_option_from_cli(int argc, char *argv[]);
extern const char *get_markup_from_style(const char *style);

#endif // OPTION_OPTION_H_
