#include "Asset.h"
#include "Console.h"
#include "Log.h"

using namespace Core;

#ifdef ANDROID

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

AssetManager Assets::Manager;

void Assets::Initialize(JavaEnvironment environment, JavaObject asset_manager)
{
  Manager = AAssetManager_fromJava(environment, asset_manager);
  PRINT("Assets: OK");
}

Asset::Asset(String filename)
{
  // Open the asset
  AAsset *handle = AAssetManager_open(Assets::manager, filename.c_str(), AASSET_MODE_BUFFER);

  // Make sure the asset is open
  if (handle == 0)
  {
    PERROR("ERROR_LOAD_ASSET: %s", filename.c_str());
    throw;
  }

  // Allocate a buffer where the asset can be loaded
  length = (int)AAsset_getLength(handle);
	memory.resize(length + 1);
  memory[length] = 0;

  // Copy the asset into the buffer and then close the asset handle
  AAsset_read(handle, memory.data(), (size_t)length);
  AAsset_close(handle);
}

#else
#include <fstream>

String Assets::Folder;

#ifdef LINUX
#include <unistd.h>
#include <cstring>

void Assets::Initialize()
{
  char filename[256];
  memset(filename, 0, 256);

  if (!getcwd(filename, 256))
  {
    PERROR("ERROR_CURRENT_WORKING_DIRECTORY: (Unable to get current working directory)");
    throw;
  }

  Folder = String(filename) + "/";

  SUCCESS("Assets: OK");
}

#else
#include <Windows.h>

void Assets::Initialize()
{
  // Get this program's filename
  CHAR filename[200];
  GetModuleFileName(0, filename, 200);

  // Find the last separator and cut of the filename
  Folder = String(filename);
  Folder = Folder.substr(0, Folder.find_last_of("\\")) + "\\";

  SUCCESS("Assets: OK");
}

#endif // LINUX

String Assets::GetFolder()
{
  return Folder;
}

Asset::Asset(String filename)
{
  ASSERT(!filename.empty());

  // Open the asset and start from the end since the asset size is needed
  std::ifstream stream(Assets::GetFolder() + filename, std::ios::in | std::ios::binary | std::ios::ate);

  if (!stream.is_open())
  {
    PERROR("ERROR_OPEN_ASSET: ", filename.c_str());
    throw;
  }

	// Save asset's size
  length = (int)stream.tellg();

  // Seek to the start
  stream.seekg(0, std::ios::beg);

  // Allocate a buffer for storing the asset
  memory.resize(length + 1);
  memory[length] = 0;

  // Copy the asset to the buffer
  stream.read(memory.data(), length);

  // Close the asset
  stream.close();
}

#endif // LINUX

String Asset::GetText() const
{
  return String(memory.data());
}

void* Asset::GetData() const
{
  return memory.data();
}

int Asset::GetLength() const
{
  return length;
}
