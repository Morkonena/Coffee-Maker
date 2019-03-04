//
// Created by Mörkönenä on 20.1.2019
//

#ifndef CORE_GRAPHICS_H
#define CORE_GRAPHICS_H

typedef struct __GLXFBConfigRec* GLXFBConfig;
typedef struct _XDisplay* XDisplay;

namespace Core
{
  class Graphics
  {
  private:
    friend class Window;
    friend class RenderingContext;
    
    static XDisplay Display;
    static GLXFBConfig* Config;
    static void* Visual;

  public:
    static void Initialize();
  };
}

#endif // !CORE_GRAPHICS_H
