cmake_minimum_required(VERSION 2.7)
project(TerminalChat)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
set(CMAKE_CXX_STANDARD 11)

#Boost
find_package(Boost 1.40.0 REQUIRED system)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif (Boost_FOUND)

if (UNIX AND NOT APPLE)
    #GTK2
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
    include_directories(${GTK2_INCLUDE_DIRS})
    link_directories(${GTK2_LIBRARY_DIRS})

    #GTK3
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})

    add_executable(TerminalChatLinux main.cpp
            network/Networking.cpp
            network/Networking.h
            network/listeners/test/LoginListener.cpp
            network/listeners/LoginListener.h
            dependencies/dependencies.cpp
            dependencies/dependencies.h
            dependencies/linux/linux_dependencies.cpp
            dependencies/linux/linux_dependencies.h
            network/listeners/test/RegisterListener.cpp
            network/listeners/RegisterListener.h
            network/listeners/test/JoinListener.cpp
            network/listeners/JoinListener.h
            network/listeners/test/SendMessageListener.cpp
            network/listeners/SendMessageListener.h
            network/listeners/test/GetMessagesListener.cpp
            network/listeners/GetMessagesListener.h
            )

    target_link_libraries(TerminalChatLinux
            ${LIBNOTIFY_INCLUDEDIR}
            ${LIBNOTIFY_INCLUDE_DIRS}
            ${GTK3_LIBRARIES}
            ${GTK2_LIBRARIES}
            ${Boost_LIBRARIES}
            -lssl -lrt -lcrypto -lpthread -lnotify -lncurses)
endif (UNIX AND NOT APPLE)
if (WIN32)
    add_executable(TerminalChatWindows main.cpp
            #network/Networking.cpp
            #network/Networking.h
            #network/listeners/test/LoginListener.cpp
            #network/listeners/LoginListener.h
            dependencies/dependencies.cpp
            dependencies/dependencies.h
            #network/listeners/test/RegisterListener.cpp
            #network/listeners/RegisterListener.h
            #network/listeners/test/JoinListener.cpp
            #network/listeners/JoinListener.h
            #network/listeners/test/SendMessageListener.cpp
            #network/listeners/SendMessageListener.h
            #network/listeners/test/GetMessagesListener.cpp
            #network/listeners/GetMessagesListener.h
            dependencies/windows/windows_dependencies.cpp
            dependencies/windows/windows_dependencies.h)

    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif (WIN32)