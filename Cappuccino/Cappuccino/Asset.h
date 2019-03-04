//
// Created by Mörkönenä on 10.7.2018
//

#ifndef CORE_ASSET_H
#define CORE_ASSET_H

#include "Standard.h"

#ifdef ANDROID
#include <jni.h>
typedef struct AAssetManager* AssetManager;
typedef JNIEnv* JavaEnvironment;
typedef jobject JavaObject;
#endif

namespace Core
{
  class Asset
  {
  private:
    mutable List<char> memory;
    int length;

  public:
    Asset(String filename);

    String GetText() const;

    void* GetData() const;
    int GetLength() const;
  };

#ifndef ANDROID

  class Assets
  {
  private:
    static String Folder;

  public:
    static void Initialize();
    static String GetFolder();
  };

#else // WINDOWS & LINUX

  class Assets
  {
  private:
		friend class Asset;
    static AssetManager Manager;

  public:
    static void Initialize(JavaEnvironment environment, JavaObject asset_manager);
  };

#endif // ANDROID
}

#endif // !CORE_ASSET_H
