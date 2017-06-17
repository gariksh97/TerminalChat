cmake_minimum_required(VERSION 2.7)
project(TerminalChat)

set(CMAKE_CXX_STANDARD 11)

if (UNIX AND NOT APPLE)
    add_executable(TerminalChatLinux main.cpp

            network/Errors.h
            network/Networking.cpp
            network/Networking.h
            network/Listener.h
            network/Listener.cpp
            network/ThreadExecutor.cpp
            network/ThreadExecutor.h

            dependencies/Dependencies.cpp
            dependencies/Dependencies.h
            dependencies/DependenciesTUI.cpp
            dependencies/DependenciesTUI.h

            tui/ChatTUI.cpp
            tui/ChatTUI.h
            tui/ChatList.cpp
            tui/ChatList.h
            tui/Chat.cpp
            tui/Chat.h
            tui/TUIHelper.cpp
            tui/TUIHelper.h
            tui/TextBox.cpp
            tui/TextBox.h

            models/ChatModel.cpp
            models/ChatModel.h
            models/MessageModel.cpp
            models/MessageModel.h

            json/json.hpp
            dependencies/ConnectExecutor.cpp dependencies/ConnectExecutor.h)

    target_link_libraries(TerminalChatLinux
            -lpthread -lcurl -lncursesw -lncurses
            )
endif (UNIX AND NOT APPLE)

if (WIN32)
    add_executable(TerminalChatWindows main.cpp)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif (WIN32)

if (APPLE)
    add_executable(TerminalChatApple main.cpp

            network/Networking.cpp
            network/Networking.h
            network/Listener.h
            network/Listener.cpp
            network/ThreadExecutor.cpp
            network/ThreadExecutor.h

            dependencies/Dependencies.cpp
            dependencies/Dependencies.h
            dependencies/DependenciesTUI.cpp
            dependencies/DependenciesTUI.h

            tui/ChatTUI.cpp
            tui/ChatTUI.h
            tui/ChatList.cpp
            tui/ChatList.h
            tui/Chat.cpp
            tui/Chat.h
            tui/TUIHelper.cpp
            tui/TUIHelper.h
            tui/TextBox.cpp
            tui/TextBox.h

            models/ChatModel.cpp
            models/ChatModel.h
            models/MessageModel.cpp
            models/MessageModel.h

            json/json.hpp
            )

    target_link_libraries(TerminalChatApple
            -lpthread -lncurses -lcurl
            )
endif (APPLE)