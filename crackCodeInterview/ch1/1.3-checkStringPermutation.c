//Given two strings, check if a string is a permutation of the other
//Assume: ASCII char set; space is significant; case sensitive;string does not contain \0 as a character

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

bool isPermutation(char* str1, char* str2)
{
    int charSet[256] = {0};
    int i = 0;
    while(*str1++ != '\0')
       ++charSet[(unsigned int)*str1];
    while(*str2++ != '\0')
        --charSet[(unsigned int)*str2];
    while(i++ < 256)
        if(charSet[i] != 0)
            return false;
    return true;
}

void main()
{
    char str1[] = "abcdefjab";
    char str2[] = "aabbcdefj";
    if(isPermutation(str1, str2))
        printf("str1 is a permutatioin of str2\n str1 is %s\n str2 is %s\n", str1, str2);
    else
        printf("str1 is NOT a permutatioin of str2\n str1 is %s\n str2 is %s\n",str1, str2);
}
