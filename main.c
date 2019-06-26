#include "ft_printf.h"

int main()
{
    printf("%d\n", -1000000000000000000);
    ft_printf("%d\n", -1000000000000000000);
    printf("\n");
    // printf("%d\n", 2000000);
    // ft_printf("%d\n", 2000000);

    // printf("x = %x\n", "salut");
    // ft_printf("|%-+.20d|\n\n", 12);
    // ft_printf("4567 |%-10]5d| plip\n", 12);
    // ft_printf("4567 |%10]5d| plip\n", 12);
    // ft_printf("|%10.5d|\n", -12);
    // ft_printf("|%010d|\n", -12);
    // ft_printf("|%-10.5d|\n", -12);
    // ft_printf("|%-010.5d|\n", -12);
    //
    // printf("|%-+.20d|\n\n", 12);
    // printf("4567 |%-10]5d| plip\n", 12);
    // printf("4567 |%10]5d| plip\n", 12);

    // TESTS OK :
    //
    // printf("%u\n", -1000000000000);
    // ft_printf("%u\n", -1000000000000);
    // printf("\n");

    // printf("%01d\n", -100);
    // ft_printf("%01d\n", -100);
    // printf("\n");

    // printf("%010o\n", -100);
    // ft_printf("%010o\n", -100);
    // printf("\n");

    // printf("%010x\n", -100);
    // ft_printf("%010x\n", -100);
    // printf("\n");

    // printf("%010u\n", -100);
    // ft_printf("%010u\n", -100);
    // printf("\n");

    // printf("%%%4d\n", 13);
    // ft_printf("%%%4d\n", 13);
    // printf("\n");

    // printf("%x\n", 548045);
    // ft_printf("%x\n", 548045);
    // printf("\n");

    // printf("%X\n", -548045);
    // ft_printf("%X\n", -548045);
    // printf("\n");

    // printf("%01uyes\n", 429495);
    // ft_printf("%01uyes\n", 429495);
    // printf("\n");

    // printf("|%10.5d|\n", -12);
    // ft_printf("|%10.5d|\n", -12);
    // printf("\n");

    // printf("|%010d|\n", -12);
    // ft_printf("|%010d|\n", -12);
    // printf("\n");

    // printf("|%-10.5d|\n", -12);
    // ft_printf("|%-10.5d|\n", -12);
    // printf("\n");

    // printf("|%-010.5d|\n", -12);
    // ft_printf("|%-010.5d|\n", -12);
    // printf("\n");

    // printf("%.3fhey\n", 34.00020049);
    // ft_printf("%.3fhey\n", 34.00020049);
    // printf("\n");

	// printf("%.6fhey\n", 34.00020049);
	// ft_printf("%.6fhey\n", 34.00020049);
    // printf("\n");

	// printf("%   .7fhey\n", 34.00020049);
	// ft_printf("%   .7fhey\n", 34.00020049);
    // printf("\n");

	// printf("%.20fhey\n", 34.00020049);
	// ft_printf("%.20fhey\n", 34.00020049);
    // printf("\n");

	// printf("%+.fhey\n", 34.00020049);
	// ft_printf("%+.fhey\n", 34.00020049);
    // printf("\n");

	// printf("%.0fhey\n", 34.00020049);
	// ft_printf("%.0fhey\n", 34.00020049);
    // printf("\n");

	// printf("%.3fhey\n", 34.00020049);
	// ft_printf("%.3fhey\n", 34.00020049);
    // printf("\n");

	// printf("%-50fhey\n", 34.02);
	// ft_printf("%-50fhey\n", 34.02);
    // printf("\n");

	// printf("%0150fhey\n", 34.02);
	// ft_printf("%0150fhey\n", 34.02);
    // printf("\n");

	// printf("%0+15fhey\n", 34.02);
	// ft_printf("%0+15fhey\n", 34.02);
    // printf("\n");

	// printf("%.0f\n", -13.49999);
	// ft_printf("%.0f\n", -13.49999);
    // printf("\n");

	// printf("% -fhey\n", 1234.5690);
	// ft_printf("% -fhey\n", 1234.5690);
    // printf("\n");

    // printf("% -dhey\n", 1234);
    // ft_printf("% -dhey\n", 1234);
    // printf("\n");

    // printf("%20.2f\n", 1234.5690);
	// ft_printf("%20.2f\n", 1234.5690);
	return (0);
}