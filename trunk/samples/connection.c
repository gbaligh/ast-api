#include <stdio.h>
#include <stdlib.h>
#include "astapi.h"


int main(void)
{
    astConnect("admin", "admin", "127.0.0.1", -1);

    astDeconnect();
    return 0;
}
