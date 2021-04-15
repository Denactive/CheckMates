#include "include/graphics.h"
#include "include/tests.h"
#include <gtest/gtest.h>

extern int m_argc;
extern char **m_argv;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    m_argc = argc;
    m_argv = argv;
    return RUN_ALL_TESTS();
}

