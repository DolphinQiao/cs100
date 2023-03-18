#include <stdio.h>
#include <string.h>

int main()
{
  freopen("a.in","r",stdin);
    char keyword[102];
    // memset(keyword, 0, sizeof(char));
    char ciphertext[1000002];
    memset(ciphertext, 0, sizeof(char));
    fgets(keyword, 102, stdin);
    fgets(ciphertext, 1000002, stdin);
    int len_keyword = strlen(keyword) - 1;
    int len_ciphertext = strlen(ciphertext);

    // keyword大写变小写
    for (int i = 0; i < len_keyword; i++)
    {
        if (keyword[i] < 97)
        {
            keyword[i] += 32;
        }
    }

    // 删去重复的字母
    for (int i = 0; i < len_keyword; i++)
        for (int j = 0; j < len_keyword; j++)
        {
            if (i < j)
            {
                if (keyword[i] == keyword[j])
                    keyword[j] = 0;
            }
        }

    char encode[52];
    int sign = 0;
    for (int i = 0; i < len_keyword; i++)
    {
        if (keyword[i] != 0)
        {
            encode[sign] = keyword[i];
            sign++;
        }
    }

    for (int i = sign; i < sign + 26; i++)
    {
        if (encode[i - 1] == 122)
            encode[i] = 97;
        else
            encode[i] = encode[i - 1] + 1;
    }

    // 删去重复字符
    for (int i = 0; i < sign + 26; i++)
        for (int j = 0; j < sign + 26; j++)
        {
            if (i < j)
            {
                if (encode[i] == encode[j])
                    encode[j] = 0;
            }
        }

    // 完成编码
    char encode_new[27];
    int flag = 0;
    for (int i = 0; i < sign + 27; i++)
    {
        if (encode[i] != 0)
        {
            encode_new[flag] = encode[i];
            flag++;
        }
    }

    // 译码
    char *pla_1 = encode_new;
    for (int i = 0; i < len_ciphertext; i++)
    {
        if (ciphertext[i] <= 90 && ciphertext[i] >= 65)
        {
            char *pla_i = strchr(encode_new, ciphertext[i] + 32);
            char encode_letter = 97 + (pla_i - pla_1) - 32;
            printf("%c", encode_letter);
        }
        else if (ciphertext[i] <= 122 && ciphertext[i] >= 97)
        {
            char *pla_i = strchr(encode_new, ciphertext[i]);
            char encode_letter = 97 + (pla_i - pla_1);
            printf("%c", encode_letter);
        }
        else
        {
            printf("%c", ciphertext[i]);
        }
    }
}