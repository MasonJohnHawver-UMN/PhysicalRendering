#include <image/image.h>

//...

/************************ private functions ****************************/

static void
die(const char* message)
{
  fprintf(stderr, "ppm: %s\n", message);
  exit(1);
}

static void
ppm_header(FILE *fp, int *width, int *height)
{
  char ch; int  maxval;

  if (fscanf(fp, "P%c\n", &ch) != 1 || ch != '6') { die("file is not in ppm raw format; cannot read"); }

  /* skip comments */
  ch = getc(fp);
  while (ch == '#')
    {
      do {
	       ch = getc(fp);
      } while (ch != '\n');
      ch = getc(fp);
    }

  if (!isdigit(ch)) { die("cannot read header information from ppm file"); }
  ungetc(ch, fp); /* put that digit back */

  /* read the width, height, and maximum value for a pixel */
  if (fscanf(fp, "%d%d%d\n", width, height, &maxval) != 3) { die("file is not in ppm raw format; cannot read"); };
  if (maxval != 255) { die("image is not true-color (24 bit); read failed"); }
}

/************************ public functions ****************************/

void alloc_bitmap(bitmap_t* bitmap, size_t width, size_t height)
{
  bitmap->width  = width;
  bitmap->height = height;
  bitmap->pixels = (pixel_t*) malloc(width * height * sizeof(pixel_t));
  if (!bitmap->pixels) { die("cannot allocate memory for new image"); }
}

void free_bitmap(bitmap_t* bitmap)
{
  if (bitmap->pixels) { free(bitmap->pixels); }
  bitmap->width = 0;
  bitmap->height = 0;
}

pixel_t* pixel_bitmap(bitmap_t* bitmap, size_t row, size_t col)
{
  return bitmap->pixels + row * bitmap->width + col;
}

void save_bitmap(bitmap_t* bitmap, const char* path)
{
  int num;
  int size = bitmap->width * bitmap->height;

  FILE *fp = fopen(path, "w");
  if (!fp) { die("cannot open file for writing"); }

  fprintf(fp, "P6\n%d %d\n%d\n", (int)bitmap->width, (int)bitmap->height, 255);

  num = fwrite((void *) bitmap->pixels, sizeof(pixel_t), (size_t)size, fp);

  if (num != size) { die("cannot write image data to file"); }
  fclose(fp);
}

void load_bitmap(bitmap_t* bitmap, const char* path)
{
  int width, height, num, size;
  FILE *fp = fopen(path, "r");
  if (!fp) { die("cannot open file"); }

  ppm_header(fp, &width, &height);

  free_bitmap(bitmap);
  alloc_bitmap(bitmap, width, height);

  size = width * height;
  num  = fread((void *) bitmap->pixels, sizeof(pixel_t), (size_t)size, fp);

  if (num != size) { die("cannot read image data from file"); }
  fclose(fp);
}
