#include <stdio.h>

static int whitespace(int c) {
  return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

int main(int argc, char **argv) {
  int status = 1;

  if (argc == 2) {
    FILE *file = fopen(argv[1], "r");

    if (file) {
      int c;

      do {
        c = fgetc(file);
        if (feof(file)) {
          c = 0;
          break;
        }
      } while (whitespace(c));

      if (c) {
        fputc(c, stdout);

        while ((c = fgetc(file))) {
          if (whitespace(c) || feof(file)) break;
          fputc(c, stdout);
          status = 0;
        }
      }

      if (status == 0) {
        fputc('\n', stdout);
      }

      fclose(file);
    }
  }

  return status;
}
