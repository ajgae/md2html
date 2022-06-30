#pragma once

// no include directives in this file!!!

typedef enum {
  M2H_LOGLEVEL_ERROR = 1,
  M2H_LOGLEVEL_WARN,
  M2H_LOGLEVEL_NOTE,
} m2h_loglevel_t;

// defined in main.c, declared here because logging macros need it
extern m2h_loglevel_t loglevel;

#define M2H_LOG(lvl, fp, fmt, ...) \
  if (lvl <= loglevel) \
    fprintf(fp, "%s:%d:" fmt "\n", __FILE__, __LINE__\
            __VA_OPT__(,) __VA_ARGS__)

#define M2H_ERROR(fmt, ...)\
  M2H_LOG(M2H_LOGLEVEL_ERROR, stderr, "ERROR: " fmt, __VA_ARGS__)
  
#define M2H_WARN(fmt, ...)\
  M2H_LOG(M2H_LOGLEVEL_WARN, stderr, "WARNING: " fmt, __VA_ARGS__)
  
#define M2H_NOTE(fmt, ...)\
  M2H_LOG(M2H_LOGLEVEL_NOTE, stderr, "NOTE: " fmt, __VA_ARGS__)

