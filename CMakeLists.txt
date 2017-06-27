cmake_minimum_required(VERSION 2.7)
project(TerminalChat)

set(CMAKE_CXX_STANDARD 11)
add_executable(TerminalChat main.cpp

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
        dependencies/ConnectExecutor.cpp
        dependencies/ConnectExecutor.h

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

if (UNIX AND NOT APPLE)
    target_link_libraries(TerminalChat
            -lpthread -lcurl -lncursesw -lncurses
            )
endif (UNIX AND NOT APPLE)

if (APPLE)
    target_link_libraries(TerminalChat
            -lpthread -lncurses -lcurl
            )
endif (APPLE)