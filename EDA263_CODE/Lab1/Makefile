all: login_linux makepass capab_test setuid_test seteuid_test

mylogin: mylogin.c pwent.h pwent.c
	gcc -g -Wall pwent.c mylogin.c -lcrypt -o mylogin

login_linux: login_linux.c pwent.h pwent.c
	gcc -g -Wall pwent.c login_linux.c -lcrypt -o login_linux

makepass: makepass.c
	gcc -o makepass makepass.c -lcrypt

capab_test: capab_test.c
	gcc -g -Wall capab_test.c -lcap -o capab_test

setuid_test: setuid_test.c
	gcc -g -Wall setuid_test.c -o setuid_test

setuid_test: setuid_test.c
	gcc -g -Wall seteuid_test.c -o seteuid_test

clean:
	rm -f *.o mylogin login_linux capab_test setuid_test seteuid_test makepass

