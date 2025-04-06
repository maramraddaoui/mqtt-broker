cmake_minimum_required(VERSION 3.10)
project(MQTTBroker)

set(CMAKE_CXX_STANDARD 17)  # Utilisation de C++17

# Ajout des fichiers sources
set(SOURCES
    src/main.cpp
    src/server.cpp
    src/client_handler.cpp
    src/mqtt_parser.cpp
    src/topic_manager.cpp
)

set(HEADERS
    include/server.h
    include/client_handler.h
    include/mqtt_parser.h
    include/topic_manager.h
)

# Create the executable with both sources and headers
# add_executable(mqtt-broker ${SOURCES} ${HEADERS})
add_library(mqtt-broker STATIC ${SOURCES})

# Ajout des fichiers sources
set(TEST
    test/client_simulation.h
    test/client_simulation.cpp
    test/main.cpp
)

# Create the executable with both sources and headers
add_executable(test ${TEST})

# Check for Windows platform
if(WIN32)
    # Link with the ws2_32 library on Windows
    target_link_libraries(mqtt-broker ws2_32)
    target_link_libraries(test ws2_32 mqtt-broker)
endif()

# Ajout des includes
include_directories(include)

# Ajout du support multi-thread
find_package(Threads REQUIRED)
target_link_libraries(mqtt-broker Threads::Threads)
