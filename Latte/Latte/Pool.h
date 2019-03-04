//
// Created by Mörkönenä on 2.8.2018
//

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <functional>
#include <atomic>

#include "Window.h"

namespace Core
{
  class Task
  {
  private:
    std::atomic_bool done;
    std::function<void()> action;

  public:
    Task(std::function<void()> action);

    void Execute();
    bool IsDone() const;
  };

  class Pool
  {
	public:
    static void Initialize(const Window* window, int thread_count = -1);
    static Task* Run(std::function<void()> action);
		static void Destroy();
	};
}

#endif