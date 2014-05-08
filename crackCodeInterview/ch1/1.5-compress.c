#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* compress(3)
 * Input:
 *  org: pointer of input string
 *  org_length: length of input string
 *  cmps: pointer of compressed string if it needs compression
 * Output:
 *  1: String is compressed
 *  0: String donot need compressed
 * */
int compress(char* org, int org_length, char* cmps)
{
    int i = 0, j = 0, count = 0, num_digit = 0, digit = 0, tmp = 0;
    char prev = '\0';

    if(org_length <= 1)
    {
        printf("No need to compress\n");
        return 0;
    }
    prev = cmps[0] = org[0];
    count++;
    /* be careful about the \0 at the end; strlen() not count the \0 */
    /* Use the last \0 to record the last char */
    for( i=1; i < org_length+1; i++ )
    {
        if(org[i] == prev)
        {
            count++;
        }else{
            tmp = count;
            num_digit = 0;
            while(  tmp = tmp / 10 )
            {
                ++num_digit;
            }
            ++num_digit;
    
            /* always check overflow before write*/
            if( (j + num_digit + 1) >= org_length )
            {
                printf("No need to compress\n");
                return 0;
            }
            tmp = sprintf((cmps+j+1), "%d", count);
//           printf("sprintf return %d, num_digit = %d", tmp, num_digit);
            j = j + num_digit; /* j is the index of the last char of cmps */

            if( (j + 1) >= org_length )
            {
                printf("No need to compress\n");
                return 0;
            }
            prev = cmps[++j] = org[i];
 
            count = 1;
        }
    }
    cmps[++j] = '\0';
    return 1; /* compressed */
}

int main(int argc, char* argv[])
{
    int org_length = 0;
    char* cmps = NULL;
    int ret = 0;
    if(argc <= 1)
    {
        printf("Usage: ./program input_string\n");
        return 0;
    }
    
    org_length = strlen(argv[1]);
    printf("input %s length: %d\n", argv[1], org_length);
    cmps = (char*) malloc(org_length);
    
    ret = compress(argv[1], org_length, cmps);

    if(ret == 1)
    {
        printf("String \"%s\" is compressed as \"%s\"\n", argv[1], cmps);
    }else{
        printf("String \"%s\" is NOT compressed\n", argv[1]);
    } 
    free(cmps); /* each malloc corresponds to a free */
    return 0;
}
