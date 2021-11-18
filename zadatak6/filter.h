#ifndef FILTER_H
#define FILTER_H
#include "date.h"
#include "atricle.h"

struct _filter;
typedef struct _filter *FilterP;
typedef struct _filter {
    DateP from;
    DateP to;
    char name[MAX_ARTICLE_NAME];
} Filter;

int initializeFilter(FilterP filter);
FilterP createFilter(char *dateFromStr, char *dateToStr, char *articleName);
int deleteFilter(FilterP filter);

#endif