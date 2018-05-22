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
#define ALERT_AGE 10
#define MAX_GUESSES 10

void catch_int(int sig) {
	signal(SIGINT, catch_int);
	printf("No.");
}

void catch_suspend(int sig) {
	signal(SIGTSTP, catch_suspend);
	printf("No.");
}

void catch_abort(int sig) {
	signal(SIGABRT, catch_abort);
	printf("No.");
}

void catch_quit(int sig) {
	signal(SIGQUIT, catch_quit);
	printf("No.");
}

void sighandler() {

	/* add signalhandling routines here */
	/* see 'man 2 signal' */
	printf("Initializing sighandler");
	signal(SIGINT, catch_int);
	signal(SIGTSTP, catch_suspend);
	signal(SIGABRT, catch_abort);
	signal(SIGQUIT, catch_quit);
}

/**
 * Function for replacing characters in a string with another character
 */
void replace_character(char source[], char original, char replace) {
	int i;
	for (i = 0; i < strlen(source); i++) {
		if (source[i] == original) {
			source[i] = replace;
		}
	}
}

int main(int argc, char *argv[]) {

	mypwent *passwddata;

	char important[LENGTH] = "***IMPORTANT***";

	char user[LENGTH];
	//char   *c_pass; //you might want to use this variable later...
	char prompt[] = "password: ";
	char *user_pass;

	char *envp[] = { NULL };

	sighandler();

	while (TRUE) {
		/* check what important variable contains - do not remove, part of buffer overflow test */
		printf("Value of variable 'important' before input of login name: %s\n",
				important);

		printf("login: ");
		fflush(NULL); /* Flush all  output buffers */
		__fpurge(stdin); /* Purge any data in stdin buffer */

		if (fgets(user, LENGTH, stdin) == NULL) /* gets() is vulnerable to buffer */
			exit(0); /*  overflow attacks.  */
		
		replace_character(user, '\n', '\0');
		/* check to see if important variable is intact after input of login name - do not remove */
		printf("Value of variable 'important' after input of login name: %*.*s\n",
				LENGTH - 1, LENGTH - 1, important);

		user_pass = getpass(prompt);
		passwddata = mygetpwnam(user);

		if (passwddata != NULL) {
			/* You have to encrypt user_pass for this to work */
			/* Don't forget to include the salt */
			user_pass = crypt(user_pass, passwddata->passwd_salt);
			if (user_pass == NULL ) {
				continue;
			}

			if (!strcmp(user_pass, passwddata->passwd)) {
				printf("Number of failed attempts: %d\n", passwddata->pwfailed);
				passwddata->pwfailed = 0;
				passwddata->pwage++;
				mysetpwent(passwddata->pwname, passwddata);
	
				if (passwddata->pwage >= ALERT_AGE) {
					printf("This password is now considered old. Please swap.\n");
				}

				printf(" You're in !\n");

				if (setuid(passwddata->uid) != 0) {
					printf("This did not go as planned\n");
				} else if (execve("/bin/sh", argv, envp) == -1) {
					printf("Execve failure\n");
				}
			} else {
				passwddata->pwfailed++;
				mysetpwent(passwddata->pwname, passwddata);
				if (passwddata->pwfailed >= MAX_GUESSES) {
					sleep(5);
				}
			}
	}
		printf("Login Incorrect \n");
	}
	return 0;
}

