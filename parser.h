#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <filesystem>

/*Adapted from https://www.bfilipek.com/2018/07/string-view-perf-followup.html . We should probably go string_view way*/
void tokenizeSentence(std::string& str, std::vector<std::string>& output, std::string delimeter = " ") {
    auto first = std::cbegin(str);

    while (first != str.end()) {
        const auto second = std::find_first_of(first, std::cend(str), std::cbegin(delimeter), std::cend(delimeter));

        if (first != second) {
            output.emplace_back(str.substr(std::distance(std::cbegin(str), first), std::distance(first, second)));
        }

        if (second == str.end())
            break;

        first = std::next(second);
    }
} 


class MakeVocab {
private:
    std::unordered_map<std::string, uint16_t> inmap;
    std::unordered_map<uint16_t, std::string> outmap;
    uint16_t vID = 0;
public:
    void operator()(std::string& line) {
        std::vector<std::string> tokens;
        tokenizeSentence(line, tokens);
        for (auto&& item : tokens) {
            if (inmap.find(item) == inmap.end()) {
                outmap.insert({vID, item});
                inmap.insert({item, vID});
                vID++;
            }
        }
    }
    std::pair<std::unordered_map<std::string, uint16_t>, std::unordered_map<uint16_t, std::string>> getMaps() {
        return {inmap, outmap};
    }
};

template <class StringType, class Operation>
void readFileByLine(StringType filename, Operation& op) {
    std::ifstream input;
    input.exceptions ( std::ifstream::badbit );
    try {
        input.open(filename);
        if (!input.good()) {
            std::cerr << "No such file or directory: " << filename << std::endl;
            std::exit(1);
        }
        std::string line;
        while (getline(input, line)) {
            op(line);
        }
    } catch (const std::ifstream::failure& e) {
        std::cerr << "Error opening file " << filename << " : " << e.what() << std::endl;
        std::exit(1);
    }

}
