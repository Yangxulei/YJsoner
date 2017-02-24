//
// Created by 杨旭磊 on 2017/2/24.
//

//宏替换是C/C++系列语言的技术特色，C/C++语言提供了强大的宏替换功能，源代码在进入编译器之前，要先经过一个称为“预处理器”的模块，这个模块将宏根据编译参数和实际编码进行展开，展开后的代码才正式进入编译器，进行词法分析、语法分析等等。在这个测试用例中，为了简洁，将测试函数用宏函数来实现，并且嵌套了另一个宏函数释放内存。


#include "json_write.h"

#define BEGIN_TEST(name) { \
    json_write *w = new json_write; \
    w->SetInitialIndentDepth (2); \
    if (compress) { \
        w->ConfigureCompressedOutput (); \
    } \
    std::cout << #name << ":" << std::endl << std::endl;

#define END_TEST \
    delete w; \
    std::cout << std::endl << std::endl; \
}

int main (int argc, char **argv)
{
    bool compress;
    for (int i = 0; i < 2; compress = i == 0, i++) {

        BEGIN_TEST(null)
            w->NullValue ();
        END_TEST

        BEGIN_TEST(bool-false)
            w->Value (false);
        END_TEST

        BEGIN_TEST(bool-true)
            w->Value (true);
        END_TEST

        BEGIN_TEST(int)
            w->Value (30000);
        END_TEST

        BEGIN_TEST(double)
            w->Value (0.123456789);
        END_TEST

        BEGIN_TEST(empty-string)
            w->Value ("");
        END_TEST

        BEGIN_TEST(simple-string)
            w->Value ("Hello");
        END_TEST

        BEGIN_TEST(escaped-string)
            w->Value ("\"newline\ntab\t\"");
        END_TEST

        BEGIN_TEST(empty-object)
            w->StartObject ();
            w->EndObject ();
        END_TEST

        BEGIN_TEST(empty-array)
            w->StartArray ();
            w->EndArray ();
        END_TEST

        BEGIN_TEST(short-object)
            w->StartShortObject ();
            w->KeyValue ("name", "Aaron");
            w->EndObject ();
        END_TEST

        BEGIN_TEST(short-array)
            w->StartShortArray ();
            for (int i = 0; i < 10; i++) {
                w->Value (i);
            }
            w->EndArray ();
        END_TEST

        BEGIN_TEST(array-with-objects)
            w->StartArray ();
            w->StartShortObject ();
            w->KeyValue ("name", "Aaron");
            w->KeyValue ("age", 7);
            w->EndObject ();
            w->StartObject ();
            w->KeyValue ("animal", "cat");
            w->KeyValue ("life-expectancy", "forever");
            w->KeyValue ("url", "http://catoverflow.com");
            w->Key ("catch-phrases");
            w->StartArray ();
            w->Value ("meow");
            w->Value ("hiss");
            w->Value ("purr");
            w->EndArray ();
            w->EndObject (),
                    w->Value (false);
            w->EndArray ();
        END_TEST

        BEGIN_TEST(nested-objects)
            w->StartObject ();
            w->Key ("a");
            w->StartObject ();
            w->Key ("b");
            w->StartObject ();
            w->Key ("c");
            w->StartObject ();
            w->EndObject ();
            w->EndObject ();
            w->EndObject ();
            w->EndObject ();
        END_TEST

        BEGIN_TEST(nested-arrays)
            w->StartArray ();
            w->StartArray ();
            w->StartArray ();
            w->StartArray ();
            w->EndArray ();
            w->EndArray ();
            w->EndArray ();
            w->EndArray ();
        END_TEST

    }

    return 0;
}
