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
#include <linux/capability.h>
#include <errno.h>

/* Uncomment next line in step 2 */
#include "pwent.h"

#define TRUE 1
#define FALSE 0
#define LENGTH 16
#define MAX_PASSWD_AGE 4
#define MAX_EMPTY_LOGINS 3
#define MAX_LOGIN_ATTEMPTS 5
/*
 in step 2:
 create file passdb and add records of users, salt need two numbers

 in step 4:
 ./makepass 'sa'

 */


//flags for toggling protections, hange 0 to 1 to enable
#define DOSIGNAL_CATCHING 0
#define BUFFER_OVERFLOW_PROTECTION 0

//get line flags
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define FAIL     3

static int get_line(char *prmpt, char *buff, int sz) {
	
	if(BUFFER_OVERFLOW_PROTECTION) {
		
		int ch, extra;
		
		// Get line with buffer overrun protection.
		if (prmpt != NULL) {
			printf("%s", prmpt);
			fflush(NULL); /* Flush all  output buffers */
			__fpurge(stdin); /* Purge any data in stdin buffer */
		}
		
		
		/* step 3, gets() is vulnerable to buffer,
		 * change to fgets(char * __restrict__ _Buf,int _MaxCount,FILE * __restrict__ _File) */
		if (fgets(buff, sz, stdin) == NULL)
			return NO_INPUT;
		
		// If it was too long, there'll be no newline. In that case, we flush
		// to end of line so that excess doesn't affect the next call.
		if (buff[strlen(buff) - 1] != '\n') {
			extra = 0;
			while (((ch = getchar()) != '\n') && (ch != EOF))
				extra = 1;
			return (extra == 1) ? TOO_LONG : OK;
		}
		
		// Otherwise remove newline and give string back to caller.
		//step 3, fgets is used instead of gets you will get a "\n"
		// at the end of the string that need to be replaced by "\0".
		buff[strlen(buff) - 1] = '\0';
		
	} else {
		if (prmpt != NULL) {
			printf("%s", prmpt);
		}
		
		gets(buff);
		
		printf("...buffer overflow protection turned off for stdin getter!\n");
	}
	
	return OK;
}

void passwd_age_handler(mypwent *passwddata) {
	char doNewPass[2]; //has to be size=2, bocs y/n + \n is 2 chars
	
	passwddata->pwage++;
	
	if (passwddata->pwage > MAX_PASSWD_AGE) {
		
		int passwdChangeStatus = get_line("...Password to old! Change password (y/n)? ", doNewPass, 2);
		
		if (passwdChangeStatus != 0) {
			printf("...Change password wrong option. Terminating...\n");
			exit(0);
		}
		
		printf(doNewPass);
		printf("\n");
		
		if (doNewPass[0] == 'y') {
			printf("...Password changed (fakely, not implemented), age reset ...\n");
			passwddata->pwage = 0;
		} else {
			printf("....Password not changed. Terminating...\n");
			exit(0);
		}
	}
}

void uid_setter(mypwent *passwddata) {
	/*  check UID, see setuid(2) */
	
	printf("...set uid\n");
	
	int setuidStatus = setuid((__uid_t) passwddata->uid);
	
	if (setuidStatus != 0) {
		printf("...Setuid failure, error : %s! Terminating...\n", strerror(errno));
		exit(errno);
	} else {
		printf("...setuid(%d) status : %d\n", passwddata->uid, setuidStatus);
		printf("...real user id -> getuid(%d)\n", getuid());
		printf("...effective user id of process -> geteuid(%d)\n", geteuid());
	}
}

void shell_runner(mypwent *passwddata) {
	/*  start a shell, use execve(2) */
	
	printf("...run /bin/sh\n");
	//Init of array used for execve()
	
	char *execveEnvp[16];
	char envc[16][64];
	
	//here even if we set user name: hpc, we will still gen shell run by user that executed this program
	sprintf(execveEnvp[0] = envc[0], "TERM=xterm");
	sprintf(execveEnvp[1] = envc[1], "USER=%s", passwddata->pwname);
	sprintf(execveEnvp[2] = envc[2], "HOME=/");
	sprintf(execveEnvp[3] = envc[3], "SHELL=/bin/sh");
	sprintf(execveEnvp[4] = envc[4], "LOGNAME=%s", passwddata->pwname);
	sprintf(execveEnvp[5] = envc[5], "PATH=/usr/bin:/bin:/opt/bin");
	
	int execveStatus = execve("/bin/sh", NULL, execveEnvp);
	
	if (execveStatus != 0) {
		printf("...Execve(bin/sh) error : %s! Terminating... %d\n", strerror(errno), execveStatus);
		exit(errno);
	}
}

