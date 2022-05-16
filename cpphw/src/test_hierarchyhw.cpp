#include "camera.h"
#include "gtest/gtest.h"

using namespace std;

TEST(Camera, Constructor)
{
    string mount = "ef-s";
    int CfocalLegnth = 14;

    Camera camera(mount, CfocalLegnth);

    ASSERT_EQ(camera.mount(), mount);
    ASSERT_EQ(camera.CfocalLength(), CfocalLegnth);
}

TEST(Camera, FocalLength)
{
    string mount = "ef-s";
    int CfocalLegnth = 14;
    Camera camera(mount, CfocalLegnth);

    ASSERT_EQ(camera.CfocalLength(), CfocalLegnth);

    int newCFocalLength = 50;
    camera.CfocalLength(newCFocalLength);

    ASSERT_EQ(camera.CfocalLength(), newCFocalLength);
}

TEST(Camera, BadFocalLength)
{
    string mount = "ef-s";
    int CfocalLegnth = 14;
    Camera camera(mount, CfocalLegnth);

    ASSERT_EQ(camera.CfocalLength(), CfocalLegnth);

    int badFocalLength = -22;

    EXPECT_THROW({
        camera.CfocalLength(badFocalLength);
    }, std::out_of_range);

    ASSERT_EQ(camera.CfocalLength(), CfocalLegnth);
}