#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Log.h"

const char *loglvl_debug = "[DEBUG]";
const char *loglvl_info = "[INFO ]";
const char *loglvl_warn = "[WARN ]";
const char *loglvl_error = "[ERROR]";

[[nodiscard]]
static inline bool term_color_rtcheck(void) {
  // return true if supporting terminal colors
  if (!isatty(STDOUT_FILENO))
    return false;
  const char *term = getenv("TERM");
  return term && (strcmp(term, "dumb") != 0);
}

void setup_colorized_loglevel(void) {
  // setup colorized log level if supported
  if (term_color_rtcheck()) {
    loglvl_debug = "\033[32m[DEBUG]\033[0m";
    loglvl_info = "\033[34m[INFO ]\033[0m";
    loglvl_warn = "\033[33m[WARN ]\033[0m";
    loglvl_error = "\033[31m[ERROR]\033[0m";
  }
}
