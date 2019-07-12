#include "trieMe.h"

int main() {
    MakeVocab vocab;
    readFileByLine("Test/test_sents", vocab);
    auto maps = vocab.getMaps();

    trieMeARiver trie(maps.first, maps.second);
    readFileByLine("Test/test_sents", trie);
    trie.find("i am");
    trie.find("this");
    trie.find("we need to read in some");
}
