#include <iostream>
#include <filesystem>
#include "common/io/printers/PrettyOutput.h"
#include "common/config/LocatorConfigurator.h"
#include "sorting/ExternalSort.h"

int main(int n, char* args[])
{
    try {
        LocatorConfigurator::configure(n, args);
        Locator::get().program.get()->run();
        return 0;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
}
