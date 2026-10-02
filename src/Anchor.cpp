#include <iostream>
#include <filesystem>
#include "BookmarkFileRepository.h"

int main(const int argc, char* argv[]) try {
    if (argc > 4 || argc < 2) {
        std::cerr << "Error: Command not found.";
        return 1;
    }

    BookmarkFileRepository bookmarkFileRepository{};

    std::string command = argv[1];

    if (command == "+") {
        if (!argv[2]) {
            std::cerr << "Error: Please provide a name for your bookmark";
            return 0;
        }
        std::string name = argv[2];

        if (argc == 4) {
            std::error_code ec;
            std::filesystem::path specifiedPath(argv[3]);

            if (std::filesystem::is_directory(specifiedPath, ec)) {
                bookmarkFileRepository.addBookmark(name, specifiedPath);
            } else {
                if (ec) {
                    std::cerr << "Error: Path is invalid\n";
                } else {
                    std::cerr << "Error: Directory does not exist\n";
                }
            }
        } else {
            bookmarkFileRepository.addBookmark(name, std::filesystem::current_path());
        }

        bookmarkFileRepository.loadBookmarks();

    } else if (command == "-") {
        if (!argv[2]) {
            std::cerr << "Error: Bookmark name not specified";
            return 0;
        }

        const std::string name = argv[2];
        bookmarkFileRepository.removeBookmark(name);
    } else {
        return bookmarkFileRepository.getBookmark(command) ? 0 : 1;
    }

} catch (const std::exception& error) {
    std::cerr << "Error: " << error.what() << '\n';
    return 1;
}
