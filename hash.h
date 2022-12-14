#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        // convert string add values to array
        int length = k.length();
        int converted[28];

        for(int i = 0; i < length; i++){
            converted[28 - length + i] = letterDigitToNumber(k[i]);
        }

        long long w[5];
        for(int i = 0; i < 5; i++){
            w[i] = 0;
        }

        int index = 4 - ((length - 1)/6);
        int counter = 0;
        long long total = 0;
        int modulus = length % 6;
           for(int i = 28 - length; i < 28; i++ ){
              if(modulus + 28 - length - 1 == i || counter == 5){
                total = total + converted[i];
                w[index] = total;
                index = index + 1;
                counter = 0;
                total = 0;
                modulus = (length - modulus) % 6;
                if(i == 27){
                    break;
                }
            }
            else{
                total = (total + converted[i]) * 36;
                counter++;
            }
        }

        long long result = 0;
        for (int i = 0; i < 5; i++){
            result = result + rValues[i]*w[i];
        }
        return result;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {

        // if digit
        if(letter >= 48 && letter <= 57){
            return letter - 22;
        }

        // if capital convert to lower
        else if(letter >= 65 && letter <= 90){
            letter = letter + 32;
        }

        return letter - 97;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
