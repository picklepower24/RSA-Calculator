// RSA Calculator for MATH135
// Justin Lu
// December 5, 2021

// TO-DO:
// Add input checking for menu()
#include <iostream>
#include <math.h>
#include <string>
#include <Vector>

class Key {
    public: 
        int val;
        int n;
        Key (int x, int y) {
            val = x;
            n = y;
        }
        friend std::ostream& operator<<(std::ostream& os, const Key& k);
};

std::ostream& operator<<(std::ostream& os, const Key& k) {
    os << "(" << k.val << ", " << k.n << ")";
    return os;
}

int menu() {
    bool invalid = true;
    int choice = 0;

    while (invalid) {
        std::cout << "Welcome to Justin's RSA Calculator!" << std::endl;
        std::cout << "Select what you'd like to calculate:\n 1. Create Keys\n 2. Encrypt Message \n 3. Decrypt message" << std::endl;;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                std::cout << "Create Keys:" << std::endl;
                invalid = false;
                break;
            }
            case 2: {
                std::cout << "Encrypt Message" << std::endl;
                invalid = false;
                break;
            }
            case 3: {
                std::cout << "Decrypt Message" << std::endl;
                invalid = false;
                break;
            }
            default: {
                invalid = true;
                std::cout << choice << " is an invalid choice. Please select from the three options below.\n" << std::endl;
                break;
            }
        }
    }
    return choice;
}

// Determines if n is prime
bool isPrime(int n) {
    int limit = ceil(sqrt(n));
    for (int i = 2; i < limit; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// Finds gcd of m, n
int gcd(int a, int b) {
   if (b == 0) return a;
   return gcd(b, a % b);
}

void createKeys() {
    int p, q, d, e;
    int step = 1;
    std::vector<int> eValues;

    bool invalidInput = true;
    bool invalidD = true;
    bool invalidE = true;

    while (invalidInput) {
        std::cout << "RSA requires two distict prime numbers: P and Q. Please enter them below." << std::endl;
        std::cin >> p >> q;
        if (isPrime(p) && isPrime(q) && p != q) {
            invalidInput = false;
        } else {
            std::cout << "Invalid input. Please make sure that both p and q are prime, and that p is not equal to q." << std::endl;
        }
    }
    int n = p * q;

    std::cout << "Great! Now, we need to choose the e value for the public key, such gcd(e, (p-1)(q-1)) = 1, and so that 1 < e < n." << std::endl;
    std::cout << "Choose an e value from the following list: ";
    for (int i = 2; i < n; i++) {
        if (gcd((p - 1) * (q - 1), i) == 1) {
            eValues.push_back(i);
            std::cout << i << " ";
        }
    }

    while (invalidE) {
        std::cin >> e;
        for (int i = 0; i < eValues.size(); i++) {
            if (e == eValues.at(i)) {
                invalidE = false;
            }
        }
        if (invalidE == true) {
            std::cout << "Invalid e value. Please choose a value from the list above.";
        } else {
            std::cout << "\nOkay, you chose e = " << e << std::endl;
        }
    }    

    std::cout << "Now, we'll calculate a d value for your private key such that de = 1 (mod (p-1)(q-1) )." << std::endl << std::endl;
    while (invalidD) {
        if ((e * step) % ((p-1) * (q-1)) == 1) {
            invalidD = false;
        } else {
            step++;
        }
    }
    

    d = step;
    Key publicKey = Key(e, n);
    Key privateKey = Key(d, n);

    std::cout << "Your public key is: " << publicKey << std::endl;
    std::cout << "Your private key is: " << privateKey << std::endl;
}


void encryptMessage() {
    
}

void decryptMessage() {
    int d, n, c;
    long long int remainder = 0;
    bool invalidR = true;
    std::cout << "Please enter the d value of the private key." << std::endl;
    std::cin >> d;
    std::cout << "Please enter the n value of the public key." << std::endl;
    std::cin >> n;
    std::cout << "Please enter the ciphertext as an integer." << std::endl;
    std::cin >> c;
    std::cout << "We want to solve the congruence R = " << c << "^" << d << "(mod " << n << ")." << std::endl;
    remainder = pow(c, d);
    remainder = remainder % n;
    /*for (int i = 0; i < n; i++) {
        if (i % n == remainder) {
            invalidR = false;
            remainder = i;
        }
    }
    if (invalidR == true) {
        std::cout << "Something went wrong... One of your values might not be valid." << std::endl;
    } else {*/
        std::cout << "Your recovered message (R) is: " << remainder << std::endl;
    //}
}

int main() {
    switch (menu()) {
        case 1: {
            createKeys();
        }
        case 2: {
            encryptMessage();
        }
        case 3: {
            decryptMessage();
        }
    }
    return 0;
}