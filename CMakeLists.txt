cmake_minimum_required(VERSION 3.5)

project(OtusHomework_11_DB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS system program_options REQUIRED)
find_package( Threads )

include_directories(${Boost_INCLUDE_DIR})



add_executable(OtusHomework_11_DB
    main.cpp
    sqlite/sqlite3.c
    sqlite/sqlite3.h
    QueryHandler/QueryHandler.hpp

    Net/Connection.hpp
    Net/Server.hpp

    NetReqHandler/Handler.hpp

    Utils/Utils.hpp
    Utils/Protocol.hpp

    Options/Options.hpp
)

target_link_libraries(OtusHomework_11_DB ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries(OtusHomework_11_DB ${Boost_LIBRARIES}    )

#BOOST_ROOT

install(TARGETS OtusHomework_11_DB
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
