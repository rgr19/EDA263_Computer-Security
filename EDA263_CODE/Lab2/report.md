
# Create new keys

## create new key pair: gpg --gen-key
>2
>2048
>3m
>Robert Grzelka (Group 68)
>grzelk@student.chalmers.se
>

## delete key: 
gpg --delete-secret-keys "Robert Grzelka (Group 68)"
gpg --delete-keys "Robert Grzelka (Group 68)"

## go to gnupg user dir and create dir to store revoke serts
cd ~/.gnupg
mkdir revokeys

## change ownership to user of .gnupg dir with its content
chown -R $(whoami) ~/.gnupg/

## change access permissions

### for owner to to use ~/.gnupg/ and ~/.gnupg/* it need read (2) and write (4) access, so he can read content of dir and files inside and create new files inside
chmod 600 ~/.gnupg/* 
### for owner to enter directory it need additional execution permission, so he can not only see names of files inside but also access any file 
chmod 700 ~/.gnupg 	 

More info about permission notation: https://en.wikipedia.org/wiki/File_system_permissions#Notation_of_traditional_Unix_permissions

## Create revoke certificate
chmod 700 revokeys
cd revokeys
gpg --output revoke_RobertGrzelkaGr68.asc --gen-revoke "Robert Grzelka (Group 68)"
chown $(whoami) revoke_RobertGrzelkaGr68.asc
chmod 500 revoke_RobertGrzelkaGr68.asc # read anc execute

## Add other group members is to key (here it will be unknown, ultimate after save and quit)
gpg --edit-key grzelka@student.chalmers.se
adduid
Danqing Li (Group 68) 
EDA263 CS - Lab2
trust
5
y
quit
y

# 5.2 Encrypt and sign files

## Encrypt document: 
gpg --output whypgp.txt.gpg --encrypt --recipient grzelka@student.chalmers.se whypgp.txt

## check content of encrypted document:
l ess whypgp.txt.gpg

## encrypt with armor option


gpg --armor --output whypgp.txt.asc --encrypt --recipient grzelka@student.chalmers.se whypgp.txt


https://www.techopedia.com/definition/23150/ascii-armor

## Definition - What does ASCII-Armor mean?
ASCII armor is a binary-to-textual encoding converter. ASCII armor is a feature of a type of encryption called pretty good privacy (PGP). ASCII armor involves encasing encrypted messaging in ASCII so that they can be sent in a standard messaging format such as email.

## Techopedia explains ASCII-Armor
The reasoning behind ASCII armor for PGP is that the original PGP format is binary, which is not considered very readable by some of the most common messaging formats. Making the file into American Standard Code for Information Interchange (ASCII) format converts the binary to a printable character representation. Handling file volume can be accomplished through compressing the file. 

Although ASCII armoring is a functional part of PGP, some developers and others worry about the potential for hacking in this system. A primary concern is often called ASCII armor parser vulnerability, and is related to the idea that a cleverly constructed ASCII armored detached signature file could be used as a kind of Trojan horse to introduce a replacement .dll that could activate a virus. This is seen as one of the major holes in an otherwise very effective encryption method.

## decrypt and compare

### decrypt binary file
gpg --output whypgp.asc.txt --decrypt --recipient grzelka@student.chalmers.se whypgp.txt.asc

### decrypt asci file
gpg --output whypgp.gpg.txt --decrypt --recipient grzelka@student.chalmers.se whypgp.txt.gpg

All identical.