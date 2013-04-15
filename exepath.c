#include "exepath.h"

static char *exepath_argv0_fallback(char *argv0) {
  return strdup(argv0 ? argv0 : "(unknown)");
}

#ifdef __APPLE__

#include <mach-o/dyld.h>

char *_exepath(char *argv0) {
  char exepath[PATH_MAX + 1];
  char *real_exepath = calloc(PATH_MAX + 1, sizeof(char));
  uint32_t size = sizeof(exepath);

  _NSGetExecutablePath(exepath, &size);

  if ((real_exepath = realpath(exepath, real_exepath))) {
    return real_exepath;
  } else {
    return exepath_argv0_fallback(argv0);
  }
}

#else

char *_exepath(char *argv0) {
  return exepath_argv0_fallback(argv0);
}

#endif
