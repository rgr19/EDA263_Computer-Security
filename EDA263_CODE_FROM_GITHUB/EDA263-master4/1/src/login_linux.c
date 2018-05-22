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
#include "pwent.h"

#define TRUE 1
#define FALSE 0
#define LENGTH 16

void sigint(int);

void sighandler() {
  signal(SIGINT, sigint); // c-C
  signal(SIGTSTP, sigint); // c-Z
}

void sigint(int sig_num) {
  // printf("Don't do that");
  // fflush(stdout);
  sighandler(); // re-register signal handler since system resets when signal is handled
}

int main(int argc, char *argv[]) {

  mypwent *passwddata;

  char *newargv[] = { "/bin/bash", "-c", "echo velkom 2 kewlest werld; whoami; /bin/bash", NULL };
  char *newenviron[] = { NULL };

  char user[LENGTH * 2];
  char * important = user + LENGTH;
  strcpy(important, "***IMPORTANT***");
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

    if (fgets(user, LENGTH, stdin) == NULL)
      exit(0);

    // Replace the last character `\n` with `\0`
    user[strlen(user) - 1] = 0;

    /* check to see if important variable is intact after input of login name - do not remove */
    printf("Value of variable 'important' after input of login name: %*.*s\n",
        LENGTH - 1, LENGTH - 1, important);

    user_pass = getpass(prompt);
    passwddata = mygetpwnam(user);

    if (passwddata != NULL) {

      sleep(passwddata->pwfailed);

      if (!strcmp(crypt(user_pass, passwddata->passwd_salt), passwddata->passwd)) {

        printf(" You're in !\n Failed attempts: %d\n", passwddata->pwfailed);

        passwddata->pwfailed = 0;
        passwddata->pwage++;

        if(passwddata->pwage > 9) {
          printf("Password is old! Age: %d", passwddata->pwage);
        }

        mysetpwent(user, passwddata);

        if (setuid(passwddata->uid) != 0) {
          printf("Could not set uid.");
        } else {
          execve(newargv[0], newargv, newenviron);
          printf("Could not start /bin/bash."); // This happends if the line above does not steal the process
        }

        return -1;
      } else {
        passwddata->pwfailed++;
        mysetpwent(user, passwddata);
      }
    }

    printf("Login Incorrect \n");
  }
  return 0;
}
