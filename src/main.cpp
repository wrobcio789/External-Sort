#include <iostream>
#include <filesystem>
#include "io/printers/PrettyOutput.h"
#include "config/LocatorConfigurator.h"
#include "sorting/ExternalSort.h"

int main(int n, char* args[])
{
    std::cout << std::filesystem::current_path()<< std::endl;

    LocatorConfigurator::configure(n, args);
    Locator::get().program->run();

    return 0;
}
