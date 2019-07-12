#include "parser.h"
#include <algorithm>

//Adapted from https://stackoverflow.com/questions/446296/where-can-i-get-a-useful-c-binary-search-algorithm
template<class Iter, class T>
Iter binarySearch(Iter begin, Iter end, T val) {
    Iter i = std::lower_bound(begin, end, val);

    if (i != end && !(val < *i))
        return i; // found
    else
        return end; // not found
}


class Node {
public:
    uint16_t id_;
    std::vector<Node> next_level;

    bool operator<(const Node& other) {
        if(id_ < other.id_) {
           return true;
        } else {
            return false;
        }
    }
    bool operator<(const uint16_t& other) {
        if(id_ < other) {
           return true;
        } else {
            return false;
        }
    }

    bool operator==(const Node& other) {
        if(id_ == other.id_) {
           return true;
        } else {
            return false;
        }
    }

    bool operator==(const uint16_t& other) {
        if(id_ == other) {
           return true;
        } else {
            return false;
        }
    }
};

class trieMeARiver {
private:
    std::vector<Node> trie_;
    std::unordered_map<uint16_t, std::string> vocab_;
    std::unordered_map<std::string, uint16_t> dict_;
public:
    trieMeARiver(std::unordered_map<std::string, uint16_t> dict,
        std::unordered_map<uint16_t, std::string> vocab) : dict_(dict), vocab_(vocab) {
        //This should be done in order in order to avoid the sort at the end
        for (auto&& item : vocab_) {
            Node node;
            node.id_ = item.first;
            trie_.push_back(node);
        }
        std::sort(trie_.begin(), trie_.end());
    }
    void operator()(std::string& line) {
        std::vector<std::string> tokens;
        tokenizeSentence(line, tokens);

        std::vector<Node>* curr_level = &trie_;
        
        for (auto&& item : tokens) {
            uint16_t id = dict_.at(item);
            Node tmp;
            tmp.id_ = id;
            auto it = binarySearch(curr_level->begin(), curr_level->end(), tmp);
            if (it == curr_level->end()) {
                std::cout << item << std::endl;
                curr_level->push_back(tmp);
                std::sort(curr_level->begin(), curr_level->end());
                curr_level = &tmp.next_level;
            } else {
                curr_level = &it->next_level;
            }
        }
    }
    std::vector<Node> getTrie() {
        return trie_;
    }


    void find(std::string input) {
        std::vector<Node>& curr_level = trie_;

        std::vector<std::string> tokens;
        tokenizeSentence(input, tokens);

        for (auto&& token : tokens) {
            uint16_t id = dict_.at(token);
            Node tmp;
            tmp.id_ = id;
            auto it = binarySearch(curr_level.begin(), curr_level.end(), tmp);
            if (it == curr_level.end()) {
                std::cout << "No continuations found" << std::endl;
                return;
            } else {
                curr_level = it->next_level;
            }
        }

        for (auto&& node : curr_level) {
            std::cout << vocab_.at(node.id_) << " ";
        }
        std::cout << std::endl;
    }
};
