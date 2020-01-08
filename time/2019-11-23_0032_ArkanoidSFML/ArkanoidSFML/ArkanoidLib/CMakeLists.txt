cmake_minimum_required(VERSION 3.15)

# SFML
IF (WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

# ArkanoidLib
add_library(arkanoid_lib
include/ArkanoidStart.h
src/World.cpp
src/World.h
src/Wall.cpp
src/Wall.h
src/State.cpp
src/State.h
src/Plate.cpp
src/Plate.h
src/PauseMenu.cpp
src/PauseMenu.h
src/ObjectFactory.cpp
src/ObjectFactory.h
src/MathVector.cpp
src/MathVector.h
src/LevelGenerator.cpp
src/LevelGenerator.h
src/IWorld.h
src/IStaticObject.h
src/IObjectFactory.h
src/IObject.h
src/ILevelGenerator.h
src/IHaveParent.h
src/IDynamicObject.h
src/IDestructible.h
src/IBonusOwner.h
src/HelperFunctions.cpp
src/HelperFunctions.h
src/DefaultObject.cpp
src/DefaultObject.h
src/CollisionBucket.cpp
src/CollisionBucket.h
src/Collision.cpp
src/Collision.h
src/Brick.cpp
src/Brick.h
src/BonusType.cpp
src/BonusType.h
src/Bonus.cpp
src/Bonus.h
src/Ball.cpp
src/Ball.h
src/ArkanoidStart.cpp
)

target_compile_features(arkanoid_lib PUBLIC cxx_std_17)
target_include_directories(arkanoid_lib PUBLIC "include")
target_include_directories(arkanoid_lib PRIVATE "${GTEST_INCLUDE_DIR}")
target_link_libraries(arkanoid_lib sfml-graphics sfml-system sfml-window)

# Tests
add_executable(arkanoid_tests
tests/TestMathVector.cpp
tests/TestMain.cpp
tests/TestLevelGenerator.cpp
)

target_link_libraries(arkanoid_tests GTest::GTest GTest::Main GMock::GMock GMock::Main arkanoid_lib)
target_include_directories(arkanoid_tests PRIVATE src include)

add_test(NAME arkanoid_tests COMMAND arkanoid_tests)