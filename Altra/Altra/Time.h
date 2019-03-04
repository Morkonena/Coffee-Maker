//
// Created by Mörkönenä on 16.7.2018
//

#ifndef CORE_TIME_H
#define CORE_TIME_H

#include <chrono>

#define NOW std::chrono::high_resolution_clock::now()
#define SINCE(X) (NOW - X).count()

#define MILLISECONDS(X) (X / 1000000.0f)

#endif // !CORE_TIME_H