#include <stdio.h>
#include <stdlib.h>

/* IMPLEMENT ME: Declare your functions here */
int add (int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);

int main()
{
	/* IMPLEMENT ME: Insert your algorithm here */
  int num1 = 10; // Example integer 1
  int num2 = 5;  // Example integer 2
  char choice;

  // Function pointers for different operations
  int (*operations[4])(int, int) = {add, subtract, multiply, divide};

  printf("Specify the operation to perform ");
  printf("(0 : add | 1 : subtract | 2 - multiply | 3 - divide | 4 - exit): ");

  // Take a single character as input
  scanf(" %c", &choice);

  // Convert character to integer and use it as an index to call the corresponding operation
  int index = choice - '0';

  while(index != 4)
  {
    // Perform the chosen operation
    int result = operations[index](num1, num2);

    // Print the result
    printf("x = %d\n", result);
    index = 4;
    
  }

	return 0;
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) 
{ 
  printf ("Adding 'a' and 'b'\n"); 
  return a + b; 
}

int subtract(int a, int b) 
{
  printf ("Subtracting 'a' and 'b'\n");
  return a - b;
}

int multiply(int a, int b) 
{
  printf ("Multiplying 'a' and 'b'\n");  
  return a * b;
}

int divide(int a, int b) 
{
  printf ("Dividing 'a' and 'b'\n");
  return a / b;
}

