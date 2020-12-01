#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

    int i;
    system("rm -rf ./testlog");
    for (i = 0; i < 100; i++)
    {
        system("../bin/main.out 24 >> testlog");
        system("cat testlog | grep -i Fail ");
        printf("done-> %d\n" , i);
    }

    return 0;
}
