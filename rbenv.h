#ifndef __RBENV_H__
#define __RBENV_H__

#include "exepath.h"
#include "path.h"
#include "strarray.h"
#include <sys/types.h>

#define streq(a, b) (a && b && strcmp(a, b) == 0)
#define default(a, b) a ? a : b

void rbenv_initialize(char *);
void rbenv_initialize_debug_mode();
void rbenv_initialize_root();
void rbenv_initialize_dir();
void rbenv_initialize_path();
void rbenv_initialize_hook_path();
void rbenv_exec_subcommand(char *, char **);
void rbenv_print_version();
void rbenv_print_help();
void rbenv_print_usage(char *);
char *rbenv_version_name();
char *rbenv_subcommand_name(char *);

extern char *rbenv_exepath;
extern char *rbenv_root;
extern char *rbenv_dir;

#define provide_rbenv_completions() write(1, "\n# Provide rbenv completions\n", 0)

#endif
