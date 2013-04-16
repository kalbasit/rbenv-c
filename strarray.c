#include "strarray.h"

char **strarray(char *first, ...) {
  size_t length = 1;
  va_list count_args, args;

  va_start(args, first);
  va_copy(count_args, args);
  while (va_arg(count_args, char *)) length++;
  va_end(count_args);

  char **array = strarray_alloc(length);
  array[0] = first;
  for (int i = 1; i < length; i++) array[i] = va_arg(args, char *);
  va_end(args);

  return array;
}

char **strarray_alloc(size_t size) {
  return calloc(size + 1, sizeof(char *));
}

char **strarray_realloc(char **array, size_t size) {
  char **result = realloc(array, sizeof(char *) * (size + 1));
  result[size] = NULL;
  return result;
}

void strarray_free(char **array) {
  strarray_each(array, char *string) free(string);
  free(array);
}

size_t strarray_len(char **array) {
  size_t length = 0;
  if (array != NULL) while (*array++) length++;
  return length;
}

char **strarray_dup(char **array) {
  size_t length = strarray_len(array);
  char **result = strarray_alloc(length);
  memcpy(result, array, sizeof(char *) * length);
  return result;
}

char **strarray_concat(char **left, char **right) {
  size_t left_length = strarray_len(left);
  size_t right_length = strarray_len(right);
  char **result = strarray_alloc(left_length + right_length);
  memcpy(result, left, sizeof(char *) * left_length);
  memcpy(result + left_length, right, sizeof(char *) * right_length);
  return result;
}

char **strarray_push(char **array, char *string) {
  size_t length = strarray_len(array) + 1;
  array = strarray_realloc(array, length);
  array[length - 1] = string;
  return array;
}

char **strarray_unshift(char **array, char *string) {
  size_t length = strarray_len(array) + 1;
  array = strarray_realloc(array, length);
  for (int i = length - 1; i > 0; i--) array[i] = array[i - 1];
  array[0] = string;
  return array;
}

char *strarray_join(char **array, char *join) {
  size_t array_length = strarray_len(array);
  char *result;

  if (array_length) {
    size_t length, join_length = strlen(join);

    size_t chars = join_length * (array_length - 1);
    for (int i = 0; i < array_length; i++) {
      chars += strlen(array[i]);
    }

    result = calloc(chars + 1, sizeof(char));
    memcpy(result, array[0], sizeof(char) * strlen(array[0]));
    char *offset = result + strlen(result);

    for (int i = 1; i < array_length; i++) {
      length = strlen(array[i]);
      memcpy(offset, join, sizeof(char) * join_length);
      memcpy(offset += join_length, array[i], sizeof(char) * length);
      offset += length;
    }

  } else {
    result = calloc(1, sizeof(char));
  }

  return result;
}

char **strarray_split(char *string, char *delimiter) {
  char **result;
  char *element;
  size_t string_length = strlen(string);
  size_t delimiter_length = strlen(delimiter);

  if (delimiter_length) {
    result = strarray(NULL);

    if (string_length) {
      char *search_string = string;

      while (*search_string) {
        size_t match_length = strcspn(search_string, delimiter);
        element = calloc(match_length + 1, sizeof(char));
        memcpy(element, search_string, match_length);
        result = strarray_push(result, element);

        search_string += match_length;
        if (*search_string) search_string += delimiter_length;
      }
    }

  } else {
    result = strarray_alloc(string_length);

    for (int i = 0; i < string_length; i++) {
      element = calloc(2, sizeof(char));
      element[0] = string[i];
      result[i] = element;
    }
  }

  return result;
}
