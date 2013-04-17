#include "rbenv.h"

static int is_executable(char *path) {
  return access(path, F_OK | X_OK) == 0;
}

static char **reject_paths(char **paths, char *rejected_path) {
  size_t length = strarray_len(paths);
  char **result = strarray_alloc(length);
  rejected_path = strdup(expand_path(rejected_path));

  for (int i = 0, offset = 0; i < length; i++) {
    char *path = paths[i];
    if (!streq(rejected_path, expand_path(path))) {
      result[offset++] = path;
    }
  }

  free(rejected_path);
  return result;
}

int main(int argc, char **argv) {
  argv++;

  provide_rbenv_completions();
  if (argc > 1 && streq(argv[1], "--complete")) {
    rbenv_exec_subcommand("shims", strarray("--short", NULL));
    argv++;
  }

  rbenv_root = default(getenv("RBENV_ROOT"), "");
  char *version = rbenv_version_name();
  char *command = default(*argv, "");

  if (strlen(command) == 0) {
    fprintf(stderr, "Usage: rbenv which <command>\n");
    exit(1);
  }

  char *command_path;

  if (streq(version, "system")) {
    char *shims_path = join_path(rbenv_root, "shims");
    char **paths = strarray_split(default(getenv("PATH"), "/usr/bin:/bin"), ":");
    char **paths_without_shims = reject_paths(paths, shims_path);
    command_path = strdup(default(search_paths(paths_without_shims, command), ""));
    strarray_free(paths);
    free(paths_without_shims);
    free(shims_path);

  } else {
    char **parts = strarray(rbenv_root, "versions", version, "bin", command, NULL);
    command_path = strarray_join(parts, "/");
    free(parts);
  }

  if (command_path && is_executable(command_path)) {
    fprintf(stdout, "%s\n", command_path);
    return 0;

  } else {
    fprintf(stderr, "rbenv: %s: command not found\n", command);
    return 1;
  }
}
