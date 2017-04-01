#ifndef SMARTHOMESERVER_BIMAP_H
#define SMARTHOMESERVER_BIMAP_H

#include <string>
#include <map>

/**
 * Very simple bimap implementation for OpenHab2 bindings storage purposes/
 */
namespace gumyns {
namespace sh {
    class Bimap {
        std::map<std::string, uint64_t> left;
        std::map<uint64_t, std::string> right;
    public:
        Bimap() {

        }

        ~Bimap() {
            left.clear();
            right.clear();
        }

        void insert(const std::string &binding, uint64_t id) {
            if (right.find(id) == right.end()) {
                right.insert(std::pair<uint64_t, std::string>(id, binding));
                left.insert(std::pair<std::string, uint64_t>(binding, id));
            }
        }

        uint64_t get(const std::string &binding) {
			auto it = left.find(binding);
            return it != left.end() ? (*it).second : 0;
        }

        std::string get(uint64_t id) {
			auto it = right.find(id);
			return it != right.end() ? (*it).second : 0;
        }

        size_t size() {
            if (left.size() == right.size())
                return left.size();
            return -1;
        }
    };
}
}

#endif //SMARTHOMESERVER_BIMAP_H
