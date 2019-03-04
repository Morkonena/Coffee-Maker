#include "../Common.h"

extern void Altra_Begin ();
extern void Altra_Tick  (float delta_time);

typedef jint		JavaInteger;
typedef jfloat		JavaFloat;
typedef jboolean	JavaBool;

extern "C"
{
	void Java_com_quanfoxes_altra_Adapter_Initialize(JavaEnvironment environment, JavaObject instance, JavaObject asset_manager)
	{
		Assets::Initialize(environment, asset_manager);

		Sprite::Initialize();
		Tilemap::Initialize();

		Camera::Initialize();
		Camera::SetWindingOrder(true);
		Camera::SetTransparency(true);
		Camera::SetDepth(false);

		Physics::Initialize(Vector2(0));

		AudioSystem::Initialize();
	}

	void Java_com_quanfoxes_altra_Adapter_Resize(JavaEnvironment environment, JavaObject instance, JavaInteger width, JavaInteger height)
	{
		float aspect = width / (float)height;

		Camera::SetProjection(Matrix::Orthographic(-50, 50, -50 / aspect, 50 / aspect));
		Camera::SetViewport(0, 0, width, height);

		Altra_Begin();
	}

	void Java_com_quanfoxes_altra_Adapter_Tick(JavaEnvironment environment, JavaObject instance, JavaFloat delta_time)
	{
		Physics::Tick(delta_time);
		AudioSystem::Tick();
		Altra_Tick(delta_time);
		Input::Update();
	}

	void Java_com_quanfoxes_altra_Adapter_TouchInput(JavaEnvironment environment, JavaObject instance, JavaInteger finger, JavaFloat x, JavaFloat y, JavaBool down)
	{
		Input::Feed(finger, x, y, down);
	}
}