#ifndef _XMLDOC_H_
#define _XMLDOC_H_

#include "xmlnode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct xmldoc {
  xmlNode* firstNode;
  char* xmlPath;
} xmlDoc;

xmlDoc* create_xmldoc(const char* path);

#endif // _XMLDOC_H_
