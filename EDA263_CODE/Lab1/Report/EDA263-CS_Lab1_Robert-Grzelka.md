
# EDA263 - Computer Security, Assignment 1

Robert Grzelka, 9110091c759

# Introduction

## Topics of Laboratory

In this laboratory assignment, we study users identification and authentication in terms of security. Also we investigate a UNIX application over the requirements to runs with permissions, especially higher privileges. In this lab we will work on linux system, so if not mentioned otherwise, all specifics will correspond to linux.

### The assignment consists of two parts: 
- one to be done at home with questions to answer
- another to be done in a laboratory that require to:
	- implement a login program for UNIX
	- demonstrate solution to TA.

### Report of assignment is covering topics about:
- identification and authentication
- methods/types of authentication
- vulnerability understanding, recognition and avoidance
- requirements of a safe UNIX application that runs with higher privileges
- protection for attempts of unauthorized login with various methods

### Code of assignment is about "UNIX login implementation" that containing protection methods like:
- buffer overflows protection during stdin
- protection from signal interruption from UNIX hotkeys
- brute force dictionary password guessing protection
- leak less login failures (in case of failed logins, no default stderr)
- users database records with refreshing values of password age and login failures
- password aging over successful logins
- account lock-down over failed login attempts
- password encryption with crypt lib
- password salt
- using sleep to delay login attempts 

## Preparations

Preparation for this laboratory required from us to review content of few readings:
- Stallings & Brown - Computer Security [1], Part One [1.1]:
    - Chapter 0 of Readers and Instructors Guide [1.1.0]
    - Chapter 1 of Overwiew [1.1.1]
	- Chapter 3 of User Authentication [1.1.3]
	- Chapter 4 of Access Control [1.1.4]
- EDA263 - Computer Security, 2018 Offprint [2], Chapter 1 [2.1] borrowed from "Computer Security, Stallings&Brown, 978-0-13-513711-6, Chapter 23.2 of Linux Security Model".

Generally from [1] we had to read only [1.1.3], but as said in [1] it is required to read all chapters in linked list, thought Chapter 2 was skipped.

## Computer Security Introduction

To answer questions and write code of program, we will overview Computer Security Technology and Principles that are technical areas that must underpin any effective security strategy. We will look at [1.1] for specific technical areas of computer security: 

- identification, authentication, and authentication technologies
- discretionary versus mandatory access control
- rule-based and role-based access control

This laboratory not only includes topic of User Authentication but also this of Access Control, which in reading of [1.1.4] has textbook coverage of 1 out of 10 CISSP certification Domains, domain of "Access Control" stated as:

- a collection of mechanisms that work together to create a security architecture to protect the assets of the information system

CISSP domain of Access Control contain topics like:

- Identification, authentication, and authorization technologies
- Discretionary versus mandatory access control models

Its worth noted that CISSP certification is required by many financial institutions according to [1]. Besides CISSP, there is also similar NSA/DHS certification fully covered in [1]. This laboratory contains partially one of its listed core Knowledge Units of "Cyber Defence" with topics:

- access control, 
- cryptography, 
- firewalls, 
- intrusion detection systems, 
- malicious activity detection and countermeasures, 
- trust relationships,
- defense in depth.

### Vulnerabilities, threats and protection mechanisms

In information and information systems security we need to ask tree basic questions:
	1. What assets do we need to protect?
	2. How are those assets thretened?
	3. What can we do to counter those threats?

It may be seen that system having some assets or other usages may have its vulnerabilities used as threats to penetrate this system by an attacker. Thats why we introduce some means of data security which we set up according to importance/assets. We secure system with some objectives after definition of Computer Security:

- "The protection afforded to an automated information system in order to attain the applicable objectives of preserving the integrity, availability and confidentiality of information system resources (includes hardware, software, information/data, and telecomunications)." 

System security is set in way that make it safe against intruders under objectives model ie. NIST standard FIPS 199 called CIA triad: Confidentiality, Integrity, Availability (with additional picturesque components of: Authenticity, and Accountability).  Thus we have to deal with security problems of system, especially with network security attacks. For this purpose we set major defence lines, defend in depth by splitting security on layers of outside, boundary and inside of system. 

