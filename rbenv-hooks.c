#include "rbenv.h"

static void print_hooks(char *command, char *path) {
  char **scripts = wildcard_paths(path, "/", command, "/", "*", ".bash", NULL);
  strarray_each(scripts, char *script_path) {
    char *resolved_script_path = NULL;
    if ((resolved_script_path = realpath(script_path, resolved_script_path))) {
      fprintf(stdout, "%s\n", resolved_script_path);
    }
  }
  strarray_free(scripts);
}

int main(int argc, char **argv) {
  char *command;

  if (argc == 2 && (command = argv[1]) && strlen(command) > 0) {
    char *hook_path = default(getenv("RBENV_HOOK_PATH"), "");
    char *state, *path = strtok_r(hook_path, ":", &state);

    while (path) {
      print_hooks(command, path);
      path = strtok_r(NULL, ":", &state);
    }

    return 0;

  } else {
    rbenv_print_usage("hooks");
    return 1;
  }
}

