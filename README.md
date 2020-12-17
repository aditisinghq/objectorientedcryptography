# objectorientedcryptography
a cryptography library in c++ using rudimentary object oriented programming language concepts

facilitates encryption and decryption in three algorythms
1- RSA( Rivest- Shamir- Adleman)
2- vigenere's cipher
3- dateshift cipher

extra features-
- can set the limit of tries to enter the correct password. Data is locked after the limit is exceeded and would not be unlocked even if the correct password is entered. this protects against attacks by brute strength. 
- using modular exponentiation for calculation involved in RSA to allow for the extremely large numbers which the data types can't contain