Based on standards, guidelines and security certifications we may follow model of protection mechanism layers, and practical security protection mechanisms principles. Besides that we may get some hints from list of popular security tools. This list also let us tell what kind of security is less/more vulnerable and mature. 

Proper usage of protection mechanisms to enhance security require from system administrators knowledge about basic information, methods and how-to about tools them-selfs. Knowledge about system objectives and available protection tools has to be matched with assets of the system what can be done by looking at security terminology flowchart. 

When dealing with already implemented or planned system, admins will be thrown into challenges of computer security. Where they may struggle with breaches into mechanisms that should be impenetrable, ie. with threats for air-gapped networks. We have a lot of protection mechanisms examples with their usages, pros and cons, that proper config may be challenged itself.

## Identification and Authentication

Means of identification and authentication are required to keep user privacy in system and avoid unauthorized access to user/admin accounts. It is basic defensive mechanism against others trying to infiltrate systems, bring some damage or simply steal data. 

In Linux systems, root is almighty and can manipulate with system and other users, thats why if attacker could get access to root account, then system is lost. 

If only one user will be penetrated successfully then it may seem that only his account would be lost when he is not root. But penetrated user may have special permissions, group permissions, be in sudoers group, read only or execute permissions. In this way files of groups that breached user have access to may be lost and all files that he can read will be leaked or in case of execution permission, will be executed. 

Ideally identification and authentication should be bullet-proof, but usually it carry bugs, vulnerabilities, etc. that are easily to overlook. There are many methods of identification and authentication of user, that may be split on types: user knows, users has, user is(/do). Different types will have its own pros and cons and may be considered as different layers of protection with specific types of vulnerabilities giving potential risk of breach. If used means of identification and authentication contains bugs then they become threat to security.

In this laboratory we will implement simple program of user identification and authentication by password means, then look for and repair bugs and typical issues in this program that attacker may use to infiltrate user account. 

## User Auth(entication)

In most CS designs, we typically have user auth as:
- fundamental building block
- primary protection mechanism
- basis for most types of access control and user accountability

RFC4949 defines user auth with:
- The process of veryfying and identity claimed by or for a system entity, consisting of two steps:
    - identification: Presenting and UID to the security system. Where id should be assigned carefully, bcos auth identities are the basis for other security services, such as access control service.
    - verification: Presenting/generating auth information that corroborates the binding between the entity and the identifier.

Each account has its UID (user identificator) that usually comes with password known only to owner of account and to system for verification purpose. Password should come with policy that make it hard to guess or steal from user, by itself its saved in system in hashed (to make it secret) form, where hash itself may not be secret. Admin is managing (ena/disa-bling) user permissions and is auditing activity of user.

## Model for Auth

NIST SP 800-63-2 (Electronic Auth Guideline, 09.2013) defines general model for user auth that involves number of entities and procedures set as sequence of user registration: 
- applicant apply to registration authority (RA) to become subscriber of a credential service provider (CSP);
- RA is trusted, set and vouches for identity of applicant to CSP
- CSP engages in exchange with subscriber
- depending on details of overall auth system, CSP issues some sort of electronic cedential to subscriber;
- credential is datastructure with authority to binds an identity and additional attrs to a token of subscriber, and can be verified at auth transaction;
- token can be encryption key or encrypted passwd that identifies subscriber, issued by CSP, generated directly by subscriber or given by 3-party. 
- token and credential may be used in subsequent auth events.

## Means of Auth

We have 3-4 general means of auth of UID used alone or combined:
- User Knows
- User Has
- User Is/Does

All of this methods if come with proper implementation can provide secure auth, but they may have problems like adversary may: guess or steal what User Knows, forge or steal what User Has. User Knows and Has come with administrative overhead for managing passwds and token infos on systems and securing this info. User Is/Does may end with false positives/negatives, deal with user acceptance, cost and convenience.

## Risk Assessment for User Auth

There are 3 concepts of security risk assesments related to auth that we wish to relate one with another: 
- assurance level
- potential impact
- areas of risk

