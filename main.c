#include "ft_printf.h"

int main()
{
    // ft_printf("@moulitest: %#.ohey %#.0ohey\n", 0, 0);
    // printf("@moulitest: %#.ohey %#.0ohey\n", 0, 0);

    // ft_printf("null %c and text\n", 0);
    // printf("null %c and text\n", 0);

    printf("val = %d\n", ft_printf("%.5p\n", 0));
    printf("val = %d\n", printf("%.5p\n", 0));

    // printf("val = %d\n", ft_printf("%.p\n", 0));
    // printf("val = %d\n", printf("%.p\n", 0));


    // printf("val = %d\n", ft_printf("@moulitest: %05c\n", 1));
    // printf("val = %d\n", printf("@moulitest: %05c\n", 1));


    // printf("1 : %d\n", ft_printf("null %c and text", 0));
    // printf("2 : %d\n", printf("null %c and text", 0));

    // ft_printf("null %c and text\n", 0);
    // printf("null %c and text\n", 0);
    // printf("moulitest: %.dhey %.0dhey\n", 0, 0);
    // ft_printf("moulitest: %.dhey %.0dhey\n", 0, 0);

    // printf("%d\n", -1000000000000000000);
    // ft_printf("%d\n", -1000000000000000000);
    // printf("\n");
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
    
    // printf("|%-+.20d|\n\n", 12);
    // printf("4567 |%-10]5d| plip\n", 12);
    // printf("4567 |%10]5d| plip\n", 12);

    // TESTS OK :
    
    // printf("%#u\n", -100000000);
    // ft_printf("%#u\n", -100000000);
    // printf("\n");

    // printf("%#01d\n", -100);
    // ft_printf("%#01d\n", -100);
    // printf("\n");

    // printf("%#o\n", -1234567);
    // ft_printf("%#o\n", -1234567);
    // printf("\n");

    // printf("%#X\n", 100000);
    // ft_printf("%#X\n", 100000);
    // printf("\n");

    // printf("%010u\n", -100);
    // ft_printf("%010u\n", -100);
    // printf("\n");

    // printf("%%%4d\n", 13);
    // ft_printf("%%%4d\n", 13);
    // printf("\n");

    // printf("%#x\n", 548045);
    // ft_printf("%#x\n", 548045);
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

	// printf("%#.0fhey\n", 34.00020049);
	// ft_printf("%#.0fhey\n", 34.00020049);
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

    // printf("%18.20Xhey\n", 0);
    // ft_printf("%18.20Xhey\n", 0);
    // printf("\n");

    // printf("%20.2f\n", 1234.5690);
	// ft_printf("%20.2f\n", 1234.5690);
	return (0);
}