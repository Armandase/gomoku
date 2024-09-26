#include <iostream>
#include "gtest/gtest.h"

int maint(int ac, char **av)
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TEST();
}