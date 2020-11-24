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
        system("../bin/main.out 4 >> testlog");
        system("cat testlog | grep -i Fail ");
    }

    return 0;
}
