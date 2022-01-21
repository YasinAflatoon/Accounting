#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "accapp.h"

FILE *signupData;
FILE *incomeData;
FILE *expenseData;

void startMenu();

void signup();

void login();

void usernameLogin(char username[15]);

void passwordLogin();

void mainMenu();

void incomeSection();

void expenseSection();

void statisticSection();

struct profile {
    char phoneNumber[15];
    char password[32];
    char firstName[50];
    char lastName[50];
    char nationalCode[11];
    char email[120];
};
struct profile mainUser;
char *r;

struct userLogin {
    char username[15];
    char password[32];
};
struct userLogin user;
char *re;

struct addIncome {
    char phoneNum[12];
    long int amount;
    char source[50];
    int day;
    int month;
    int year;
    char description[200];
};
struct addIncome inc;

struct addExpense {
    char phoneNum[12];
    long int amount;
    char expenseCase[50];
    int day;
    int month;
    int year;
    char description[200];
};
struct addExpense expen;


int main() {
    printf("\n******Welcome to Aflatoon's accounting application!******\n\n");

    startMenu();
    return 0;
}

void startMenu() {
    char startMenuInput[10];
    printf("-> Choose from options blow:\n1. Login\n2. Sign up\n3. Exit\n>> ");
    gets(startMenuInput);
    if (strcmp(startMenuInput, "1") == 0 || strcasecmp(startMenuInput, "login") == 0) {
        Sleep(1000);
        printf("Welcome to login page!\n\n");
        login();
    } else if (strcmp(startMenuInput, "2") == 0 || strcasecmp(startMenuInput, "sign up") == 0 ||
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

    printf("Welcome to SignUp page!\nThis will take shortly...\n\nYou can type \"back\" meanwhile filling the forms to head back to start menu.\n\n");
    Sleep(800);
    while (1) {
        printf("Please enter your first name: ");
        gets(mainUser.firstName);
        if (strcmp(mainUser.firstName, "\0") == 0)
            printf("ERROR! First name cannot be empty!\n\n");
        else if (strcasecmp(mainUser.firstName, "back") == 0) {
            startMenu();
            break;
        } else break;
    }
    while (1) {
        printf("Please enter your last name: ");
        gets(mainUser.lastName);
        if (strcmp(mainUser.lastName, "\0") == 0)
            printf("ERROR! Last name cannot be empty!\n\n");
        else if (strcasecmp(mainUser.lastName, "back") == 0) {
            startMenu();
            break;
        } else break;
    }
    // National code receiving and validation check:
    while (1) {
        printf("Please enter your national code: ");
        gets(mainUser.nationalCode);
        if (strcasecmp(mainUser.nationalCode, "back") == 0) {
            startMenu();
            break;
        } else if (nationCodLenChk(mainUser.nationalCode) == 1) {
            printf("ERROR! National code must contain 10 digits!\n\n");
        } else if (nationCodDigChk(mainUser.nationalCode) == 1) {
            printf("ERROR! National code must contain numbers only!\n\n");
        } else break;
    }
    // Phone number receiving and validation check:
    while (1) {
        printf("Please enter your phone number (This will be taken as your username): ");
        gets(mainUser.phoneNumber);
        if (strcasecmp(mainUser.phoneNumber, "back") == 0) {
            startMenu();
            break;
        } else if (phoneNumLenChk(mainUser.phoneNumber) == 1)
            printf("ERROR! Phone number must contain 11 digits!\n\n");
        else if (phoneNumFormatChk(mainUser.phoneNumber) == 1)
            printf("ERROR! Phone number must contain numbers only!\n\n");
        else if (phoneNumFormatChk(mainUser.phoneNumber) == 2)
            printf("ERROR! Phone number must contain \"09\" at beginning!\n\n");
        else break;
    }
    // Email address receiving and validation check:
    while (1) {
        printf("Please enter your email address (You can press enter key to skip this part): ");
        gets(mainUser.email);
        if (strcasecmp(mainUser.email, "back") == 0) {
            startMenu();
            break;
        } else if (mainUser.email[0] == '\0' || emailFormatChk(mainUser.email) == 0)
            break;
        else if (emailFormatChk(mainUser.email) == 1)
            printf("ERROR! Invalid email format!\n\n");
    }
    // Password receiving and weakness check:
    while (1) {
        printf("Please enter a password contains numbers and 1 letter at least: ");
        gets(mainUser.password);
        if (strcasecmp(mainUser.password, "back") == 0) {
            startMenu();
            break;
        } else if (passwordWeaknessChk(mainUser.password) == 1)
            printf("ERROR! Password must contain 4 characters at min, 32 at max!\n\n");
        else if (passwordWeaknessChk(mainUser.password) == 2)
            printf("ERROR! Password must contain one letter at least!\n\n");
        else break;
    }
    // Password confirmation:
    char passwordRpt[32];
    while (1) {
        printf("Please re-enter your password: ");
        gets(passwordRpt);
        if (strcasecmp(passwordRpt, "back") == 0) {
            startMenu();
            break;
        } else if (strcmp(mainUser.password, passwordRpt) == 0)
            break;
        else printf("ERROR! Passwords do not match!\n\n");
    }
    fwrite(&mainUser, sizeof(struct profile), 1, signupData);
    fclose(signupData);
    printf("Congrats! you signed up successfully!\n\n");
    Sleep(800);
    startMenu();
}

void login() {
    signupData = fopen("profiles.txt", "r");
    printf("****Welcome to login page!****\n");
    Sleep(500);
    system("clear");
    printf("Please enter your username: ");
    gets(user.username);
    usernameLogin(user.username);
}

void usernameLogin(char username[15]) {
    signupData = fopen("profiles.txt", "r");
    while (fread(&mainUser, sizeof(struct profile), 1, signupData) == 1) {
        if (strcmp(mainUser.phoneNumber, username) == 0) {
            fclose(signupData);
            passwordLogin();
            break;
        }
    }
    fclose(signupData);
    char unRegUser[1];
    printf("This username has not been registered in database!\nDo you wish to Sign Up? [Y/N] or enter a key to retry: ");
    gets(unRegUser);
    if (strcmp(unRegUser, "y") == 0 || strcmp(unRegUser, "Y") == 0) {
        signup();
    }
    else if (strcmp(unRegUser, "N") == 0 || strcmp(unRegUser, "n") == 0) {
        startMenu();
    }
    else {
        login();
    }
}

void passwordLogin() {
    signupData = fopen("profiles.txt", "r");
    static int i = 5;
    printf("Please enter your password!");
    gets(user.password);
    while (fread(&mainUser, sizeof(struct profile), 1, signupData) == 1) {
        if (strcmp(user.password, mainUser.password) == 0) {
            fclose(signupData);
            printf("Welcome friend!\n");
            Sleep(400);
            mainMenu();
            break;
        }
    }
    i--;
    if (i > 0) {
        printf("Wrong password!, %d tries remaining!\n\n", i);
        fclose(signupData);
        passwordLogin();
    }
    else {
        printf("You had 5 unsuccessful attempts!, App is getting closed...");
        fclose(signupData);
        Sleep(300);
        exit(0);
    }
}

void mainMenu() {
    system("clear");
    char mainMenuInput[20];
    printf("Hello, there!\n\n-> Please choose from options blow:\n1. Record an income\n2. Record an expense\n3. Statistics\n4. Account Setting\n5. Logout\n6. Exit\n>> ");
    gets(mainMenuInput);
    if (strcmp(mainMenuInput, "1") == 0 || strcasecmp(mainMenuInput, "record an income") == 0)
        incomeSection();
    else if (strcmp(mainMenuInput, "2") == 0 || strcasecmp(mainMenuInput, "record an expense") == 0)
        expenseSection();
    else if (strcmp(mainMenuInput, "3") == 0 || strcasecmp(mainMenuInput, "records") == 0)
        statisticSection();
    else if (strcmp(mainMenuInput, "4") == 0 || strcasecmp(mainMenuInput, "account setting") == 0)
        printf("Account Setting section");
    else if (strcmp(mainMenuInput, "5") == 0 || strcasecmp(mainMenuInput, "logout") == 0 ||
             strcasecmp(mainMenuInput, "log out") == 0)
        startMenu();
    else if (strcmp(mainMenuInput, "6") == 0 || strcasecmp(mainMenuInput, "exit") == 0)
        exit(0);
    else {
        printf("PLease enter a valid option!\n");
        mainMenu();
    }
}

void incomeSection() {
    incomeData = fopen("incomes.txt", "a+");
    system("clear");
    printf("***Income Record Section***\nYou can type \"back\" meanwhile filling the forms to head back to main menu\n\n");
    // Income Amount:
    char amount[12];
    while (1) {
        printf("Please enter your income amount: ");
        gets(amount);
        if (strcasecmp(amount, "back") == 0) {
            mainMenu();
            break;
        } else if (amountFormatChk(amount) == 1)
            printf("ERROR! Your income amount must contain numbers only!");
        else {
            inc.amount = strtol(amount, &r, 10);
            break;
        }
    }
    // Income Source:
    char sourceInput[50];
    while (1) {
        printf("Please choose your income source:\n1. Job Salary\n2. University Grant\n3. Subsidy\n4. Pocket Money\n5. Custom Title\n>>");
        gets(sourceInput);
        if (strcasecmp(sourceInput, "back") == 0) {
            mainMenu();
            break;
        } else if (strcmp(sourceInput, "1") == 0 || strcasecmp(sourceInput, "job salary") == 0) {
            strcpy(inc.source, "Job Salary");
            break;
        } else if (strcmp(sourceInput, "2") == 0 || strcasecmp(sourceInput, "university grant") == 0) {
            strcpy(inc.source, "University Grant");
            break;
        } else if (strcmp(sourceInput, "3") == 0 || strcasecmp(sourceInput, "Subsidy") == 0) {
            strcpy(inc.source, "Subsidy");
            break;
        } else if (strcmp(sourceInput, "4") == 0 || strcasecmp(sourceInput, "Pocket Money") == 0) {
            strcpy(inc.source, "Pocket Money");
            break;
        } else if (strcmp(sourceInput, "5") == 0 || strcasecmp(sourceInput, "Custom Title") == 0) {
            char incomeCustomTitle[50];
            while (1) {
                printf("Enter custom title (You cannot use \"back\" here): ");
                gets(incomeCustomTitle);
                if (customTitleLenChk(incomeCustomTitle) == 0) {
                    strcpy(inc.source, incomeCustomTitle);
                    break;
                } else printf("ERROR! Title must contain 50 letters maximum!\n\n");
            }

        } else printf("ERROR! Please enter a valid option!\n\n");
    }
    // Date:
    char day[4];
    while (1) {
        printf("Please specify the date of income (day): ");
        gets(day);
        if (strcasecmp(day, "back") == 0) {
            mainMenu();
            break;
        } else if (dateDigitChk(day) == 1)
            printf("ERROR! Please enter numbers only!\n\n");
        else {
            inc.day = atoi(day);
            if (dayRangeChk(inc.day) == 1)
                printf("ERROR! Day must range in [1 - 31]!\n\n");
            else break;
        }
    }
    char month[4];
    while (1) {
        printf("Please specify the date of income (month): ");
        gets(month);
        if (strcasecmp(month, "back") == 0) {
            mainMenu();
            break;
        } else if (dateDigitChk(month) == 1)
            printf("ERROR! Please enter numbers only!\n\n");
        else {
            inc.month = atoi(month);
            if (monthRangeChk(inc.month) == 1)
                printf("ERROR! Month must range in [1 - 12]!\n\n");
            else break;
        }
    }
    char year[4];
    while (1) {
        printf("Please specify the date of income (year): ");
        gets(year);
        if (strcasecmp(month, "back") == 0) {
            mainMenu();
            break;
        } else if (dateDigitChk(year) == 1)
            printf("ERROR! Please enter numbers only!\n\n");
        else if (yearlenChk(year) == 1)
            printf("ERROR! Year must contain 4 digits!\n\n");
        else {
            inc.year = atoi(year);
            break;
        }
    }
    // Description:
    while (1) {
        printf("Please enter description (optional): ");
        gets(inc.description);
        if (strcasecmp(inc.description, "back") == 0) {
            mainMenu();
            break;
        } else if (strlen(inc.description) > 200)
            printf("Description is too long! Please enter 200 letters a most!\n\n");
        else break;
    }
    strcpy(user.username, inc.phoneNum);

    fwrite(&inc, sizeof(struct addIncome), 1, incomeData);
    fclose(incomeData);
    printf("Successfully recorded!\n");
    mainMenu();
}

void expenseSection() {
    expenseData = fopen("expenses.txt", "a+");
    system("clear");
    printf("***Expense Record Section***\nYou can type \"back\" meanwhile filling the forms to head back to main menu\n\n");
    // Expense Amount:
    char amount[12];
    while (1) {
        printf("Please enter your expense amount: ");
        gets(amount);
        if (strcasecmp(amount, "back") == 0) {
            mainMenu();
            break;
        } else if (amountFormatChk(amount) == 1)
            printf("ERROR! Your expense amount must contain numbers only!");
        else {
            expen.amount = strtol(amount, &re, 10);
            break;
        }
    }
    // Expense Case:
    char caseInput[50];
    while (1) {
        printf("Please choose your expense case:\n1. Meal Costs\n2. Educational Expense\n3. Medical Expense\n4. Rent \n5. Bills\n6. Transportation Expense\n6. Shopping\n7. Custom Title\n>>");
        gets(caseInput);
        if (strcasecmp(caseInput, "back") == 0) {
            mainMenu();
            break;
        } else if (strcmp(caseInput, "1") == 0 || strcasecmp(caseInput, "Meal Costs") == 0) {
            strcpy(expen.expenseCase, "Meal Costs");
            break;
        } else if (strcmp(caseInput, "2") == 0 || strcasecmp(caseInput, "Educational Expense") == 0) {
            strcpy(expen.expenseCase, "Educational Expense");
            break;
        } else if (strcmp(caseInput, "3") == 0 || strcasecmp(caseInput, "Medical Expense") == 0) {
            strcpy(expen.expenseCase, "Medical Expense");
            break;
        } else if (strcmp(caseInput, "4") == 0 || strcasecmp(caseInput, "Rent") == 0) {
            strcpy(expen.expenseCase, "Rent");
            break;
        } else if (strcmp(caseInput, "5") == 0 || strcasecmp(caseInput, "Bills") == 0) {
            strcpy(expen.expenseCase, "Bills");
            break;
        } else if (strcmp(caseInput, "6") == 0 || strcasecmp(caseInput, "Transportation") == 0) {
            strcpy(expen.expenseCase, "Transportation Expense");
            break;
        } else if (strcmp(caseInput, "7") == 0 || strcasecmp(caseInput, "Custom Title") == 0) {
            char expenseCustomTitle[50];
            while (1) {
                printf("Enter custom title (You cannot use \"back\" here): ");
                gets(expenseCustomTitle);
                if (customTitleLenChk(expenseCustomTitle) == 0) {
                    strcpy(expen.expenseCase, expenseCustomTitle);
                    break;
                } else printf("ERROR! Title must contain 50 letters maximum!\n\n");
            }
        } else printf("ERROR! Please enter a valid option!\n\n");
    }
    // Date:
    char day[4];
    while (1) {
        printf("Please specify the date of expense (day): ");
        gets(day);
        if (strcasecmp(day, "back") == 0) {
            mainMenu();
            break;
        } else if (dateDigitChk(day) == 1)
            printf("ERROR! Please enter numbers only!\n\n");
        else {
            expen.day = atoi(day);
            if (dayRangeChk(expen.day) == 1)
                printf("ERROR! Day must range in [1 - 31]!\n\n");
            else break;
        }
    }
    char month[4];
    while (1) {
        printf("Please specify the date of expense (month): ");
        gets(month);
        if (strcasecmp(month, "back") == 0) {
            mainMenu();
            break;
        } else if (dateDigitChk(month) == 1)
            printf("ERROR! Please enter numbers only!\n\n");
        else {
            expen.month = atoi(month);
            if (monthRangeChk(expen.month) == 1)
                printf("ERROR! Month must range in [1 - 12]!\n\n");
            else break;
        }
    }
    char year[4];
    while (1) {
        printf("Please specify the date of expense (year): ");
        gets(year);
        if (strcasecmp(year, "back") == 0) {
            mainMenu();
            break;
        } else if (dateDigitChk(year) == 1)
            printf("ERROR! Please enter numbers only!\n\n");
        else if (yearlenChk(year) == 1)
            printf("ERROR! Year must contain 4 digits!\n\n");
        else {
            expen.year = atoi(year);
            break;
        }
    }
    // Description:
    while (1) {
        printf("Please enter description (optional): ");
        gets(expen.description);
        if (strcasecmp(expen.description, "back") == 0) {
            mainMenu();
            break;
        } else if (strlen(expen.description) > 200)
            printf("Description is too long! Please enter 200 letters a most!\n\n");
        else break;
    }
    strcpy(user.username, expen.phoneNum);

    fwrite(&expen, sizeof(struct addExpense), 1, expenseData);
    fclose(expenseData);
    printf("Successfully recorded!\n\n");
    mainMenu();
}

void statisticSection() {

}
