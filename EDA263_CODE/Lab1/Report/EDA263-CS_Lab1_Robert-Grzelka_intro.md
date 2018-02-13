
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

Preparation for this laboratory requires from us to review content of:
- Stallings & Brown - Computer Security [1], Part One [1.1]:
	- Chapter 3 of User Authentication [1.1.3]
	- Chapter 4 of Access Control [1.1.4]
- EDA263 - Computer Security, 2018 Offprint [2], Chapter 1 [2.1] borrowed from "Computer Security, Stallings&Brown, 978-0-13-513711-6, Chapter 23.2 of Linux Security Model".

By [1] it is required to read all chapters in order.

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

Below we will shortly describe general information about system security, then we will smoothly pass to protection mechanisms focused on authentication methods. 

#### Certification guidelines followed  

##### CISSP

CISSP (Certified Information Systems Security Professional) certification:
- from International Information Systems Security Certification Consortium (ISC), that is non-profit org.
- referred as "gold standard" of information security certification
- only universally recognized certification in security industry
- rquired by many organizations, like US Dep. of Def., and many financial organizations
- in 2004 became first IT program with accreditation under ISO/IEC 17024 (General Requirements for Bodies Operating Certification of Person)
- CISSP examination is based on Common Body of Knowledge (CBK), a compedium of IS best practices developed and maintained by ISC
- CBK made up of 10 domains required for CISSP, where in this paper, we focus on first one that is "Access Control".

CISSP Access Control is defines as: 
- A collection of mechanisms that work together to create a security architecture to protect the assets of the information system.

Key topics of CISSP "Access Control":
- identification, authentication and authorization technologies
- discretionary versus mandatory access control models
- rule based and role based access control

List of CISSP Domains:
- Access Control
- Application Development Security
- Bussiness Continuity and Disaster Recovery Planning
- Cryptography
- IS Governance and Risk Management
- Legal, Regulations, Investigations and Compliance
- Operations Security
- Physical (Environmental) Security
- Security Architecture And Design
- Telecomunications and Network Security

##### NSA/DHS 

NSA/DHS comes from National Centers of Academic Excellence in Information Assurance/Cyber Defense (IA/CD) sponsored by US NSA and US Dep. of Homeland Security (DHS). Its goal is to:
- reduce vulnerability in national information infrastructure by promoting higher education and research in IA
- producing growing number of profesionals with IA expertise in various disciplines

Defined with set of Knowledge Units for 2/4 year institutions supported in curriculum. In area of CS the 2014 Knowledge Units lists 6 core items:
1. Cyber Defense:
	- access control, cryptography, firewalls, intrusion detection systems, malicious activity detection and countermeasures, trust relationships, defense in depth
2. Cyber Threats:
	- types of attacks, legal issues, attack surfaces, attack trees, insider problems, threat information sources
3. Fundamental Security Design Principles:
	- list of 12 principles in this paper found in section of "Security Functional Requirements" 
4. Information Assurance Fundamentals: 
	- threats and vulnerabilities, intrusion detecton and prevention system, cryptography, access control models, identification/authenitication, audit
5. Databases:
	- overwies of databases, database access controls, security issues of inference

Book [1] gives externsive information about this areas, but in this lab we will focus on conten of items like 1, 2, 4.

##### ACM/IEEE Computer Society Computer Science Curricual 2013

CS2013 (Computer Science Curricual 2013) of IAS (Information Assurance and Security) Knowledge Area:
- created by ACM (Association for Computing Machinery) and IEEE-CS (Computer Science Society of Institute of Electrical and Electronics Engineers) 
- first revision from 2001 with many experts involwed
- from consensus that it is needed to add new Knowledge Area of Information Assurance and Security (IAS) 
- have concept of assurance and security for complete perspective
- IAS is domain set of technical and policy controls and processes intended to:
	- protect information by keeping theri CIA triad, authentication and providing for non-repudation
	- give assurance carring attestation that current and past processes and data are valid 
- divides course work on: Core Tier 1, Core Tier 2, Elective,
- IAS area includes CS2013 3 from Tier 1, 5 from Tier 2 and number of Elective topics with subtopics.

