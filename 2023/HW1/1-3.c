#include<stdio.h>
int n, back, front;
void Num_Trans(int num)
{
    switch (num)
    {
        case 1:
            printf("one");
            break;
        case 2:
            printf("two");
            break;
        case 3:
            printf("three");
            break;
        case 4:
            printf("four");
            break;
        case 5:
            printf("five");
            break;
        case 6:
            printf("six");
            break;
        case 7:
            printf("seven");
            break;
        case 8:
            printf("eight");
            break;
        case 9:
            printf("nine");
            break;
        case 10:
            printf("ten");
            break;
        case 11:
            printf("eleven");
            break;
        case 12:
            printf("twelve");
            break;
        case 13:
            printf("thirteen");
            break;
        case 14:
            printf("fourteen");
            break;
        case 15:
            printf("fifteen");
            break;
        case 16:
            printf("sixteen");
            break;
        case 17:
            printf("seventeen");
            break;
        case 18:
            printf("eighteen");
            break;
        case 19:
            printf("nineteen");
            break;
        case 20:
            printf("twenty");
            break;
        case 30:
            printf("thirty");
            break;
        case 40:
            printf("forty");
            break;
        case 50:
            printf("fifty");
            break;
        case 60:
            printf("sixty");
            break;
        case 70:
            printf("seventy");
            break;
        case 80:
            printf("eighty");
            break;
        case 90:
            printf("ninety");
            break;
        default:
            Num_Trans(num - num % 10);
            printf("-");
            Num_Trans(num % 10);
    }
}
void print_Num(int num)
{
    if(num / 100 != 0)
    {
        Num_Trans(num / 100);
        printf(" hundred");
        if(num % 100 != 0) printf(" and ");
    }
    if(num % 100 != 0)
    {
        Num_Trans(num % 100);
    }
}
int main()
{
    freopen("a.in","r",stdin);
    scanf("%d", &n);
    if(n == 0){
        printf("zero");
        return 0;
    } 
    
    back = n % 1000;
    front = n / 1000;
    if(front != 0)
    {
        print_Num(front);
        printf(" thousand ");
        if(back / 100 == 0 && back != 0) printf("and ");
        print_Num(back);
    }else{
        print_Num(back);
    }
    return 0;
}