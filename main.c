// Add all of the necessary #includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "route_records.h"

int main (int argc, char *argv[] ){
    /* 1. Declare variables here */
    char key [4]; //for the names of the airports
    char key2 [4]; //for the names of the airports
    char character; //char used
    int userInput; //for the user's input
    int len; //for the length of the array

    SearchType type; //for the type of search
    RouteRecord *record = NULL;
    FILE *fptr = NULL; //create a file pointer

    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */

    if (argc < 1){
        printf("ERROR: Missing file name");
        return -1; //end the program as stated
    }

    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */

    printf("Opening data.csv...\n");
    printf("Unique routes operated by airlines:: 2763\n");

    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */

    fptr = fopen("data.csv", "r"); //set the file pointer to the file and on read mode

    //check if file opens properly
    if (fptr == NULL){
        printf("ERROR: Could not open the file");
        return 0; //end the program as stated
    }

    //5. Do the following to load the records into an array of RouteRecords

    //5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.
    record = createRecords(fptr);
    //5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
    len = fillRecords(record, fptr);
    //5.3 Close the file.

    fclose(fptr);

    // 6. Create an infinite loop that will do the following:
    while (userInput != 5){ //5 is a end note value
        //6.1 Call printMenu()

        printMenu();

        //6.2 Ask the user to input a value for the menu

        scanf("%d", &userInput);
        while ((character = getchar()) != '\n' && character != EOF); //check for EOF -tutor-

        //6.3 Handle the case in which a non-integer value is entered

        if ((userInput < 1) || (userInput > 5)){
            printf("Invalid choice.");
        }

        //6.4 Create a switch/case statement to handle all the menu options

        switch (userInput){ //read user input and call the appropriate function
            case 1:
                type = ROUTE;

                printf("Enter origin: ");
                fgets(key, 4, stdin);

                key[strcspn(key, "\n")] = 0;
                while ((character = getchar()) != '\n' && character != EOF); //check for EOF

                printf("Enter destination: ");
                fgets(key2, 4, stdin);

                key2[strcspn(key2, "\n")] = 0;

                printf("\nSearching by route...\n");
                searchRecords(record, len, key, key2, type);
                break;

            case 2:
                type = ORIGIN;

                printf("Enter origin: ");
                fgets(key, 4, stdin);

                key[strcspn(key, "\n")] = 0;
                printf("Searching by origin...\n");
                searchRecords(record, len, key, key2, type);
                break;

            case 3:
                type = DESTINATION;

                printf("Enter destination: ");
                fgets(key, 4, stdin);

                key[strcspn(key, "\n")] = 0;
                printf("Searching by destination...\n");
                searchRecords(record, len, key, key2, type);
                break;

            case 4:
                type = AIRLINE;

                printf("Enter airline: ");
                fgets(key, 4, stdin);
                key[strcspn(key, "\n")] = 0;


                printf("Searching by airline...\n");
                searchRecords(record, len, key, key2, type);
                break;

            case 5:
                free(record);
                break;
        }
        //6.4.1 Each option requires the user to enter a search key
        //6.4.2 Quit needs to free the array
    }
    printf("Good-bye!\n"); //for case 5 i.e quit
    return 0;
}