### Assurance Level

It describes degree of certainity if who refers himself as certain user, truly has this identity. We define it as degree of confidence in the:
- vetting process that identify individual to whom has credential issued
- who uses credential is whom it was issued 

SP 800-63-2 issues 4 

# Answers to the questions

## 1. Password Aging

### What is password aging? 

It is maximum and minimum lifetime for user passwords, a method used to protect user account by means of recording number of user logins with correct password. By this policy user is prompted or forced to change password on regular basis, ie. after 10 successfully logins.

### And what methods exist to implement it?

Aging is set globally in the files /etc/login.defs and /etc/default/useradd, but these settings are only applied when new user accounts are created, so to modify lifetime of password for some existing account, one may use change command. 

Considering minium and maximum password ages, passwords should have some minimum age to prevent users from rapidly "cycling throught" password changes in attempts to resuse old passwords. Few days is optimal minimum password lifetime. As for maximum password age, reasonable seems to be two or few months to dont let user be frustrated due to many password changes that may lower password quality.

Its better to eduacate users about proetecting passwords that to rely on password aging.

## 2. If you want to increase the security of a system, you can use one-time passwords.  What are the advantages? What are the disadvantages?

One-time password is valid only once. This kind of password system may be implemented using special password generators (time dependant passwords, dynamic password generation) or simply as a list of passwords. Special type of one-time passwords are those generated by a challenge-response system for which user calculates response (as password) using the challenge, so password will change every time and can not be reused; secret lays in function translating challenge to response. 

Main advantage and distadvantage are: 
+ resistant to evasdropping and wire-taping;
- being non user friendly;
+ anti brute force guessing;
+ leaks of databases will not give valid password;
- requires some way of creating new password, like mobile phone, already generated list, smart card, email;
- attacker with fresh one-time password is free to go;
- replaces know with have;

Biggest disadvantage is being non-user friendly, also hard to implement and forces user to have external source of one time passwords. Advantage is protection against brute force login attempts. In this case salt may strengthen it even more, but at the same time, salt seems to be not necessary if hacker has only one time guess for each password.


## 3. Authentication systems are often based on some knowledge shared by the computing system and the user. This knowledge can be of three types: something the user knows, has or is. For each of these types, answer the following questions in subsections.

Role of authentication is to verify a users identity. Each user will have one identifier and one authenticator, where identifier tells who you are, and authenticator verifies that this is true that you are specific user. Authentication procedure has 4 steps of : identification, provision of authentication information, transmission of authentication information, validation of information vs reference. Problems or attacks may occur in all 4 steps. It may be assumed that validation is similar among tree types : knows, has, is. Weakest point is often at transmission channel, specially at long distances (short may be vulnerable too). Transmission channel usual threats are: eavesdropping; manipulation of routers or gateways; replay attacks. Usual remedies also apply for it. 

### 3.1. How can the authentication mechanism be implemented?

User Knows:
- Generally passwords kept in user brain memory. 
- Examples include a password, PIN, answers to set of questions.
- System may offer user accounts with passwords/pin-code that only user should know, then restrict access to this user files only for this user (and in linux to root).

User Has:
- Generally tokens, ie. electronic keycards, smar cards, physical keys, emails, ID badges, two step authentication with phone or email, NFC or RFID chips. 
- External tools that are hard to get access to beside user and hard to emulate. 
- For example to access by ssh it is more safe to use encrypted key than password, which user may store in his account.

User Is:
- Generally unique characteristics divided on static and dynamic (is/does). 
- Biometric authentication like DNA, iris, face, fingerprint scan or voice recognition, hand geometry.
- Also signature, gesture;
- It can be implemented by scanners that at first record user characteristics and then use it authenticate at each login attempt by means of comparision. 

### 3.2. What advantages and disadvantages does the authentication method have with respect to e.g. user friendliness, cost of introduction, and accuracy?

