#include <stdio.h>
#include <string.h>
#include "json.h"

int main (void)
{
  const char *name;
  char buffer[1024];
  char fname[] = "/home/test/tmp/json_sandbox/test_jsons/fwupdate.cfg";
  struct json_object_iterator itBeg, itEnd;
  struct json_object *root, *obj;

  root = json_object_from_file (fname);
  itBeg = json_object_iter_begin (root);
  itEnd = json_object_iter_end (root);
  while (!json_object_iter_equal (&itBeg, &itEnd))
  {
    name = json_object_iter_peek_name (&itBeg);
    if (strcmp (name, "otaFreqMinutes") == 0)
    {
      obj = json_object_iter_peek_value (&itBeg);
      if (strcmp ("int", json_type_to_name(json_object_get_type (obj))) == 0)
        printf ("%d\n", json_object_get_int (obj));
      json_object_iter_next (&itBeg);
    }
  }
  return (0);
}
