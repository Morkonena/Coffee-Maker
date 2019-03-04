#include "Png.h"

#include <Asset.h>
#include <png.h>

using namespace Core;

Texture* Png::Import(String filename)
{
  // Load the asset
  Asset asset(filename);

  png_image image = { 0 };
  image.version = PNG_IMAGE_VERSION;

  // Begin creating a image from the asset
  if (png_image_begin_read_from_memory(&image, asset.GetData(), asset.GetLength()))
  {
    // Support transparency
    image.format = PNG_FORMAT_RGBA;

    // Create a managed pixel array to store the pixels
		Managed<uint8_t[]> pixels(new uint8_t[PNG_IMAGE_SIZE(image)]);

    // Finish creating the image
    if (png_image_finish_read(&image, 0, pixels.get(), 0, 0) != 0)
    {
      // Convert the image into a texture
      Texture* texture = new Texture();

      // Make sure the texture is valid
      if (!texture->IsValid())
      {
        return nullptr;
      }

      // Configure the texture
      texture->SetPixels(TEXTURE_FORMAT_RGBA8, image.width, image.height, pixels.release());
      texture->SetSmoothing(true);

      return texture;
    }
  }

  return nullptr;
}
