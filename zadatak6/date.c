#define _CRT_SECURE_NO_WARNINGS
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

DateP createDateFromString(char *str) {
    DateP date = NULL;
    int status = 0;

    if (!str) {
        printf("String passed as null to create date!\r\n");
        return NULL;
    }

    date = (DateP)malloc(sizeof(Date));

    if (!date) {
        perror("Date allocation failed!");
        return NULL;
    }

    status = sscanf(str, "%d-%d-%d",
        &date->year,
        &date->month,
        &date->day
    );

    if (status != 3) {
        printf("Invalid date \"%s\", should be in format YYYY-MM-DD!\r\n", str);
        free(date);
        return NULL;
    }

    return date;
}

int dateToString(char *destination, DateP date) {
    if (!destination) {
        printf("Destination string is null!\r\n");
        return -1;
    }

    if (!date) {
        sprintf(destination, "-");
        return EXIT_SUCCESS;
    }

    sprintf(destination, "%04d-%02d-%02d", date->year, date->month, date->day);
    return EXIT_SUCCESS;
}

int printDate(DateP date) {
    char dateAsString[MAX_DATE_AS_STRING] = { 0 };
   
    dateToString(dateAsString, date);
    printf(dateAsString);

    return EXIT_SUCCESS;
}

int datecmp(DateP date1, DateP date2) {
    int result = date1->year - date2->year;

    if (result == 0) {
        result = date1->month - date2->month;

        if (result == 0) {
            result = date1->day - date2->day;
        }
    }

    return result;
}

bool isDateInsideOfRange(DateP date, DateP from, DateP to) {
    return datecmp(date, from) >= 0 && datecmp(date, to) <= 0;
}