#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "accapp.h"

void startMenu();

void signup();


void main() {
    printf("\n******Welcome to Aflatoon's accounting application!******\n\n");

    startMenu();

}

void startMenu() {
    char startMenuInput[10];
    printf("-> Choose from options blow:\n1. Login\n2. Sign up\n3. Exit\n>> ");
    gets(startMenuInput);
    if (strcmp(startMenuInput, "1") == 0 || strcasecmp(startMenuInput, "login") == 0)
        printf("Login Page");
    else if (strcmp(startMenuInput, "2") == 0 || strcasecmp(startMenuInput, "sign up") == 0)
        signup();
    else if (strcmp(startMenuInput, "3") == 0 || strcasecmp(startMenuInput, "exit") == 0)
        exit(0);
    else {
        printf("ERROR! Please enter a valid option!\n");
        startMenu();
    }
}

void signup() {
    system("clear");
    printf("Welcome to SignUp page!\nThis will take shortly...\n\n");
    char firstName[30];
    printf("Please enter your first name: ");
    gets(firstName);
    char lastName[30];
    printf("Please enter your last name: ");
    gets(lastName);
    // National code receiving and validation check:
    char nationalCode[10];
    while (1) {
        printf("Please enter your national code: ");
        gets(nationalCode);
        if (nationCodDigChk(nationalCode) == 1) {
            printf("ERROR! National code must contain 10 digits!\n\n");
        } else if (nationCodLenChk(nationalCode) == 1) {
            printf("ERROR! National code must contain numbers only!\n\n");
        } else break;
    }
    // Phone number receiving and validation check:
    char phoneNumber[11];
    while (1) {
        printf("Please enter your phone number (This will be taken as your username): ");
        gets(phoneNumber);
        if (phoneNumLenChk(phoneNumber) == 1)
            printf("ERROR! Phone number must contain 11 digits!\n\n");
        else if (phoneNumFormatChk(phoneNumber) == 1)
            printf("ERROR! Phone number must contain numbers only!\n\n");
        else if (phoneNumFormatChk(phoneNumber) == 2)
            printf("ERROR! Phone number must contain \"09\" at beginning!\n\n");
        else break;
    }
    char email[120];
    while(1){
        printf("Please enter your email address (optional): ");
        gets(email);
        if(email[0] == '\0')
            break;
        else if (emailformatcheck(email) == 1)
            printf("ERROR! Invalid email format!");
        else break;
    }
}
