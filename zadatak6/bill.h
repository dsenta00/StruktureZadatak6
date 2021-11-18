#ifndef BILL_H
#define BILL_H
#include "date.h"
#include "atricle.h"

#define MAX_BILL_NAME (128)

struct _bill;
typedef struct _bill* BillP;
typedef struct _bill {
    char name[MAX_BILL_NAME];
    DateP date;
    Article articleHead;
    BillP next;
} Bill;

int initializeBill(BillP bill);
BillP createBill(char *billFileName);
int insertBillAfter(BillP position, BillP bill);
int insertBillSorted(BillP head, BillP bill);
int readBillsFromFile(BillP head, char *fileName);
int printBill(BillP bill);
int printAllBills(BillP head);
int deleteBill(BillP bill);
int deleteBillAfter(BillP position);
int deleteAllBills(BillP head);

#endif