#ifndef DATA_H
#define DATA_H
#include <stdbool.h>

#define YEAR_STRING_LENGTH (4)           // 1999
#define DAY_STRING_LENGTH (2)            // 08
#define MONTH_STRING_LENGTH (2)          // 13
#define DASH_LENGTH (1)                  // -
#define NULL_TERMINATING_CHAR_LENGTH (1) // \0
#define MAX_DATE_AS_STRING (YEAR_STRING_LENGTH + DASH_LENGTH + MONTH_STRING_LENGTH + DASH_LENGTH + DAY_STRING_LENGTH + NULL_TERMINATING_CHAR_LENGTH)

struct _date;
typedef struct _date* DateP;
typedef struct _date {
    int year;
    int month;
    int day;
} Date;

DateP createDateFromString(char *str);
int dateToString(char *destination, DateP date);
int printDate(DateP date);
int datecmp(DateP date1, DateP date2);
bool isDateInsideOfRange(DateP date, DateP from, DateP to);

#endif
