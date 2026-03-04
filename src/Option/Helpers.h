#ifndef OPTION_HELPERS_H_
#define OPTION_HELPERS_H_

#include "Option/Option.h"
#include "Option/Types.h"

#define CH_RGBASEP ","

extern OptionRgba parse_rgba_from_string(char *srgba);
extern const char *parse_style_from_string(char *sstyle);
extern float parse_scale_from_string(char *sscale);
extern u64 parse_shift_from_string(char *sscale);

extern const char *get_markup_from_style(const char *style);

#endif // OPTION_HELPERS_H_
