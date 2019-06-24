int main()
{
    // printf("%lld\n", -10000000000000000000);
    // ft_printf("%lld\n", -10000000000000000000);
    // printf("%d\n", 2000000);
    // ft_printf("%d\n", 2000000);

    int n;
    int *nu;

    n = 12;
    nu = &n;
    printf("p = %100p\n", nu);
    ft_printf("p = %100p\n", nu);
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
    // printf('\n');
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
    // printf('\n');
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
    return (0);
}