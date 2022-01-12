#include "include/StringUtilities.h"

namespace mythtitans::exprl::util {

    bool starts_with(const std::string& str, const std::string& prefix) {
        return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
    }

    bool ends_with(const std::string& str, const std::string& suffix) {
        return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    bool contains(const std::string& str, const std::string& content) {
        return str.find(content) != std::string::npos;
    }

}