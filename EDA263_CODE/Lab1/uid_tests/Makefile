all: setuid_test seteuid_test uid_drop_test#capab_test

setuid_test: setuid_test.c
	gcc -g -Wall setuid_test.c -o setuid_test

seteuid_test: seteuid_test.c
	gcc -g -Wall seteuid_test.c -o seteuid_test

uid_drop_test: uid_drop_test.c
	gcc -g -Wall uid_drop_test.c -o uid_drop_test


#capab_test: capab_test.c
#	gcc -g -Wall capab_test.c -lcap -o capab_test

clean:
	rm -f *.o setuid_test seteuid_test capab_test uid_drop_test

