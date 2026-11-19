#include <_stdio.h>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

int shell_execute(const std::vector<std::string> &args) {
    if (args.empty()) {
        return 1;
    }

    if (args[0] == "exit") {
        return 0;
    }

    if (args[0] == "cd") {
        if (args.size() < 2) {
            std::cerr << "cd: no arguments provided\n";
            return 1;
        }

        if (chdir(args[1].c_str()) == -1) {
           perror("error when changing directories");
        }

        return 1;
    }


    std::vector<char*> argv;

    for (const std::string& arg : args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }

    // execvp requires nullptr at the end, same as in c
    argv.push_back(nullptr);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        execvp(argv[0], argv.data());
        perror(argv[0]);
        _exit(EXIT_FAILURE);
    } else {
        if (waitpid(pid, NULL, 0) == -1) {
            perror("waitpid");
        }
    }




    return 1;
}

std::vector<std::string> shell_split_line(const std::string& line) {
    std::istringstream input(line);
    std::vector<std::string> args;
    std::string token;

    while (input >> token) {
        args.push_back(token);
    }

    return args;
}

std::optional<std::string> shell_readline() {
    std::string line;

    if (!getline(std::cin, line)) {
       return std::nullopt;
    }

    return line;
}

void shell_loop() {
    int status;

    do {
        std::cout << "> " << std::flush;

        auto line = shell_readline();
        if (!line) {
            break;
        }

        auto args = shell_split_line(*line);
        status = shell_execute(args);
    } while (status);
}

int main() {
    shell_loop();
    return EXIT_SUCCESS;
}
