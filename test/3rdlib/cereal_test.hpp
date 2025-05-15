#include <cassert>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Test structure containing all types we want to test
struct TestData {
    std::vector<int> int_vec;
    std::vector<double> double_vec;
    std::string regular_string;
    std::wstring wide_string;

    // Serialization function required by cereal
    template <class Archive> void serialize(Archive& archive)
    {
        archive(int_vec, double_vec, regular_string, wide_string);
    }
};

struct TestDataNoWstring {
    std::vector<int> int_vec;
    std::vector<double> double_vec;
    std::string regular_string;

    // Serialization function required by cereal
    template <class Archive> void serialize(Archive& archive)
    {
        archive(int_vec, double_vec, regular_string);
    }
};

// Helper function to print vector contents
template <typename T>
void print_vector(const std::vector<T>& vec, const std::string& name)
{
    std::cout << name << ": [";
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != 0)
            std::cout << ", ";
        std::cout << vec[i];
    }
    std::cout << "]" << std::endl;
}

// Test binary serialization functionality
void test_binary_serialization()
{
    std::cout << "\n=== Testing Binary Serialization ===" << std::endl;

    // Create test data
    TestData original;
    original.int_vec = {1, 2, 3, 4, 5};
    original.double_vec = {1.1, 2.2, 3.3, 4.4, 5.5};
    original.regular_string = "Hello, cereal! This is a test string.";
    // original.wide_string = L"Wide character string test - 宽字符测试.";

    // Print original data
    std::cout << "Original data:" << std::endl;
    print_vector(original.int_vec, "int_vec");
    print_vector(original.double_vec, "double_vec");
    std::cout << "regular_string: " << original.regular_string << std::endl;
    // std::wcout << L"wide_string: " << original.wide_string << std::endl;

    // Serialize to file
    {
        std::ofstream ofs("test_data.bin", std::ios::binary);
        cereal::BinaryOutputArchive archive(ofs);
        archive(original);
    }

    // Deserialize from file
    TestData loaded;
    {
        std::ifstream ifs("test_data.bin", std::ios::binary);
        cereal::BinaryInputArchive archive(ifs);
        archive(loaded);
    }

    // Verify loaded data
    std::cout << "\nLoaded data:" << std::endl;
    print_vector(loaded.int_vec, "int_vec");
    print_vector(loaded.double_vec, "double_vec");

    // Assert data integrity
    assert(original.int_vec == loaded.int_vec);
    assert(original.double_vec == loaded.double_vec);
    assert(original.regular_string == loaded.regular_string);
    assert(original.wide_string == loaded.wide_string);

    std::cout << "Binary serialization test passed!" << std::endl;
}

// Test JSON serialization functionality
void test_json_serialization()
{
    std::cout << "\n=== Testing JSON Serialization ===" << std::endl;

    // Create test data
    TestDataNoWstring original;
    original.int_vec = {10, 20, 30};
    original.double_vec = {1.5, 2.5, 3.5};
    original.regular_string = "JSON test string";

    // Print original data
    std::cout << "Original data:" << std::endl;
    print_vector(original.int_vec, "int_vec");
    print_vector(original.double_vec, "double_vec");
    std::cout << "regular_string: " << original.regular_string << std::endl;

    // Serialize to file
    {
        std::ofstream ofs("test_data.json");
        cereal::JSONOutputArchive archive(ofs);
        archive(original);
    }

    // Deserialize from file
    TestDataNoWstring loaded;
    {
        std::ifstream ifs("test_data.json");
        cereal::JSONInputArchive archive(ifs);
        archive(loaded);
    }

    // Verify loaded data
    std::cout << "\nLoaded data:" << std::endl;
    print_vector(loaded.int_vec, "int_vec");
    print_vector(loaded.double_vec, "double_vec");
    std::cout << "regular_string: " << loaded.regular_string << std::endl;

    // Assert data integrity
    assert(original.int_vec == loaded.int_vec);
    assert(original.double_vec == loaded.double_vec);
    assert(original.regular_string == loaded.regular_string);

    std::cout << "JSON serialization test passed!" << std::endl;
}