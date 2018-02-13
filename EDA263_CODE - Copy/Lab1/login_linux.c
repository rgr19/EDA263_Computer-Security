/* $Header: https://svn.ita.chalmers.se/repos/security/edu/course/computer_security/trunk/lab/login_linux/login_linux.c 585 2013-01-19 10:31:04Z pk@CHALMERS.SE $ */

/* gcc -Wall -g -o mylogin login.linux.c -lcrypt */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>
#include <crypt.h>
/* Uncomment next line in step 2 */
#include "pwent.h"

#define TRUE 1
#define FALSE 0
#define LENGTH 16

/*
 in step 2:
 create file passdb and add records of users, salt need two numbers

 in step 4:
 ./makepass 'sa'

 */

void sighandler() {

    /* add signalhandling routines here */
    /* see 'man 2 signal' */
}


int main(int argc, char *argv[]) {

    //struct passwd *passwddata; /* this has to be redefined in step 2 */
    /* see pwent.h */
    mypwent *passwddata;

    char important[LENGTH] = "***IMPORTANT***";

    char user[LENGTH];
    //char   *c_pass; //you might want to use this variable later...
    char prompt[] = "password: ";
    char *user_pass;

    sighandler();

    while (TRUE) {
        /* check what important variable contains - do not remove, part of buffer overflow test */
        printf("Value of variable 'important' before input of login name: %s\n",
               important);

        printf("login: ");
        fflush(NULL); /* Flush all  output buffers */
        __fpurge(stdin); /* Purge any data in stdin buffer */

        /* step 3, gets() is vulnerable to buffer,
         * change to fgets(char * __restrict__ _Buf,int _MaxCount,FILE * __restrict__ _File) */
        if (fgets(user,LENGTH,stdin) == NULL)
            exit(0); /*  overflow attacks.  */

        //step 3, fgets is used instead of gets you will get a "\n"
        // at the end of the string that need to be replaced by "\0".
        user[strlen(user)-1] = '\0';

        /* check to see if important variable is intact after input of login name - do not remove */
        printf("Value of variable 'important' after input of login name: %*.*s\n",
               LENGTH - 1, LENGTH - 1, important);

        user_pass = getpass(prompt);
        passwddata = mygetpwnam(user); //step 2

        if (passwddata != NULL) {
            /* You have to encrypt user_pass for this to work */
            /* Don't forget to include the salt */

            //step 2, change to ->passwd
            //step 4, has to hash given password with salt
            if (!strcmp(crypt(user_pass, passwddata->passwd_salt), passwddata->passwd)) {

                printf(" You're in !\n");

                /*  check UID, see setuid(2) */
                /*  start a shell, use execve(2) */

            }
        } else {
            printf("Login Incorrect \n");
        }
    }
    return 0;
}

