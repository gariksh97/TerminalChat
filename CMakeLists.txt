cmake_minimum_required(VERSION 2.7)
project(TerminalChat)

set(CMAKE_CXX_STANDARD 11)

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
            network/Listener.h
            network/Listener.cpp
            network/ThreadExecutor.cpp
            network/ThreadExecutor.h

            dependencies/Dependencies.cpp
            dependencies/Dependencies.h

            dependencies/linux/LinuxDependencies.cpp
            dependencies/linux/LinuxDependencies.h

            dependencies/linux/tui/ChatTUI.cpp
            dependencies/linux/tui/ChatTUI.h
            dependencies/linux/tui/ChatList.cpp
            dependencies/linux/tui/ChatList.h
            dependencies/linux/tui/Chat.cpp
            dependencies/linux/tui/Chat.h
            dependencies/linux/tui/TUIHelper.cpp
            dependencies/linux/tui/TUIHelper.h
            dependencies/linux/tui/TextBox.cpp
            dependencies/linux/tui/TextBox.h

            models/ChatModel.cpp
            models/ChatModel.h
            models/MessageModel.cpp
            models/MessageModel.h

            json/json.hpp
            )

    target_link_libraries(TerminalChatLinux
            -lssl -lrt -lcrypto -lpthread -lncurses
            )
endif (UNIX AND NOT APPLE)
if (WIN32)
    add_executable(TerminalChatWindows main.cpp
            #network/Networking.cpp
            #network/Networking.h
            #network/listeners/implementation/LoginListener.cpp
            #network/listeners/LoginListener.h
            dependencies/Dependencies.cpp
            dependencies/Dependencies.h
            #network/listeners/implementation/RegisterListener.cpp
            #network/listeners/RegisterListener.h
            #network/listeners/implementation/JoinListener.cpp
            #network/listeners/JoinListener.h
            #network/listeners/implementation/SendMessageListener.cpp
            #network/listeners/SendMessageListener.h
            #network/listeners/implementation/GetMessagesListener.cpp
            #network/listeners/GetMessagesListener.h
            dependencies/windows/WindowsDependencies.cpp
            dependencies/windows/WindowsDependencies.h models/ChatModel.cpp models/ChatModel.h models/MessageModel.cpp models/MessageModel.h)

    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif (WIN32)
if (APPLE)
    add_executable(TerminalChatLinux main.cpp

            network/Networking.cpp
            network/Networking.h
            network/Listener.h
            network/Listener.cpp
            network/ThreadExecutor.cpp
            network/ThreadExecutor.h

            dependencies/Dependencies.cpp
            dependencies/Dependencies.h

            dependencies/linux/LinuxDependencies.cpp
            dependencies/linux/LinuxDependencies.h

            dependencies/linux/tui/ChatTUI.cpp
            dependencies/linux/tui/ChatTUI.h
            dependencies/linux/tui/ChatList.cpp
            dependencies/linux/tui/ChatList.h
            dependencies/linux/tui/Chat.cpp
            dependencies/linux/tui/Chat.h
            dependencies/linux/tui/TUIHelper.cpp
            dependencies/linux/tui/TUIHelper.h
            dependencies/linux/tui/TextBox.cpp
            dependencies/linux/tui/TextBox.h

            models/ChatModel.cpp
            models/ChatModel.h
            models/MessageModel.cpp
            models/MessageModel.h

            json/json.hpp
            )

    target_link_libraries(TerminalChatLinux
            -lssl -lrt -lcrypto -lpthread -lncurses
            )
endif (APPLE)