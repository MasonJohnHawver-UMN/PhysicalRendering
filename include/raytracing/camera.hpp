#include <glm/glm.hpp>

#pragma once

namespace rt
{

  struct Ray
  {
    glm::vec3 pos; //x, ,y z
    glm::vec3 dir;
  };

  struct Camera
  {

    Camera(float x, float y, float z, float p, float ya, float r, float fw, float fh) : pos(x, y, z), pitch(p), yaw(ya), roll(r), fov_w(fw), fov_h(fh) {}




    glm::vec3 pos;
    float pitch, yaw, roll; //x y z
    float fov_w, fov_h;

    static glm::vec3 right, up, front; // x y z
  };


}
