#include <stdio.h>
#include <unistd.h>

int myruid, myeuid;

int main(int argc, char **argv)
{
    int result;
    uid_t uid_to_set;

    printf("SETEUID TEST:\t");

    if(argc != 2){
        printf("Bad argument\n");
        printf("a.out <uid_t to set>\n");
        return 1;
    }
    result = atoi(*(argv+1));
    uid_to_set = (uid_t) result;

    printf("(ruid=%4d, euid=%4d)", getuid(), geteuid());

    myruid = getuid();
    myeuid = geteuid();

    printf("::: SET euid=%4d; ", uid_to_set);
    result = seteuid(uid_to_set);

    printf("---> RESULT: %d; ", result);

    if(result == 0){
        printf("OK! ");
        printf("(ruid=%4d, euid=%4d)", getuid(), geteuid());

    } else {
        printf("BAD! ");
    }

    printf("::: SETB euid=%4d; ", myeuid);
    result = seteuid(myeuid);

    printf("---> RESULT: %d; ", result);

    if(result == 0){
        printf("OK! ");
        printf("(ruid=%4d, euid=%4d)\n", getuid(), geteuid());

    } else {
        printf("BAD!\n");
    }

    return 0;
}