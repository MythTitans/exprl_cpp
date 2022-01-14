#include "include/ExpressionUtilities.h"

namespace mythtitans::exprl::util {

    std::unordered_set<std::string>
    getLiteralVariables(const std::vector<std::shared_ptr<eval::Expression>>& expressions) {
        std::unordered_set<std::string> literalVariables;

        for (const auto& expression: expressions) {
            for (const auto& variableName: expression->getLiteralVariables()) {
                literalVariables.insert(variableName);
            }
        }

        return literalVariables;
    }

}