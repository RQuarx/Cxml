#pragma once
#ifndef __XML_H
#define __XML_H
#include <stdint.h>


typedef enum
{
    XML_ELEMENT = 0,
    XML_TEXT    = 1,
    XML_COMMENT = 2,
    XML_CDATA   = 3,
    XML_PI      = 4,
    XML_NONE    = 5
} xml_node_type;


struct xml_node
{
    xml_node_type type;

    char *name;
    char *content;

    struct map *attributes;

    struct xml_node *parent;
    struct xml_node *children;
    struct xml_node *next;

    /* Debugging information */
    int32_t src_line[2];
    char   *raw_tag[2];
};

#endif /* __XML_H */
