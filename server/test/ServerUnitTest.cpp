#include <string>
#include <iostream>
#include <unistd.h>

#include "gtest/gtest.h"
#include "test_client.h"

#define timeout -1
const char binary_file_name [] = "server";
static int PROCESS_PID;

bool wait_for_response() {
    // TODO: timer
    while (!NEW_DATA.state());
    NEW_DATA.set(false);
    return true;
}

std::string moves[] = {
        "{\n\t\"code\": \"move\",\n\t\"game_token\": \"%s\",\n\t\"uid\": \"%zu\",\n\t\"prev\": \"12\",\n\t\"cur\": \"28\"\n}", // m
        "{\n\t\"code\": \"move\",\n\t\"game_token\": \"%s\",\n\t\"uid\": \"%zu\",\n\t\"prev\": \"52\",\n\t\"cur\": \"36\"\n}", // a
        "{\n\t\"code\": \"move\",\n\t\"game_token\": \"%s\",\n\t\"uid\": \"%zu\",\n\t\"prev\": \"5\",\n\t\"cur\": \"26\"\n}", // b
        "{\n\t\"code\": \"move\",\n\t\"game_token\": \"%s\",\n\t\"uid\": \"%zu\",\n\t\"prev\": \"57\",\n\t\"cur\": \"42\"\n}", // c
        "{\n\t\"code\": \"move\",\n\t\"game_token\": \"%s\",\n\t\"uid\": \"%zu\",\n\t\"prev\": \"3\",\n\t\"cur\": \"39\"\n}", // d
        "{\n\t\"code\": \"move\",\n\t\"game_token\": \"%s\",\n\t\"uid\": \"%zu\",\n\t\"prev\": \"62\",\n\t\"cur\": \"45\"\n}", // e
        "{\n\t\"code\": \"move\",\n\t\"game_token\": \"%s\",\n\t\"uid\": \"%zu\",\n\t\"prev\": \"39\",\n\t\"cur\": \"53\"\n}", // f
};

TEST(ServerUnitTest, Main) {
    std::cout << "Logic test" << std::endl;
    pid_t pid_fork = fork();

    // Дочерний процесс
    if (!pid_fork) {
        PROCESS_PID = getpid();
        std::cout<<"server process forked" << PROCESS_PID << "\n";
        execl(binary_file_name, binary_file_name, ".", "test", NULL);
        exit(0);
    }

    // Родительский процесс

    auto const host = "127.0.0.1";
    msg_Singleton::instance();
    net::io_context ioc;

    client c1(ioc);
    client c2(ioc);

    std::string buffer;
    std::string http_buffer;

    c1.http_connection.run(host, "8001");
    c2.http_connection.run(host, "8001");
    c1.ws_connection.run(host, "1234");
    c2.ws_connection.run(host, "1234");

    // create a thread to maintain communication
    std::thread t(
            [&ioc]() { ioc.run(); }
    );


    try {
        http_buffer = "/register/Sveta";
        c1.http_connection.write(http_buffer);
        if (!wait_for_response())
            throw timeout;
        EXPECT_STRNE((*c1.token).c_str(), "null_token");
        http_buffer = "/start_game/" + *(c1.token);
        c1.http_connection.write(http_buffer);
        // hold http session
        sleep(1);

        http_buffer = "/register/Denis";
        c2.http_connection.write(http_buffer);
        if (!wait_for_response())
            throw timeout;
        EXPECT_STRNE((*c2.token).c_str(), "null_token");
        http_buffer = "/start_game/" + *(c2.token);
        c1.http_connection.write(http_buffer);
        if (!wait_for_response())
            throw timeout;
        // double answer. need some time probably
        sleep(1);
        EXPECT_STRNE((*c1.game).c_str(), "null_token");
        EXPECT_STRNE((*c2.game).c_str(), "null_token");
        NEW_DATA.set(false);
        sleep(1);


        buffer =
                "{\n\t\"code\": \"start\",\n\t\"game_token\": \"" + *c1.game + "\",\n\t\"uid\": \"" + *c1.uid + "\"\n}";
        c1.ws_connection.write(buffer);
        if (!wait_for_response())
            throw timeout;
        EXPECT_STREQ((msg_Singleton::instance().get()).c_str(), "wait for opponent connection");
        sleep(1);
        buffer =
                "{\n\t\"code\": \"start\",\n\t\"game_token\": \"" + *c2.game + "\",\n\t\"uid\": \"" + *c2.uid + "\"\n}";
        c2.ws_connection.write(buffer);
        if (!wait_for_response())
            throw timeout;
        sleep(1);
        EXPECT_STRNE((*c1.side).c_str(), "undefined");
        EXPECT_STRNE((*c2.side).c_str(), "undefined");
        NEW_DATA.set(false);

        client *first = &c1;
        client *second = &c2;
        if (*c2.side == "white")
            std::swap(first, second);
        int i = 0;
    }
    catch (int e) {
        std::cout << "timeout\n";
    }

    std::cout<<"server process (PID: " << PROCESS_PID << ") will be killed now\n";
    kill(PROCESS_PID, SIGUSR1);
    // Родительский процесс
    std::cout<<"server process has been killed\n";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}