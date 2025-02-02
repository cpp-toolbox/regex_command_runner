#ifndef REGEX_COMMAND_RUNNER_HPP
#define REGEX_COMMAND_RUNNER_HPP

#include <iostream>
#include <vector>
#include <regex>
#include <functional>

class RegexCommandRunner {
  public:
    struct RegexAction {
        std::string pattern_string;
        std::regex pattern;
        std::function<void(const std::smatch &)> action;
    };

    void add_regex(const std::string &pattern, std::function<void(const std::smatch &)> action);
    bool potentially_run_command(const std::string &new_string);

  private:
    std::vector<RegexAction> regex_action;
};

#endif
