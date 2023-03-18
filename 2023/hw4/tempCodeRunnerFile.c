#include <stddef.h>
#include <stdio.h>
int hw4_islower(int ch);
int hw4_isupper(int ch);
int hw4_isalpha(int ch);
int hw4_isdigit(int ch);
int hw4_tolower(int ch);
int hw4_toupper(int ch);
size_t hw4_strlen(const char *str);
char *hw4_strchr(const char *str, int ch); 
char *hw4_strcpy(char *dest, const char *src); 
char *hw4_strcat(char *dest, const char *src); 
int hw4_strcmp(const char *lhs, const char *rhs);

int hw4_strcmp(const char *lhs, const char *rhs)
{
    while(*lhs != '\0' && *rhs != '\0')
    {
        if(*lhs < *rhs) return -1;
        if(*lhs > *rhs) return 1;
        ++lhs; ++rhs;
    }
    if(*lhs == '\0' && *rhs == '\0') return 0;
    else if(*lhs == '\0') return -1;
    else return 1;
}

char *hw4_strcat(char *dest, const char *src)
{
    char *temp = dest;
    while(*dest!='\0') dest++;
    while(*src!='\0')
    {
        *dest = *src;
        src++;
        dest++;
    }
    *dest = '\0';
    return temp;
}

char *hw4_strcpy(char *dest, const char *src){
    char *temp = dest;
    while(*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return temp;
}

char *hw4_strchr(const char *str, int ch)
{
    while (*str != '\0')
    {
        if (*str == ch)
        {
            return (char *)str;
        }
        else
        {
            str++;
        }
    }
    if(ch == '\0') return (char *) str;
    return NULL;
}

int hw4_islower(int ch){
    return (ch >= 'a' && ch <= 'z') ?1:0;
}

int hw4_isupper(int ch)
{
    return (ch >= 'A' && ch <= 'Z') ?1:0;
}

int hw4_isalpha(int ch)
{
    return((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ?1:0;
}

int hw4_isdigit(int ch)
{
    return(ch >= '0' && ch <='9')?1:0;
}

int hw4_tolower(int ch)
{
    return (ch < 'A' || ch > 'Z') ?ch:ch-'A'+'a';
}

int hw4_toupper(int ch)
{
    return(ch < 'a' || ch > 'z') ?ch:ch-'a'+'A';
}

size_t hw4_strlen(const char *str)
{
    size_t len = 0;
    while(*str != '\0')
    {
        str++;
        len++;
    }
    return len;
}

// int main()
// {
//     printf("%lld\n",hw4_strlen("asdadasdasdf"));
//     return 0;
// }