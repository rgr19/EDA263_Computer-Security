call: vuln

vuln: vuln.c
	gcc -z execstack -fno-stack-protector -mpreferred-stack-boundary=3 -g vuln.c -o vuln	
	#gcc -g -Wall vuln.c -o vuln

clean:
	rm -f *.o vuln

