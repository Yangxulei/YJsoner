//
// Created by 杨旭磊 on 2017/2/24.
//
#include "iostream"
#include <cmath>
#include "json_write.h"

int main(){
    auto writer = new json_write;
    writer->StartArray();

    writer->StartShortObject ();
    writer->KeyValue ("name", "yangxulei");
    writer->KeyValue ("age", 18);
    writer->EndObject ();

    writer->StartObject ();
    writer->KeyValue ("skills", "c++");
    writer->KeyValue ("skills","python");
    writer->KeyValue ("skills","reading");
    writer->KeyValue ("skills","写书");
    writer->KeyValue ("url", "http://www.yangxulei.top");

    writer->Key ("path");
    writer->StartArray ();
    writer->Value ("web");
    writer->Value ("algorithm");
    writer->Value ("linux");
    writer->EndArray ();

    writer->Key ("short-array");
    writer->StartShortArray ();
    writer->Value (1);
    writer->Value ((uint64_t)0xabcdef123456);
    writer->Value (M_PI);
    writer->EndContainer ();

    writer->EndObject (),
            writer->Value (false);
    writer->EndArray ();


}
