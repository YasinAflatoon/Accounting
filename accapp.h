//
// Created by Yasin on 1/3/2022.
//
#include <ctype.h>

#ifndef IKIU_FIRST_PROJECT_ACCAPP_H
#define IKIU_FIRST_PROJECT_ACCAPP_H

#endif //IKIU_FIRST_PROJECT_ACCAPP_H

int nationCodLenChk(char input[10]) {
    unsigned int lenChk = strlen(input);
    if (lenChk == 10)
        return 0;
    else return 1;
}

int nationCodDigChk(const char input[10]) {
    int digChk;
    for (int i = 0; i <= 9; i++) {
        digChk = isdigit(input[i]);
        if (digChk == 0) {
            return 1;
        }
    }
    return 0;
}

int phoneNumLenChk(char input[11]) {
    unsigned int lenChk_Num = strlen(input);
    if (lenChk_Num == 11)
        return 0;
    else return 1;
}

int phoneNumFormatChk(const char input[11]) {
    int digChk;
    for (int i = 0; i <= 10; i++) {
        digChk = isdigit(input[i]);
        if (digChk == 0)
            return 1;
    }
    if (input[0] == '0' && input[1] == '9')
        return 0;
    else return 2;
}

int emailFormatChk(const char input[120]) {
    int i = 0, atSignCount = 0, dotCount = 0, temp, temp1;
    while (input[i] != '\0') {
        if (input[i] == '@') {
            atSignCount++;
            temp = i;
        }
        if (input[i] == '.') {
            dotCount++;
            temp1 = i;
        }
        i++;
    }
    if (dotCount == 1 && atSignCount == 1 && temp < temp1) {
        return 0;
    } else return 1;
}

int passwordWeaknessChk(char input[32]) {
    if (strlen(input) < 4 || strlen(input) > 32)
        return 1;
    else {
        int i = 0, alphaCounter = 0, alphaChk;
        while (input[i] != '\0') {
            alphaChk = isalpha(input[i]);
            if (alphaChk != 0)
                alphaCounter++;
            i++;
        }
        if (alphaCounter < 1)
            return 2;
        else
            return 0;
    }
}

