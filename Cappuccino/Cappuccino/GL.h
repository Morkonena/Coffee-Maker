//
// Created by Mörkönenä on 14.7.2018
//

#ifndef CORE_GL_H
#define CORE_GL_H

#ifdef ANDROID
#include <GLES3/gl32.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#endif // !CORE_GL_H