All of these methods, properly implemented and used, can provide secure user authentication. However, each method has problems. An adversary may be able to guess or steal a password. Similarly, an adversary may be able to forge or steal a token. A user may forget a password or lose a token. Further, there is a significant administrative overhead for managing password and token information on systems and securing such information on systems. With respect to biometric authenticators, there are a variety of problems, including dealing with false positives and false negatives, user acceptance, cost, and convenience.

User Knows:
+ Easy to implement, low cost;
+ familiar to user and easy to get used to;
- less user friendly in case of one-time passwords;
- Can be steal or guessed by adversary;
+ high accuracy if salt included;
+ Password authentication is portable;
- Cant be lost, but may forgotten;
+ totally accurate;

User Knows is generally threated by:
- offline dictionary attack (brute force)
- specific account attack
- popular password attack
- password guessing against single user
- workstation hijacking
- exploiting user mistakes
- exploiting multiple password use
- electronic monitoring

User Has:
- require special reader: additional hardware to match tokens, rise cost;
- token loss: temp prevent its owner from system access
- user dissatisfaction: ie. for memory cards fine with ATM but for computer access seems inconvienant
+ more user friendly, when it only requires some connection of token to reader;
- if system is simple, ie. rfid token may be forgeable or system may be breached with brute force;
- its not portable
+ requires direct access;
- direct access to token-reader may allow attacker to break it by special tools;
- can get lost or stolen;
+ can be shared between users;
- can be borrowed by attacked without notice of user;
+ accurate as password (its actually kind of movable password);


User Is:
- from most to least costly and grouped by accuracy we may consider biometric authentication of:
    - iris, 
    - retina, finger, 
    - hand, signature, face, voice 
- require additional hardware that accuracy will rise with price;
- can be breached with brute force in some cases, ie. multiple pictures of iris;
+ faster and more user friendly than password and even pin, like phone finger print scan;
+ generally more safe that token and password, require spy techniquest, laboratory access;
- with funds to hire a spy it may be easier to steal than password ie. user may watch out his password, but not where he left fingerprints or where speak that may be recorded.
+ requires direct access to user, so it may be hard to achieve 
- in case of very high standard of user tools, user life may be in danger;
+ mass produced may rise general effectiveness
- mass produced may make it more crackable
- may give acces to imposer with some probability and block genuine user

### 3.3. How can the disadvantages be overcome?

User Knows:
- use of password manager, ie. in browsers there is last-pass;
- usage of long passwords with fake words that are easy to remember for user;
- strong password may be better than password ageing;
- usage of one-time passwords;
- use within multiauth with has or/and is

User Knows - countermeasures to types of attacks:
- offline dictionary attack: 
    - include controls to prevent unauthorized access to password file
    - intrusion detection measures to identify a compromise
    - rapid reissuance of passwords should one be compromissed
- specific account attack:
    - account lockout mechanism against brute force guessing after number of failed logins, typical limit is 5 attemps
- popular password attack over multiple users:
    - include policies to inhibit selection by users of common password and scanning the IP addresses of auth requests and client cookies for submission patterns
- password guessing against against single user:
    - training and enforcment of password policies of secrecy, minimum length and character set of passwords, prohibition to use well-known ID, password aging
- workstation hijacking:
    - auto logout after period of inactivity
    - detection schemes used on user behaviour
- exploiting user mistakes:
    - user training, intrustion detection, simpler passwords within multiauth
- exploiting multiple password use:
    - policy that forbids same or similar password on particular network devices
- electronic monitoring:
    - hard to deal with, simple encryption will not fix problem, so password can be observed and reused by adversary

Despite security vulnerabilities of passwords they are still most commonly used for auth with reasons like:
- problem with software for utilization of client-size auth hardware
- physicial tokens are expensive and inconvenient to carry (if multiple of them needed)
- schemes that rely on single sign-on to multi services using non-passwd services create single point of security risk
- automated password managers that relieve users have poor support for roaming and sync in cross platform.

User Has:
- Make tokens user friendly, that can be keep with keys, in wallet, phone app, etc and autolock tocken readers in case of brute force attacks.

User Is:
- Mass produced may rise general security
- Protection and life monitoring of important users. 
- Connect with authentication by knows and/or has.
