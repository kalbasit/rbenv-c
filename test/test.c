#include "test.h"

void begin() {
  assertions = 0;
  failures = 0;
}

void end() {
  fprintf(stdout, "%d assertions, %d failures\n", assertions, failures);
  exit(failures != 0);
}

void assert(int expression, char *message) {
  assertions++;
  if (expression) {
    fprintf(stderr, "✓ %s\n", message);
  } else {
    fprintf(stderr, "✗ %s\n", message);
    failures++;
  }
}