IAS Knowledge Units:
1. Tier 1: 
	- Foundational Concepts in Security:
		- CIA triad
		- Risk, threats, vulnebralities, attack vectors
		- Authenitication and authorization, access control (mandatory vs discretionary)
		- Trust and trustworthiness
		- Ethics 
	- Principles of Secure Design:
		- Least privilege and isolation
		- fail-safe defaults
		- open design
		- end-to-end security
		- defense in depth
		- security by design
		- tension between security and other design goals
	- Defensive Programming:
		- input validation and data sanization
		- choice of programming language and type-safe language
		- examples of input validation and data sanization errors (buffer, overflow,s, integer errors, SQL injection, XSS vulnerability)
		- race conditions
		- correct handling of exceptions and unexpected behaviours
		- correct usage of third party components
		- effective deploying security updates
2. Tier 2:
	- Principles of Secure Design:
		- complete mediation
		- use of vetted security components
		- economy of mechanisms (reducing trusted computing base, minimze attack surface)
		- usable security
		- security composability
		- prevention, detection and detterence
	- Threats and attacks:
		- attacker goals, capabilities, motivation
		- malware
		- DOS (denial of service) and distributed DOS
		- social engineering
	- Network security:
		- network specific threats and attack types
		- use of cryptography for data and network security
		- architectures for secure networks
		- defense mechanisms and countermeasures
		- security for wireless, cellular networks
	- Cryptography:
		- basic cryptography terminology
		- cipher types
		- overview of math. preliminaries
		- public key infrastructure


#### System penetration
Systems that are meant to be secure and private may get under intrusion or penetration. It will start with attack attempting to cause a breach in this system or to compromise it. Successful attack will end with breach in the system resulting in violation of the security policy of a system. 

#### System threats
Threats as penetration attempts are usually performed using some vulnerability of system where it is open for attack (more or less). This usually hidden treats are giving undesired, negative consequences for the system. We protect system against attacks with some countermeasures, controls and restricted permissions.

#### Data Security

This brings us to security of data. We may define it with triad of Confidentiality, Integrity, Availability (CIA), that we see as key objectives of CS with additional Authenticity and Accountability (included by FIPS199).

Confidentality: 
- Assures:
	- data confidentality: data privacy, not avaiable or disclosed to others
	- privacy: control or influence over individuals related information collection and storage, disclosure units
- Loss:
	- is unauthorized disclosure of information

Integrity:
- Assures:
	- data integrity: information and programs are changed with proper authorization
	- system integrity: unimpaired functionality of system without deliberate or inadvertend uauthorized manupulation 
- Loss:
	- is unauthorized modification or descrution of information

Availability:
- Assures:
	- that system work promptly without service denials to authorized users
- Loss:
	- is disruption of access to or use of information or and information system
	
Authenticity:
- its property of being genuine and able to be verified and trusted
- confidence in the validity of a transmission, a message, or message orginator
- verification that users who they say they are and system input came from trusted source 

Accountability:
- its goal is to trace actions of entity uniquely to that entity
- this supports nonrepudation, deterrence, fault isolation, intrusion detection and prevention, after-action recovery and legal action
- in case of insecurity
- ability to trace a security breach to responsible party
- keeping records of breach for later forensic analysis to trace breach or aid in transaction disputes

#### CIA triad breach

With low, moderate and high level of impacts on organizations or individuals, there are few examples worth to note of cases if security breach will happen in any of CIA triad objectives.

Breach of Confidentaility on example of students:
- high: student grade information
- moderate: student enrollment information
- low: directory information like list of students or faculty or departmental list (usually public on website)
 
Breach of Integrity on example of hospital database about patient allergy:
- doctor should be able to trust that database is correct and current
- in case of authorized employe messing with files that may cause harm to hospital, database need to be restored to trusted basis quickly, plus trace error to responsible
- high: patient allergy information exposed may cause death to patient and hospital under liability
- moderate: online forum with registered users to discuss specific topics
- low: anonymous online poll, bcos inaccuracy and unscientific nature of pools is understood

Breach of Availability:
- more critical component, higher level of avilability required
- high: 
	- case of system with authentication services for critical systems, applications and devices
	- interruption will result in inability for custormers to access computing resources and staff to access resources they need to perform critical tasks 
	- large finansial loss in employee productivity and potential customer loss
- moderate:
	- public website of university with information for current and prospective students and donors
	- not critical component, but inaviliability will cause some embarrassment
- low: 
	- online telephone directory lookup application loss may be annoyance but there are other ways to acces this information like hardcopy or operator

#### System Intruders
In case of system security, we need to protect it from intruders that may be insiders and outsiders. 

Outsiders compose of : hackers, terrorists, thieves, enemy states, spy organizations, anybody! 

But insiders are units already having some kind of access to the system, they may be: ordinary users, former users, maintenance personnel (ie. admin), designers (that may leave back doors, Trojan horses, etc.).


