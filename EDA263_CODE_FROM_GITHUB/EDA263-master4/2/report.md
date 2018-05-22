### 1

Group 42

| Name             | SSN         |
|------------------|-------------|
| Niklas Tegnander | 931030-3731 |
| Pierre Kraft     | 940916-2451 |

### 2

Fingerprint: 515E2DAA777BDF0178461CCBA235BBD627F77F17

### 3

Thunderbird

### 4

We don't think that we will use gpg in the future privately. We understand the security behind a "web of trust" but 
it is to much of a hassle to handle gpg keys and have them signed by people.

If it is used inside a company with a key server we can see the appeal.

### 5

Signing ensures _integrity_ of the data. This means that the data is protected from modification and ensures that
the received data originated from the actual sender. The hash function ensures that it's infeasible to change the message without the recipient noticing.

#### How does this work in PGP?

* The sender uses a hash function on the message to calculate the message digest[1].
* The message digest is used in combination with the sender's private key to create a signature.
* The message and signature is sent to the receiving end.
* The signature is decrypted using the senders public key.
* The message is verified by calculating the message digest from the message and  comparing it to the 
message digest in the received signature.

#### Why a hash function?

A hash function is a one way function that generates a fixed length string [2]. Compared to encyption a hash function doesn't increase the size of the message and still verifies the integrity of the sent message. A hash function is also less CPU intensive than encypting the whole message.

### 6

Encyption ensures _confidentiality_  of the data. This means that the data is protected from being read by others than the recipient.

#### How does this work in PGP?

##### Encyption

* The message is compressed to save bandwidth[1]
* A random _session key_ is generated
* The compressed message is encrypted with the _session key_, using a symmetrical encryption scheme
* The _session key_ is encypted with the recepients public key, using an assymetric encryption

##### Decryption

* The _session key_ is decrypted using the recepients private key
* The compressed message is decrypted with the _session key_
* The message is uncompressed

Symmetrical encryption is faster and has less overhead than assymetrical encryption, but the secret has to be shared between the sender and the recepient[3]. Assymetrical encryption doesn't require a secret to be shared and can therefore be used to send messages without any communication beforehand (except exchanging public keys).  
PGP solves the problem with symmetrical encryption by sending the new generated key with each message, encrypted using the slower assymetrical encryption.

### 7

PGP uses a web of trust where digital signatures is the form of introduction.
When a user signs another user's key, he/she becomes the _introducer_ of that specific key.
Keys connected to either a fully trusted key, or three marginally trusted keys are by default
marked as valid. A key must be valid to be used in the trust calculations. Another requirement for a key to be 
considered valid is that the _path_ of signed keys from your key to it, 
must be less than or equal to five steps long[4].

A key can be marked as trusted by yourself or a meta-introducer and when the key becomes/is valid its trust level will be used in the web of trust calculations.

### 8

#### a  
Elena trust: -, validity: -

#### b  
Elena trust: -, validity: full

### 9
```
-----BEGIN PGP PUBLIC KEY BLOCK-----
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
YzqNwM/geVSCJLsr8vH86w==
=woD/
-----END PGP PUBLIC KEY BLOCK-----
```

### Sources
[1] http://www.tutonics.com/2012/11/gpg-encryption-guide-part-3-digital.html  
[2] http://www.pgpi.org/doc/pgpintro/  
[3] https://www.digicert.com/ssl-cryptography.htm  
[4] https://www.gnupg.org/gph/en/manual.html#AEN385
