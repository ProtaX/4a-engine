#include "GameObject.hpp"

namespace fae {

void GameObject::SetTextureCoords(point2_t rt, point2_t rb, point2_t lb, point2_t lt) {
    m_verticies[0].tex_coords = rt;
    m_verticies[1].tex_coords = rb;
    m_verticies[2].tex_coords = lb;
    m_verticies[3].tex_coords = lt;
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
}

void GameObject::SetCoords(point2_t lb, point2_t lt, point2_t rt, point2_t rb) {
    m_verticies[0].coords = {rt.x, rt.y, 0.};
    m_verticies[1].coords = {rb.x, rb.y, 0.};
    m_verticies[2].coords = {lb.x, lb.y, 0.};
    m_verticies[3].coords = {lt.x, lt.y, 0.};
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
}

void GameObject::SetCoords(point3_t lb, point3_t lt, point3_t rt, point3_t rb) {
    m_verticies[0].coords = rt;
    m_verticies[1].coords = rb;
    m_verticies[2].coords = lb;
    m_verticies[3].coords = lt;
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
}

void GameObject::SetCoords(point2_t lb, point2_t rt) {
    m_verticies[0].coords = {rt.x, rt.y, 0.};
    m_verticies[1].coords = {rt.x, lb.y, 0.};
    m_verticies[2].coords = {lb.x, lb.y, 0.};
    m_verticies[3].coords = {lb.x, rt.y, 0.};
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
}

void GameObject::SetSize(point2_t rt) {
    m_verticies[0].coords = {rt.x, rt.y, 0.};
    m_verticies[1].coords = {rt.x, 0.,   0.};
    m_verticies[2].coords = {0.,   0.,   0.};
    m_verticies[3].coords = {0.,   rt.y, 0.};
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
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
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
}

void GameObject::SetSingleTexture(unsigned char* pixel_data, int h, int w, int target) {
    float borderColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
    m_texture.target = target;
    GLCall(glGenTextures(1, &(m_texture.id)));
    GLCall(glActiveTexture(m_texture.target));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_texture.id));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, h, w, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data));
    GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    SOIL_free_image_data(pixel_data);
}

void GameObject::UseShaderProgram() {
    GLCall(glUseProgram(m_shader_program));
    //TODO: эти вызовы должны быть частью класса шейдера
    GLint texture_loc = GLCall(glGetUniformLocation(m_shader_program, "ourTexture"));
    GLint transform_loc = GLCall(glGetUniformLocation(m_shader_program, "is_transformable"));
    GLCall(glUniform1i(transform_loc, 0));
    GLCall(glUniform1i(texture_loc, m_texture.target - GL_TEXTURE0 ));
}

GameObject::GameObject() {
    //TEST
    /*
    m_verticies[0].coords = {200., 100., 0.};
    m_verticies[0].color = {0., 0., 0.};
    m_verticies[0].tex_coords = {1., 1.};

    m_verticies[1].coords = {200., 100., 0.};
    m_verticies[1].color = {0., 0., 0.};
    m_verticies[1].tex_coords = {1., 0.};

    m_verticies[2].coords = {200., 100., 0.};
    m_verticies[2].color = {0., 0., 0.};
    m_verticies[2].tex_coords = {0., 0.};

    m_verticies[3].coords = {200., 100., 0.};
    m_verticies[3].color = {0., 0., 0.};
    m_verticies[3].tex_coords = {0., 1.};
    */
    p_vertex_buffer = std::make_unique<VertexBuffer>(m_verticies, sizeof(m_verticies));
    p_vertex_layout = std::make_unique<VertexLayout>();
    p_index_buffer = std::make_unique<IndexBuffer>(m_indicies, sizeof(m_indicies));
    p_vertex_array = std::make_unique<VertexArray>();
    
    SetTextureCoords({1., 1.},
                     {1., 0.},
                     {0., 0.},
                     {0., 1.});
                     
    m_model_mtx = glm::mat4(1.0f);

    p_vertex_layout->Push<float>(3);
    p_vertex_layout->Push<float>(3);
    p_vertex_layout->Push<float>(2);

    p_vertex_array->Bind();
    p_index_buffer->Bind();
    p_vertex_array->AddBuffer(p_vertex_buffer.get(), p_vertex_layout.get());
    p_vertex_array->Unbind();

    m_texture.target = GL_TEXTURE7;
}

void GameObject::Draw() {
    UseShaderProgram();
    BindVertexArray();
    BindVertexBuffer();
    BindIndexBuffer();
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    UnbindVertexBuffer();
    UnbindIndexBuffer();
    UnbindVertexArray();
}

}