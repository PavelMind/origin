#include "forTest.h"
#include <iostream>
#include "extended_array.h"

void test_mean() {
	ExtArray<int> v1{ 4, 2, 7, 3, -5, 0, -3, 1 };
	AssertEq(v1.mean(), 1.125);
}


void test_mean_good_range() {
	ExtArray<int> v1{ 4, 2, 7, 3, -5, 0, -3, 1 };
	AssertEq(v1.mean(0, 3), 4);
}
void test_mean_good_range2() {
	ExtArray<int> v1{ 4, 2, 7, 3, -5, 0, -3, 1 };
	AssertEq(v1.mean(0, 7), 1.125);
}

void test_mean_bad_range1() {
	ExtArray<int> v1{ 4, 2, 7, 3, -5, 0, -3, 1 };
	AssertEq(v1.mean(0, 8), 1.125);
}
void test_mean_bad_range2() {
	ExtArray<int> v1{ 4, 2, 7, 3, -5, 0, -3, 1 };
	AssertEq(v1.mean(3, 3), 1.125);
}
void test_mean_bad_range3() {
	ExtArray<int> v1{ 4, 2, 7, 3, -5, 0, -3, 1 };
	AssertEq(v1.mean(5, 3), 1.125);
}


int main() {
	RunOneTest<>(test_mean, "base mean");
	RunOneTest<>(test_mean_good_range, "mean, good renge");
	RunOneTest<>(test_mean_good_range2, "mean, good renge full");
	RunOneTest<>(test_mean_bad_range1, "mean, bad renge end>size");
	RunOneTest<>(test_mean_bad_range2, "mean, bad renge beg=end");
	RunOneTest<>(test_mean_bad_range3, "mean, bad renge beg>end");
}


