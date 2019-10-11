#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "json.h"

char buffer[1024];
void process_object (struct json_object *obj); /* forward declaration */

/**
 * @brief JSON object parser.
 *
 * Using an iterator, parses a given object, depending on types of object.
 *
 * @param object - Object to be parsed.
 *
 * @return int : 0 on success
 */
int parse_object (struct json_object* object)
{
  const char *name;
  struct json_object_iterator itBeg;
  struct json_object_iterator itEnd;
  struct json_object* obj;

  itBeg = json_object_iter_begin (object);
  itEnd = json_object_iter_end (object);
  while (!json_object_iter_equal(&itBeg, &itEnd))
  {
    name = json_object_iter_peek_name(&itBeg);
    obj = json_object_iter_peek_value(&itBeg);
    printf("\t%s = ", name);
    /*
    if (strcmp ("string", json_type_to_name(json_object_get_type(obj))) == 0)
      printf ("%s\n", json_object_to_json_string (obj));
    */
    process_object (obj);
    json_object_iter_next(&itBeg);
  }
  return (0);
}

/**
 * @brief JSON array parser.
 *
 * Parses JSON array type object.
 *
 * @param object - Array object to be parsed.
 *
 * @return int : 0 on success.
 */
int parse_array (struct json_object* object)
{
  int i;
  size_t n;
  struct json_object *obj;

  n = json_object_array_length(object);
  printf ("array [%lu]\n", n);
  for (i = 0; i < n; i++)
  {
    obj = json_object_array_get_idx (object, i);
    process_object (obj);
  }
  return (0);
}

/**
 * @bried JSON file parser.
 *
 * Opens a JSON file and parses object hierarchy.
 *
 * @param fname - JSON file to be parsed.
 *
 * @return 0 on success, -1 on failure
 */
int parse_output (const char *fname)
{
  const char *name;
  struct json_object_iterator itBeg;
  struct json_object_iterator itEnd;
  struct json_object* root, *obj1;

  /*
   * read_file (fname);
   * root = json_tokener_parse(buffer);
   */
  root = json_object_from_file (fname);
  if (root == NULL)
    return (-1);

  itBeg = json_object_iter_begin(root);
  itEnd = json_object_iter_end(root);
  while (!json_object_iter_equal(&itBeg, &itEnd))
  {
    name = json_object_iter_peek_name(&itBeg);
    obj1 = json_object_iter_peek_value(&itBeg);
    printf("%s = ", name);
    process_object (obj1);
    json_object_iter_next(&itBeg);
  }

  return 0;
}

/**
 * @brief process JSON object.
 *
 * Given a JSON object, checks type of object and processes following types:
 *   - string type
 *   - object type
 *   - array type
 *
 * @param obj - JSON object
 *
 * @return void
 */
void process_object (struct json_object *obj)
{
  if (strcmp ("string", json_type_to_name(json_object_get_type(obj))) == 0)
    printf ("%s\n", json_object_to_json_string (obj));
  else if (strcmp ("object", json_type_to_name(json_object_get_type(obj))) == 0)
  {
    printf ("\n");
    parse_object (obj);
  }
  else if (strcmp ("array", json_type_to_name(json_object_get_type(obj))) == 0)
    parse_array (obj);
  else
    printf ("unhandled object type\n");
}

int main(int argc, char **argv)
{
  int i;
  char files[7][40] = {
                     "../test_jsons/deployment.json",
                     "../test_jsons/firmware-binary.json",
                     "../test_jsons/firmware.json",
                     "../test_jsons/firmware-manifest.json",
                     "../test_jsons/firmware-package.json",
                     "../test_jsons/firmware-updateplan.json",
                     "../test_jsons/live-deployment-res.json"
                   };

  for (i = 0; i < 7; i++)
  {
    printf ("parsing %s\n", files[i]);
    parse_output (files[i]);
    printf ("\n\n");
  }

  return (0);
}
