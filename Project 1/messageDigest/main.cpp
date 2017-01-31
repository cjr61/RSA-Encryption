/***
compile and run (in linux):
g++ sha256.cpp main.cpp -o sha256_example && ./sha256_example
**/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "sha256.h"
#include "../bigInt435/BigIntegerLibrary.hh"

using namespace std;
 
int main(int argc, char *argv[])
{
    char choice;
    cout << "Press 's' to sign file, or 'v' to verify\n";
    cin >> choice;
    
    
    /** FILE SIGNING **/
    
    
    // variable declarations
    string fName, fHash, dString, eString, nString;
    
    
    // read in the d, n, and  e fromm the files
    ifstream inputFile;
    
    inputFile.open("d_n.txt");
    
    inputFile >> dString;
    inputFile >> nString;
    
    inputFile.close();
    
    inputFile.open("e_n.txt");
    
    inputFile >> eString;
    
    inputFile.close();
    
    // convert strings to Big Ints
    BigUnsigned d = 0, n=0, e=0;
    d = stringToBigUnsigned(dString);
    e = stringToBigUnsigned(eString);
    n = stringToBigUnsigned(nString);
    
    if (choice == 's') {
    
    
    // open file to encode, retry if invalid name
    cout << "Input file name to encode\n";
    cin >> fName;
    
    inputFile.open(fName);
    while (!inputFile)
    {
        cout << "invalid file name, try again\n";
        cin >> fName;
        inputFile.open(fName);
    }
    
    //convert file bytes to string
    int fSize;
    string fData;
    string fBytes;
    
    while (getline(inputFile, fData))
    {
        fBytes += fData;
        fBytes.push_back('\n');
    }
    
    
    fHash = sha256(fBytes);
    
    
    //convert hash from base 16 to base 10 and calculate signiture
    BigUnsigned hashString = BigUnsignedInABase(fHash, 16);
    
    BigUnsigned signiture = modexp(hashString, d, n);
    
    string strSig = bigUnsignedToString(signiture);
    int end = strSig.size();
    strSig.insert(end, "\n");
    
    // Add the signiture to the beginning of the file
    fBytes.insert(0, strSig);
    
    
    //save the signed file
    ofstream outputFile;
    
    outputFile.open("file.txt.signed");
    outputFile << fBytes;
    outputFile.close();
    }

    else if (choice == 'v'){
    /**** FILE VERIFICATION ****/
    
    //read in file
    ifstream testFile("file.txt.signed");
    
    string testSig, testData, testBytes, testHashStr;
    
    //grab the signiture from the first line
    getline(testFile, testSig);
    
    //read in rest of file
    while (getline(testFile, testData))
    {
        testBytes += testData;
        testBytes.push_back('\n');
    }
    
    //type conversions to test the hash value against the signiture
    BigUnsigned testSigInt = stringToBigUnsigned(testSig);
    
    testHashStr = sha256(testBytes);
    
    BigUnsigned testHashInt = BigUnsignedInABase(testHashStr, 16);
    testHashStr = bigUnsignedToString(testHashInt);
    
    BigUnsigned originalHash = modexp(testSigInt, e, n);
    
    string originalHashStr = bigUnsignedToString(originalHash);
    
    // state weather file is altered
    if (originalHashStr == testHashStr)
        cout << "File has not been altered\n";
    else
        cout<< "File has been altered\n";
    }
    
    else
    {
        cout << "Invalid selection, run program again and select v or s\n";
    }
    
    
    return 0;
}