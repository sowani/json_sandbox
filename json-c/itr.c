#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "json.h"

int main(int argc, char **argv)
{
  FILE *fp;
  char buffer[1024];

  struct json_object_iterator it;
  struct json_object_iterator itEnd;
  struct json_object* obj;

  fp = fopen (argv[1], "r");
  fread (buffer, 1024, 1, fp);
  fclose (fp);

  obj = json_tokener_parse(buffer);
  it = json_object_iter_begin(obj);
  itEnd = json_object_iter_end(obj);
  while (!json_object_iter_equal(&it, &itEnd)) {
    printf("%s\n", json_object_iter_peek_name(&it));
    json_object_iter_next(&it);
  }

  return 0;
}
