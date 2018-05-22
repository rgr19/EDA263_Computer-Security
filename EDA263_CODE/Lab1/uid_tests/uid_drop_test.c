#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define NEED_EUID 1
#define EUID geteuid()
#define RUID getuid()

int root2user(){
    /* Store the privileged ID for later verification */

    uid_t myRUID = RUID;
    uid_t myEUID = EUID;

    /* Code intended to run with elevated privileges   */

    printf("1(ruid=%4d, euid=%4d) ::: ", myRUID, myEUID);

    /* Temporarily drop privileges */
    if (seteuid(myRUID) != 0) {
        printf("error: temporary drop failed: %s\n", strerror(errno));
    }

    printf("2(ruid=%4d, euid=%4d) ::: ", RUID, EUID);

    /* Code intended to run with lower privileges  */

    if (NEED_EUID) {
        /* Restore Privileges */
        if (seteuid(0) != 0) {
            printf("error: restore privileges failed: %s\n", strerror(errno));
        }

        /* Code intended to run with elevated privileges   */
        printf("3(ruid=%4d, euid=%4d) ::: ", RUID, EUID);

    }

    /* ... */
    printf("\n4(ruid=%4d, euid=%4d) ::: ", RUID, EUID);

    /* Restore privileges if needed */
    if (EUID != 0) {
        if (seteuid(0) != 0) {
            printf("error: restore privileges failed: %s\n", strerror(errno));
        }
        printf("5(ruid=%4d, euid=%4d) ::: ", RUID, EUID);
    }

    /* Permanently drop privileges */
    if (setuid(myRUID) != 0) {
        printf("error: permanent drop failed: %s\n", strerror(errno));
    }
    printf("7(ruid=%4d, euid=%4d) ::: ", RUID, EUID);

    if (setuid(0) != -1) {
        printf("error: privileges can be restored: %s\n", strerror(errno));
    }

    printf("8(ruid=%4d, euid=%4d)\n\n", RUID, EUID);

    /*
     * Code intended to run with lower privileges;
     * attacker cannot regain elevated privileges
     */

    return 0;
}


int main(int argc, char **argv)
{

    printf("DROP EUID TEST \t");

    root2user();

    return 0;
}