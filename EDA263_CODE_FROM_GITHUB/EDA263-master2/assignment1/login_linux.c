/* $Header: https://svn.ita.chalmers.se/repos/security/edu/course/computer_security/trunk/lab/login_linux/login_linux.c 585 2013-01-19 10:31:04Z pk@CHALMERS.SE $ */

/* gcc -Wall -g -o mylogin login.linux.c -lcrypt */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>
#include <crypt.h>
#include <unistd.h>
#include "pwent.h"

#define TRUE 1
#define FALSE 0
#define LENGTH 160

void sigh_2() {
  // printf("Catching Ctrl-C\n");
}
void sigh_20() {
  // printf("Catching Ctrl-Z\n");
}
void sigh_3() {
  // printf("Catching Ctrl-\\\n");
}

int main(int argc, char *argv[]) {
  mypwent *pwd;
  char important[LENGTH] = "***IMPORTANT***";
  char user[LENGTH];
  char prompt[] = "password: ";
  char *user_pass;
  char *hash;

  // Prevent C-z, C-x, C-\
  signal(2, sigh_2);
  signal(20, sigh_20);
  signal(3, sigh_3);

  while (TRUE) {
    /* check what important variable contains - do not remove, part of buffer overflow test */
    printf("Value of variable 'important' before input of login name: %s\n",
        important);

    printf("login: ");
    fflush(NULL); /* Flush all  output buffers */
    __fpurge(stdin); /* Purge any data in stdin buffer */

    // Only read LENGTH chars from stdin, to prevent buffer overflows
    if (fgets(user, LENGTH, stdin) == NULL)
      exit(0); /*  overflow attacks.  */

    // fgets doesn't end the stream with a null byte
    // we therefor add one our self
    user[strlen(user) - 1] = '\0';
    
    // we really want to be able to quit the application
    // the default C-x and C-z has been catched above, so this
    // is currently the only easy escape out :)
    if(!strcmp(user, "exit"))
      return 0;
    
    /* check to see if important variable is intact after input of login name - do not remove */
    printf("Value of variable 'important' after input of login name: %*.*s\n",
        LENGTH - 1, LENGTH - 1, important);

    // Read (hidden) password from stdin
    user_pass = getpass(prompt);
    // Read password struct from provided username
    pwd =  mygetpwnam(user);

    // No user found or invalid data passed?
    if (pwd != NULL) {
      // Hash input password with salt from passdb
      hash = crypt(user_pass, pwd->passwd_salt); 

      // Does our hash correspond do the hashed password in passdb?
      if (!strcmp(pwd->passwd, hash)) {

        printf("You're in !\n");

        // Reset number of failed logins
        pwd->pwfailed = 0;

        // Increment password age
        pwd->pwage++;

        // Update user credentionals
        // Print error if failed
        if(!mysetpwent(user, pwd))
          printf("Could not write to password file");

        // Execute /bin/sh using the users' uuid
        // If failed, print an error message
        if(!setuid(pwd->uid))
          printf("Could not set uid");
         
        if(!system("/bin/sh"))
          printf("Could not exec sh");

      } else {
        // Login failed, increment the failed param in passdb
        pwd->pwfailed++;

        // Prevent attacks by sleeping 2 secs 
        // if #no failed logins is > 2
        if(pwd->pwfailed > 2)
          sleep(2);

        // Again, try to save user credentionals
        // Print error on failure
        if(!mysetpwent(user, pwd))
          printf("Could not write to password file");
      }
    }
    printf("Login Incorrect \n");
  }
  return 0;
}