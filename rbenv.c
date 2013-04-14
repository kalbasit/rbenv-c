#include "rbenv.h"

static int hasenv(char *);
static int run(char *, char **);
static void cd_or_exit(char *);
static char **make_argv(char *, char **);
static void redirect_stdout_to_stderr();

void rbenv_initialize(char *progname) {
  if (!rbenv_progname) {
    rbenv_progname = progname;
    rbenv_initialize_debug_mode();
    rbenv_initialize_root();
    rbenv_initialize_dir();
    rbenv_initialize_path();
    rbenv_initialize_hook_path();
  }
}

void rbenv_initialize_debug_mode() {
  if (hasenv("RBENV_DEBUG")) {
    setenv("PS4", "+ [${BASH_SOURCE##*/}:${LINENO}] ", 1);
  }
}

void rbenv_initialize_root() {
  if (hasenv("RBENV_ROOT")) {
    rbenv_root = trim_trailing_slash(getenv("RBENV_ROOT"));
  } else {
    rbenv_root = join_path(default(getenv("HOME"), "/"), ".rbenv");
  }

  setenv("RBENV_ROOT", rbenv_root, 1);
}

void rbenv_initialize_dir() {
  char *pwd = getpwd();

  if (hasenv("RBENV_DIR")) {
    cd_or_exit(getenv("RBENV_DIR"));
    rbenv_dir = getpwd();
    cd_or_exit(pwd);
    free(pwd);
  } else {
    rbenv_dir = pwd;
  }

  setenv("RBENV_DIR", rbenv_dir, 1);
}

void rbenv_initialize_path() {
  char **dirs = wildcard_paths(rbenv_root, "/plugins/", "*", "/bin", NULL);
  dirs = strarray_unshift(dirs, abs_dirname(rbenv_progname));
  dirs = strarray_push(dirs, strdup(default(getenv("PATH"), "")));

  char *path = strarray_join(dirs, ":");
  setenv("PATH", path, 1);

  strarray_free(dirs);
  free(path);
}

void rbenv_initialize_hook_path() {
  char *rbenv_d = calloc(strlen(rbenv_root) + 9, sizeof(char));
  strcat(rbenv_d, rbenv_root);
  strcat(rbenv_d, "/rbenv.d");

  char **dirs = wildcard_paths(rbenv_root, "/plugins/", "*", "/etc/rbenv.d", NULL);
  dirs = strarray_unshift(dirs, strdup("/usr/local/etc/rbenv.d:/etc/rbenv.d:/usr/lib/rbenv/hooks"));
  dirs = strarray_unshift(dirs, rbenv_d);
  dirs = strarray_unshift(dirs, strdup(default(getenv("RBENV_HOOK_PATH"), "")));

  char *hook_path = strarray_join(dirs, ":");
  setenv("RBENV_HOOK_PATH", hook_path, 1);

  strarray_free(dirs);
  free(hook_path);
}

void rbenv_exec_subcommand(char *command, char **argv) {
  char *subcommand = rbenv_subcommand_name(command);
  execvp(subcommand, make_argv(subcommand, argv));
  fprintf(stderr, "rbenv: no such command `%s'\n", command);
  exit(1);
}

void rbenv_print_version() {
  run("rbenv---version", NULL);
}

void rbenv_print_help() {
  redirect_stdout_to_stderr();
  run("rbenv---version", NULL);
  run("rbenv-help", NULL);
}

char *rbenv_subcommand_name(char *command) {
  size_t size = strlen(command) + strlen("rbenv-") + 1;
  char *result = malloc(sizeof(char) * size);
  snprintf(result, size, "rbenv-%s", command);
  return result;
}

static int hasenv(char *name) {
  char *value = getenv(name);
  return value && strlen(value) > 0;
}

static int run(char *command, char **args) {
  int status;
  pid_t pid = vfork();

  if (pid == -1) {
    abort();
  } else if (pid == 0) {
    execvp(command, make_argv(command, args));
    _exit(1);
  } else {
    wait(&status);
    return status;
  }
}

static void cd_or_exit(char *dir) {
  if (!cd(dir)) {
    fprintf(stderr, "rbenv: cannot change working directory to `%s'\n", dir);
    exit(1);
  }
}

static char **make_argv(char *command, char **args) {
  char **argv = strarray_dup(args);
  argv = strarray_unshift(argv, command);
  return argv;
}

static void redirect_stdout_to_stderr() {
  close(1);
  dup2(2, 1);
}
