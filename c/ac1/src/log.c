#include <stdio.h>
#include <stdarg.h>
#include "log.h"

void debug(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    fprintf(stdout, T_DEBUG": ");
    vfprintf(stdout, format, ap);
    va_end(ap);
}

void debug_n(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);
}

void info(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    fprintf(stdout, T_INFO": ");
    vfprintf(stdout, format, ap);
    va_end(ap);
}

void info_n(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);
}

void warn_(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    fprintf(stderr, T_WARNING": ");
    vfprintf(stderr, format, ap);
    va_end(ap);
}

void warn_n(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
}

void error(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    fprintf(stderr, T_ERROR": ");
    vfprintf(stderr, format, ap);
    va_end(ap);
}

void error_n(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
}
