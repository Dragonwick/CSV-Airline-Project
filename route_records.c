//
// Created by Aaron S on 3/19/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "route_records.h"

RouteRecord* createRecords (FILE* fileIn){
    int counter = 0;
    char inputStream [200];

    RouteRecord *record = NULL;

    fgets(inputStream, 200, fileIn);

    while (fgets(inputStream, 100, fileIn) != NULL){
        counter++;
    }

    record = (RouteRecord*) malloc(counter * sizeof(RouteRecord) );

    for (int i = 0; i < 6; i++){
        for (int j = 0; j < counter; j++){
            record[j].passengers[i] = 0;
        }
    }

    rewind(fileIn);
    return record;
}

int fillRecords (RouteRecord* r, FILE* fileIn){
    int month; //do not set equal to 0 because it will be used to index the array
    int ammountCount = 0;
    int count = 1;
    int passengers;

    char inputStream [100];
    char type [20];
    char origin [4];
    char destination [4];
    char airline [4];

    fgets(inputStream, 100, fileIn);

    while (fgets(inputStream, 100, fileIn) != NULL){
        sscanf(inputStream, "%d,%[^,],%[^,],%[^,],%[^,],%d", &month, origin, destination, airline, type, &passengers); //read data and store according to layout

        if (strlen(airline) < 3){ //if the airline is less than 3 characters
            ammountCount = findAirlineRoute(r, count, origin, destination, airline, 0);

            if (ammountCount == -1){
                strcpy(r[count].origin, origin);
                strcpy(r[count].destination, destination);
                strcpy(r[count].airline, airline);
                r[count].passengers[month - 1] = passengers;
            }

            else {
                r[ammountCount].passengers[month - 1] += passengers;
            }
            count++;
        }
    }
    return count;
}

int findAirlineRoute (RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx){
    //USE RECURSION
    if (curIdx == length){ //base case
        return -1;
    }

    if (strcmp(r[curIdx].origin, origin) == 0 && strcmp(r[curIdx].destination, destination) == 0 && strcmp(r[curIdx].airline, airline) == 0){ //if the origin, destination, and airline are the same
        return curIdx;
    }

    return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1); //recursive call
}

void searchRecords (RouteRecord* r, int length, const char* key1, const char* key2, SearchType st ){
    int counter = 0;
    int amount = 0;
    int total = 0;

    int months [6] = {0, 0, 0, 0, 0, 0}; //array of months

    for (int i = 0; i < length; i++){
        if (st == ORIGIN){
            if (strcmp(r[i].origin, key1) == 0){ //if the origin is the same as the key
                printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);

                for (int j = 0; j < 6; j++){
                    months[j] += r[i].passengers[j]; //add the passengers to the months
                    total += r[i].passengers[j]; //add the passengers to the total
                }
                counter++;
            }
        }
        else if (st == DESTINATION){
            if (strcmp(r[i].destination, key1) == 0){
                printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);

                for (int j = 0; j < 6; j++){
                    months[j] += r[i].passengers[j];
                    total += r[i].passengers[j];
                }
                counter++;
            }
        }
        else if (st == AIRLINE){
            if (strcmp(r[i].airline, key1) == 0){
                printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);

                for (int j = 0; j < 6; j++){
                    months[j] += r[i].passengers[j];
                    total += r[i].passengers[j];
                }
                counter++;
            }
        }
        else{
            if (strcmp(r[i].origin, key1) == 0 && strcmp(r[i].destination, key2) == 0){
                printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);

                for (int j = 0; j < 6; j++){
                    months[j] += r[i].passengers[j];
                    total += r[i].passengers[j];
                }
                counter++;
            }
        }

    }

    //print the months and total
    printf("\n%d matches were found.\n\n", counter);
    printf("Statistics\n");
    printf("Total Passengers:\t%d\n", total);

    for (int i = 0; i < 6; i++){
        printf("Total Passengers per Month %d:\t%d\n", i + 1, months[i]);
    }
    printf("\nAverage Passengers per Month: %.lf\n", total / 6.0);
}

void printMenu(){
    printf( "\n\n######### Airline Route Records Database MENU #########\n" );
    printf( "1. Search by Route\n" );
    printf( "2. Search by Origin Airport\n" );
    printf( "3. Search by Destination Airport\n" );
    printf( "4. Search by Airline\n" );
    printf( "5. Quit\n" );
    printf( "Enter your selection: " );
}
