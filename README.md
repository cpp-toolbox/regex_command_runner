# regex_command_runner
SUBPROJECT

# usage
```cpp
int main() {

    RegexCommandRunner runner;

    runner.add_regex(":", []() { std::cout << "entered command mode" << std::endl; });
    runner.add_regex("j", []() { std::cout << "go down" << std::endl; });
    runner.add_regex("k", []() { std::cout << "go up" << std::endl; });
    runner.add_regex("\\d+G", []() { std::cout << "Found a number!" << std::endl; });
    runner.add_regex("gg", []() { std::cout << "go to top of file" << std::endl; });
    runner.add_regex("^G", []() { std::cout << "go to end of file" << std::endl; });
    runner.add_regex("[dc][tTfF][a-zA-Z]", []() { std::cout << "change or delete motion" << std::endl; });

    // Test the runner with different strings
    runner.update_string("253G");
    runner.update_string("j");
    runner.update_string("dtw");

    return 0;
}
```
