#include <iostream>

#include "asio_test.hpp"
#include "cereal_test.hpp"

/*----------------------------------------------------------------------
 *
 * This file is a test program to verify:
 *   1. Whether a third-party library can be successfully compiled.
 *   2. Whether the compiled library functions correctly.
 *
 * Usage:
 *    - Build this file along with the target third-party library.
 *    - Run the executable to check basic functionality.
 *
 *--------------------------------------------------------------------*/

int main()
{
    // Test binary serialization
    test_binary_serialization();
    // Test JSON serialization
    test_json_serialization();

    try {
        asio::io_context io_context;
        Server server(io_context, 8990);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    std::cout << "\nAll tests completed successfully!" << std::endl;
    return 0;
}