//
// Created by karol on 07/03/2020.
//

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "processing.h"
#include "../Avl_Tree_lib/avl_tree.h"
// TODO insert zwraca AvlTree ??

AvlTree data;

AvlTree *giveDict(char *names[], int len);

AvlTree *giveDict(char *names[], int len) {

//    AvlTree *output = getDict(data, names[0]);
    AvlTree *output = &data;
    for (int i = 0; i < len; ++i)
        if (output == NULL)
            return NULL;
        else
            output = getDict(*output, names[i]);

    return output;
}


void add(char *commands[], int len) {

    if (len == 0) {
        fprintf(stderr, "ERROR\n");
        return;
    }

    if (len >= 1)
        insert(&data, commands[0]);
    if (len >= 2)
        insert(getDict(data, commands[0]), commands[1]);
    if (len == 3)
        insert(getDict(*getDict(data, commands[0]),
                commands[1]), commands[2]);

    printf("OK\n");
}

void del(char *commands[], int len) {

    if (len == 0) {
        resetAll();
        return;
    }

    char *sub[len - 1];
    for (int i = 0; i < len - 1; ++i) {
        sub[i] = commands[i];
    }
    AvlTree *dict = giveDict(sub, len - 1);
    if (dict == NULL)
        return;

    // sprawdzac czy cos usunalem w ogole
    // na pale contains i dopiero ???
    *giveDict(sub, len - 1) = deleteNode(*dict, commands[len - 1]);


//    if (len <= 1) {
//        data = deleteNode(giveDict(), commands[0]);
//    }
//    else if (len <= 2) {
//        // nwm czy ok tu jest
//        *getDict(data, commands[0]) = deleteNode(*getDict(data, commands[0]), commands[1]);
//
//    }
//    else if (len <= 3) {
//        *getDict(*getDict(data, commands[0]), commands[1]) =
//                deleteNode(*getDict(*getDict(data, commands[0]), commands[1]), commands[2]);
//    }
    printf("OK\n");
}

void print(char *commands[], int len) {

    if (len >= 3) {
        fprintf(stderr, "ERROR\n");
        return;
    }

    AvlTree *toPrint = giveDict(commands, len);
    if (toPrint != NULL)
        printAll(*toPrint);
}


void checkPrinter(bool present) {
    if (present)
        printf("YES\n");
    else
        printf("NO\n");
}


void check(char *commands[], int len) {

    // 3rd command is "*"
    // if (len == 3 && strcmp(commands[2], "*") == 0)
    if (len == 0 || strcmp(commands[len - 1], "*") == 0)
        fprintf(stderr, "ERROR\n");
    else
        checkPrinter(iterateOverAllNodes(data, commands, 0, len));
}


void resetAll() {
    removeAll(data);
    data = NULL;
}

void perform(char *operation, char *commands[], int len) {
//    // ADD las drzewo zwierzę
//       0   1   2      3

//    printf("%s ", operation);
//    printf("%s ", commands[0]);
//    printf("%s ", commands[1]);
//    printf("%s ", commands[2]);
//    del/print/check robia to samo

    if (strcmp(operation, "ADD") == 0) {
        add(commands, len);
    }
    else if (strcmp(operation, "DEL") == 0) {
        del(commands, len);
    }
    else if (strcmp(operation, "PRINT") == 0) {
        print(commands, len);
    }
    else if (strcmp(operation, "CHECK") == 0) {
        check(commands, len);
    }
    else
        fprintf(stderr, "ERROR\n");
}