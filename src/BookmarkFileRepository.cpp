//
// Created by catcherpearce on 9/27/26.
//
#include "BookmarkFileRepository.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>

BookmarkFileRepository::BookmarkFileRepository() {
    std::filesystem::path dataDirectory;
    const char* xdgDataHome = std::getenv("XDG_DATA_HOME");

    if (xdgDataHome && *xdgDataHome && std::filesystem::path(xdgDataHome).is_absolute()) {
        dataDirectory = xdgDataHome;
    } else {
        const char* userHome = std::getenv("HOME");
        if (!userHome || !*userHome || !std::filesystem::path(userHome).is_absolute()) {
            throw std::runtime_error("Cannot locate bookmarks: set HOME or an absolute XDG_DATA_HOME");
        }
        dataDirectory = std::filesystem::path(userHome) / ".local" / "share";
    }

    const auto bookmarksDirectory = dataDirectory / "anchor";
    bookmarksFilePath = bookmarksDirectory / "bookmarks.txt";
    std::filesystem::create_directories(bookmarksDirectory);
    std::ofstream file;

    const bool alreadyExists = std::filesystem::exists(bookmarksFilePath);

    file.open(bookmarksFilePath, std::ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open bookmarks file");
    }

    if (!alreadyExists) {
        file << "// This is your bookmark persistence file. Bookmarks are stored in this format '<name> <directory>'\n";
        file << "anchors " << bookmarksDirectory << '\n';
    }

    file.close();
    if (file.fail()) {
        throw std::runtime_error("Could not close " + bookmarksFilePath.string() + " after initialization");
    }

    loadBookmarks();
};

void BookmarkFileRepository::loadBookmarks() {
    std::ifstream bookmarkFiles(bookmarksFilePath);
    if (!bookmarkFiles.is_open()) {
        std::cerr << "Error: Could not open " << bookmarksFilePath << " for reading\n";
        return;
    }
    decltype(bookmarks) loadedBookmarks;
    std::string bookmarkLine;

    while (std::getline(bookmarkFiles, bookmarkLine)) {
        if (bookmarkLine.starts_with("//")) {
            continue;
        }
        std::stringstream stringStream(bookmarkLine);
        std::string name;
        std::string path;
        if (!(stringStream >> name >> std::quoted(path))) {
            std::cerr << "Error: Invalid bookmark entry in " << bookmarksFilePath << '\n';
            continue;
        }

        loadedBookmarks[name] = std::filesystem::path(path);
    }
    if (bookmarkFiles.bad() || (bookmarkFiles.fail() && !bookmarkFiles.eof())) {
        std::cerr << "Error: Could not read " << bookmarksFilePath << "\n";
        return;
    }
    bookmarks = std::move(loadedBookmarks);
}

bool BookmarkFileRepository::addBookmark(const std::string& name, const std::filesystem::path path) {
    if (bookmarks.contains(name)) {
        std::cerr << "Error: bookmark already exists, replacing it\n";
        removeBookmark(name);
    }

    std::ofstream bookmarkFiles(bookmarksFilePath, std::ios::app);
    if (!bookmarkFiles.is_open()) {
        std::cerr << "Error: Could not open " << bookmarksFilePath << " for appending\n";
        return false;
    }

    bookmarkFiles << name << " " << path << "\n";
    bookmarkFiles.close();
    if (bookmarkFiles.fail()) {
        std::cerr << "Error: Could not write or close " << bookmarksFilePath << "\n";
        return false;
    }

    return true;
}

bool BookmarkFileRepository::getBookmark(const std::string &name) {
    if (!bookmarks.contains(name)) {
        std::cerr << "Error: Bookmark not found";
        return false;
    }

    std::cout << bookmarks[name].string() << '\n';
    return true;
}

bool BookmarkFileRepository::removeBookmark(const std::string &name) {
    if (!bookmarks.contains(name)) {
        std::cerr << "Error: Bookmark not found";
        return false;
    }

    std::ifstream bookmarkFile(bookmarksFilePath);
    if (!bookmarkFile.is_open()) {
        std::cerr << "Error: Could not open " << bookmarksFilePath << " for reading\n";
        return false;
    }

    std::string line;
    std::string currName;
    size_t firstSpace;

    auto tempPath = bookmarksFilePath;
    tempPath += ".tmp";

    std::ofstream output(tempPath, std::ios::trunc);
    if (!output.is_open()) {
        std::cerr << "Error: Could not create temporary bookmarks file\n";
        return false;
    }

    while (std::getline(bookmarkFile, line)) {
        if (line.starts_with("//")) {
            output << line << '\n';
            continue;
        }
        firstSpace = line.find(' ');
        currName = line.substr(0, firstSpace);

        if (currName != name) {
            output << line << "\n";
        }
    }

    output.close();
    if (output.fail()) {
        std::filesystem::remove(tempPath);
        std::cerr << "Error: Could not write or close " << tempPath << "\n";
        return false;
    }

    if (bookmarkFile.bad() ||
    (bookmarkFile.fail() && !bookmarkFile.eof())) {
        output.close();
        std::error_code cleanupError;
        std::filesystem::remove(tempPath, cleanupError);
        std::cerr << "Error: Could not read bookmarks; removal cancelled\n";
        return false;
    }

    bookmarkFile.close();

    std::error_code error;
    std::filesystem::rename(tempPath, bookmarksFilePath, error);
    if (error) {
        std::cerr << "Error: Could not replace bookmarks: "
                  << error.message() << '\n';
        return false;
    }

    return true;
}
