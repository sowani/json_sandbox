#include <stdio.h>
#include <time.h>
#include "json.h"

int main (void)
{
  const char *filename = "sample.json";
  int retval = 0;
  struct json_object *obj;
  struct json_object *intObj1, *intObj2;
  time_t currtime;

  /* construct sample JSON */
  obj = json_object_new_object();

  intObj1 = json_object_new_int (2);
  retval = json_object_object_add (obj, "updateState", intObj1);
  currtime = time(NULL);
  intObj2 = json_object_new_int ((int) time(NULL));
  retval = json_object_object_add (obj, "updateTime", intObj2);

  /* export sample JSON to file */
  retval = json_object_to_file (filename, obj);
  return (retval);
}
