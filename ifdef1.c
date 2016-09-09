#include<stdio.h>
int main()
{
 #ifdef _DATE_
        printf("%s",_DATE_);
 #else
         printf("date is not defined\n");
 #endif

return 0;
}
