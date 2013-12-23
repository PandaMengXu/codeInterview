//replace all space in a string with '%20'; assume 'true' string has enough space
//

#include<stdio.h>

int getNumOfSpace(char* str)
{
    int num = 0;
    while(*str++ != '\0')
        if(*str == ' ')
            ++num;
    return num;
}

/**
 * not include '\0'
 */
int getLengthOfStr(char* str)
{
    int num = 0;
    while(*str++ != '\0')
        ++num;
    return num;
}

void replaceSpace(char* str)
{
    int numOfSpace = 0;
    int lengthOfStr = 0;
    int lengthOfNewStr = 0;
    int i = 0;
    char* str_j = str;

    numOfSpace = getNumOfSpace(str);
    lengthOfStr = getLengthOfStr(str);
    lengthOfNewStr = lengthOfStr + 2*numOfSpace;
    i = lengthOfStr;

    str_j = str + lengthOfNewStr;
    *str_j = '\0';
    --str_j;
    --i;
    while(i >= 0)//careful: if use i--, the i in the loop use --i value which is inconsistent with the condition and is easy to cause error
    {
        if(*(str+i) == ' ')
        {
            *str_j-- = '0';
            *str_j-- = '2';
            *str_j-- = '%';
        }else{
            *str_j-- = *(str+i);
        }
        --i;
    }
}

void main()
{
    char str[100] = "Mr John Smith     ";
    printf("original str=%s\n", str);
    replaceSpace(str);
    printf("replaced str=%s\n", str);
}
