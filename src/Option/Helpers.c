#include "Option/Helpers.h"

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "Log.h"

static inline void assert_string_nonnull(const char *str) {
  if (!str) {
    error("AssertError: Got null string pointer");
    exit(EXIT_FAILURE);
  } else if (!(*str)) {
    error("AssertError: Got empty string");
    exit(EXIT_FAILURE);
  }
}

static inline u8 get_rgba_component_from_string(const char *str) {
  char *end;
  errno = 0;
  auto l = strtol(str, &end, 0);

  if (end == str) {
    error("Cannot parse '%s' as long integer", str);
    exit(EXIT_FAILURE);
  } else if (errno == ERANGE) {
    error("Overflow/Underflow when parsing '%s'", str);
    exit(EXIT_FAILURE);
  } else if (l < 0 || l > UINT8_MAX) {
    error("Value out of RGBA range (0-255): %ld", l);
    exit(EXIT_FAILURE);
  }

  if (*end)
    warn("'%s' is partially interpreted as %ld", str, l);

  return (u8)l;
}

static inline float get_scale_from_string(const char *str) {
  char *end;
  errno = 0;
  auto f = strtof(str, &end);

  if (end == str) {
    error("Cannot parse '%s' as float", str);
    exit(EXIT_FAILURE);
  } else if (errno == ERANGE) {
    error("Overflow/Underflow when parsing '%s'", str);
    exit(EXIT_FAILURE);
  } else if (f <= 0.f) {
    error("Scale should be greater than 0, got %.3f", f);
    exit(EXIT_FAILURE);
  }

  if (*end)
    warn("'%s' is partially interpreted as %.3f", str, f);

  return f;
}

static inline u64 get_shift_from_string(const char *str) {
  char *end;
  errno = 0;
  auto im = strtoimax(str, &end, 0);

  if (end == str) {
    error("Cannot parse '%s' as intmax_t", str);
    exit(EXIT_FAILURE);
  } else if (errno == ERANGE) {
    error("Overflow/Underflow when parsing '%s'", str);
    exit(EXIT_FAILURE);
  } else if (im < 0 || im > UINT64_MAX) {
    error("Impossible width/height: %jd", im);
    exit(EXIT_FAILURE);
  }

  if (*end)
    warn("'%s' is partially interpreted as %jd", str, im);

  return (u64)im;
}

OptionRgba parse_rgba_from_string(char *srgba) {
  debug("Parsing rgba from string '%s'", srgba);
  auto srgba_orig = strdup(srgba);

  OptionRgba rgba;

  char *d_srgba[4] = {nullptr, nullptr, nullptr, nullptr};
  u8 *u8_rgba[4] = {&rgba.r, &rgba.g, &rgba.b, &rgba.a};

  for (int i = 0; i < 4; ++i) {
    if (i == 0) {
      d_srgba[i] = strtok(srgba, CH_RGBASEP);
    } else {
      d_srgba[i] = strtok(nullptr, CH_RGBASEP);
    }
    assert_string_nonnull(d_srgba[i]);
    *u8_rgba[i] = get_rgba_component_from_string(d_srgba[i]);
  }

  if (strtok(nullptr, CH_RGBASEP)) {
    warn("'%s' is partially interpreted", srgba_orig);
  }
  free(srgba_orig);

  debug("Got Rgba { r=%d, g=%d, b=%d, a=%d }", rgba.r, rgba.g, rgba.b, rgba.a);

  return rgba;
}

static inline void capitalize(char *str) {
  assert_string_nonnull(str);
  *str = (char)toupper((unsigned char)*str);
  str++;
  while (*str) {
    *str = (char)tolower((unsigned char)*str);
    str++;
  }
}

static const struct StyleMarkupPair {
  const char *k;
  const char *v;
} style_alternatives[] = {
    {.k = "Normal", .v = "style='normal'"},
    {.k = "Italic", .v = "style='italic'"},
    {.k = "Oblique", .v = "style='oblique'"},
    {.k = "Bold", .v = "weight='bold'"},
    {.k = "Underline", .v = "underline='single'"},
    {.k = "Underline_single", .v = "underline='single'"},
    {.k = "Underline_double", .v = "underline='double'"},
    {.k = "Strike", .v = "strikethrough='true'"},
    {.k = nullptr, .v = nullptr},
};

const char *parse_style_from_string(char *sstyle) {
  debug("Parsing style from string '%s'", sstyle);

  capitalize(sstyle);
  debug("String has been capitalized to '%s'", sstyle);

  for (const struct StyleMarkupPair *alt = style_alternatives; alt->k; ++alt) {
    debug("Compare input style '%s' and target '%s'", sstyle, alt->k);
    if (strcmp(sstyle, alt->k) == 0) {
      return alt->k;
    }
  }

  error("'%s' cannot match any of the style alternatives", sstyle);
  exit(EXIT_FAILURE);
}

const char *get_markup_from_style(const char *style) {
  debug("Get markup string from style string '%s'", style);

  for (const struct StyleMarkupPair *alt = style_alternatives; alt->k; ++alt) {
    debug("Compare input style '%s' and target '%s'", style, alt->k);
    if (strcmp(style, alt->k) == 0) {
      return alt->v;
    }
  }

  error("'%s' cannot match any of the style alternatives", style);
  exit(EXIT_FAILURE);
}

float parse_scale_from_string(char *sscale) {
  debug("Parsing scale from string '%s'", sscale);

  auto scale = get_scale_from_string(sscale);

  return scale;
}

u64 parse_shift_from_string(char *sshift) {
  debug("Parsing hshift/vshift from string '%s'", sshift);

  auto shift = get_shift_from_string(sshift);

  return shift;
}
