// Primitive Root Finder

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int find_greatest_common_divisor(int a, int b)
{
    return b ? find_greatest_common_divisor(b, a % b) : a;
}

int find_totient(int number)
{
    int totient = 1;
    
    for (int index = 2; index < number; index++)
        if (find_greatest_common_divisor(index, number) == 1)
            totient++;
            
    return totient;
}

int find_binary_logarithm(int number)
{
    int logarithm = 1;
    
    while (number >>= 1) logarithm++;
    
    return logarithm;
}

int * find_distinct_prime_factors(int number, int * upper_bound)
{
    int * distinct_prime_factors = malloc(sizeof (int) * * upper_bound);
    
    int index = 0;
    
    if (~number & 1)
    {
        distinct_prime_factors[index] = 2;
        
        index++;
        
        do number >>= 1; while (~number & 1);
    }
    
    for (int factor_candidate = 3; factor_candidate <= sqrt(number); factor_candidate += 2)
    {
        if (number % factor_candidate == 0) 
        {
            int factor = factor_candidate;
            
            distinct_prime_factors[index] = factor;
            
            index++;
            
            do number /= factor; while (number % factor == 0);
        }
    }
    
    if (number > 2)
    {
        distinct_prime_factors[index] = number;
        
        index++;
    }
    
    * upper_bound = index;
    
    return distinct_prime_factors;
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

int exponentiate_modularly(int base, int index, int modulus)
{
    int residue = 1;
    
    base %= modulus;
    
    if (base == 0) return 0;
    
    while (index)
    {
        if (index & 1) residue = (residue * base) % modulus;
        
        base = (base * base) % modulus;
        
        index >>= 1;
    }
    
    return residue;
}

int find_least_primitive_root(int prime_number)
{
    if (prime_number == 2) return 1;
    
    // primitive root α
    int primitive_root = 2;
    
    int prime_number_less_one = prime_number - 1;
    
    // number of primitive roots of n is equal to phi(phi(n))
    int number_of_primitive_roots = find_totient(find_totient(prime_number));
    
    int * primitive_roots = malloc(sizeof (int) * number_of_primitive_roots);
    
    int upper_bound = log(prime_number) / log(log(prime_number_less_one));
    
    int * distinct_prime_factors = find_distinct_prime_factors(prime_number_less_one, & upper_bound);
    
    iterate_over_distinct_prime_factors:
    for (int index = 0; index < upper_bound; index++)
    {
        int exponent = (prime_number_less_one) / (* (distinct_prime_factors + index));
        
        if (exponentiate_modularly(primitive_root, exponent, prime_number) == 1)
        {
            primitive_root++;
            goto iterate_over_distinct_prime_factors;
        }
        else if (index == number_of_primitive_roots - 1)
        {
            return primitive_root;
        }
    }
    
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
        
        printf("\n");
        
        printf("Prime factors of %d: ", number);
        
        int upper_bound;
        
        upper_bound = find_binary_logarithm(number);
        
        int * prime_factors = find_prime_factors(number, & upper_bound);
        
        for (int index = 0; index < find_binary_logarithm(number); index++)
        {
            if (* (prime_factors + index) == 0) break;
            printf("%d ", * (prime_factors + index));
        }
        
        printf("\n\n");
        
        printf("Distinct prime factors of %d: ", number);
        
        upper_bound = log(number) / log(log(number));
        
        int * distinct_prime_factors = find_distinct_prime_factors(number, & upper_bound);
        
        for (int index = 0; index < upper_bound; index++)
        {
            if (* (distinct_prime_factors + index) == 0) break;
            printf("%d ", * (distinct_prime_factors + index));
        }
        
        printf("\n\n");
        
        printf("Least primitive root of %d: %d", number, find_least_primitive_root(number));
        
        printf("\n\n");
    }
    
    return 0;
}
