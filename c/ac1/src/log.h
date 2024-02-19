#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>

#define S_RESET    "\033[0m"
#define S_RED      "\033[0;31m"
#define S_RED_BOLD "\033[1;31m"
#define S_GREEN    "\033[0;32m"
#define S_YELLOW   "\033[0;33m"
#define S_BLUE     "\033[0;34m"

#define red(text)      S_RED text S_RESET
#define red_bold(text) S_RED_BOLD text S_RESET
#define green(text)    S_GREEN text S_RESET
#define yellow(text)   S_YELLOW text S_RESET
#define blue(text)     S_BLUE text S_RESET

#define T_DEBUG   green("debug")
#define T_INFO    blue("info")
#define T_WARNING yellow("warning")
#define T_ERROR   red_bold("error")

#define debug(format, ...)   fprintf(stdout, T_DEBUG": "format, ##__VA_ARGS__)
#define debug_n(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define info(format, ...)    fprintf(stdout, T_INFO": "format, ##__VA_ARGS__)
#define info_n(format, ...)  fprintf(stdout, format, ##__VA_ARGS__)
#define warn_(format, ...)   fprintf(stderr, T_WARNING": "format, ##__VA_ARGS__)
#define warn_n(format, ...)  fprintf(stderr, format, ##__VA_ARGS__)
#define error(format, ...)   fprintf(stderr, T_ERROR": "format, ##__VA_ARGS__)
#define error_n(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

#endif // __LOG_H__