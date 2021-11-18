#define _CRT_SECURE_NO_WARNINGS
#include "bill.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (1024)

int initializeBill(BillP bill) {
    bill->date = NULL;
    bill->next = NULL;
    memset(bill->name, 0, MAX_BILL_NAME);
    initializeArticle(&bill->articleHead);
    return EXIT_SUCCESS;
}

BillP createBill(char *billFileName) {
    FILE *fp = NULL;
    BillP bill = NULL;
    int status = EXIT_SUCCESS;
    char fileLine[MAX_LINE] = { 0 };

    fp = fopen(billFileName, "r");
    if (!fp) {
        perror("Bill not opened!");
        return NULL;
    }

    bill = (BillP)malloc(sizeof(Bill));
    if (!bill) {
        perror("Bill not allocated!");
        fclose(fp);
        return NULL;
    }

    initializeBill(bill);

    strcpy(bill->name, billFileName);

    fgets(fileLine, MAX_LINE, fp);
    bill->date = createDateFromString(fileLine);
    if (!bill->date) {
        fclose(fp);
        deleteBill(bill);
        return NULL;
    }

    while (!feof(fp)) {
        ArticleP article = NULL;
        fgets(fileLine, MAX_LINE, fp);

        if (strlen(fileLine) == 0) {
            continue;
        }

        article = createArticleFromString(fileLine);
        if (!article) {
            fclose(fp);
            deleteBill(bill);
            return NULL;
        }

        insertArticleSorted(&bill->articleHead, article);
    }

    fclose(fp);

    return bill;
}

int insertBillAfter(BillP position, BillP bill) {
    bill->next = position->next;
    position->next = bill;

    return EXIT_SUCCESS;
}

int insertBillSorted(BillP head, BillP bill) {
    BillP position = head;

    while (position->next != NULL && datecmp(position->next->date, bill->date) < 0) {
        position = position->next;
    }

    insertBillAfter(position, bill);

    return EXIT_SUCCESS;
}


int readBillsFromFile(BillP head, char *fileName) {
    FILE *fp = NULL;
    char fileLine[MAX_LINE] = { 0 };

    fp = fopen(fileName, "r");
    if (!fp) {
        perror("File with bills not opened!");
        return -1;
    }

    while (!feof(fp)) {
        BillP bill = NULL;
        fscanf(fp, "%s", fileLine);

        if (strlen(fileLine) == 0) {
            continue;
        }

        bill = createBill(fileLine);
        if (!bill) {
            fclose(fp);
            deleteAllBills(head);
            return -2;
        }

        insertBillSorted(head, bill);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int printBill(BillP bill) {
    ArticleP article = NULL;

    printf("\t============================\r\n");
    printf("\t\t** Date => ");
    printDate(bill->date);
    printf("\r\n");
    printf("\t\t** Articles (name, count, price) \r\n");

    for (article = bill->articleHead.next; article != NULL; article = article->next) {
        printf("\t\t\t * ");
        printArticle(article);
        printf("\r\n");
    }

    return EXIT_SUCCESS;
}

int printAllBills(BillP head) {
    BillP bill = NULL;

    for (bill = head->next; bill != NULL; bill = bill->next) {
        printBill(bill);
    }

    return EXIT_SUCCESS;
}

int deleteBill(BillP bill) {
    if (!bill) {
        return EXIT_SUCCESS;
    }

    if (bill->date) {
        free(bill->date);
    }

    deleteAllArticles(&bill->articleHead);
    free(bill);
}

int deleteBillAfter(BillP position) {
    BillP toDelete = position->next;

    if (!toDelete) {
        return EXIT_SUCCESS;
    }

    position->next = toDelete->next;
    deleteBill(toDelete);

    return EXIT_SUCCESS;
}

int deleteAllBills(BillP head) {
    while (head->next) {
        deleteBillAfter(head);
    }

    return EXIT_SUCCESS;
}