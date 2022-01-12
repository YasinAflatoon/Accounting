#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "accapp.h"

void startMenu();

void signup();

void login();

void mainMenu();

void recordSection();

FILE *signupData;


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
        login();
    else if (strcmp(startMenuInput, "2") == 0 || strcasecmp(startMenuInput, "sign up") == 0 ||
             strcasecmp(startMenuInput, "signup") == 0)
        signup();
    else if (strcmp(startMenuInput, "3") == 0 || strcasecmp(startMenuInput, "exit") == 0)
        exit(0);
    else {
        printf("Please enter a valid option!\n");
        startMenu();
    }
}

void signup() {
    system("clear");
    signupData = fopen("profiles.txt", "a+");
    struct profile {
        char phoneNumber[12];
        char password[32];
    };
    struct profile user;
    printf("Welcome to SignUp page!\nThis will take shortly...\n\n");
    char firstName[50];
    while (1) {
        printf("Please enter your first name: ");
        gets(firstName);
        if (strcmp(firstName, "\0") == 0)
            printf("ERROR! First name cannot be empty!\n\n");
        else break;
    }
    char lastName[50];
    while (1) {
        printf("Please enter your last name: ");
        gets(lastName);
        if (strcmp(lastName, "\0") == 0)
            printf("ERROR! Last name cannot be empty!\n\n");
        else break;
    }
    // National code receiving and validation check:
    char nationalCode[11];
    while (1) {
        printf("Please enter your national code: ");
        gets(nationalCode);
        if (nationCodLenChk(nationalCode) == 1) {
            printf("ERROR! National code must contain 10 digits!\n\n");
        } else if (nationCodDigChk(nationalCode) == 1) {
            printf("ERROR! National code must contain numbers only!\n\n");
        } else break;
    }
    // Phone number receiving and validation check:
    //char phoneNumber[12];
    while (1) {
        printf("Please enter your phone number (This will be taken as your username): ");
        gets(user.phoneNumber);
        if (phoneNumLenChk(user.phoneNumber) == 1)
            printf("ERROR! Phone number must contain 11 digits!\n\n");
        else if (phoneNumFormatChk(user.phoneNumber) == 1)
            printf("ERROR! Phone number must contain numbers only!\n\n");
        else if (phoneNumFormatChk(user.phoneNumber) == 2)
            printf("ERROR! Phone number must contain \"09\" at beginning!\n\n");
        else break;
    }
    // Email address receiving and validation check:
    char email[120];
    while (1) {
        printf("Please enter your email address (You can press enter key to skip this part): ");
        gets(email);
        if (email[0] == '\0' || emailFormatChk(email) == 0)
            break;
        else if (emailFormatChk(email) == 1)
            printf("ERROR! Invalid email format!\n\n");
    }
    // Password receiving and weakness check:
    //char password[32];
    while (1) {
        printf("Please enter a password contains numbers and 1 letter at least: ");
        gets(user.password);
        if (passwordWeaknessChk(user.password) == 1)
            printf("ERROR! Password must contain 4 characters at min, 32 at max!\n\n");
        else if (passwordWeaknessChk(user.password) == 2)
            printf("ERROR! Password must contain one letter at least!\n\n");
        else break;
    }
    // Password confirmation:
    char passwordRpt[32];
    while (1) {
        printf("Please re-enter your password: ");
        gets(passwordRpt);
        if (strcmp(user.password, passwordRpt) == 0)
            break;
        else printf("ERROR! Passwords do not match!\n\n");
    }
    printf("Congrats! you signed up successfully!\n\n");
    fwrite(&user, sizeof(struct profile), 1, signupData);
    fputs(firstName, signupData);
    fputs(lastName, signupData);
    fputs(nationalCode, signupData);
    fputs(email, signupData);
    fclose(signupData);
    startMenu();
}

void login() {
    signupData = fopen("profiles.txt", "r");

    system("clear");
    printf("Welcome to login page!\n\n");
    struct userLogin {
        char username[12];
        char password[32];
    };
    struct userLogin user;

    char phoneNumber[12];
    while (fread(&user, sizeof(struct userLogin), 1, signupData) == 1) {
        printf("Please enter your phone number: ");
        gets(phoneNumber);
        if (strcmp(phoneNumber, user.username) == 0)
            break;
        else {
            printf("This phone number have not been registered!\nDo you wish to sign up?[Y/N] or [R] to retry: ");
            char unRegUser;
            gets(&unRegUser);
            if(unRegUser == 'Y' || unRegUser == 'y'){
                signup();
                break;
            } else if(unRegUser == 'N' || unRegUser == 'n'){
                startMenu();
                break;
            } else if (unRegUser == 'R' || unRegUser == 'r'){
                rewind(signupData);
                continue;
            } else printf("invalid option!");
        }
    }
    rewind(signupData);
    char pass[32];
    int i = 0;
    while (fread(&user, sizeof(struct userLogin), 1, signupData) == 1) {
        printf("Please enter your password: ");
        gets(pass);
        if(strcmp(pass, user.password) == 0) {
            mainMenu();
            break;
        }
        else if(i < 4){
            printf("Wrong password, %d tries remaining.\n\n", 4 - i);
            i++;
            rewind(signupData);
        } else {
            printf("You had 5 unsuccessful attempts. app is getting closed.");
            exit(0);
        }
    }
}

void mainMenu() {
    system("clear");
    char mainMenuInput[20];
    printf("Hello, there!\n\n-> Please choose from options blow:\n1. Add income\n2. Add payment\n3. Records\n4. Account Setting\n5. Logout\n6. Exit\n>>");
    gets(mainMenuInput);
    if (strcmp(mainMenuInput, "1") == 0 || strcasecmp(mainMenuInput, "add income") == 0)
        printf("Add income section");
    else if (strcmp(mainMenuInput, "2") == 0 || strcasecmp(mainMenuInput, "add payment") == 0)
        printf("Add payment section");
    else if (strcmp(mainMenuInput, "3") == 0 || strcasecmp(mainMenuInput, "records") == 0)
        printf("Records section");
    else if (strcmp(mainMenuInput, "4") == 0 || strcasecmp(mainMenuInput, "account setting") == 0)
        printf("Account Setting section");
    else if (strcmp(mainMenuInput, "5") == 0 || strcasecmp(mainMenuInput, "logout") == 0 ||
             strcasecmp(mainMenuInput, "log out") == 0)
        printf("Logout");
    else if (strcmp(mainMenuInput, "6") == 0 || strcasecmp(mainMenuInput, "exit") == 0)
        exit(0);
    else {
        printf("PLease enter a valid option!\n");
        mainMenu();
    }
}