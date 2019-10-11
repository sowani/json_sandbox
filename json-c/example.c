#include <stdio.h>
#include "json.h"

int main (int argc, char **argv)
{
  FILE *fp;
  char buffer[1024];
  struct json_object *parsed_json;
  struct json_object *str1, *str2, *str3, *str4;
  size_t i;

  fp = fopen (argv[1], "r");
  fread (buffer, 1024, 1, fp);
  fclose (fp);

  parsed_json = json_tokener_parse (buffer);
  json_object_object_get_ex (parsed_json, "description", &str1);
  json_object_object_get_ex (parsed_json, "signer", &str2);

  printf ("description = %s\n", json_object_get_string (str1));
  printf ("signer = %s\n", json_object_get_string (str2));
  return (0);
}
