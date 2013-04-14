#include "test.h"
#include "../strarray.h"

void test_strarray_va() {
  char **array;

  array = strarray(NULL);
  assert(strarray_len(array) == 0, "0-element va array length");
  assert(array[0] == NULL,         "0-element va array is null-terminated");
  free(array);

  array = strarray("hello", NULL);
  assert(strarray_len(array) == 1, "1-element va array length");
  assert(streq("hello", array[0]), "1-element va array first element");
  assert(array[1] == NULL,         "1-element va array is null-terminated");
  free(array);

  array = strarray("hello", "world", NULL);
  assert(strarray_len(array) == 2, "2-element va array length");
  assert(streq("hello", array[0]), "2-element va array first element");
  assert(streq("world", array[1]), "2-element va array second element");
  assert(array[2] == NULL,         "2-element va array is null-terminated");
  free(array);
}

void test_strarray_alloc() {
  char **array;

  array = strarray_alloc(0);
  assert(strarray_len(array) == 0, "0-element alloced array length");
  assert(array[0] == NULL,         "0-element alloced array is null-terminated");
  free(array);

  array = strarray_alloc(1);
  assert(strarray_len(array) == 0, "1-element alloced initial array length");
  array[0] = "hello";
  assert(strarray_len(array) == 1, "1-element alloced array length");
  assert(array[1] == NULL,         "1-element alloced array is null-terminated");
  free(array);
}

void test_strarray_dup() {
  char **src_array = strarray("one", "two", "three", NULL);
  char **dst_array = strarray_dup(src_array);

  assert(strarray_len(dst_array) == 3, "duped array has same length");
  assert(src_array != dst_array,       "duped array has different address");
  assert(src_array[0] == dst_array[0] &&
         src_array[1] == dst_array[1] &&
         src_array[2] == dst_array[2], "duped array elements are the same");
  assert(dst_array[3] == NULL,         "duped array is null-terminated");

  free(src_array);
  free(dst_array);
}

void test_strarray_concat() {
  char **left = strarray("red", "orange", NULL);
  char **right = strarray("yellow", "green", "blue", NULL);
  char **array = strarray_concat(left, right);

  assert(strarray_len(array) == 5,        "concatenated array length");
  assert(array != left && array != right, "concatenated array has different address");
  assert(array[0] == left[0] &&
         array[1] == left[1] &&
         array[2] == right[0] &&
         array[3] == right[1] &&
         array[4] == right[2],            "concatenated array elements are the same");
  assert(array[5] == NULL,                "concatenated array is null-terminated");

  free(left);
  free(right);
  free(array);
}

void test_strarray_push() {
  char **array = strarray("red", "orange", NULL);
  array = strarray_push(array, "blue");

  assert(strarray_len(array) == 3,  "pushed array length");
  assert(streq("red", array[0]),    "pushed array first element");
  assert(streq("orange", array[1]), "pushed array second element");
  assert(streq("blue", array[2]),   "pushed array third element");
  assert(array[3] == NULL,          "pushed array is null-terminated");

  free(array);
}

void test_strarray_unshift() {
  char **array = strarray("red", "orange", NULL);
  array = strarray_unshift(array, "blue");

  assert(strarray_len(array) == 3,  "unshifted array length");
  assert(streq("blue", array[0]),   "unshifted array first element");
  assert(streq("red", array[1]),    "unshifted array second element");
  assert(streq("orange", array[2]), "unshifted array third element");
  assert(array[3] == NULL,          "unshifted array is null-terminated");

  free(array);
}

void test_strarray_join() {
  char **array = strarray(NULL);
  char *string = strarray_join(array, ", ");
  assert(strlen(string) == 0, "0-element joined array");
  free(string);
  free(array);

  array = strarray("hello", NULL);
  string = strarray_join(array, ", ");
  assert(streq("hello", string), "1-element joined array");
  free(string);
  free(array);

  array = strarray("red", "orange", "yellow", NULL);
  string = strarray_join(array, ", ");
  assert(streq("red, orange, yellow", string), "3-element joined array");
  free(string);
  free(array);
}

int main(int argc, char **argv) {
  begin();

  test_strarray_va();
  test_strarray_alloc();
  test_strarray_dup();
  test_strarray_concat();
  test_strarray_push();
  test_strarray_unshift();
  test_strarray_join();

  end();
}
