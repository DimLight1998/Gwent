cmake_minimum_required(VERSION 3.8)
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
        Models/Assets/Effects/FirstLight.cpp
        Models/Assets/Effects/FirstLight.hpp
        Controllers/GameController.cpp
        Controllers/GameController.hpp
        Models/Assets/Effects/BitingFrost.cpp
        Models/Assets/Effects/BitingFrost.hpp
        Models/Containers/CardManager.cpp
        Models/Containers/CardManager.hpp
        Models/Assets/Effects/ImpenetrableFog.cpp
        Models/Assets/Effects/ImpenetrableFog.hpp
        Models/Assets/Units/Foglet.cpp
        Models/Assets/Units/Foglet.hpp
        Models/Assets/Effects/TorrentialRain.cpp
        Models/Assets/Effects/TorrentialRain.hpp
        Models/Assets/Effects/Lacerate.cpp
        Models/Assets/Effects/Lacerate.hpp
        Models/Assets/Effects/CommandersHorn.cpp
        Models/Assets/Effects/CommandersHorn.hpp
        Models/Assets/Effects/BekkersTwistedMirror.cpp
        Models/Assets/Effects/BekkersTwistedMirror.hpp
        Models/Assets/Effects/ThunderboltPotion.cpp
        Models/Assets/Effects/ThunderboltPotion.hpp
        Models/Assets/Units/GeraltIgni.cpp
        Models/Assets/Units/GeraltIgni.hpp
        Models/Assets/Units/WildHuntRider.cpp
        Models/Assets/Units/WildHuntRider.hpp
        Models/Assets/Units/Roach.cpp Models/Assets/Units/Roach.hpp Models/Assets/Units/CroneWeavess.cpp Models/Assets/Units/CroneWeavess.hpp Models/Assets/Units/CroneBrewess.cpp Models/Assets/Units/CroneBrewess.hpp Models/Assets/Units/CroneWhispess.cpp Models/Assets/Units/CroneWhispess.hpp Models/Assets/Units/Arachas.cpp Models/Assets/Units/Arachas.hpp Models/Assets/Units/HarpyEgg.cpp Models/Assets/Units/HarpyEgg.hpp Models/Assets/Units/HarpyHatchling.cpp Models/Assets/Units/HarpyHatchling.hpp Models/Assets/Units/RabidWolf.cpp Models/Assets/Units/RabidWolf.hpp Models/Assets/Units/LesserEarthElemental.cpp Models/Assets/Units/LesserEarthElemental.hpp Models/Assets/Units/ArachasHatchling.cpp Models/Assets/Units/ArachasHatchling.hpp)

add_executable(Gwent ${SOURCE_FILES})

target_link_libraries(Gwent Qt5::Widgets Qt5::Core)