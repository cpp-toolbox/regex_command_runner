#include <iostream>
#include <vector>
#include <regex>
#include <functional>
#include "regex_command_runner.hpp"

void RegexCommandRunner::add_regex(const std::string &pattern, std::function<void(const std::smatch &)> action) {
    regex_action.emplace_back(RegexAction{pattern, std::regex(pattern), action});
}

bool RegexCommandRunner::potentially_run_command(const std::string &command) {
    int match_count = 0;
    std::vector<size_t> matched_regex_indices;
    std::vector<std::smatch> regex_matches;

    for (size_t i = 0; i < regex_action.size(); ++i) {
        std::smatch match_result;
        if (std::regex_search(command, match_result, regex_action[i].pattern)) {
            ++match_count;
            matched_regex_indices.push_back(i);
            regex_matches.push_back(match_result);
        }
    }

    if (match_count == 1) {
        size_t matched_index = matched_regex_indices.back();
        auto match = regex_matches.back();
        // If exactly one regex matches, run the associated action
        regex_action[matched_index].action(match);
        return true;
    } else if (match_count >= 2) {

        std::cout << "WARNING multiple matches in regex command runner, fix your regex to be mutally disjoint"
                  << std::endl;

        for (auto &i : matched_regex_indices) {
            std::cout << regex_action[i].pattern_string << std::endl;
        }
        return false;
    } else {
        return false;
    }
}
