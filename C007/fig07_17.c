/* Fig. 7.17: fig07_17.c
   Demonstrating the sizeof operator */
#include <stdio.h>
int main()
{  char c;           
   short s;         
   int i;       
   long l;         
   float f;        
   double d;         
   long double ld;   
   int array[ 20 ];  /* create array of 20 int elements */
   int *ptr = array; /* create pointer to array */
   printf( "     sizeof c = %lu\tsizeof(char)  = %lu"   
           "\n     sizeof s = %lu\tsizeof(short) = %lu"   
           "\n     sizeof i = %lu\tsizeof(int) = %lu"   
           "\n     sizeof l = %lu\tsizeof(long) = %lu"   
           "\n     sizeof f = %lu\tsizeof(float) = %lu"   
           "\n     sizeof d = %lu\tsizeof(double) = %lu"   
           "\n    sizeof ld = %lu\tsizeof(long double) = %lu"   
           "\n sizeof array = %lu"   
           "\n   sizeof ptr = %lu\n",    
          sizeof c, sizeof( char ), sizeof s, sizeof( short ), sizeof i,
          sizeof( int ), sizeof l, sizeof( long ), sizeof f, 
          sizeof( float ), sizeof d, sizeof( double ), sizeof ld, 
          sizeof( long double ), sizeof array, sizeof ptr );  

   return 0; /* indicates successful termination */
} /* end main */