void bad_pass_handler(mypwent *passwddata) {
	printf("...login incorrect \n");
	passwddata->pwfailed++;//step 5, failed logins
	sleep((unsigned int) passwddata->pwfailed); //sleep for n[s] where n is # bad passwords
	if (passwddata->pwfailed > MAX_LOGIN_ATTEMPTS) passwddata->pwage = MAX_PASSWD_AGE + 1;
}

int good_pass_handler(mypwent *passwddata) {
	
	int loginStatus = OK;
	
	if (passwddata->pwfailed > MAX_LOGIN_ATTEMPTS) {
		printf("To many login attempts. Account locked!\n");
		sleep(5);
		loginStatus = FAIL;
	} else {
		printf(" You're in !\n");
		passwddata->pwfailed = 0;//step 5, failed logins reset
		passwd_age_handler(passwddata);//even if we login successfully, raise the age
	}
	return loginStatus;
}

void signal_catcher(int sign, void(*function)(int)) {
	signal(sign, function);
}

void signal_handler() {
	
	/* add signalhandling routines here */
	/* see 'man 2 signal' */
	if(DOSIGNAL_CATCHING) {
		signal_catcher(SIGINT, (void (*)(int)) &signal_handler);  //int
		signal_catcher(SIGTSTP, (void (*)(int)) &signal_handler); //suspend
		signal_catcher(SIGQUIT, (void (*)(int)) &signal_handler); //quit
		signal_catcher(SIGABRT, (void (*)(int)) &signal_handler); //abort
	} else {
		printf("...signal catching is turned off!\n");
	}
}

int main(int argc, char *argv[]) {
	
	//struct passwd *passwddata; /* this has to be redefined in step 2 */
	/* see pwent.h */
	int nEmptyLogins = 0;

	char *userPass;
	char *encrPass;
	
	char prompt[] = "password: ";
	
	char user[LENGTH];
	char important[LENGTH] = "***IMPORTANT***";
	
	mypwent *passwddata;
	
	signal_handler();
	
	while (TRUE) {
		/* check what important variable contains - do not remove, part of buffer overflow test */
		printf("...value of variable 'important' before input of login name: %s\n",
		       important);

		int loginStatus = get_line("login: ", user, LENGTH);
		
		if (loginStatus == TOO_LONG) {
			printf("...buffer overflow attack detected, terminating!\n");
			//exit(0); should not exit, fgets
		}

		/* check to see if important variable is intact after input of login name - do not remove */
		printf("...value of variable 'important' after input of login name: %*.*s\n",
		       LENGTH - 1, LENGTH - 1, important);
		
		userPass = getpass(prompt);
		passwddata = mygetpwnam(user); //step 2
		
		sleep(1);//against brute force attack
		
		if (passwddata != NULL) {
			/* You have to encrypt user_pass for this to work */
			/* Don't forget to include the salt */
			
			//step 2, change to ->passwd
			//step 4, has to hash given password with salt
			encrPass = crypt(userPass, passwddata->passwdSalt);
			
			loginStatus = FAIL;
			if (!strcmp(encrPass, passwddata->passwd)) {
				loginStatus = good_pass_handler(passwddata);
			} else bad_pass_handler(passwddata);
			
			//step 5, failed logins
			mysetpwent(passwddata->pwname, passwddata);
			
			if (loginStatus == OK) {
				uid_setter(passwddata);
				shell_runner(passwddata);
			}
			
		} else {
			
			//NOTHING SHOULD BE HERE, DONT INFORM IF LOGIN BAD OR WRONG PASSWORD
		}
		
		
	}
	
	return 0;
}

//cd ~/projects/EDA263_CODE/Lab1 && make && ./login_linux
