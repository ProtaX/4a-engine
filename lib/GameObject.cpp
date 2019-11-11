#include "GameObject.hpp"

namespace fae {

void GameObject::SetTextureCoords(point2_t lb, point2_t lt, point2_t rt, point2_t rb) {
    m_verticies[0].tex_coords = rt;
    m_verticies[1].tex_coords = rb;
    m_verticies[2].tex_coords = lb;
    m_verticies[3].tex_coords = lt;
}

void GameObject::SetCoords(point2_t lb, point2_t lt, point2_t rt, point2_t rb) {
    m_verticies[0].coords = {rt.x, rt.y, 0.};
    m_verticies[1].coords = {rb.x, rb.y, 0.};
    m_verticies[2].coords = {lb.x, lb.y, 0.};
    m_verticies[3].coords = {lt.x, lt.y, 0.};
}

void GameObject::SetCoords(point3_t lb, point3_t lt, point3_t rt, point3_t rb) {
    m_verticies[0].coords = rt;
    m_verticies[1].coords = rb;
    m_verticies[2].coords = lb;
    m_verticies[3].coords = lt;
}

void GameObject::SetCoords(point2_t lb, point2_t rt) {
    m_verticies[0].coords = {rt.x, rt.y, 0.};
    m_verticies[1].coords = {rt.x, lb.y, 0.};
    m_verticies[2].coords = {lb.x, lb.y, 0.};
    m_verticies[3].coords = {lb.x, rt.y, 0.};
}

void GameObject::SetSize(point2_t rt) {
    m_verticies[0].coords = {rt.x, rt.y, 0.};
    m_verticies[1].coords = {rt.x, 0.,   0.};
    m_verticies[2].coords = {0.,   0.,   0.};
    m_verticies[3].coords = {0.,   rt.y, 0.};
}

void GameObject::SetCoords(point3_t lb, point3_t rt) {
    if (lb.z != rt.z) {
        std::cout << "GameObject::SetCoords::Error: Bad z coordinate" << std::endl;
        return;
    }
    m_verticies[0].coords = {rt.x, rt.y, lb.z};
    m_verticies[1].coords = {rt.x, lb.y, lb.z};
    m_verticies[2].coords = {lb.x, lb.y, lb.z};
    m_verticies[3].coords = {lb.x, rt.y, lb.z};
}

void GameObject::SetSingleTexture(unsigned char* pixel_data, int h, int w, int target = GL_TEXTURE) {
    float borderColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
    m_texture.target = target;
    glGenTextures(1, &m_texture.id);
    glActiveTexture(m_texture.target);
    glBindTexture(GL_TEXTURE_2D, m_texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, h, w, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GameObject::UseShaderProgram() {
    glUseProgram(m_shader_program);
    //TODO: эти вызовы должны быть частью класса шейдера
    glUniform1i(glGetUniformLocation(m_shader_program, "is_transformable"), 0);
    glUniform1i(glGetUniformLocation(m_shader_program, "ourTexture"), m_texture.target);
}

GameObject::GameObject() {
    m_model_mtx = glm::mat4(1.0f);
    m_verticies[0] = {};
    SetTextureCoords({1., 1.},
                     {1., 0.},
                     {0., 0.},
                     {0., 1.});

    p_vertex_buffer = std::make_unique<VertexBuffer>(m_verticies, sizeof(m_verticies));
    p_vertex_layout = std::make_unique<VertexLayout>();
    p_index_buffer = std::make_unique<IndexBuffer>(m_indicies, sizeof(m_indicies));
    p_vertex_array = std::make_unique<VertexArray>();

    p_vertex_layout->Push<float>(3);
    p_vertex_layout->Push<float>(3);
    p_vertex_layout->Push<float>(2);

    p_vertex_array->Bind();
    p_index_buffer->Bind();
    p_vertex_array->AddBuffer(p_vertex_buffer.get(), p_vertex_layout.get());
    p_vertex_array->Unbind();
}

}