#pragma once
#include <string>
#include "extended_array.h"



template <typename T, typename U>
void AssertEq(const T& valueA, const U& valueB) {
	if (valueA != valueB) {
		std::string err;
		err = "Assertion failed: " + std::to_string( valueA) + " != " + std::to_string(valueB);
		throw std::runtime_error(err);
	}
}



template <typename TestFunc>
void RunOneTest(TestFunc tfunc, const std::string& test_name) {
	try
	{
		tfunc();
		std::cerr << test_name << " OK" << std::endl;
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << test_name << " FAIL: " << e.what() << std::endl;
	}
	catch (std::runtime_error& e)
	{
		std::cerr << test_name << " FAIL: " << e.what() << std::endl;
	}
}