//
// Created by catcherpearce on 9/27/26.
//

#ifndef BOOKMARK_BOOKMARKFILEREPOSITORY_H
#define BOOKMARK_BOOKMARKFILEREPOSITORY_H
#include <filesystem>
#include <string>
#include <unordered_map>

class BookmarkFileRepository {
public:
    BookmarkFileRepository();

    bool addBookmark(const std::string& name, std::filesystem::path& path);
    bool removeBookmark(const std::string& name);
    bool getBookmark(const std::string& name);
    void loadBookmarks();

private:
    std::filesystem::path bookmarksFilePath;
    std::unordered_map<std::string, std::filesystem::path> bookmarks;

};
#endif //BOOKMARK_BOOKMARKFILEREPOSITORY_H
