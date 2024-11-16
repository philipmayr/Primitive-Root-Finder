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

int find_least_primitive_root(int number)
{
    if (number == 2) return 1;
    
    // primitive root α
    int primitive_root = 2;
    
    int number_less_one = number - 1;
    
    // number of primitive roots of n is equal to phi(phi(n))
    int number_of_primitive_roots = find_totient(find_totient(number));
    
    int * primitive_roots = malloc(sizeof (int) * number_of_primitive_roots);
    
    int upper_bound = find_binary_logarithm(number);
        
    int * prime_factors = find_prime_factors(number, & upper_bound);
    
    for (int a = 2; a < number_of_primitive_roots; a++)
    {
        for (int i = 0; i < upper_bound; i++)
        {
            if (exponentiate_modularly(a, number_less_one / * (prime_factors + i), number) == 1) break;
            else if (i == upper_bound - 1) return a;
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
    
        int upper_bound = find_binary_logarithm(number);
        
        int * prime_factors = find_prime_factors(number, & upper_bound);
       
        // printf("%d ", * (prime_factors));
        
        for (int index = 0; index < find_binary_logarithm(number); index++)
        {
            if (* (prime_factors + index) == 0) break;
            printf("%d ", * (prime_factors + index));
        }
            
        // printf("\n%d\n", find_least_primitive_root(number));
            
        printf("\n\n");
    }
    
    return 0;
}