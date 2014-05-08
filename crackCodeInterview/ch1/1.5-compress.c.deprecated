//compress if the compressed string is smaller
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
bool compress(char* str, char** cmp_str)
{
    int i = 0;
    int j = 0;
    int length = 0;
    int rep_num = 0;
    while(str[i++] != '\0');
    length = i - 1;
    if(length == 0)
        return str;

    *cmp_str = (char*) calloc(length,sizeof(int));
    i = 0;
    j = 0;
    while(str[i] != '\0')
    {
        if(str[i] == str[(i-1)])
        {
            ++rep_num;
        }else{
            if(rep_num == 0)
                (*cmp_str)[j] = str[i];
            else
                (*cmp_str)[j] = '0' + ++rep_num;
            if(++j >= length)
            {
                free(*cmp_str);
                return false;
            }
            rep_num = 0;
        }
        ++i;
    }
    return true;
}


void main()
{
    char str1[] = "aabccccaaa";
    char str2[] = "abcd";
    char str3[] = "";
    char* cmp_str[3] = {NULL};
    bool isCompressed[3] = {false};
    bool i = 0;
    printf("str1 = %s\nstr2 = %s\nstr3 = %s\n",str1, str2, str3);
    isCompressed[0] = compress(str1, &cmp_str[0]);
    isCompressed[1] = compress(str2, &cmp_str[1]);
    isCompressed[2] = compress(str3, &cmp_str[2]);
    printf("compressed: str1 = %s\nstr2 = %s\nstr3 = %s\n", cmp_str[0], cmp_str[1], cmp_str[2]);
    while(i++<3)
        if(isCompressed[i]) free(cmp_str[i]);
}
