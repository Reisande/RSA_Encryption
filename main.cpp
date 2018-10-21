#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int WordToBeEncryptedSize = 6;

/* Int_Pow exists because the pow function included in the c++ standard library returns a double, and a double is an invalid operand for the mod operand
 */
int IntPow(int base, int exponent){
    long int multiple = 1;
    for(int i = 0; i < exponent; i++) {
        multiple = multiple * base;
    }
    return multiple;
}

int Encryption(char letterToBeEncrypted, long int primeEncryption, int modNumber)
{
    int encryptedLetter = IntPow(letterToBeEncrypted, primeEncryption) % modNumber;
    return encryptedLetter;
}


int Decryption(int encryptedLetter, int PrimeDecryption, int modNumber)
{
    return (IntPow(encryptedLetter,  PrimeDecryption) % modNumber);
}


int ModularInverse(int primeEncryption, int phiModNumber)
{
    int originalPhi = phiModNumber;
    int x, v, y, u;
    x = v = 0;
    y = u = 1;
    int q, r, m, n;
    while(primeEncryption != 0) {
        q = phiModNumber / primeEncryption;
        r = phiModNumber % primeEncryption;
        m = x - (u * q);
        n = y - (v * q);
        phiModNumber = primeEncryption;
        primeEncryption = r;
        x = u;
        y = v;
        u = m;
        v = n;
        cout << " x: " << x << " y: " << y << " v: " << v << " u: " << u << " q: " << q << " r: " << r << " m: " << m << " n: " << n  << " phi: " << phiModNumber << " prime: " << primeEncryption << endl;
    }
    if (x < 0) {
        x = x + originalPhi;
    }

    return x;
}


int main() {
    int moduloPrime1 = 11;                                               // normally a larger prime number, but value ultimately doesn't matter
    int moduloPrime2 = 17;                                               // also normally a prime number
    int primeEncryption = 3;                                             // can be any number relatively prime to moduloPrime1 and moduloPrime2
    int modNumber = moduloPrime1 * moduloPrime2;                         // second half of the public key
    int phiModNumber = (moduloPrime1 - 1) * (moduloPrime2 - 1);          // number which the encrypted world is
    char wordToBeEncrypted[WordToBeEncryptedSize] = "Hello";             // each string/ char array will be converted to numeric ASCII values
    int primeDecryption = ModularInverse(phiModNumber, primeEncryption); // modular inverse of primeEncryption mod modNumber
    int encryptedWord[WordToBeEncryptedSize];
    int decryptedWord[WordToBeEncryptedSize];

    for (int letter = 0; letter < WordToBeEncryptedSize - 1; letter++) { // for loop because each individual letter is encrypted
        encryptedWord[letter] = Encryption(wordToBeEncrypted[letter], primeEncryption, modNumber);
        cout << encryptedWord[letter] << " ";
    }
    cout << endl << ModularInverse(42, 2017) << endl;

    for (int letter = 0; letter < WordToBeEncryptedSize - 1; letter++) {
        decryptedWord[letter] = Decryption(encryptedWord[letter], primeDecryption, modNumber);
        cout << decryptedWord[letter] << " ";
    }

    return 0;
}