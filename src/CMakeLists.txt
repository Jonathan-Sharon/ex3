cmake_minimum_required(VERSION 3.17.3)
project(ex2 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

add_compile_options(-Wall -Wextra -pedantic -Werror -Wshadow)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# add the .cpp files of the project
add_executable(ex3.out
                Bmp/Bmp.cpp
                Bmp/bmp_tester.cpp
                CacheManagement/CacheManagement.cpp
                CacheOperations/BinaryStringHash.cpp
                CacheOperations/BmpCacheOperations.cpp
                CacheOperations/CacheOperationFactory.cpp
                CacheOperations/MatrixCacheOperations.cpp
                fileReading/file_reading.cpp
                Hash/crc32.c
                Matrix/Matrix.cpp
                Matrix/MatrixErrorCode.cpp
                Main.cpp
                )

# add the library
target_link_libraries(ex3.out matrix)

# add the folders of the .h files (to be able to include them)
target_include_directories(ex3.out PUBLIC
                            ${CMAKE_SOURCE_DIR}/Bmp
                            ${CMAKE_SOURCE_DIR}/CacheManagement
                            ${CMAKE_SOURCE_DIR}/CacheOperations
                            ${CMAKE_SOURCE_DIR}/fileReading
                            ${CMAKE_SOURCE_DIR}/Hash
                            ${CMAKE_SOURCE_DIR}/Matrix
                            )

# make the cache directory
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/cache)

# include the src directory
target_link_directories(ex3.out PUBLIC ${PROJECT_SOURCE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
