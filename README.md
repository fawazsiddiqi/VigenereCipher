Reading the File
The cipher text we were provided with was encoded in hexadecimal, thus we would want to change the values to either decimal or binary in order to allow the operations which would make our job easier when it comes to applying the operations we will have within our program such as XOR which is mainly used and is the backbone of the deciphering.

Structures Used
1.	Using a vector to store the extracted ciphertext after converting the hexadecimal ciphertext into bits using the bitset.
2.	Using a vector to segregate the ciphertext using a sample of the ciphertext and the characters of the ciphertext.
3.	We use a function which calculates the Index of Coincidence to find the spike within the sample size allowing us to decide the key size.
4.	We use the segregate function to place each and every ciphertext character into a column corresponding to the position of the character within the key.
5.	We also use pairs to store the hexadecimal characters into bits in the vector.

Implementation
To imply this terminology of deciphering without knowing the key size, we would first need to figure out the key within the ciphertext. That is done by calculating the Index of Coincidence of all the characters within the ciphertext, and finding a spike in the values, the key size with the first spike is most likely to be the key value.
 
And in our case as we see we see a spike in the Index of Coincidence in the key size 48, thus we could confirm that the size of the key would be 48 characters.

Then we would look for the most used character within our ciphertext which is considered to be SPACE and according to the English language E as well, and we scan our cipher text for positions of  both the space and the letter E.

Once we find the positions of the spaces and the character E, we start XORing the bits of the position at the ciphertext and the space or E

SPACE XOR CipherText = Key
E XOR CipherText = Key

Once completed, we would have a partial key which might not have all the correct characters within the key, but it would make the plaintext a bit readable.

After we have the initial plaintext and the initial key, and as we know that our key is 48 characters, we decide to guess all the letters which are missing in the initial plaintext, we would consider that as taking a part of the plaintext to figure out the correct key.
 
This is hardcoded within the program and will have to be entered manually to the source code, or to make it more optimized a user input can be used in order to deliver the same result.

Once we have the part of the plaintext, we will XOR it with the ciphertext in order to attain the correct key. 

PartOfPlaintext XOR CipherText = Key

Once that is completed we will have the final key of the ciphertext, and we can use that final key to XOR it with the ciphertext and get the final plaintext which is readable by the user and consists of no errors.

To conclude, the program cannot be fully automated since we will need to enter the guessing of the part of the plaintext, and for further improvement we would take the input of the part of the plaintext from the user, instead of hard coding as it is done in our case and will need to be changed from file to file. We could also implement a dictionary to guess the missing characters of the plaintext and gain the part of the plaintext which would allow us to get the final key, but would result in making our code and algorithm more complex.
