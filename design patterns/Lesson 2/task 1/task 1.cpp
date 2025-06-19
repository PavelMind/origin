#include <iostream>
#include "textRenders.h"

int main()
{
    auto text_block = new Paragraph(new Text());
    text_block->render("Hello world");
    std::cout << std::endl;

    auto text_block_2 = new Reversed(new Text());
    text_block_2->render("Hello world");
    std::cout << std::endl;


    auto text_block_3 = new Link(new Text());
    text_block_3->render("netology.ru", "Hello world");
}
