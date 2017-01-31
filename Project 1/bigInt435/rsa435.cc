// Cameron Reilly
// cjr61@zips.uakron.edu
// This program generates files containing the keys for RSA encryption

// Standard libraries
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>


// `BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"


bool Fermat(BigUnsigned p)
{
    for (BigInteger i = 0; i < 10; i++)
    {
        BigInteger rando = rand();
        
        if (modexp( rando, p-1, p)== 1)
            return true;
    }
    return false;
}



int main() {
	/* The library throws `const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a `try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {
      
        //generate the primes
        BigUnsigned p;
        do{
            p = BigUnsigned(1);
            for (int i=0;i<100;i++) {
                p = p*10 +rand();
            }
        } while (!Fermat(p));
        
        BigUnsigned q;
        do{
            q = BigUnsigned(1);
            for (int i=0;i<100;i++) {
                q = q*10 +rand();
            }
        } while (!Fermat(q));
        
        BigUnsigned n = p*q;
        
        //calculate the other values based on the primes
        BigUnsigned phi, e, d;
        
        phi = (p-1)*(q-1);
        
        e = rand();
        
        while (gcd(phi, e) != 1)
            e++;
        
        d = modinv( e, phi);
        
        //Output the values to the files
        std::ofstream outputFile;
        
        outputFile.open("p_q.txt");
        outputFile << p << std::endl;
        outputFile << q << std::endl;
        outputFile.close();
        
        outputFile.open("e_n.txt");
        outputFile << e << std::endl;
        outputFile << n << std::endl;
        outputFile.close();
        
        outputFile.open("d_n.txt");
        outputFile << d << std::endl;
        outputFile << n << std::endl;
        outputFile.close();
        
        outputFile << p << std::endl;
        
      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

	return 0;
}