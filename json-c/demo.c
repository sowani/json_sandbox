#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "json.h"

int main(int argc, char **argv)
{
  struct json_object *new_obj;
  FILE *fp;
  char buffer[1024];
  struct json_object *parsed_json;
  struct json_object *str1, *str2, *str3, *str4;
  struct json_object *root;
  const char *tt;
  size_t i;

  fp = fopen (argv[1], "r");
  fread (buffer, 1024, 1, fp);
  fclose (fp);

  root = json_tokener_parse(buffer);
  printf("root.to_string()=%s\n", json_object_to_json_string(root));
  printf ("\n");

  str1 = json_object_object_get(root, "glossary");
  printf("str1.to_string()=%s\n", json_object_to_json_string(str1));
  printf ("\n");

  new_obj = json_object_object_get(str1, "pageCount");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  printf ("\n");

  int pageCount = json_object_get_int(new_obj);
  printf("Page count = %d\n", pageCount);

  new_obj = json_object_object_get(str1, "GlossDiv");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  printf ("\n");

  new_obj = json_object_object_get(new_obj, "title");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  printf ("\n");


  tt = json_object_get_string(new_obj);
  printf("title = %s\n", tt);

  json_object_put(new_obj);

  return 0;
}
