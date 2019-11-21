#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <Camera.hpp>

using namespace fae;

TEST_CASE("Wrong params type", "[Camera]") {
    //Arrange
    int windowW = 1024, windowH = 720;
    Camera orthCam(windowW, windowH);
    //Act
    Camera orthCam_right(1024., 720.);
    //Assert
    REQUIRE(orthCam.GetProj() == orthCam_right.GetProj());
}