#### Security Problems

We have many kinds of security problems that intruders may try to use to penetrate or compromise system, ie.:
- intrusions, attacks
- eavesdropping (local, transmission, radiation, tempest)
- hardware, hardware errors
- software errors (bugs), software design methods!
- malicious software (virus, Trojan Horses, COTS, etc...)
- inadequate management, deficient configurations
- failure propagation, ie. consequences of security problems in other systems
- naive or ignorant users 
- mistakes

#### Network Security Attacks

We may classify this attacks as passive and active. 

Passive attacks are eavesdropping:
- release of message contents
- traffic analysis
- are hard to detect so aim to prevent.

Active attacks do modify/fake data:
- masquerade
- replay
- modification 
- denial of service
- hard to prevent so aim to detect.

#### Threat Consequences, Types of Threat Actions that cause each consequence

We may split threat consequences on types like (with actions): 
- Unauthorized Dosclosure threat to confidentality: 
	- exposure:
		- release sensitive info, ie. credit cards number
		- result of human, hardware or software error giving user unauthorized data
		- numberous cases, ie. uni posting student confidental information on web
	- interception:
		- common on communication
		- any device on LAN can receive copy of packet intended for another device
		- on internet hacker can gain access to email traffic or other data transfer
	- inference (indirectly acces data):
		- traffic analysis, ie. pattern of trafic or amount between pairs
		- of detailed information from a database by limited access user
		- eneabled by repeated queries that combined results 
	- intrusion (circument security to gain data):
		- overcome acces control protection
- Deception threat to integirty of system or data: 
	- masquerade (posing as authorized):
		- happend if learned about logon ID and password
		- malicious logic as Trojan horse that appears to do desirable function buy gains access or tricks user into executing other logic
 	- falsification (deceive authorized user):
		- ie. student may alter grades on school database 
	- repudation (deny responsibility):
		- user denies sending or receiving or possesing data
- Disruption threat to availability or system integrity: 
	- incapacitation (attack on availability, disable component)
		- destruct or damage hardware
		- malicious software like Trojan horses, viruses, worms to disable a system or some services 
	- corruption (attack on integrity, modify functions):
		- malicious software to make services run in unintended manner
		- gain acces and modify system functions
		- ie. user placing backdoor logic in the system to provide subsequent access by other than usual procedure
	- obstruction (hinder system):
		- interfere with communication by disabling links or altering comm. control information
		- overload system by placing excess burden on communication traffic or processing resources
- Usurpation: 
	- misappropriation (assume unauthorized control of resource):
		- theft of service
		- DDOS, when malicious software is installed on number oh hosts as platforms to launch traffic attack on target host
		- malicious software makes unauth. use of system resources
	- misuse (perform function/service deterimental to security):
		- diabled or thwarted security functions of system by malicious logic or hacker with access

#### Threats and assets on examples

|			| Avaiability 		| Confidentality 	| Integrity |
|-----------|-------------------|-------------------|-----------|
| Hardware  |major threat		| unencrypted data stolen | 	|
|			|accidental or deliberate damage or theft| 		|	|
|			|most vulnerable to attack				|		|	|
|			|least susceptible to automated controls|		|	|
|			|equipment is stolen or disabled, denying service | 
|			|physical and admin measures deal with these threats |||
|Software   |key threat, deletion denying acces to user | unauthorized copy, piracy| modifications causing fail during execution or unintended task|
|			|software configur|| viruses and related attacks |
|Data 		|files are deleted, denying acces to users | unauthorized read of data | existing files modified|
|			|analysis of statistical data revelas underlying data | new files are fabricated |
|Communication Lines and Networks | messages destroyed or deleted | messages are read | messages modified, delayed, reordered or duplicated|
|								  | lines or networks unavailable | traffic pattern observed | false messages fabricated |



#### Computer Security - Major Defence Lines

We may see system security as graph composed of components like: 
- threat -> system -> user.

To make system more secure, we intend to prevent or reduce the treat of system, also protect system on its boundary from outside interference, set means for system recovery in case of penetration. We need to make system secure under idea of CIA, so we can deliver services to user. 

#### Application of Defence in Depth

Threat of system begins outside the system boundaries. Nearer we go to system and later, deeper we go inside the system, with next layers of defence, all threats should be minimized to zero until they arrive to system resources and system service can be shared to users. 

#### Model of protection mechanisms layers

We use protection mechanisms in three types of layers:
- outside the system in form of prevention:
	- legal means protection
	- deterence
