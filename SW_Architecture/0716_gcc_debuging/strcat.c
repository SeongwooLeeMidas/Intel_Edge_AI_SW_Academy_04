#include <string.h>
#include <stdio.h>
char* my_strcat(char* , const char* );
int	main(int argc, char* argv[])
{
    char  fruit[80] = "straw";
    printf(" %p \n", "berry");
    my_strcat(fruit, "berry");
    printf("연결된 문자열 : % s\n", fruit);
    printf("연결된 문자열 : % s\n", my_strcat(fruit, "berry"));

}
char* my_strcat(char* pd, const char* ps)
{
    char* po = pd;
    while (*pd != '\0')
    {
        pd++;
    }
    while (*ps != '\0')
    {
        *pd = *ps;
        pd++;
        ps++;
    }
    *pd = '\0';
    return po;
}