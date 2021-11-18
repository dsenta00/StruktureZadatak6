#include "filter.h"
#include <stdio.h>
#include <stdlib.h>

int initializeFilter(FilterP filter) {
    filter->from = NULL;
    filter->to = NULL;
    memset(filter->name, MAX_ARTICLE_NAME, 0);

    return EXIT_SUCCESS;
}

FilterP createFilter(char *dateFromStr, char *dateToStr, char *articleName) {
    FilterP filter = NULL;

    filter = (FilterP)malloc(sizeof(Filter));
    if (!filter) {
        perror("Filter not allocated!");
        return NULL;
    }

    initializeFilter(filter);

    filter->from = createDateFromString(dateFromStr);
    if (!filter->from) {
        deleteFilter(filter);
        return NULL;
    }

    filter->to = createDateFromString(dateToStr);
    if (!filter->to) {
        deleteFilter(filter);
        return NULL;
    }

    strcpy(filter->name, articleName);

    return filter;
}

int deleteFilter(FilterP filter) {
    if (filter->from) {
        free(filter->from);
    }

    if (filter->to) {
        free(filter->to);
    }

    free(filter);

    return EXIT_SUCCESS;
}