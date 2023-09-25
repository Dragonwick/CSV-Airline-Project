#ifndef ROUTE_RECORDS_H
#include <stdio.h>
#include <stdlib.h>
#define ROUTE_RECORDS_H

typedef struct{
    char origin [5];
    char destination [5];
    char airline[4];
    int passengers [12];
} RouteRecord;

typedef enum SearchType {
    ROUTE, ORIGIN, DESTINATION, AIRLINE
} SearchType;

RouteRecord* createRecords (FILE* fileIn);
int fillRecords (RouteRecord* r, FILE* fileIn);
int findAirlineRoute (RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);
void searchRecords (RouteRecord* r, int length, const char* key1, const char* key2, SearchType st);
void printMenu();

#endif //PROJECT_2_ROUTE_RECORDS_H
