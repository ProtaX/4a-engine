#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <VertexLayout.hpp>
#include <VertexBuffer.hpp>
#include <Camera.hpp>
#include <stdio.h>

using namespace fae;

TEST_CASE("Eq class", "[VertexLayout]") {
    VertexLayout vl(0);
    //Внутри эти push образуют класс эквивалентности {3, 3, 2}
    vl.Push<float>(3);
    vl.Push<float>(3);
    vl.Push<float>(2);

    //Создадим такую же структуру вручную
    std::vector<struct VertexBufferAttributes> test_struct = {{GL_FLOAT, 3, GL_FALSE}, 
                                                              {GL_FLOAT, 3, GL_FALSE}, 
                                                              {GL_FLOAT, 2, GL_FALSE}};
    auto created_struct = vl.GetAttributes();

    //Сравним результаты
    for (int i = 0; i < 3; i++) {
        REQUIRE(memcmp(&test_struct[i], &created_struct[i], sizeof(struct VertexBufferAttributes)) == 0);
    }
}

TEST_CASE("Border values", "[VertexLayout]") {
    VertexLayout vl(0);
    vl.Push<float>(-1);

    //-1 - некорректное граничное значение
    REQUIRE(vl.GetStride() < 0);
}

TEST_CASE("Cause and effect analysis", "[VertexLayout]") {
    VertexLayout vl(0);
    vl.Push<float>(3);
    vl.Push<float>(3);
    vl.Push<float>(2);

    //Добавляется 8 элементов типа float, следовательно, и размер (stride)
    //будет равен 8 * sizeof(float)
    REQUIRE(vl.GetStride() == 8 * sizeof(float));
}

TEST_CASE("Error prediction", "[Camera]") {
    //Предскажем ошибку: пользователь перепутал тип параметров
    int windowW = 1024, windowH = 720;
    Camera orthCam(windowW, windowH);

    //Сравним его с приером, в котором параметры парвильные
    Camera orthCam_right(1024., 720.);
    REQUIRE(orthCam.GetProj() == orthCam_right.GetProj());
}