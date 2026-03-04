#ifndef LOG_H_
#define LOG_H_

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

extern void setup_colorized_loglevel(void);

#define lvllog(lvl, fmtstr, ...)                                               \
  do {                                                                         \
    fprintf(stderr, "%s " fmtstr "\n", lvl, ##__VA_ARGS__);                    \
  } while (0)

extern const char *loglvl_info;
extern const char *loglvl_warn;
extern const char *loglvl_error;

#define info(fmtstr, ...) lvllog(loglvl_info, fmtstr, ##__VA_ARGS__);
#define warn(fmtstr, ...) lvllog(loglvl_warn, fmtstr, ##__VA_ARGS__);
#define error(fmtstr, ...) lvllog(loglvl_error, fmtstr, ##__VA_ARGS__);

#ifndef NDEBUG
extern const char *loglvl_debug;
#define debug(fmtstr, ...) lvllog(loglvl_debug, fmtstr, ##__VA_ARGS__);
#else
#define debug(...) (void)0
#endif

#endif // LOG_H_
