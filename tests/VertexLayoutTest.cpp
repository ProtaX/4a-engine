#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <VertexLayout.hpp>
#include <VertexBuffer.hpp>
#include <stdio.h>

using namespace fae;

TEST_CASE("Eq class", "[VertexLayout]") {
    //Arrange
    VertexLayout vl(0);
    std::vector<struct VertexBufferAttributes> test_struct = {{GL_FLOAT, 3, GL_FALSE}, 
                                                              {GL_FLOAT, 3, GL_FALSE}, 
                                                              {GL_FLOAT, 2, GL_FALSE}};
    auto created_struct = vl.GetAttributes();
    //Action
    vl.Push<float>(3);
    vl.Push<float>(3);
    vl.Push<float>(2);
    //Assert
    for (int i = 0; i < 3; i++) {
        REQUIRE(memcmp(&test_struct[i], &created_struct[i], sizeof(struct VertexBufferAttributes)) == 0);
    }
}

TEST_CASE("Border values", "[VertexLayout]") {
    //Arrange
    VertexLayout vl(0);
    //Action
    vl.Push<float>(-1);
    //Assert
    REQUIRE(vl.GetStride() < 0);
}

TEST_CASE("Cause and effect analysis", "[VertexLayout]") {
    //Arrange
    VertexLayout vl(0);
    //Action
    vl.Push<float>(3);
    vl.Push<float>(3);
    vl.Push<float>(2);
    //Assert
    REQUIRE(vl.GetStride() == 8 * sizeof(float));
}

