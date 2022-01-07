#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "accapp.h"

void startMenu();

void signup();


int main() {
    printf("\n******Welcome to Aflatoon's accounting application!******\n\n");

    startMenu();
    return 0;
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
    while (1) {
        printf("Please enter your email address (optional): ");
        gets(email);
        if (email[0] == '\0' || emailFormatChk(email) == 0)
            break;
        else if (emailFormatChk(email) == 1)
            printf("ERROR! Invalid email format!");
    }
    char password[32];
    while (1) {
        printf("Please enter a password contains numbers and 1 letter at least: ");
        gets(password);
        if (passwordWeaknessChk(password) == 1)
            printf("ERROR! Password must contain 4 characters at min, 32 at max!\n\n");
        else if (passwordWeaknessChk(password) == 2)
            printf("ERROR! Password must contain one letter at least!\n\n");
        else if (passwordWeaknessChk(password) == 0)
            break;
    }
    char passwordRpt[32];
    while (1) {
        printf("Please re-enter your password: ");
        gets(passwordRpt);
        if (strcmp(password, passwordRpt) == 0)
            break;
        else printf("ERROR! Passwords do not match!\n\n");
    }
}