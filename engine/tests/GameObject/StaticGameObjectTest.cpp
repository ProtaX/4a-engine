#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <StaticGameObject.hpp>

using namespace fae;

TEST_CASE("SetSize", "[GameObject]") {
  //Arrange
  StaticGameObject obj;
  float x = 100, y = 200;
  //Act
  obj.SetSize({x, y});
  vertex_t* vertex_data = obj.GetVertexDataPtr();
  //Assert
  REQUIRE(vertex_data[0].coords.x == x);
  REQUIRE(vertex_data[0].coords.y == y);
}