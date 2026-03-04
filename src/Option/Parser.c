#include "Option/Parser.h"

#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "Log.h"
#include "Option/Helpers.h"
#include "Option/Option.h"

static inline void showhelp() {
  warn("Function 'showhelp' is not implemented yet.");
}

static const Option user_option_fallback = {
    .text1 = "Activate Linux",
    .style1 = "Normal",
    .font1 = "",
    .text2 = "Go to Settings to activate Linux.",
    .style2 = "Normal",
    .font2 = "",

    .scale = 1.f,
    .hshift = 330,
    .vshift = 115,
    .rgba = (OptionRgba){196, 196, 196, 102},

    .daemonize = false,
    .kill = false,
};

static const struct option available_opts_long[] = {
    {"help", no_argument, NULL, 'h'},

    {"text1", required_argument, NULL, 'x'},
    {"style1", required_argument, NULL, 'e'},
    {"font1", required_argument, NULL, 'o'},
    {"text2", required_argument, NULL, 'y'},
    {"style2", required_argument, NULL, 'f'},
    {"font2", required_argument, NULL, 'p'},

    {"scale", required_argument, NULL, 's'},
    {"hshift", required_argument, NULL, 'w'},
    {"vshift", required_argument, NULL, 'v'},
    {"rgba", required_argument, NULL, 'r'},

    {"daemonize", no_argument, NULL, 'd'},
    {"kill", no_argument, NULL, 'k'},

    {0, 0, 0, 0},
};

static const char *const available_opts_short = "hx:e:o:y:f:p:s:w:v:r:dk";

Option parse_option_from_cli(int argc, char *argv[]) {
  auto opt = user_option_fallback;

  char *duparg;
  int ch = 0, optidx = 0;
  while ((ch = getopt_long(argc, argv, available_opts_short,
                           available_opts_long, &optidx)) != -1) {

    switch (ch) {

    case 'h':
      showhelp();
      exit(EXIT_SUCCESS);

    case 'x':
      opt.text1 = optarg;
      break;

    case 'e':
      duparg = strdup(optarg);
      opt.style1 = parse_style_from_string(duparg);
      free(duparg);
      break;

    case 'o':
      opt.font1 = optarg;
      break;

    case 'y':
      opt.text2 = optarg;
      break;

    case 'f':
      duparg = strdup(optarg);
      opt.style2 = parse_style_from_string(duparg);
      free(duparg);
      break;

    case 'p':
      opt.font2 = optarg;
      break;

    case 's':
      duparg = strdup(optarg);
      opt.scale = parse_scale_from_string(duparg);
      free(duparg);
      break;

    case 'w':
      duparg = strdup(optarg);
      opt.hshift = parse_shift_from_string(duparg);
      free(duparg);
      break;

    case 'v':
      duparg = strdup(optarg);
      opt.vshift = parse_shift_from_string(duparg);
      free(duparg);
      break;

    case 'r':
      duparg = strdup(optarg);
      opt.rgba = parse_rgba_from_string(duparg);
      free(duparg);
      break;

    case 'd':
      opt.daemonize = true;
      break;

    case 'k':
      opt.kill = true;
      break;

    case '?':
      if (optarg) {
        warn("Unknown option '%c' with value '%s'", optopt, optarg);
      } else {
        warn("Unknown option '%c'", optopt);
      }
      break;

    default:
      error("Cannot match any branch when parsing arguments using "
            "'getopt_long'. This is a bug.");
      exit(EXIT_FAILURE);
    }
  }

  while (optind < argc) {
    warn("Got non-option ARGV-elements '%s'", argv[optind++]);
  }

  return opt;
}
