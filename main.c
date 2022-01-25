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

void currentCredit();

void totTransactPerYear();

void incomePerYear();

void expensePerYear();

void totTransactInPeriod();

void incomeInPer();

void expenseInPer();

void transactionTypesInPer();

void incomeTypes();

void expenseTypes();

void transactionsRatio();

void incomeRatio();

void expenseRatio();

void search();

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

struct periodDates {
    int month;
    int day;
    int year;
};
struct periodDates start;
struct periodDates end;

int main() {
    printf("\n******Welcome to Aflatoon's accounting application!******\n\n");

    Sleep(1500);

    startMenu();
    return 0;
}

void startMenu() {
    system("clear");
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
            //fclose(signupData);
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
    } else if (strcmp(unRegUser, "N") == 0 || strcmp(unRegUser, "n") == 0) {
        startMenu();
    } else {
        login();
    }
}

void passwordLogin() {
    //signupData = fopen("profiles.txt", "r");
    static int i = 5;
    printf("Please enter your password: ");
    gets(user.password);
    //while (fread(&mainUser, sizeof(struct profile), 1, signupData) == 1) {
        if (strcmp(user.password, mainUser.password) == 0) {
            fclose(signupData);
            printf("Welcome friend!\n");
            Sleep(800);
            mainMenu();
           // break;
        }
    //}
    i--;
    if (i > 0) {
        printf("Wrong password!, %d tries remaining!\n\n", i);
        //fclose(signupData);
        passwordLogin();
    } else {
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
    else if (strcmp(mainMenuInput, "3") == 0 || strcasecmp(mainMenuInput, "statistics") == 0)
        statisticSection();
    else if (strcmp(mainMenuInput, "4") == 0 || strcasecmp(mainMenuInput, "account setting") == 0) {
        printf("This Section Will be added in next updates!\n");
        Sleep(500);
        mainMenu();
    } else if (strcmp(mainMenuInput, "5") == 0 || strcasecmp(mainMenuInput, "logout") == 0 ||
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
        printf("Please enter your income amount ($): ");
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
        printf("\nPlease choose your income source:\n\n1. Job Salary\n2. University Grant\n3. Subsidy\n4. Pocket Money\n5. Custom Title\n>> ");
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
                printf("Enter custom title carefully because you may need this later (You cannot use \"back\" here): ");
                gets(incomeCustomTitle);
                if (customTitleLenChk(incomeCustomTitle) == 0) {
                    strcpy(inc.source, incomeCustomTitle);
                    break;
                } else printf("ERROR! Title must contain 50 letters maximum!\n\n");
            }
            break;
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
    strcpy(inc.phoneNum, user.username);

    fwrite(&inc, sizeof(struct addIncome), 1, incomeData);
    fclose(incomeData);
    printf("\n\nSuccessfully recorded!\n\nDo you want to record another income? [Y] for YES or any key for NO:\n>> ");
    char yesNo[4];
    gets(yesNo);
    if (strcasecmp(yesNo, "Y") == 0 || strcasecmp(yesNo, "yes") == 0)
        incomeSection();
    else
        mainMenu();
}

void expenseSection() {
    expenseData = fopen("expenses.txt", "a+");
    system("clear");
    printf("***Expense Record Section***\nYou can type \"back\" meanwhile filling the forms to head back to main menu\n\n");
    // Expense Amount:
    char amount[12];
    while (1) {
        printf("Please enter your expense amount ($): ");
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
        printf("\nPlease choose your expense case:\n\n1. Meal Costs\n2. Educational Expense\n3. Medical Expense\n4. Rent \n5. Bills\n6. Transportation Expense\n6. Shopping\n7. Custom Title\n>> ");
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
            break;
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
    strcpy(expen.phoneNum, user.username);

    fwrite(&expen, sizeof(struct addExpense), 1, expenseData);
    fclose(expenseData);
    printf("\n\nSuccessfully recorded!\n\nDo you want to record another expense? [Y] for YES or any key for NO:\n>> ");
    char yesNo[4];
    gets(yesNo);
    if (strcasecmp(yesNo, "Y") == 0 || strcasecmp(yesNo, "yes") == 0)
        expenseSection();
    else
        mainMenu();
}

void statisticSection() {
    system("clear");
    printf("Please choose your desired transaction record: \n\n1. Current Credit\n2. Total Transactions per Year\n3. Total Transactions in a Period\n4. Specific Type of Transaction\n5. Transactions Ratio\n6. Search\n7. Back\n>> ");
    char expenseSectionInput[20];
    gets(expenseSectionInput);
    if (strcmp(expenseSectionInput, "1") == 0 || strcasecmp(expenseSectionInput, "Current Credit") == 0) {
        currentCredit();
    } else if (strcmp(expenseSectionInput, "2") == 0 ||
               strcasecmp(expenseSectionInput, "Total Transactions per year") == 0) {
        totTransactPerYear();
    } else if (strcmp(expenseSectionInput, "3") == 0 ||
               strcasecmp(expenseSectionInput, "Total Transactions in a period") == 0) {
        totTransactInPeriod();
    } else if (strcmp(expenseSectionInput, "4") == 0 ||
               strcasecmp(expenseSectionInput, "specific type of transaction") == 0) {
        transactionTypesInPer();
    } else if (strcmp(expenseSectionInput, "5") == 0 || strcasecmp(expenseSectionInput, "transactions ratio") == 0) {
        transactionsRatio();
    } else if (strcmp(expenseSectionInput, "6") == 0 || strcasecmp(expenseSectionInput, "search") == 0) {
        search();
    } else if (strcmp(expenseSectionInput, "7") == 0 || strcasecmp(expenseSectionInput, "back") == 0) {
        mainMenu();
    } else {
        printf("Please enter a valid option!");
        Sleep(200);
        statisticSection();
    }
}

void currentCredit() {
    printf("Your current credit is: ");


}

void totTransactPerYear() {
    system("clear");
    char transactPerYearInput[20];
    printf("Please choose the transaction type to see its total in a year:\n1. Income\n2. Expense\n3. Back\n>> ");
    gets(transactPerYearInput);
    if (strcmp(transactPerYearInput, "1") == 0 || strcasecmp(transactPerYearInput, "income") == 0)
        incomePerYear();
    else if (strcmp(transactPerYearInput, "2") == 0 || strcasecmp(transactPerYearInput, "expense") == 0)
        expensePerYear();
    else if (strcmp(transactPerYearInput, "3") == 0 || strcasecmp(transactPerYearInput, "back") == 0) {
        statisticSection();
    } else {
        printf("PLease enter a valid option!\n");
        Sleep(200);
        totTransactPerYear();
    }
}

void incomePerYear() {
    system("clear");
    char yearChar[6];
    printf("Please enter a Year to see your Total income: ");
    gets(yearChar);
    if (yearlenChk(yearChar) == 1) {
        printf("ERROR! Year must contain 4 digits!");
        incomePerYear();
    } else {
        int yearInt = atoi(yearChar);
        incomeData = fopen("incomes.txt", "r");
        long int totIncome = 0;
        while (fread(&inc, sizeof(struct addIncome), 1, incomeData) == 1) {
            if (yearInt == inc.year && strcmp(user.username, inc.phoneNum) == 0)
                totIncome += inc.amount;
        }
        char yesNo[4];
        printf("Your Total income in %d is: %li\n\nDo you want to retry with another year? [Y] for YES, any key for NO\n>> ",
               yearInt, totIncome);
        fclose(incomeData);
        gets(yesNo);
        if (strcasecmp(yesNo, "Y") == 0 || strcasecmp(yesNo, "yes") == 0)
            incomePerYear();
        else
            statisticSection();
    }
}

void expensePerYear() {
    system("clear");
    char yearChar[6];
    printf("Please enter a Year to see your expense records: ");
    gets(yearChar);
    if (yearlenChk(yearChar) == 1) {
        printf("ERROR! Year must contain 4 digits!");
        expensePerYear();
    } else {
        int yearInt = atoi(yearChar);
        expenseData = fopen("expenses.txt", "r");
        long int totExpense = 0;
        while (fread(&expen, sizeof(struct addExpense), 1, expenseData) == 1) {
            if (yearInt == expen.year && strcmp(user.username, expen.phoneNum) == 0)
                totExpense += expen.amount;
        }
        char yesNo[4];
        printf("Your Total expense in %d is: %li\n\nDo you want to retry with another year? [Y] for YES or any key for NO\n>> ",
               yearInt, totExpense);
        fclose(expenseData);
        gets(yesNo);
        if (strcasecmp(yesNo, "Y") == 0 || strcasecmp(yesNo, "yes") == 0)
            expensePerYear();
        else
            statisticSection();
    }
}

void totTransactInPeriod() {
    system("clear");
    char transactInPeriodInput[20];
    printf("Please choose the transaction type to see its total in a Period:\n1. Income\n2. Expense\n3. Back\n>> ");
    gets(transactInPeriodInput);
    if (strcmp(transactInPeriodInput, "1") == 0 || strcasecmp(transactInPeriodInput, "income") == 0)
        incomeInPer();
    else if (strcmp(transactInPeriodInput, "2") == 0 || strcasecmp(transactInPeriodInput, "expense") == 0)
        expenseInPer();
    else if (strcmp(transactInPeriodInput, "3") == 0 || strcasecmp(transactInPeriodInput, "back") == 0) {
        statisticSection();
    } else {
        printf("PLease enter a valid option!\n");
        Sleep(200);
        totTransactInPeriod();
    }
}

void incomeInPer() {
    system("Clear");
    printf("Please enter a date in (MM-DD-YYYY) format as start point: ");
    scanf("%d%*c%d%*c%d", &start.month, &start.day, &start.year);
    getchar();
    if (start.year < 1000 || start.year > 9999 || start.month > 12 || start.month < 1 || start.day > 31 ||
        start.day < 1) {
        printf("ERROR! Not Valid Date!");
        incomeInPer();
    }
    printf("\nPlease enter a date in (MM-DD-YYYY) format as end point: ");
    scanf("%d%*c%d%*c%d", &end.month, &end.day, &end.year);
    getchar();
    if (end.year < 1000 || end.year > 9999 || end.month > 12 || end.month < 1 || end.day > 31 || end.day < 1) {
        printf("ERROR! Not Valid Date!");
        incomeInPer();
    } else if ((start.year > end.year) || (start.year == end.year && start.month > end.month) ||
               (start.year == end.year && start.month == end.month && start.day > end.year)) {
        printf("Entered start and end point does not form a period!");
        incomePerYear();
    } else {
        long int totIncome = 0;
        incomeData = fopen("incomes.txt", "r");
        while (fread(&inc, sizeof(struct addIncome), 1, incomeData) == 1) {
            if ((inc.year == start.year && inc.month == start.month && inc.day >= start.day) ||
                (inc.year == start.year && inc.month >= start.month) || (inc.year >= start.year)) {
                if ((inc.year == end.year && inc.month == end.month && inc.day <= end.day) ||
                    (inc.year == end.year && inc.month <= end.month) || (inc.year <= end.year)) {
                    if (strcmp(user.username, inc.phoneNum) == 0)
                    totIncome += inc.amount;
                }
            }
        }
        printf("\n\n\nYour Total income from %d/%d/%d to %d/%d/%d is: %li$\n\n", start.month, start.day, start.year,
               end.month, end.day, end.year, totIncome);
        printf("Do you want to retry with another period? enter [Y] for YES or any key for NO: \n>> ");
        char yesNo[4];
        fclose(incomeData);
        gets(yesNo);
        if (strcasecmp(yesNo, "Y") == 0 || strcasecmp(yesNo, "yes") == 0)
            incomePerYear();
        else
            statisticSection();
    }
}

void expenseInPer() {
    system("Clear");
    printf("Please enter a date in (MM-DD-YYYY) format as start point: ");
    scanf("%d%*c%d%*c%d", &start.month, &start.day, &start.year);
    getchar();
    if (start.year < 1000 || start.year > 9999 || start.month > 12 || start.month < 1 || start.day > 31 ||
        start.day < 1) {
        printf("ERROR! Not Valid Date!");
        expenseInPer();
    }
    printf("\nPlease enter a date in (MM-DD-YYYY) format as end point: ");
    scanf("%d%*c%d%*c%d", &end.month, &end.day, &end.year);
    getchar();
    if (end.year < 1000 || end.year > 9999 || end.month > 12 || end.month < 1 || end.day > 31 || end.day < 1) {
        printf("ERROR! Not Valid Date!");
        expenseInPer();
    } else if ((start.year > end.year) || (start.year == end.year && start.month > end.month) ||
               (start.year == end.year && start.month == end.month && start.day > end.year)) {
        printf("Entered start and end point does not form a period!");
        expenseInPer();
    } else {
        long int totExpense = 0;
        expenseData = fopen("expenses.txt", "r");
        while (fread(&expen, sizeof(struct addExpense), 1, expenseData) == 1) {
            if ((expen.year == start.year && expen.month == start.month && expen.day >= start.day) ||
                (expen.year == start.year && expen.month >= start.month) || (expen.year >= start.year)) {
                if ((expen.year == end.year && expen.month == end.month && expen.day <= end.day) ||
                    (expen.year == end.year && expen.month <= end.month) || (expen.year <= end.year)) {
                    if (strcmp(user.username, expen.phoneNum) == 0)
                    totExpense += expen.amount;
                }
            }
        }
        printf("\n\n\nYour Total expense from %d/%d/%d to %d/%d/%d is: %li$\n\n", start.month, start.day, start.year,
               end.month, end.day, end.year, totExpense);
        printf("Do you want to retry with another period? enter [Y] for YES or any key for NO: \n>> ");
        char yesNo[4];
        fclose(expenseData);
        gets(yesNo);
        if (strcasecmp(yesNo, "Y") == 0 || strcasecmp(yesNo, "yes") == 0)
            expenseInPer();
        else
            statisticSection();
    }
}

void transactionTypesInPer() {
    system("clear");
    char transactTypesInput[20];
    printf("Please choose the transaction type to see its details in a Period by source or case:\n1. Income\n2. Expense\n3. Back\n>> ");
    gets(transactTypesInput);
    if (strcmp(transactTypesInput, "1") == 0 || strcasecmp(transactTypesInput, "income") == 0)
        incomeTypes();
    else if (strcmp(transactTypesInput, "2") == 0 || strcasecmp(transactTypesInput, "expense") == 0)
        expenseTypes();
    else if (strcmp(transactTypesInput, "3") == 0 || strcasecmp(transactTypesInput, "back") == 0) {
        statisticSection();
    } else {
        printf("PLease enter a valid option!\n");
        Sleep(200);
        transactionTypesInPer();
    }
}

void incomeTypes() {
    system("clear");
    char sourceInput[20];
    char type[20];
    printf("Please choose your income source (you can head back by typing \"back\"):\n1. Job Salary\n2. University Grant\n3. Subsidy\n4. Pocket Money\n5. Custom Title\n>>");
    gets(sourceInput);
    if (strcasecmp(sourceInput, "back") == 0) {
        transactionTypesInPer();
    } else if (strcmp(sourceInput, "1") == 0 || strcasecmp(sourceInput, "job salary") == 0) {
        strcpy(type, "Job Salary");
    } else if (strcmp(sourceInput, "2") == 0 || strcasecmp(sourceInput, "university grant") == 0) {
        strcpy(type, "University Grant");
    } else if (strcmp(sourceInput, "3") == 0 || strcasecmp(sourceInput, "Subsidy") == 0) {
        strcpy(type, "Subsidy");
    } else if (strcmp(sourceInput, "4") == 0 || strcasecmp(sourceInput, "Pocket Money") == 0) {
        strcpy(type, "Pocket Money");
    } else if (strcmp(sourceInput, "5") == 0 || strcasecmp(sourceInput, "Custom Title") == 0) {
        char incomeCustomTitle[50];
        while (1) {
            printf("Enter custom title (You cannot use \"back\" here): ");
            gets(incomeCustomTitle);
            if (customTitleLenChk(incomeCustomTitle) == 0) {
                break;
            } else printf("ERROR! Title must contain 50 letters maximum!\n\n");
        }

    } else {
        printf("ERROR! Please enter a valid option!\n\n");
        incomeTypes();
    }
    long int totIncome = 0;
    char yesNo[5];
    printf("Do you want search your income sources in a period? enter [Y] for YES or ant key for NO\n>> ");
    gets(yesNo);
    if (strcasecmp(yesNo, "Y") == 0 || strcasecmp(yesNo, "yes") == 0) {
        printf("Please enter a date in (MM-DD-YYYY) format as start point: ");
        scanf("%d%*c%d%*c%d", &start.month, &start.day, &start.year);
        getchar();
        if (start.year < 1000 || start.year > 9999 || start.month > 12 || start.month < 1 || start.day > 31 ||
            start.day < 1) {
            printf("ERROR! Not Valid Date!");
            incomeTypes();
        }
        printf("\nPlease enter a date in (MM-DD-YYYY) format as end point: ");
        scanf("%d%*c%d%*c%d", &end.month, &end.day, &end.year);
        getchar();
        if (end.year < 1000 || end.year > 9999 || end.month > 12 || end.month < 1 || end.day > 31 || end.day < 1) {
            printf("ERROR! Not Valid Date!");
            incomeTypes();
        } else if ((start.year > end.year) || (start.year == end.year && start.month > end.month) ||
                   (start.year == end.year && start.month == end.month && start.day > end.year)) {
            printf("Entered start and end point does not form a period!");
            incomeTypes();
        } else {
            incomeData = fopen("incomes.txt", "r");
            while (fread(&inc, sizeof(struct addIncome), 1, incomeData) == 1) {
                if ((inc.year == start.year && inc.month == start.month && inc.day >= start.day) ||
                    (inc.year == start.year && inc.month >= start.month) || (inc.year >= start.year)) {
                    if ((inc.year == end.year && inc.month == end.month && inc.day <= end.day) ||
                        (inc.year == end.year && inc.month <= end.month) || (inc.year <= end.year)) {
                        if (strcasecmp(inc.source, type) == 0 && strcmp(user.username, inc.phoneNum) == 0)
                            totIncome += inc.amount;
                    }
                }
            }
            fclose(incomeData);
            printf("\n\n\nYour Total income from %d/%d/%d to %d/%d/%d is: %li$\n\n", start.month, start.day, start.year,
                   end.month, end.day, end.year, totIncome);
        }
    } else {
        incomeData = fopen("incomes.txt", "r");
        while (fread(&inc, sizeof(struct addIncome), 1, incomeData) == 1) {
            if (strcasecmp(inc.source, type) == 0 && strcmp(user.username, inc.phoneNum) == 0)
                totIncome += inc.amount;
        }
        fclose(incomeData);
        printf("\n\n\nYour Total income from \"%s\" is: %li$\n\n", type, totIncome);
    }
    char yes[5];
    printf("Do want to retry with another income source? enter [Y] for YES or any key for NO:\n>> ");
    gets(yes);
    if (strcasecmp(yesNo, "Y") == 0 || strcasecmp(yesNo, "yes") == 0)
        incomeTypes();
    else
        statisticSection();
}

void expenseTypes() {
    system("clear");
    char caseInput[20];
    char type[20];
    printf("Please choose an expense case (you can head back by typing \"back\"):\n\n1. Meal Costs\n2. Educational Expense\n3. Medical Expense\n4. Rent \n5. Bills\n6. Transportation Expense\n6. Shopping\n7. Custom Title\n>> ");
    gets(caseInput);
    if (strcasecmp(caseInput, "back") == 0) {
        transactionTypesInPer();
    } else if (strcmp(caseInput, "1") == 0 || strcasecmp(caseInput, "Meal Costs") == 0) {
        strcpy(type, "Meal Costs");
    } else if (strcmp(caseInput, "2") == 0 || strcasecmp(caseInput, "Educational Expense") == 0) {
        strcpy(type, "Educational Expense");
    } else if (strcmp(caseInput, "3") == 0 || strcasecmp(caseInput, "Medical Expense") == 0) {
        strcpy(type, "Medical Expense");
    } else if (strcmp(caseInput, "4") == 0 || strcasecmp(caseInput, "Rent") == 0) {
        strcpy(type, "Rent");
    } else if (strcmp(caseInput, "5") == 0 || strcasecmp(caseInput, "Bills") == 0) {
        strcpy(type, "Bills");
    } else if (strcmp(caseInput, "6") == 0 || strcasecmp(caseInput, "Transportation") == 0) {
        strcpy(type, "Transportation Expense");
    } else if (strcmp(caseInput, "7") == 0 || strcasecmp(caseInput, "Custom Title") == 0) {
        char expenseCustomTitle[50];
        while (1) {
            printf("Enter custom title (You cannot use \"back\" here): ");
            gets(expenseCustomTitle);
            if (customTitleLenChk(expenseCustomTitle) == 0) {
                strcpy(type, expenseCustomTitle);
                break;
            } else printf("ERROR! Title must contain 50 letters maximum!\n\n");
        }
    } else {
        printf("ERROR! Please enter a valid option!\n\n");
        expenseTypes();
    }

    long int totExpense = 0;
    char yesNo[5];
    printf("Do you want search your expense cases in a period? enter [Y] for YES or ant key for NO\n>> ");
    gets(yesNo);
    if (strcasecmp(yesNo, "Y") == 0 || strcasecmp(yesNo, "yes") == 0) {
        printf("Please enter a date in (MM-DD-YYYY) format as start point: ");
        scanf("%d%*c%d%*c%d", &start.month, &start.day, &start.year);
        getchar();
        if (start.year < 1000 || start.year > 9999 || start.month > 12 || start.month < 1 || start.day > 31 ||
            start.day < 1) {
            printf("ERROR! Not Valid Date!");
            expenseTypes();
        }
        printf("\nPlease enter a date in (MM-DD-YYYY) format as end point: ");
        scanf("%d%*c%d%*c%d", &end.month, &end.day, &end.year);
        getchar();
        if (end.year < 1000 || end.year > 9999 || end.month > 12 || end.month < 1 || end.day > 31 || end.day < 1) {
            printf("ERROR! Not Valid Date!");
            expenseTypes();
        } else if ((start.year > end.year) || (start.year == end.year && start.month > end.month) ||
                   (start.year == end.year && start.month == end.month && start.day > end.year)) {
            printf("Entered start and end point does not form a period!");
            expenseTypes();
        } else {
            expenseData = fopen("expenses.txt", "r");
            while (fread(&expen, sizeof(struct addExpense), 1, expenseData) == 1) {
                if ((expen.year == start.year && expen.month == start.month && expen.day >= start.day) ||
                    (expen.year == start.year && expen.month >= start.month) || (expen.year >= start.year)) {
                    if ((expen.year == end.year && expen.month == end.month && expen.day <= end.day) ||
                        (expen.year == end.year && expen.month <= end.month) || (expen.year <= end.year)) {
                        if (strcasecmp(expen.expenseCase, type) == 0 && strcmp(user.username, expen.phoneNum) == 0)
                            totExpense += expen.amount;
                    }
                }
            }
            fclose(expenseData);
            printf("\n\n\nYour expense in case: \"%s\" from %d/%d/%d to %d/%d/%d is: %li$\n\n",type, start.month, start.day, start.year,
                   end.month, end.day, end.year, totExpense);
        }
    } else {
        expenseData = fopen("expenses.txt", "r");
        while (fread(&expen, sizeof(struct addExpense), 1, expenseData) == 1) {
            if (strcasecmp(expen.expenseCase, type) == 0 && strcmp(expen.phoneNum, user.username) == 0)
                totExpense += expen.amount;
        }
        fclose(expenseData);
        printf("\n\n\nYour total expense in case: \"%s\" is: %li$\n\n", type, totExpense);
    }
    char yes[5];
    printf("Do want to retry with another expense case? enter [Y] for YES or any key for NO:\n>> ");
    gets(yes);
    if (strcasecmp(yesNo, "Y") == 0 || strcasecmp(yesNo, "yes") == 0)
        expenseTypes();
    else
        statisticSection();
}

void transactionsRatio() {
    system("clear");
    char transactRatioInput[20];
    printf("Please choose the transaction type to see its details in a year:\n1. Income\n2. Expense\n3. Back\n>> ");
    gets(transactRatioInput);
    if (strcmp(transactRatioInput, "1") == 0 || strcasecmp(transactRatioInput, "income") == 0)
        incomeRatio();
    else if (strcmp(transactRatioInput, "2") == 0 || strcasecmp(transactRatioInput, "expense") == 0)
        expenseRatio();
    else if (strcmp(transactRatioInput, "3") == 0 || strcasecmp(transactRatioInput, "back") == 0) {
        statisticSection();
    } else {
        printf("PLease enter a valid option!\n");
        Sleep(200);
        transactionsRatio();
    }
}

void incomeRatio() {
    printf("Please enter a year as an start point: ");
    scanf("%d", &start.year);
    getchar();
    if (start.year < 1000 || start.year > 9999) {
        printf("Not Valid Year!");
        incomeRatio();
    }
    printf("Please enter a year as an ending point: ");
    scanf("%d", &end.year);
    getchar();
    if (end.year < 1000 || start.year > 9999) {
        printf("Not Valid Year!");
        incomeRatio();
    } else if (end.year < start.year) {
        printf("ERROR! entered years does not conform a period!");
        incomeRatio();
    }
    long int totIncome = 0;
    float jobSalaryPercent, uniGrantPercent, pocketMoneyPercent, subsidyPercent, otherPercent;
    long int totSalary = 0, totGrant = 0, totPocket = 0, totSubsidy = 0, totOthers = 0;
    incomeData = fopen("incomes.txt", "r");
    while (fread(&inc, sizeof(struct addIncome), 1, incomeData) == 1) {
        if (strcmp(user.username, inc.phoneNum) == 0 && (inc.year >= start.year && inc.year <= end.year)) {
            totIncome += inc.amount;
            if (strcasecmp(inc.source, "Job Salary") == 0 && (inc.year >= start.year && inc.year <= end.year))
                totSalary += inc.amount;
            else if (strcasecmp(inc.source, "University Grant") == 0 &&
                     (inc.year >= start.year && inc.year <= end.year))
                totGrant += inc.amount;
            else if (strcasecmp(inc.source, "Pocket Money") == 0 && (inc.year >= start.year && inc.year <= end.year))
                totPocket += inc.amount;
            else if (strcasecmp(inc.source, "Subsidy") == 0 && (inc.year >= start.year && inc.year <= end.year))
                totSubsidy += inc.amount;
            else if (inc.year >= start.year && inc.year <= end.year)
                totOthers += inc.amount;
        }
    }
    fclose(incomeData);
    jobSalaryPercent = (float) totSalary / (float) totIncome * 100;
    uniGrantPercent = (float) totGrant / (float) totIncome * 100;
    pocketMoneyPercent = (float) totPocket / (float) totIncome * 100;
    subsidyPercent = (float) totSubsidy / (float) totIncome * 100;
    otherPercent = (float) totOthers / (float) totIncome * 100;
    if (start.year == end.year) {
        printf("Your whole income of \"Job Salary\", in %d conforms \"%2.2f%%\" of your Total income.\n\n", start.year,
               jobSalaryPercent);
        printf("Your whole income of \"University Grant\", in %d conforms \"%2.2f%%\" of your Total income.\n\n", start.year,
               uniGrantPercent);
        printf("Your whole income of \"Pocket Money\", in %d conforms \"%2.2f%%\" of your Total income.\n\n", start.year,
               pocketMoneyPercent);
        printf("Your whole income of \"Subsidy\", in %d conforms \"%2.2f%%\" of your Total income.\n\n", start.year, subsidyPercent);
        printf("Your whole income of \"Other Sources\", in %d conforms \"%2.2f%%\" of your Total income.\n\n", start.year, otherPercent);
    }
    else {
        printf("Your whole income of \"Job Salary\", from %d to %d conforms \"%2.2f%%\" of your Total income.\n\n", start.year, end.year,
               jobSalaryPercent);
        printf("Your whole income of \"University Grant\", from %d to %d conforms \"%2.2f%%\" of your Total income.\n\n", start.year, end.year,
               uniGrantPercent);
        printf("Your whole income of \"Pocket Money\", from %d to %d conforms \"%2.2f%%\" of your Total income.\n\n", start.year, end.year,
               pocketMoneyPercent);
        printf("Your whole income of \"Subsidy\", from %d to %d conforms \"%2.2f%%\" of your Total income.\n\n", start.year, end.year, subsidyPercent);
        printf("Your whole income of \"Other Sources\", from %d to %d conforms \"%2.2f%%\" of your Total income.\n\n", start.year, end.year, otherPercent);
    }
    printf("\nEnter any key to continue...");
    getchar();
    transactionsRatio();
}

void expenseRatio() {
    printf("Please enter a year as an start point: ");
    scanf("%d", &start.year);
    getchar();
    if (start.year < 1000 || start.year > 9999) {
        printf("Not Valid Year!");
        expenseRatio();
    }
    printf("Please enter a year as an ending point: ");
    scanf("%d", &end.year);
    getchar();
    if (end.year < 1000 || start.year > 9999) {
        printf("Not Valid Year!");
        expenseRatio();
    } else if (end.year < start.year) {
        printf("ERROR! entered years does not conform a period!");
        expenseRatio();
    }
    long int totExpense = 0;
    float mealCostPercent, eduExpensePercent, medicExpensePercent, rentPercent, billsPercent, transportPercent, otherPercent;
    long int totMeal = 0, totEdu = 0, totMedic = 0, totRent = 0, totBills = 0, totTransport = 0, totOthers = 0;
    expenseData = fopen("expenses.txt", "r");
    while (fread(&expen, sizeof(struct addExpense), 1, expenseData) == 1) {
        if (strcmp(user.username, expen.phoneNum) == 0 && (expen.year >= start.year && expen.year <= end.year)) {
            totExpense += expen.amount;
            if (strcasecmp(expen.expenseCase, "Meal Costs") == 0 && (expen.year >= start.year && expen.year <= end.year))
                totMeal += expen.amount;
            else if (strcasecmp(expen.expenseCase, "Educational Expense") == 0 &&
                     (expen.year >= start.year && expen.year <= end.year))
                totEdu += expen.amount;
            else if (strcasecmp(expen.expenseCase, "Medical Expense") == 0 && (expen.year >= start.year && expen.year <= end.year))
                totMedic += expen.amount;
            else if (strcasecmp(expen.expenseCase, "Rent") == 0 && (expen.year >= start.year && expen.year <= end.year))
                totRent += expen.amount;
            else if (strcasecmp(expen.expenseCase, "Bills") == 0 && (expen.year >= start.year && expen.year <= end.year))
                totBills += expen.amount;
            else if (strcasecmp(expen.expenseCase, "Transportation") == 0 && (expen.year >= start.year && expen.year <= end.year))
                totTransport += expen.amount;
            else if (expen.year >= start.year && expen.year <= end.year)
                totOthers += expen.amount;
        }
    }
    fclose(signupData);

    mealCostPercent = (float) totMeal / (float) totExpense * 100;
    eduExpensePercent = (float) totEdu / (float) totExpense * 100;
    medicExpensePercent = (float) totMedic / (float) totExpense * 100;
    rentPercent = (float) totRent / (float) totExpense * 100;
    billsPercent = (float) totBills / (float) totExpense * 100;
    transportPercent = (float) totTransport / (float) totExpense * 100;
    otherPercent = (float) totOthers / (float) totExpense * 100;

    if (start.year == end.year) {
        printf("Your \"Meal\" expenses in %d, conforms \"%2.2f%%\" of your Total expense.\n\n", start.year,
               mealCostPercent);
        printf("Your \"Educational\" expenses in %d, conforms \"%2.2f%%\" of your Total expense.\n\n", start.year,
               eduExpensePercent);
        printf("Your \"Medical\" expenses in %d, conforms \"%2.2f%%\" of your Total expense.\n\n", start.year,
               medicExpensePercent);
        printf("Your \"Rent\" expenses in %d, conforms \"%2.2f%%\" of your Total expense.\n\n", start.year, rentPercent);
        printf("Your \"Bills\" expenses in %d, conforms \"%2.2f%%\" of your Total expense..\n\n", start.year, billsPercent);
        printf("Your \"Transportation\" expenses in %d, conforms \"%2.2f%%\" of your Total expense..\n\n", start.year, transportPercent);
        printf("Your \"Other\" expenses in %d, conforms \"%2.2f%%\" of your Total expense..\n\n", start.year, otherPercent);
    }
    else {
        printf("Your \"Meal\" expenses from %d to %d, conforms \"%2.2f%%\" of your Total expense.\n\n", start.year, end.year,
               mealCostPercent);
        printf("Your \"Educational\" expenses from %d to %d, conforms \"%2.2f%%\" of your Total expense.\n\n", start.year, end.year,
               eduExpensePercent);
        printf("Your \"Medical\" expenses from %d to %d, conforms \"%2.2f%%\" of your Total expense.\n\n", start.year, end.year,
               medicExpensePercent);
        printf("Your \"Rent\" expenses from %d to %d, conforms \"%2.2f%%\" of your Total expense.\n\n", start.year, end.year, rentPercent);
        printf("Your \"Bills\" expenses from %d to %d, conforms \"%2.2f%%\" of your Total expense..\n\n", start.year, end.year, billsPercent);
        printf("Your \"Transportation\" expenses from %d to %d, conforms \"%2.2f%%\" of your Total expense..\n\n", start.year, end.year, transportPercent);
        printf("Your \"Other\" expenses from %d to %d, conforms \"%2.2f%%\" of your Total expense..\n\n", start.year, end.year, otherPercent);
    }
    printf("Enter any key to continue...");
    getchar();
    transactionsRatio();
}

void search() {

}