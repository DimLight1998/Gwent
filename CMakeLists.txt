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
set(
        SOURCE_FILES
        Main.cpp
        Main.cpp
        Models/Meta/CardMeta.cpp
        Models/Meta/CardMeta.hpp
        Models/Meta/UnitMeta.cpp
        Models/Meta/UnitMeta.hpp
        Models/Meta/EffectsMeta.cpp
        Models/Meta/EffectsMeta.hpp
        Models/Card/Card.cpp
        Models/Card/Card.hpp
        Models/Card/Unit.cpp
        Models/Card/Unit.hpp
        Models/Card/Effect.cpp
        Models/Card/Effect.hpp
        Models/Containers/CardGroup.cpp
        Models/Containers/CardGroup.hpp
        Models/Containers/BattleLine.cpp
        Models/Containers/BattleLine.hpp
        Models/Containers/CardContainer.cpp
        Models/Containers/CardContainer.hpp
        Models/Containers/BattleSide.cpp
        Models/Containers/BattleSide.hpp
        Models/Containers/BattleField.cpp
        Models/Containers/BattleField.hpp
        Models/Assets/FirstLight.cpp
        Models/Assets/FirstLight.hpp
        Controllers/GameController.cpp
        Controllers/GameController.hpp
        Models/Assets/BitingFrost.cpp
        Models/Assets/BitingFrost.hpp
        Models/Containers/CardManager.cpp
        Models/Containers/CardManager.hpp
)

add_executable(Gwent ${SOURCE_FILES})

target_link_libraries(Gwent Qt5::Widgets Qt5::Core)