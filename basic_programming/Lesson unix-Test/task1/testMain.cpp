#include "forTest.h"
#include <iostream>
#include "extended_array.h"

void test_mean_int() {
	ExtArray<int> v1{ 4, 2, 7, 3, -5, 0, -3, 1 };
	AssertEq(v1.mean(), 1.125);
}

ExtArray<int> vNul{ }; //пустой класс

void test_mean_no_num() {
	
	AssertEq(vNul.mean(), 0);
}
void test_median_no_num() {

	AssertEq(vNul.median(), 0);
}
void test_mode_no_num() {

	AssertEq(vNul.mode().second, 0);
}


int main() {
	RunOneTest<>(test_mean_int, "mean int with numbers");
	RunOneTest<>(test_mean_no_num, "mean, no numbers");
	RunOneTest<>(test_median_no_num, "median, no numbers");
	RunOneTest<>(test_mode_no_num, "mode, no numbers");

}