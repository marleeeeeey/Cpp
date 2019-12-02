#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "LevelGenerator.h"

class ObjectFactoryMock : public IObjectFactory
{
public:
    MOCK_METHOD1(createObject, std::shared_ptr<IObject> (ObjectType));
};

TEST(LevelGenerator, LevelLinesHaveSameSize)
{
    auto objectFactoryMock = std::make_shared<ObjectFactoryMock>();
    LevelGenerator levelGenerator(objectFactoryMock, {0,0});
    auto levels = levelGenerator.getSymbolLevels();

    for(const auto& level : levels)
    {
        EXPECT_FALSE(level.empty());

        auto lineSize = level.front().size();
        for(const auto& line : level)
        {
            EXPECT_TRUE(lineSize == line.size());
        }
    }
}
