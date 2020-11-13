#include <iostream>
#include "config/LocatorConfigurator.h"
#include "sorting/ExternalSort.h"

int main(int n, char* args[])
{
    LocatorConfigurator::configure(n, args);
    ExternalSort().Sort();
    return 0;
}
