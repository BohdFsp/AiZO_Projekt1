cmake_minimum_required(VERSION 3.31)
project(AiZO_Projekt1)

# c++ wersja 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# bez zastrzerzeń
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# organizacja katalogów
include_directories(include)
include_directories(include/structures)
include_directories(include/algorithms)
include_directories(include/utils)

#pliki źródłowe
set(SOURCES
        src/main.cpp
        include/structures/CustomArray.hpp
        include/utils/FileIO.hpp
        include/algorithms/BubbleSort.hpp
        include/structures/SinglyLinkedList.hpp
        include/algorithms/BucketSort.hpp
        include/algorithms/QuickSort.hpp
        include/algorithms/ShellSort.hpp
        include/structures/DoublyLinkedList.hpp
        include/structures/Queue.hpp
        include/structures/BinaryTree.hpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

# --- DOŁĄCZENIE BIBLIOTEKI PROWADZĄCEGO ---
target_include_directories(${PROJECT_NAME} PRIVATE external/argparser)
#Linkujemy bibliotekę
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/argparser/libparameters.so)