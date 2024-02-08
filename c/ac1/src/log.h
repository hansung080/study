#ifndef __LOG_H__
#define __LOG_H__

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

void debug(const char* format, ...);
void debug_n(const char* format, ...);
void info(const char* format, ...);
void info_n(const char* format, ...);
void warn_(const char* format, ...);
void warn_n(const char* format, ...);
void error(const char* format, ...);
void error_n(const char* format, ...);

#endif // __LOG_H__