#include <iostream>
#include <filesystem>
#include "common/io/printers/PrettyOutput.h"
#include "common/config/LocatorConfigurator.h"
#include "sorting/ExternalSort.h"

int runProgram(Subprogram* program) {
    try {
        program->run();
        return 0;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
}

int main(int n, char* args[])
{
    std::cout << std::filesystem::current_path()<< std::endl;

    LocatorConfigurator::configure(n, args);
    return runProgram(Locator::get().program.get());
}
