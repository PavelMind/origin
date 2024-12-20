#define CATCH_CONFIG_MAIN
#include"catch2/catch_all.hpp"
#include"extended_array.h"
TEST_CASE("checkSum") {
	SECTION("int numbers") {
		ExtArray<int> v1{ 0,1,1,0,0,1,1,0 };
		REQUIRE(v1.checkSum() == 4);
	}
	SECTION("bool numbers") {
		ExtArray<bool> v2{ 0,1,1,0,0,1,1,0 };
		REQUIRE(v2.checkSum() == 4);
	}
}

TEST_CASE("Bad arr") {
	SECTION("Bad type") {
		ExtArray<double> v3{ 0,1,1,0,0,1,1,0 };
		REQUIRE(v3.checkSum() == 4);
	}
	SECTION("Not bit") {
		ExtArray<int> v4{ 8,1,1,0,0,1,1,0 };
		REQUIRE(v4.checkSum() == 11);
	}
}


