#include <image/image.h>

//ray caster

int main(void)
{
  bitmap_t test;
  alloc_bitmap(&test, 1000, 1000);

  for (int r = 0; r < test.height; r++)
  {
    for(int c = 0; c < test.width; c++)
    {
      pixel_t* pixel = pixel_bitmap(&test, r, c);
      pixel->r = (r - 50) * (r - 50) + (c - 50) * (c - 50) <= 50 * 50 ? 255 : r % 256;
      pixel->g = (r - 50) * (r - 50) + (c - 50) * (c - 50) <= 50 * 50 ? 0   : c % 256;
    }
  }

  save_bitmap(&test, "test.ppm");
  free_bitmap(&test);


}
