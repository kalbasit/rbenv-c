#include "test.h"
#include "../path.h"

void test_dirname() {
  char *dir = dirname(NULL);
  assert(streq(".", dir), "dirname with null path");
  free(dir);

  dir = dirname("");
  assert(streq(".", dir), "dirname with empty path");
  free(dir);

  dir = dirname("one");
  assert(streq(".", dir), "dirname with no slash in path");
  free(dir);

  dir = dirname("one/two");
  assert(streq("one", dir), "dirname with one slash");
  free(dir);

  dir = dirname("one/two/three");
  assert(streq("one/two", dir), "dirname with two slashes");
  free(dir);
}

int main(int argc, char **argv) {
  begin();

  test_dirname();

  end();
}
