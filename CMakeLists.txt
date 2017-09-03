cmake_minimum_required(VERSION 3.7)
project(Gwent)

set(CMAKE_CXX_STANDARD 11)


# set local Qt location
set(CMAKE_PREFIX_PATH "F:\\Dev\\Qt\\5.9\\mingw53_32")

# set moc uic rcc
set(CMAKE_AUTOMOC on)
set(CMAKE_AUTOUIC on)
set(CMAKE_AUTORCC on)

# set modules
find_package(Qt5Widgets REQUIRED)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")


# qrc file put here
set(SOURCE_FILES Main.cpp Main.cpp)
add_executable(Gwent ${SOURCE_FILES})

target_link_libraries(Gwent Qt5::Widgets Qt5::Core)