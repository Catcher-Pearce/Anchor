#include <iostream>
#include <filesystem>

int main(const int argc, char* argv[]) {
    if (argc > 3) {
        std::cerr << "Error";
        return 1;
    }

    std::string command = argv[1];

    if (command == "add") {
        std::string currentPath = std::filesystem::current_path();
        std::string name = argv[2];

        std::cout << "added " << name << " (" + currentPath << ") " << "to bookmarks";
    }
    return 0;
}
