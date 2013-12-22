//Problem 1.2 on page 73
//Implement a function void reverse(char* str) in C which reverses a null-terminated string

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void reverse(char* str)
{
    char* end = str;
    char* i = str;
    char* j = str;
    while(*end)
        ++end;
    j = end;
    *end = *str;
    --j;
    while(j > i)
    {
        *i = *j;
        ++i;
        *j = *i;
        --j;
    }
    while(i < end)
    {
        *i = *(i+1);
        ++i;
    }
    *i = '\0';
}

void main(int argc, char* argv[])
{
    char* str_test1;
    char* str_test2;
    str_test1 = (char*) malloc(10);
    str_test2 = (char*) malloc(2);
    strcpy(str_test1, "abcdefjhi");
    strcpy(str_test2,"a");
    printf("input str1=%s, str2=%s\n", str_test1, str_test2);
    reverse(str_test1);
    reverse(str_test2);
    printf("output str=%s, str2=%s\n", str_test1, str_test2);
    free(str_test1);
    free(str_test2);
}
