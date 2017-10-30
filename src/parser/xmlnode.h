#ifndef _XMLNODE_H_
#define _XMLNODE_H_

#include "map.h"

typedef struct xmlnode xmlNode;

typedef struct xmlnode {
  char* name;
  char* content;
  Map* attr;
  xmlNode* parent;
  xmlNode* firstChild;
  xmlNode* nextSibling;
} xmlNode;

xmlNode* create_xml_node(xmlNode* parent);

void xmlnode_check_line(xmlNode** cnode, char** line, int* type);

int xmlnode_check_tag(xmlNode** cnode, char** tag);

char* xmlnode_check_end_tag(xmlNode** cnode, char** tag);

void xmlnode_check_attribute(xmlNode** cnode, char** attribute);

void* xmlnode_get_attribute(xmlNode* node, char* key);

#endif // _XMLNODE_H_
