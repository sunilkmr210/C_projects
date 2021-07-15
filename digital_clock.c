#include <stdio.h>
#include <windows.h>
int main()
{
    int hr, min, sec;
    int delay = 1000; // we add a delay of 1000 milliseconds and we will use it in the function sleep
    printf("Set time : \n");
    scanf("%d%d%d", &hr, &min, &sec);
    if (hr > 12 || min > 60 || sec > 60)
    {
        printf("ERORR ! \n");
        exit(0);
    }
    while (1)
    {
        sec++;
        if (sec > 59)
        {
            min++;
            sec = 0;
        }
        if (min > 59)
        {
            hr++;
            min = 0;
        }
        if (hr > 12)
        {
            hr = 1;
        }
        printf("\n Clock :");
        printf("\n %02d:%02d:%02d",hr,min,sec);
        Sleep(delay);
        system("cls");
    }
}