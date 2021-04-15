#include "gtest/gtest.h"
#include "Authorizer.h"



TEST(Authorizer, wrong_input) {
    Authorizer A;
    User B;
    ASSERT_EQ(B, A.authorize());

}
