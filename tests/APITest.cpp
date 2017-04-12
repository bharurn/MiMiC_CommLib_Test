//
// Created by vbolnykh on 4/12/17.
//

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../src/transport/Transport.h"

//class MockTransport : public Transport {
//public:
//    MockTransport(Serializer *serializer) : Transport(serializer) {}
//
////    MOCK_METHOD1(initServ, void(std::string paths));
//
//};

TEST(APIInit, ProperCalls) {

}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}