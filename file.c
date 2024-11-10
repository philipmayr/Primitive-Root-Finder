// Primitive Root Finder

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int find_binary_logarithm(int number)
{
    int logarithm = 1;
    
    while (number >>= 1) logarithm++;
    
    return logarithm;
}

int * find_prime_factors(int number, int * upper_bound)
{
    int * prime_factors = malloc(sizeof (int) * * upper_bound);
    
    int index = 0;
    
    while (~number & 1)
    {
        prime_factors[index] = 2;
        
        number >>= 1;
        
        index++;
    }
    
    for (int factor_candidate = 3; factor_candidate <= sqrt(number); factor_candidate += 2)
    {
        while (number % factor_candidate == 0)
        {
            int factor = factor_candidate;
            
            prime_factors[index] = factor;
            
            number /= factor;
            
            index++;
        }
    }
    
    if (number > 2) prime_factors[index] = number;
    
    * upper_bound = index;
    
    return prime_factors;
}

int find_primitive_root(int prime_modulus)
{
    if (prime_modulus == 2) return 1;
    
    // primitive root α
    int primitive_root = 2;
    
    int prime_modulus_less_one = prime_modulus - 1;
    
    // TODO 
    
    return primitive_root;
}

int main()
{
    for (;;)
    {    
        printf("Enter a number to find its prime factors: ");
        
        // integer input validation
        // https://jackstromberg.com/2013/02/how-to-validate-numeric-integer-input-in-c/
        
        int input, status, buffer;

    	status = scanf("%d", & input);
    	
    	while (status != 1)
    	{
            while ((buffer = getchar()) != EOF && buffer != '\n');
            
            printf("Invalid input.");
            printf("\n\n");
            printf("Enter a number to find its prime factors: ");
            
            status = scanf("%d", & input);
    	}
    
    	int number = input;
    
        int upper_bound = find_binary_logarithm(number);
        
        int * prime_factors = find_prime_factors(number, & upper_bound);
       
        printf("%d ", * (prime_factors));
        
        for (int index = 1; index < upper_bound; index++)
            printf("%d ", * (prime_factors + index));
            
        printf("\n\n");
    }
    
    return 0;
}
