#include <iostream>
#include <vector>
#include <regex>
#include <functional>
#include "regex_command_runner.hpp"

void RegexCommandRunner::add_regex(const std::string& pattern, std::function<void()> action) {
    regex_action.emplace_back(RegexAction{pattern, std::regex(pattern), action});
}

void RegexCommandRunner::update_string(const std::string& new_string) {
    int match_count = 0;
    std::vector<size_t> matched_regex_indices;

    for (size_t i = 0; i < regex_action.size(); ++i) {
        if (std::regex_search(new_string, regex_action[i].pattern)) {
            ++match_count;
            matched_regex_indices.push_back(i);
        }
    }

    if (match_count == 1) {
        size_t matched_index = matched_regex_indices.back();
        // If exactly one regex matches, run the associated action
        regex_action[matched_index].action();
    } else if (match_count >= 2) {
        for (auto &i : matched_regex_indices) {
            std::cout << regex_action[i].pattern_string << std::endl;
        }
        // If more than one regex matches, alert the user
        std::cout << "Warning: More than one regex matched, no action executed." << std::endl;
    } else {
        // No match found
        std::cout << "No regex matched." << std::endl;
    }
}
