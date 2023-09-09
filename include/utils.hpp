#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline auto read_file(const std::string& file_path) -> std::string {
    std::ifstream source_file{file_path};

    if (!source_file.is_open() || !source_file.good()) {
        return {};
    }

    std::stringstream content;
    content << source_file.rdbuf();

    source_file.close();

    return content.str();
}

inline auto print_usage() -> void {
    std::cout << "Usage: nio [options] file\n"
              << "Options:\n"
              << "  -h, --help       Show this help message..\n"
              << "  -o, --output     Specify the output file name.\n";
}

inline auto parse_arguments(int argc, char** argv) -> std::vector<std::string> {

    std::string input_file{};
    std::string output_file{};

    for (int i = 1; i < argc; ++i) {
        std::string arg{argv[i]};

        if (arg == "-h" || arg == "--help") {
            print_usage();
            return {};
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                std::cerr << "Error: Output file name not specified after "
                             "-o/--output.\n";
                return {};
            }
        } else {
            input_file = arg;
            break;
        }
    }

    return {input_file, output_file};
}