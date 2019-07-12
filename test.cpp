#include "trieMe.h"

int main() {
    MakeVocab vocab;
    readFileByLine("Test/test_sents", vocab);
    auto maps = vocab.getMaps();

    trieMeARiver trie(maps.first, maps.second);
    readFileByLine("Test/test_sents", trie);
    std::cout << trie.find("i am") << std::endl;
    std::cout << trie.find("this") << std::endl;
    std::cout << trie.find("we need to read in some") << std::endl;
    std::cout << trie.find("we need to read in some duplicates ,") << std::endl;
    std::cout << trie.find("please don't") << std::endl;
    std::cout << trie.find("you have to") << std::endl;
}
