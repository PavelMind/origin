#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "list.h"


List obj;



TEST_CASE("List class", "[list]") {
    SECTION("Empty ") {
        INFO("emply error");
        CHECK(obj.Empty() == true);
        obj.PushFront(7);
        CHECK(obj.Empty() == false);
    }
    SECTION("size") {
        INFO("size error");
        obj.PopFront();

        CHECK(obj.Size() == 0);
        obj.PushBack(28);
        CHECK(obj.Size() == 1);
        obj.PopFront();
        CHECK(obj.Size() == 0);
    }
    SECTION("Clear") {
        INFO("clear error");
        obj.PushBack(666);
        obj.PushBack(777);
        obj.PushBack(888);
        obj.Clear();
        CHECK(obj.Empty() == true);
    }
}