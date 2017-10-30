#include "xmldoc.h"

xmlDoc* create_xmldoc(const char* path) {

  FILE * file = fopen(path, "r");
  char * line = NULL;
  size_t len = 0;
  ssize_t read = 0;
  if (file == NULL) {
    printf("Não foi possível abrir o arquivo %s\n", path);
    return NULL;
  }
  xmlDoc* doc;
  doc = malloc(sizeof(*doc));

  xmlNode* actual_node = create_xml_node(NULL);

  doc->firstNode = actual_node;
  int size = strlen(path);
  doc->xmlPath = malloc(sizeof(char) * size);
  doc->xmlPath = path;

  xmlNode* p = actual_node;

  int open = 1;
  
  while ((read = getline(&line, &len, file)) != -1) {
    xmlnode_check_line(&p, &line, &open);
  }

  return doc;
}