- on boundary of system:
	- shield cables
	- encryption
	- physical protection (ie. locks, cages, etc...)
	- access control
- inside boundary of system in form of internal control:
	- detection and countermeasures mechanisms
	- (anti-)virus programs
	- supervision mechanisms (with response capabilities)
	- intrusion detection (with response capability)
	- encryption of stored data
	- deflection to honeypot outside the system

#### Security Functional Requirements 

Countermeasures to reduce vulnerabilities and deal with threats may be classified and characterized in multiways. We will view them in terms of functional requirements and follow classification defined in FIPS 200 (Minimum Security Requirements for Federal Information and Information Systems) - standard with 17 security areas of protecting CIA tria of information systems including their processing, storing and data transmission.

Protection of system may be seen from "technical measures" or/and "management controls and procedures" points of view. This principles of protection mechanisms can be categorized accordingly, based on FIPS 200.

Technical measures:
- access control
- identification & authentication
- system & communication protection
- system & information integrity

Management controls and procedures:
- awareness & training
- audit & accountability
- certification, accreditation & security assessments
- contingency planning
- maintenance
- physical & environmental protection
- planning
- personnel security
- risk assessment
- systems & services acquisition

Overlapping technical and management:
- configuration management 
- incident response
- media protection


Here we focus mostly on Access Control and Identification & Authenitication.

Access control is stated as:
- Limit Information system access to authorized users, processes acting on behalf of authorized users, or devices (including other IS) and to the types of transactions and functions that authorized users are permitted to exercise.

Identification and Autheniticatin:
- Identify information system users, processes acting on behalf of users, or devices, and autheniicate (or verify) the identities of those users, processes, or devices, as a prerequisite to allowing aceces to organizational IS

#### Fundamental Security Design Principles

Flaws in security and unauthorized actions made it usefull to have set of widely agreed deisng principles helpfull in development of protection mechanisms. NCAE13 sponsored by NSA/DHS list following fundamental security design principles:
- Economy of mechanism
- fail-safe defaults
- complete mediation
- open design
- separation of privilidge
- least privilidge
- least common mechanism
- psychological acceptability
- isolation
- encapsulation
- modularity
- layering
- least astonishment

Of which first eight were proposed in SALT75 and withstood in time.

Economy of mechanism: 
- try to eliminate unnecesary complexity, 
- easier to verify, 
- tend to have fewer exploitable flaws and require less maintanence
- configuration mechanisms are simple, so updating or replacing become less intensive process

Fail Safe default:
- access decisions based on permission rather than exclussion
- exclussions tend to fail by allowing acces, may go long unnoticed in normal use

Complete mediation:
- every access must be checked agains access control mechanism
- not rely on access retrieved from cache
- once user opened file, no check is made to see permissions change
- its resource-intensive and rarely used

Open Desing:
- ie. encryption keys must be secret, but encryption algorithms should be open to public

Separation of Privilidges:
- practice in which multiple privilidge attributes are required to achieve access to a restricted resource
- multifactor user authentication, ie. password and smart card to auth user
- program is divided into parts with limited specific privileges required in order to perform specific task
- ie. removing high privilidge operations to another processs and running it with higher privilidges required to perform its tasks, when day-to-day interfaces are executed in lower privilidges process

Least privilidge: 
- every process and every user of the system should operate using the last set of privilidges necessary to perform the task
- ie. role based access control [1.4]
- system security policy can identify and define various roles of users or processes
- system programs or admins should have special privilidges only when necessary otherwise withdrawn for ordinary activities that close door to accidents

Least common mechanism:
- design should minimize functions shared by different users providing mutual security
- reduce unintended communication paths
- reduce amount of hardware and software that all users depend on
- easier to verify any undesirable security mechanisms

Psychological acceptablity:
- security should not interfere unduly with works of users
- but should meet needs of those who authorize access
- should make sense to user to avoid errors
- should be transparent and introduce minimal obstruction

Isolation:
- public access systems should be isloated from critical resources
- processes and files of individual users have isolate process space, memory space, and file space with protection for preventing unauth access
- security mechanisms should be isolated to prevent access to them, ie. isolation of cryptographic software and keys

Encapsulation:
- isolation bases on object oriented functionality

#### Typical security tools used 

Firewall: 97%
Anti-Virus Software: 96%
Anti-Spyware Software: 79%
Server-Based access control list: 70%
Intrusion Detection System: 69%
Encryption for data in transit: 63%
Encryption for data in storage: 46%
Reusable account/login password: 44%
Intrusion prevention systems: 42%
Log management software: 41%
Application-level firewall: 39%
Smartcart/one-time password token: 38%
Forensics tools: 38%
Public-Key Infrastructure: 35%
Specialized wireless security system: 31%
Endpoint security client software: 30%
Biometrics: 20%
Other: 5%

