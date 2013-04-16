#include "rbenv.h"

static void detect_path(char *dirname, char *basename) {
  char *path = join_path(dirname, basename);
  if (access(path, R_OK) == 0) {
    fprintf(stdout, "%s\n", path);
    exit(0);
  } else {
    free(path);
  }
}

static void find_local_version_file(char *root) {
  char *path = strdup(root);
  while (strlen(path) > 0) {
    detect_path(path, ".ruby-version");
    detect_path(path, ".rbenv-version");
    truncate_path(path);
  }
  free(path);
}

int main(int argc, char **argv) {
  char *rbenv_dir = default(getenv("RBENV_DIR"), "");
  find_local_version_file(rbenv_dir);

  char *pwd = getpwd();
  if (!streq(rbenv_dir, pwd)) find_local_version_file(pwd);
  free(pwd);

  char *rbenv_root = default(getenv("RBENV_ROOT"), "");
  detect_path(rbenv_root, "version");
  detect_path(rbenv_root, "global");
  detect_path(rbenv_root, "default");

  fprintf(stdout, "%s/version\n", rbenv_root);
  return 0;
}
