#include "../Common.h"

#define ABORT while (true)

extern void Altra_Begin ();
extern void Altra_Tick  (float dt);

Managed<Window> window;

void Initialize()
{
	Graphics::Initialize();

	window = std::make_unique<Window>(1920, 1080, "Altra");
	//window->SetVSync(false);

	Assets::Initialize();
	// Pool::Initialize(window.get(), std::thread::hardware_concurrency() - 1); TODO: Linux Support

	window->Start();
	window->SetFullscreen(true);
	//window->SetCursorVisible(true);

	Sprite::Initialize();
	Tilemap::Initialize();

	Camera::Initialize();

	float aspect = 1920.0f / 1080.0f;

	Camera::SetProjection(Matrix::Orthographic(-50, 50, -50 / aspect, 50 / aspect));
	Camera::position = Vector3(0, 0, 0);
	Camera::SetViewport(0, 0, 1920, 1080);
	Camera::SetWindingOrder(true);
	Camera::SetTransparency(true);
	Camera::SetDepth(false);

	Physics::Initialize(Vector2(0, 0));
}

int main ()
{
	//Console::Initialize();

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
