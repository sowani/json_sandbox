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

  const char *fname = "/home/test/tmp/fw_sandbox/fwsim/fwbackup/result";
  char line[20];
  FILE *fp;
  int val, ts;

  fp = fopen (fname, "r");
  /* fgets (&line[0], 20, fp); */
  fscanf (fp, "%d:%d", &val, &ts);
  fclose (fp);
/*
  printf ("line = %s", line);
  sscanf (line, "%d:%d", &val, &ts);
*/
  printf ("val = %d, ts = %d\n", val, ts);

  /* construct sample JSON */
  obj = json_object_new_object();

  intObj1 = json_object_new_int (val);
  retval = json_object_object_add (obj, "updateState", intObj1);
  currtime = time(NULL);
  /* intObj2 = json_object_new_int ((int) time(NULL)); */
  intObj2 = json_object_new_int (ts);
  retval = json_object_object_add (obj, "updateTime", intObj2);

  /* export sample JSON to file */
  /* retval = json_object_to_file (filename, obj); */
  retval = json_object_to_file_ext (filename, obj, JSON_C_TO_STRING_PRETTY);
  return (retval);
}
