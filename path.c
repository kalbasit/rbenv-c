#include "path.h"

char *getpwd() {
  long path_max = pathconf("/", _PC_PATH_MAX);
  size_t size = path_max < 1 ? _POSIX_PATH_MAX : path_max;
  char *buffer, *result;

  for (buffer = result = NULL; result == NULL; size *= 2) {
    buffer = realloc(buffer, size);
    if (buffer == NULL) abort();
    result = getcwd(buffer, size);
    if (result == NULL && errno != ERANGE) abort();
  }

  return result;
}

char *dirname(char *path) {
  char *result;

  if (path) {
    char *last_slash = strrchr(path, '/');
    if (last_slash) {
      size_t size = last_slash - path;
      result = calloc(size + 1, sizeof(char));
      memcpy(result, path, sizeof(char) * size);
      return result;
    }
  }

  result = calloc(2, sizeof(char));
  result[0] = '.';
  return result;
}

char *abs_dirname(char *path) {
  char *dir, *result, *resolved_name = NULL;
  dir = dirname(path);

  if ((result = realpath(dir, resolved_name))) {
    free(dir);
    return result;
  }

  return dir;
}

char *expand_path(char *path) {
  char *result, *resolved_path = NULL;
  result = realpath(path, resolved_path);
  return result ? result : path;
}

int cd(char *dir) {
  int fd = open(dir, O_RDONLY | O_DIRECTORY);
  if (fd == -1) return 0;
  int result = fchdir(fd);
  close(fd);
  return result == 0;
}

char *join_path(char *left, char *right) {
  char *trimmed_left = trim_trailing_slash(left);
  size_t size = strlen(trimmed_left) + strlen(right) + 2;
  char *result = malloc(sizeof(char) * size);
  snprintf(result, size, "%s/%s", trimmed_left, right);
  free(trimmed_left);
  return result;
}

static char *wildcard_escape(char *string) {
  size_t length = strlen(string);
  char *result;

  if (length == 1 && string[0] == '*') {
    result = strdup(string);

  } else {
    size_t size = length * 2 + 1;
    result = calloc(size, sizeof(char));

    for (int offset = 0; offset < length; offset++) {
      result[offset * 2 + 0] = '\\';
      result[offset * 2 + 1] = string[offset];
    }
  }

  return result;
}

char **wildcard_paths(char *base, ...) {
  va_list args;
  va_start(args, base);

  char *arg;
  char **parts = strarray(wildcard_escape(base), NULL);
  while ((arg = va_arg(args, char *))) {
    parts = strarray_push(parts, wildcard_escape(arg));
  }

  char *pattern = strarray_join(parts, "");
  strarray_free(parts);
  va_end(args);

  glob_t glob_result;
  glob(pattern, 0, NULL, &glob_result);

  size_t size = glob_result.gl_pathc;
  char **result = strarray_alloc(size);
  for (int i = 0; i < size; i++) result[i] = strdup(glob_result.gl_pathv[i]);

  globfree(&glob_result);
  return result;
}

char *trim_trailing_slash(char *string) {
  char *result = strdup(string);
  size_t length = strlen(result);
  size_t offset = length - 1;

  if (length > 1 && result[offset] == '/') {
    result[offset] = '\0';
  }

  return result;
}

void truncate_path(char *path) {
  if (!path) return;
  char *slash = strrchr(path, '/');
  path[slash ? slash - path : 0] = '\0';
}

static int is_file(char *path) {
  struct stat s;
  return stat(path, &s) == 0 && S_ISREG(s.st_mode);
}

char *search_paths(char **paths, char *filename) {
  char *result = NULL, *candidate;

  strarray_each(paths, char *path) {
    candidate = join_path(path, filename);
    if (is_file(candidate)) {
      result = candidate;
      break;
    }
    free(candidate);
  }

  return result;
}
