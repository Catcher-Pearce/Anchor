#include <iostream>
#include <filesystem>
#include "../BookmarkFileRepository.h"

int main(const int argc, char* argv[]) try {
    if (argc != 3 || argc != 2) {
        std::cerr << "Command not found.";
        return 1;
    }

    BookmarkFileRepository bookmarkFileRepository{};

    std::string command = argv[1];

    if (command == "+") {
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::string name = argv[2];

        bookmarkFileRepository.addBookmark(name, currentPath);
        bookmarkFileRepository.loadBookmarks();

    } else if (command == "remove") {
        const std::string name = argv[2];
        bookmarkFileRepository.removeBookmark(name);
    } else {
        return bookmarkFileRepository.getBookmark(command) ? 0 : 1;
    }

} catch (const std::exception& error) {
    std::cerr << "Error: " << error.what() << '\n';
    return 1;
}
