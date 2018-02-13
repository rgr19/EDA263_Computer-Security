#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/capability.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char ** argv) {
    printf("cap_setuid and cap_setgid: %d\n", prctl(PR_CAPBSET_READ, CAP_SETUID|CAP_SETGID, 0, 0, 0));
    printf(" %s\n", cap_to_text(cap_get_file(argv[0]), NULL));
    printf(" %s\n", cap_to_text(cap_get_proc(), NULL));
    if (setresuid(0, 0, 0)) printf("setresuid(): %s\n", strerror(errno));
    execve("/bin/sh", NULL, NULL);
}

/* At first sight, it looks like an application to get root privileges (setresuid()) and then spawn a shell.
 * If that application would be given CAP_SETUID and CAP_SETGID effectively,
 * it would allow anyone who executed it to automatically get a root shell, wouldn't it?

$ gcc -o test -lcap test.c
# setcap cap_setuid,cap_setgid+ep test
$ ./test
cap_setuid and cap_setgid: 1
 = cap_setgid,cap_setuid+ep
 =
setresuid() failed: Operation not permitted
 */