#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "list.h"


List obj;



TEST_CASE("List class", "[list]") {    
    SECTION("simple") {
        INFO("push_back");
        CHECK(obj.Empty() == true);
        obj.PushBack(666);
        CHECK(obj.Empty() == false);
        CHECK(obj.Size() == 1);

        INFO("push_front");
        obj.PushFront(777);
        CHECK(obj.Size() == 2);

        INFO("Pop_Back");
        CHECK(obj.PopBack() == 666);

        obj.PushBack(1);

        INFO("Pop_Front");
        CHECK(obj.PopFront() == 777);
    }

    SECTION("hard") {
        obj.Clear();
        INFO("hard example error");
        obj.PushFront(2);
        obj.PushFront(4);
        obj.PushBack(12);
        obj.PushBack(7);
        CHECK(obj.PopFront() == 4);
        CHECK(obj.PopBack() == 7);
        CHECK(obj.Size() == 2);
    }
    
    SECTION("exceptions") {
        obj.Clear();
        
        INFO("throw in PopFront");        
        CHECK_THROWS(obj.PopFront());
        
        INFO("throw in PopBack");        
        CHECK_THROWS_AS(obj.PopBack(), std::runtime_error);
    }

}