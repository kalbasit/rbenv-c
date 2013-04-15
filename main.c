#include "rbenv.h"

int main(int argc, char **argv) {
  char *argv0 = *argv++;

  if (streq(*argv, "--debug")) {
    setenv("RBENV_DEBUG", "1", 1);
    argv++;
  }

  rbenv_initialize(argv0);

  char *command = *argv++;

  if (!command || streq(command, "") || streq(command, "-h") || streq(command, "--help")) {
    rbenv_print_help();
  } else if (streq(command, "-v")) {
    rbenv_print_version();
  } else {
    rbenv_exec_subcommand(command, argv);
  }

  return 0;
}
