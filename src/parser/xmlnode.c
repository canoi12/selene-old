#include "xmlnode.h"

xmlNode* create_xml_node(xmlNode* parent) {
  xmlNode* node = malloc(sizeof(*node));
  node->parent = parent;
  node->firstChild = NULL;
  node->nextSibling = NULL;
  node->content = malloc(sizeof(char) * 2048);

  node->name = NULL;
  node->content = NULL;
  
  node->attr = create_map("", NULL, 1);

  return node;
}

void xmlnode_check_line(xmlNode** cnode, char** line, int* type) {
  char* content = NULL;
  xmlNode* node = *cnode;
  char* p = *line;
  while(*p == ' ') {
    (p++);
  }

  if (*p == '<' && *(p + 1) == '?') {
    //free(*line);
    return;
  }

  while (*p != '\n') {
    if (*p == '<' && *(p + 1) != '/') {
      if (node->name == NULL) {
	xmlnode_check_tag(&node, &p);
      } else {
	if (*type == 1) {
	  node->firstChild = create_xml_node(node);
	  node = node->firstChild;
	  *type = xmlnode_check_tag(&node, &p);
	} else if (*type == 0) {
	  node->nextSibling = create_xml_node(node->parent);
	  node = node->nextSibling;
	  *type = xmlnode_check_tag(&node, &p);
	}
      }
    }
    else if (*p != '<' && *(p + 1) != '/') {
      if (!content) {
	content = malloc(sizeof(char) * 512);
	memset(content, 0, sizeof(*content));
      }
      strncat(content, p, 1);
    }
    else if (*p == '<' && *(p + 1) == '/') {
      char* nome_end_tag = xmlnode_check_end_tag(&node, &p);
      if (!strcmp(node->name, nome_end_tag)) {
	*type = 0;
      } else {
	node = node->parent;
	*type = 0;
      }
    }
    p++;
  }
  
  if (content) {
    int size = strlen(content);
    node->content = malloc(sizeof(char) * size);
    //printf("%s\n", content);
    strcpy(node->content, content);
    free(content);
  }
  *cnode = node;
  *line = p;
}

int xmlnode_check_tag(xmlNode** cnode, char** tag) {
  char* nome = NULL;
  xmlNode* node = *cnode;
  char* p = *tag;
  if (*p == '<') {
    (p++);
    while (*p != ' ' && *p != '>') {
      if (!nome) {
	nome = malloc(sizeof(char) * 512);
	memset(nome, 0, sizeof(*nome));
      }
      strncat(nome, p, 1);
      (p++);
    }
    int size = strlen(nome);
    (node->name) = malloc(sizeof(char) * size);
    strcpy((node->name), nome);
  }
  
  while (*p != '>') {
    if (*p == ' ' && ((*(p + 1) >= 'A' && *(p + 1) <= 'Z') ||
		      (*(p + 1) >= 'a' && *(p + 1) <= 'z'))) {
      //printf("%c\n", *(p + 1));
      xmlnode_check_attribute(&node, &p);
    }
    //printf("A: %c\n", *p);
    if (*p == '>')
      break;
    p++;
  }
  int examine = 2;
  if (*p == '>') {
    if (*(p - 1) == '/')
      examine = 0;
    else
      examine = 1;
  }
  /*if (examine)
    printf("Tag aberta\n");
  else
  printf("Tag fechada\n");*/
  
  free(nome);

  *cnode = node;
  *tag = p;
  
  return examine;
}

char* xmlnode_check_end_tag(xmlNode** cnode, char** tag) {
  char* nome = malloc(sizeof(char) * 512);
  int size = sizeof(char) * 512;
  
  memset(nome, 0, size);
  xmlNode* node = *cnode;
  char* p = *tag;

  //printf("%s", p);
  
  while(*p != '>') {
    if (*p != '<' && *p != '/') {
      strncat(nome, p, 1);
    }
    p++;
  }

  *cnode = node;
  *tag = p;

  return nome;
}

void xmlnode_check_attribute(xmlNode** cnode, char** attribute) {
  char* name = malloc(sizeof(char) * 512);
  memset(name, 0, sizeof(*name));
  char* attr = malloc(sizeof(char) * 512);
  memset(attr, 0, sizeof(*attr));
  
  xmlNode* node = *cnode;
  char* p = *attribute;
  char* j = *attribute;
  
  int asp_count = 0;
  
  if (*p == ' ') {
    (p++);
  }

  while (*p != '=') {
    strncat(name, p, 1);
    p++;
  }
  while(asp_count < 2) {
    if (*p == '\"' || *p == '\'') {
      ++asp_count;
    }
    if (asp_count) {
      if (*p != '\"' && *p != '\'')
	strncat(attr, p, 1);
    }
    (p++);
  }

  int vsize = sizeof(attr);
  int nsize = sizeof(name);

  char* vattr = calloc(vsize, sizeof(char));
  strcpy(vattr, attr);
  char* vname = calloc(nsize, sizeof(char));
  strcpy(vname, name);
  //printf("%c\n", *(j + 5));
  
  map_add_value((node->attr), vname, vattr, sizeof(attr));

  *cnode = node;
  *attribute = p;
  free(name);
  free(attr);
}

void* xmlnode_get_attribute(xmlNode* node, char* key) {
  return map_get_value(node->attr, key);
}
