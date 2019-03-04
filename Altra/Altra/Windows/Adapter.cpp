#include "../Common.h"

#define ABORT while (true)

extern void Altra_Begin();
extern void Altra_Tick(float dt);

Managed<Window> window;

void Initialize()
{
	Graphics::Initialize();
	
	window = std::make_unique<Window>(1920, 1080, true, "Altra");
	window->SetVSync(false);

	Assets::Initialize();
	Pool::Initialize(window.get(), std::thread::hardware_concurrency() - 1);

	window->Start();
	window->SetCursorVisible(true);
	
	Sprite::Initialize();
	Tilemap::Initialize();

	Camera::Initialize();

	Camera::SetProjection(Matrix::Orthographic(-50, 50, -50 / Screen::GetAspect(), 50 / Screen::GetAspect()));
	Camera::position = Vector3(0, 0, 0);
	Camera::SetWindingOrder(true);
	Camera::SetTransparency(true);
	Camera::SetDepth(false);

	Physics::Initialize(Vector2(0, 0));

	AudioSystem::Initialize();
}

int main ()
{
	Console::Initialize();

	try
	{
		Initialize();
	}
	catch (const std::exception& e)
	{
		PERROR("ERROR_INITIALIZE: ", e.what());
		ABORT;
	}
	catch (...)
	{
		PERROR("ERROR_INITIALIZE");
		ABORT;
	}

	try
	{
		Altra_Begin();
	}
	catch (const std::exception& e)
	{
		PERROR("ERROR_ALTRA_BEGIN: ", e.what());
		ABORT;
	}
	catch (...)
	{
		PERROR("ERROR_ALTRA_BEGIN");
		ABORT;
	}

	auto a = NOW;
	auto b = 0.0f;

	while (!window->IsClosing())
	{
		b = MILLISECONDS(SINCE(a)) / 1000.0f;
		a = NOW;

		try
		{
			Physics::Tick(b);
		}
		catch (const std::exception& e)
		{
			PERROR("ERROR_PHYSICS_SYSTEM: ", e.what());
		}
		catch (...)
		{
			PERROR("ERROR_PHYSICS_SYSTEM");
		}

		try
		{
			AudioSystem::Tick();
		}
		catch (const std::exception& e)
		{
			PERROR("ERROR_AUDIO_SYSTEM: ", e.what());
		}
		catch (...)
		{
			PERROR("ERROR_AUDIO_SYSTEM");
		}

		try
		{
			Altra_Tick(b);
		}
		catch (const std::exception& e)
		{
			PERROR("ERROR_ALTRA_RUNTIME: ", e.what());
		}
		catch (...)
		{
			PERROR("ERROR_ALTRA_RUNTIME");
		}

		try
		{
			Input::Update();
		}
		catch (const std::exception& e)
		{
			PERROR("ERROR_INPUT_SYSTEM: ", e.what());
		}
		catch (...)
		{
			PERROR("ERROR_INPUT_SYSTEM");
		}

		try
		{
			window->Update();
		}
		catch (...)
		{
			PERROR("ERROR_WINDOW_SYSTEM");
		}
	}

	return 0;
}

