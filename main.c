#include "rbenv.h"

int main(int argc, char **argv) {
  char *progname = *argv++;

  if (streq(*argv, "--debug")) {
    setenv("RBENV_DEBUG", "1", 1);
    argv++;
  }

  rbenv_initialize(progname);

  char *command = *argv++;

  if (!command || streq(command, "-h") || streq(command, "--help")) {
    rbenv_print_help();
  } else if (streq(command, "-v")) {
    rbenv_print_version();
  } else {
    rbenv_exec_subcommand(command, argv);
  }

  return 0;
}
