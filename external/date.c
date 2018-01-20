#include <time.h>
#include <stdio.h>

int main(int agrc, char **agrv)
{

    time_t t = time(NULL); // returns seconds passed since January 1, 1970
    printf(ctime(&t)); // returns time is the following format Www Mmm dd hh:mm:ss yyyy
    return 0;
}
