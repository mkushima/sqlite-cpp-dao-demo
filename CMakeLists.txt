cmake_minimum_required(VERSION 3.10)
project(sqlite_example)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(sqlite_example ${SOURCES})

# Add SQLite3 C++ wrapper around sqlite3 library (and sqlite3 itself provided for ease of use)
# Here you can set CMake variables to avoid building Example, as well as cpplint, cppcheck...
# or set them in the cmake command line (see for instance provided build.bat/build.sh scripts)
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
add_subdirectory(SQLiteCpp)

target_link_libraries(sqlite_example SQLiteCpp)
