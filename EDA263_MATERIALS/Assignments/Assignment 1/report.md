
## Introduction

### In this lab, the following topics are covered:
* Authentication methods
* Guessing protection
* Linux permissions with SUID

### The implementation touches these topics:
* Mimic UNIX login
* Password guessing protection
* Buffer overrun
* Signal interrupt
* Set UID + start terminal

## Answers to the questions

### 1

Password ageing is a method of limiting the time a password can be used. The age
can be implemented using a creation date or with a simple use counter.
The implementation used in this assignment is a simple counter which is incremented
every time a successful login is made.

### 2

Advantages:
  - Intruders who get notion of an already used one-time password can not use it, because it
  can only be used once.
  - Leaked database doesn't leak password used on other site
  - Intruder can't do an attack based on trying commnonly used passwords

Disadvantages:
  - Requires a way of receiving the one-time password, such as a mobile phone, pregenerated list, email or
  smartcard.
  - Intruder who gets hold of an unused one-time password isn't restricted in any way
  - Replaces something you know with something you have

### 3a

Knows:
- A normal password.

Has:
- A mobile phone, smartcard or email adress.

Is:
- Fingerprint, eye-scanner.

### 3b

Knows:
  - Advantages:
    - Always with you (can't be lost physically)
    - Very accurate
    - Familiar for user
  - Disadvantages:
    - Can't be shared for temporary access 
    - Can forget

Has:
  - Advantages:
    - Can be shared for temporary access
    - Very accurate
  - Disadvantages:
    - Can get lost

Is:
  - Advantages:
    - Difficult to steal
    - Always with you
    - Possibility to be very easy to use
    - Often very fast
  - Disadvantages:
    - Expensive to make sufficiently accurate for use as a standalone
    - Lost by burn accident etc.
    - Criminals might kill you to get body part

### 3c

Knows:
  - Password manager
  - Unconstrained passwords allows the user to create a password that is meaningful to them
  - Don't force the user to change password after a time period
  - Allow one-time passwords to be created
Has:
  - Make the thing the user has something they can bring with them easily (or already brings with them)
Is:
  - Mass production lowers cost
  - Other means of access in case of damaged body

### 4a

For login at computers placed in class rooms authentication using somehting the user knows is the easiest and cheapest to use. The computers are already restricted meaning that a malicious user can't damage unauthenticated users or the system as a whole.  
A user gaining illegal access to someones student portal has the potential to delete current courses etc. which could warrant for increased security. The changes a malicious user could make to someone else account are fairly limited and probably revertable with admin interaction, therefore not warranting increased security for standard users. The convenience of allowing the user to use the same password for the computers and the student portal outweighs the risk associated with it.

### 4b

Security is very important in a military facility. We assume that a security breach could cause a disaster.
The correct way to secure the facility would be to be very strict on authentication rules.
When a person is accessing the system, we want to be sure that the person really is the owner of the account.
Accounts are defined on a one-to-one basis. This is to make a person accountable for their actions in the system.
Biometrics, combined with a secure password is suitable in this environment.

### 4c

Security is not super important in a middle-sized company and should be handled on a case-by-case basis.
Some data can be vital for the company to survive, whilst other data is just considered arbitrary.
The usual username and password combo is a good fit here, with more secure passwords.

### 4d

We assume that the personal home computer doesn't contain valuable files (work related, bank authentication etc.). Yhe primary reason to protect such home computer is to fend away those who are just curious or want to play a prank on you. Convenience is a big priority and the threat level is low. Pin code or a short password is one possibility, A cheap fingerprint reader is profficiently secure and extremely convenient. 

### 5

Making sure the system has not been altered with or impersonated.
Example: SSH and a client and server using keysigning

### 6a

i) ruid = 20757, euid = 20757  
ii) ruid = 20757, euid = 20757  

### 6b

| # | success/failure | user ID after setuid() |
|---|-----------------|------------------------|
| 1 | success         | 0                      |
| 2 | success         | 20757                  |
| 3 | success         | 20716                  |
| 4 | failure         | 20716                  |
| 5 | failure         | 20716                  |
| 6 | success         | 20716                  |

### 7a

ruid = 20757, euid = 0  

### 7b

The purpose of SUID is to get the file owner's permissions as well as owner UID and GID when executing a file/program/command.
A program can use this to share parts of the owner's permissions: e.g. ping uses this to open ports (which normal users can't do)

### 8a

i) ruid = 20757, euid = 0  
ii) ruid = 20757, euid = 20757

### 8b

To lower the permissions when they aren't needed anymore. This decreases the attack area.

## Conclusions

Some things that we have learned in this assignment:
* Choosing a authentication method is difficult
* Making the modifications was easy
* Following the man pages etc. was clear and easy
* learned how SUID works
* Signal handling
* Locating the attacker: Our code locks the user out (not good)

## Appendix: Code

```C
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

```
