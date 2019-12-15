#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <Camera.hpp>

using namespace fae;

TEST_CASE("Wrong params type", "[Camera]") {
    //Arrange
    int windowW = 1024, windowH = 720;
    Camera orthCam(windowH, windowW);
    //Act
    Camera orthCam_right(720., 1024.);
    //Assert
    REQUIRE(orthCam.GetProj() == orthCam_right.GetProj());
}