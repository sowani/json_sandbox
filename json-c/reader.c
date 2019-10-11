#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "json.h"

int main(int argc, char **argv)
{
  FILE *fp;
  char buffer[1024];
  const char *name;

  struct json_object_iterator it;
  struct json_object_iterator itEnd;
  struct json_object* obj, *obj1;

  fp = fopen (argv[1], "r");
  fread (buffer, 1024, 1, fp);
  fclose (fp);

  obj = json_tokener_parse(buffer);
  it = json_object_iter_begin(obj);
  itEnd = json_object_iter_end(obj);
  while (!json_object_iter_equal(&it, &itEnd)) {
    name = json_object_iter_peek_name(&it);
    if (strcmp (name, "targetDistributionType") == 0)
    {
      printf("%s\n", name);
      obj1 = json_object_iter_peek_value(&it);
      if (strcmp ("string", json_type_to_name(json_object_get_type(obj1))) == 0)
      {
        printf ("val = %s\n", json_object_to_json_string (obj1));
      }
    }
    json_object_iter_next(&it);
  }

  return 0;
}
