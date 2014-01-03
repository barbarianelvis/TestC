#include <stdio.h>
#include <string.h>

int StringContainsChar(const char *str, char c)
{
    while(*str)
    {
        if(*str == c)
            return 1;
        ++str;
    }
    return 0;
}

//reverse function
void reverse(char *dst, const char *src, const char *delimiter)
{
    int dst_len = 0;
    int token_start;
    int token_end = strlen(src);
    int i;
    do{
        for(token_start = token_end - 1; token_start >= 0 && !StringContainsChar(delimiter, src[token_start]); --token_start){}

        for(i = token_start + 1; i < token_end; ++i, ++dst_len)
        {
            dst[dst_len] = src[i];
        }

        if(token_start >= 0)
        {
            dst[dst_len] = src[token_start];
            ++dst_len;
        }
        else
        {
            dst[dst_len] = '\0';
        }

        token_end = token_start;
    }while(token_start >= 0);
}

int main(void)
{
    const char str[] = "how are you";
    const char delimiter[] = " ";
    char strRev[sizeof(str)];
    
    reverse(strRev, str, delimiter);

    printf("input  : %s\noutput : %s\n", str, strRev);

    return 0;
}
