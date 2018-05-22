# Assignment 2

- Group 27
  - Linus Oleander, 8806134873
  - Hsin-Kai Chen, 920412C355

## Answers

### 1.

- Linus Oleander, Group 27, 8806134873
- Hsin-Kai Chen, Group 27, 920412C355

### 2.

    > gpg --fingerprint 551B0640
    0ADD 6020 4121 B03E A4E2  55ED D39C C5E6 551B 0640

### 3.

Here we use the software Thunderbird as our mail client. The reasons that we use it is because it is easy to use and already combined with the gpg key so that we can directly encrypt our message through the Thunderbird's interface.

### 4.

Hsin-Kai Chen: I think I won't use it in the future since that most of my friends are not computer science students. It is too hard for them to decrypt my message using gpg. We don't care about the security of our message that much. But if I want to encrypt my own file, I will consider to use it since it is safer.

### 5. (signing)

- A
  - Integrity
    - Only certain users should be able to change data. The data passed 
    to the system can be verified using signing.

- B (signing)
  - 1. D = H(M) => Hash message M using MD5 or something similar.
  - 2. S = C_K(D) => Encrypt digested messaged using private key to generate signature.
  - 3. Send S,M to receiver.

- C
  - We can sign a message in two ways; one using a public key encryption and the other one using a hash function. The hash function requires less CPU and can in the case of MD5 compress the message down to 128 bits, which is an advantage if the bandwidth and CPU is slow.

### 6. (encryption)

- A
  - Confidentiality
    - Only certain users should be able to read the data. Using encryption
    only authorized users has read access.

- B
  - Encryption
    - 1. Generate random key K.
    - 2. Encrypt the date using key K to D'.
    - 3. Encrypt K with receiver's public key to K'.
    - 4. Send D' and K' to receiver.

  - Decryption
    - 1. Receive D and K.
    - 2. Use receiver's private key to decrypt K to K'.
    - 3. Use K' to decrypt D to D'.
    - 4. D' is the message from sender.
- C
  - Conventional Encryption:
    - 1. It is fast.
    - 2. It is simple.
    - 3. It is low cost.

  - Public Key Cryptography
    - 1. The distribution of key is easier to achieve.
    - 2. It is safer because only owner knows his private key.

### 7.

A key is marked as trusted by an owner if any of these requirements are meet:

- You as an owener has signed it personally.
- It has been signed by one fully trusted key owner.
- It has been signed by three marginally trusted key owners.

... and the path of signed keys leading from the key in question back to your own key is less than six steps.

The trusted parameter for a person in you keychain is the truested-value you have set by your self. The validity on the other hand is the calculated value based on your web-of-trust.

### 8.

- (a) Elena trust: unknown, validity: unknown
- (b) Elena trust: unknown, validity: full

### 9.

-----BEGIN PGP PUBLIC KEY BLOCK-----
Version: GnuPG v2.0.14 (GNU/Linux)

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
x6M=
=VONf
-----END PGP PUBLIC KEY BLOCK-----