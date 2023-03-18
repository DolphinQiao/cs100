#include <stddef.h>
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
    int len1 = hw4_strlen(lhs);
    int len2 = hw4_strlen(rhs);
    int minn = len1 <= len2 ? len1 : len2;
    for (int i = 0; i < minn; ++i)
    {
        if(rhs[i] > lhs[i]) return -1;
        if(rhs[i] < lhs[i]) return 1;
    }
    if(len1 == len2) return 0;
    else if(len1 > len2) return 1;
    else return -1;
}

char *hw4_strcat(char *dest, const char *src)
{
    int len = hw4_strlen(src);
    int len1 = hw4_strlen(dest);
    for (int i = len1; i < len1 + len; ++i)
    {
        dest[i] = src[i - len1];
    }
    return dest;
}

char *hw4_strcpy(char *dest, const char *src){
    int len = hw4_strlen(src);
    for (int i = 0; i < len; ++i)
    {
        dest[i] = src[i];
    }
    return dest;
}

char *hw4_strchr(const char *str, int ch)
{
    int len = (int)hw4_strlen(str);
    for (int i = 0; i < len; ++i)
    {
        if(str[i] == ch) return (str + i);
    }
    return NULL;
}

int hw4_islower(int ch){
    if(ch >= 'a' && ch <= 'z') return 1;
    return 0;
}

int hw4_isupper(int ch)
{
    if(ch >= 'A' && ch <= 'Z') return 1;
    return 0;
}

int hw4_isalpha(int ch)
{
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) return 1;
    return 0;
}

int hw4_isdigit(int ch)
{
    if(ch >= '0' && ch <='9') return 1;
    return 0;
}

int hw4_tolower(int ch)
{
    if(hw4_islower(ch)) return ch;
    return ch - 'A' + 'a';
}

int hw4_toupper(int ch)
{
    if(hw4_isupper(ch)) return ch;
    return ch - 'a' + 'A';
}

size_t hw4_strlen(const char *str)
{
    return sizeof(str)/sizeof(char) - 1;
}
