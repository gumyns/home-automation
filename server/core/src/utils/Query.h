#ifndef SMARTHOMESERVER_QUERY_H
#define SMARTHOMESERVER_QUERY_H

#include <sstream>
#include <string>
#include <vector>
#include <map>

class Query {
public:
    static std::vector<std::string> split(const std::string &string, const char delimeter) {
        std::stringstream stringStream(string);
        std::string item;
        std::vector<std::string> elements;
        while (std::getline(stringStream, item, delimeter)) {
            elements.push_back(item);
        }
        return elements;
    }

    static std::map<std::string, std::string> queryMap(const std::string &string) {
        std::map<std::string, std::string> map;
        auto vector = split(string, '&');
        for (auto query : vector) {
            auto pair = split(query, '=');
            if (pair.size() == 2) {
                map[pair[0]] = pair[1];
            }
        }
        return map;
    };
};

#endif //SMARTHOMESERVER_QUERY_H
