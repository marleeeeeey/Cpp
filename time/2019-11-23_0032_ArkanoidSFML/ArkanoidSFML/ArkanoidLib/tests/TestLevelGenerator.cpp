#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "LevelGenerator.h"
#include "BonusType.h"

class ObjectFactoryMock : public IObjectFactory
{
public:
    MOCK_METHOD1(createObject, std::shared_ptr<IObject> (ObjectType));
};

TEST(LevelGenerator, CheckAllLevels_ObsoleteTest)
{
    auto objectFactoryMock = std::make_shared<ObjectFactoryMock>();
    LevelGenerator levelGenerator(objectFactoryMock, {0, 0});
    auto levels = levelGenerator.getSymbolLevels();
}
