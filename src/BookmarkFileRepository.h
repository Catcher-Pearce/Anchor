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
    /**
     * @brief instantiates the class and creates a
     * directory and persistence file for bookmarks
     * if one has not already been created yet
     */
    BookmarkFileRepository();

    /**
     * @brief adds or replaces a bookmark to the users bookmark persistence file.
     *
     * @param the name of the bookmark to add or replace
     * @param the file path that the bookmark points to
     * @return bool whether the function succeeded or not
     */
    bool addBookmark(const std::string& name, std::filesystem::path& path);

    /**
     * @brief removes a bookmark from the users bookmark persistence file
     *
     * @param name name of the bookmark to remove
     * @return bool whether the function succeeded or not
     */
    bool removeBookmark(const std::string& name);

    /**
     * @brief retrieves a bookmark from the users bookmark persistence file
     *
     * @param name the name of the bookmark to retrieve
     * @return bool whether the function succeeded or not
     */
    bool getBookmark(const std::string& name);

    /**
     * @brief loads bookmarks from persistence file into unordered_map (bookmarks) for retrieval
     */
    void loadBookmarks();

private:
    std::filesystem::path bookmarksFilePath;
    std::unordered_map<std::string, std::filesystem::path> bookmarks;

};
#endif //BOOKMARK_BOOKMARKFILEREPOSITORY_H
