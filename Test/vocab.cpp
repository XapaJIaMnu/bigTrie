#include "parser.h"
#define CATCH_CONFIG_MAIN 
#include "3rd_party/catch.hpp" 

TEST_CASE("Check vocab", "[factorial]" ) {
    MakeVocab vocabFunctor;
    readFileByLine("Test/test_sents", vocabFunctor);
    std::unordered_map<std::string, uint16_t> inmap;
    std::unordered_map<uint16_t, std::string> outmap;
    auto maps = vocabFunctor.getMaps();
    inmap = maps.first;
    outmap = maps.second;
    {
        INFO("i is indexed as " << inmap.at("i") << " expected 0.")
        CHECK(inmap.at("i") == 0);
        CHECK(outmap.at(0) == "i");
    }
    {
        INFO("am is indexed as " << inmap.at("am") << " expected 1.")
        CHECK(inmap.at("am") == 1);
        CHECK(outmap.at(1) == "am");
    }
    {
        INFO("read is indexed as " << inmap.at("read") << " expected 7.")
        CHECK(inmap.at("read") == 7);
        CHECK(outmap.at(7) == "read");
    }
    {
        INFO(". is indexed as " << inmap.at(".") << " expected 10.")
        CHECK(inmap.at(".") == 10);
        CHECK(outmap.at(10) == ".");
    }
    {
        INFO("working is indexed as " << inmap.at("working") << " expected 28.")
        CHECK(inmap.at("working") == 24);
        CHECK(outmap.at(24) == "working");
    }
    {
        INFO("wrong is indexed as " << inmap.at("wrong") << " expected 27.")
        CHECK(inmap.at("wrong") == 27);
        CHECK(outmap.at(27) == "wrong");
    }

}