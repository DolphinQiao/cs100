#include<stdio.h>
int x1, y1, x2, y2;
int main()
{
    freopen("a.in","r",stdin);
    scanf("(%d, %d)\n", &x1, &y1);
    scanf("(%d, %d)\n", &x2, &y2);

    double k, b;
    if (x1 != x2){
        k = 1.0f * (y2 - y1) / (x2 - x1);
        printf("y = %.2f", k);
        b = - k * x1 + y1;
        if(b >= 0)
        {
            printf("x + %.2f", b);
        }else
        {
            printf("x - %.2f", -b);
        }
    }else{
        printf("x = %.2f", 1.0f * x1);
    }
    return 0;
}