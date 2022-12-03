#include <glm/glm.hpp>

#pragma once

namespace rt
{

  struct Ray
  {
    Ray(const glm::vec3& p, const glm::vec3& d) : pos(p), dir(d) {}

    glm::vec3 pos; //x y z
    glm::vec3 dir;
  };

  struct Camera
  {

    Camera(float x, float y, float z, float fw, float fh) : pos(x, y, z), fov_w(fw), fov_h(fh) {}

    glm::vec3 pos;
    float fov_w, fov_h;

    static glm::vec3 right, up, front; // x y z
  };

  struct Target
  {

    Target(int width, int height) : width(width), height(height) {}

    size_t width, height;
  };

  glm::vec3 Camera::right = glm::vec3(1, 0, 0);
  glm::vec3 Camera::up    = glm::vec3(0, 1, 0);
  glm::vec3 Camera::front = glm::vec3(0, 0, 1);


}
