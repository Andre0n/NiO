#include "utils.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: No input file specified.\n";
        print_usage();
        return 1;
    }

    auto files = parse_arguments(argc, argv);

    auto content = read_file(files.at(0));

    std::cout << content << std::endl;

    return 0;
}
