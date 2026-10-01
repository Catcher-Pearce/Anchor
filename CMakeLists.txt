cmake_minimum_required(VERSION 4.3)
project(Bookmark)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bookmark Anchor.cpp
        BookmarkFileRepository.cpp
        BookmarkFileRepository.h)