#### Information, methods and tools to enhance security

General advices about system securing for administrator (and users):

- Know your system
- update it continuously
- supervise it
- make use of available security mechanisms
- alarm reports (CERT, OWASP, hacker-sites, etc...)
- information about "pathes"
- tools for analysis and intrusion detection
- educate the people (specially users)
 
#### Security terminology flow chart

System security may be described with graph containing elements like:
- Owners
- security policy or countermeasures
- vulnerabilities
- risk
- adversary or threat agents
- threats
- assets or system resources

#### Challenges of computer security

1. Security is not as simple as it may appear to the novice:
- possible to attack the security mechanism
- security is not done in isolation from the rest of the system
- mechanisms used to meet requirements of CIA triad, nonrepudation may be complex and need subtle reasoning
2. Development of security mechanism or algorithm we have to consider potential attack on those features. Successful attacks happens by looking in different way to exploit unexpected weakness in mechanism.
3. Bcos prev point, procedures providing services may be counterintuitive. Security mechanism is complex, not so obvious to see from particular requirement that elaborate measures are needed.
4. Its necessary to decide where to use designed security mechanisms, both in physical placement (what point of network require security) or in logical sense (at what layer or layers of ie. TCP/IP should security be placed).
5. Security involve typically more than some algorithm or protocol. Also require from participants to possess some secret info (ie. encryption key), which gives question how to create, distribute and protect this secret. Also reliance on communication protocols behaviour may complicate development of security mechanism, ie. random delays in network or protocols will render time limits in transit of message as useless.
2. Security is a "chess game" between the attacker and the system admin:
- attacker only needs to find single vulnerability to penetrate the system
- while the administrator needs to patch all holes to ensure system security
3. Natural tendency to disregard security problems until a security failure occurs
4. Security is a process of:
- constant monitoring 
- long-term perspective
5. Security is often an afterthought:
- added after the system has been designed
6. Some users think security is restricting them in their job
7. Security is the lack of insecurity:
- in system chain weakest points define its security


#### Example of threats for air-gapped network meant to be secure

Equation Group:
- unit of NSA been around since 2001 
- by CIA its name not of group by complex malware suite (tools for hacking), 
- labeled as "most advanced that have been seen"
- infects firmware what is impossible to get rid off
- designed to counter air-gapped systems by transfer of information on USB
- its self terminating protocol make it hard to detect
- discovered by Kaspersky

Way of breaching air gapped system:
- attacker infects and air-gapped computer using a USB device
- infected computer displays a modified image containing hidden sensitive data
- graphics card emits FM radio signals containing hidden data
- this signal can be picked by an FM receiver within range of 7[m]
- insider can bring/have an infected device within range of FM signal to receive up to 60Bps of stolen data
	
#### Protection mechanisms examples

- hardware protection (computers, servers, CDs, backups, modems, printers)
- usage of authentication (passwords, smartcards, etc...)
- proper access control (read, write, execute, install)
- usage of anti-virus programs
- proper config of firewall
- supervision and intrusion detection mechanisms
- spam filtering (whitelisting, blacklisting, greylisting, etc...)
- isolation of real sensitive networks and computers 

## Identification and Authentication

Means of identification and authentication are required to keep user privacy in system and avoid unauthorized access to user/admin accounts. It is basic defensive mechanism against others trying to infiltrate systems, bring some damage or simply steal data. 

In Linux systems, root is almighty and can manipulate with system and other users, thats why if attacker could get access to root account, then system is lost. 

If only one user will be penetrated successfully then it may seem that only his account would be lost when he is not root. But penetrated user may have special permissions, group permissions, be in sudoers group, read only or execute permissions. In this way files of groups that breached user have access to may be lost and all files that he can read will be leaked or in case of execution permission, will be executed. 

Ideally identification and authentication should be bullet-proof, but usually it carry bugs, vulnerabilities, etc. that are easily to overlook. There are many methods of identification and authentication of user, that may be split on types: user knows, users has, user is(/do). Different types will have its own pros and cons and may be considered as different layers of protection with specific types of vulnerabilities giving potential risk of breach. If used means of identification and authentication contains bugs then 

In this laboratory we will implement simple program of user identification and authentication by password means, then look for and repair bugs and typical issues in this program that attacker may use to infiltrate user account. 





