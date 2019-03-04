#include <list>
#include <queue>
#include <thread>
#include <mutex>

#include <Log.h>

#include <GL.h>
#include <GL\wglew.h>

#include "Graphics.h"
#include "Pool.h"

using namespace Core;

std::queue<Task*> tasks;

std::mutex lock;
std::condition_variable signal;

std::list<std::thread> threads;

void Pool::Initialize(const Window* window, int thread_count)
{
  // Make sure no context is binded
  window->GetRenderingContext().Unbind();

  // Tells how many threads should be created
  thread_count = (thread_count == -1) ? (int)std::thread::hardware_concurrency() : thread_count;

  // Tells how many threads are ready
  std::atomic_int ready_count = 0;

  for (int i = 0; i < thread_count; i++)
  {
    RenderingContext rc(window, &window->GetRenderingContext());

    threads.push_back(std::thread([&, index = i, rendering_context = std::move(rc)]() mutable
    {
      while (!rendering_context.Bind())
      {
        WARNING("Pool: Thread (", index, ")", ": Failed to bind rendering context, trying again soon...");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }

      PRINT("Pool: Thread (", index, "): OK");
      ready_count++;
      
      while (true)
      {
        Task* task;
        {
          // Wait for the queue to get tasks
          std::unique_lock<std::mutex> quard(lock);

          signal.wait(quard, [&]() -> bool
          {
            return tasks.size() > 0;
          });

          // Take and remove the next task from the queue
          task = tasks.front();
          tasks.pop();
        }

        task->Execute();
      }

    }));
  }

  // Wait for all threads to get ready
  while (ready_count < thread_count)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  SUCCESS("Pool: OK");
}

Task* Pool::Run(std::function<void()> action)
{
  std::unique_lock<std::mutex> quard(lock);

  Task* task = new Task(action);
  tasks.push(task);

  signal.notify_one();

  return task;
}

void Pool::Destroy()
{
  while (tasks.size() > 0)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

Task::Task(std::function<void()> action)
{
  this->action = action;
  this->done = false;
}

void Task::Execute()
{
  try
  {
    action();
  }
  catch (const std::exception& e)
  {
    PERROR("ERROR_EXECUTE_TASK: ", e.what());
  }

  done = true;
}

bool Task::IsDone() const
{
  return done;
}
