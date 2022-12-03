#include <image/image.hpp>
#include <raytracer/rt.hpp>

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/string_cast.hpp"

//ray tracer

boolean hit_sphere(const rt::Ray& ray, const glm::vec3& center, float radius)
{
  
}

void trace(const rt::Ray r, pixel_t* pixel)
{
  glm::vec3 color = glm::abs(glm::normalize(r.dir)) * 255.0f;
  pixel->r = color.x; pixel->g = color.y; pixel->b = color.z;
}

int main(void)
{
  rt::Camera cam(0, 4, 0, 90, 90);
  rt::Target tar(1000, 1000);

  float height = 1.0f / glm::tan( glm::half_pi<float>() - (cam.fov_h * (glm::pi<float>() / 180.0f) / 2.0f) );
  float width  = 1.0f / glm::tan( glm::half_pi<float>() - (cam.fov_w * (glm::pi<float>() / 180.0f) / 2.0f) );

  glm::vec3 lowwer_left = rt::Camera::front - ( width * rt::Camera::right ) - ( height * rt::Camera::up );
  glm::vec3 horizontal  = rt::Camera::right * (2 * width);
  glm::vec3 vertical    = rt::Camera::up * (2 * height);

  bitmap_t render;
  alloc_bitmap(&render, 1000, 1000);

  for (int r = 0; r < render.height; r++)
  {
    for(int c = 0; c < render.width; c++)
    {
      pixel_t* pixel = pixel_bitmap(&render, r, c);

      float u = (float)(c) / (float)(render.width - 1);
      float v = (float)(r) / (float)(render.height - 1);

      rt::Ray ray(cam.pos, lowwer_left + u*horizontal + v*vertical);
      trace(ray, pixel);
    }
  }

  save_bitmap(&render, "render.ppm");
  free_bitmap(&render);
}
