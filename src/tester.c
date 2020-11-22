#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

    int i;
    system("rm -rf ./testlog");
    for (i = 0; i < 1000; i++)
    {
        system("../bin/main.out 16 >> testlog");
        system("cat testlog | grep Fail ");
    }

    return 0;
}
