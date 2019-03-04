#include "Input.h"

#include <Log.h>
#include <Standard.h>

using namespace Core;

List<Cursor> Input::Cursors;
Input::KeyboardInput Input::Keyboard;

void Input::Feed (int id, float x, float y, bool down)
{
	auto i = std::find_if(Cursors.begin(), Cursors.end(), [id](const Cursor& x) { return x.id == id; });

	if (Cursors.end() == i)
	{
		Cursor cursor = { 0 };
		cursor.id = id;
		cursor.position = Vector2(x, y);

		Cursors.push_back(cursor);
	}
	else
	{
		Cursor& cursor = *i;
		cursor.state = CURSOR_STATE_JUST_RELEASED;
		cursor.Update(x, y);
	}
}

void Input::Feed(int id, float x, float y)
{
	auto i = std::find_if(Cursors.begin(), Cursors.end(), [id](const Cursor& x) { return x.id == id; });

	if (Cursors.end() != i)
	{
		Cursor& cursor = *i;
		cursor.Update(x, y);
	}
}

void Input::Feed(VirtualKey key, bool down)
{
	Keyboard.Changes[key] = Keyboard.States[key] != down;
	Keyboard.States[key] = down;
}

void Input::OnCursorLeave(int i)
{
	if (i < 0)
	{
		Cursors.clear();
	}
	else if (i < Cursors.size())
	{
		Cursors.erase(Cursors.begin() + i);
	}
}

void Input::Update()
{
	memset(Keyboard.Changes, 0, 256);

	for (int i = (int)Cursors.size() - 1; i >= 0; i--)
	{
		Cursor& cursor = Cursors[i];

		if (cursor.state == CURSOR_STATE_JUST_PRESSED)
		{
			cursor.state = CURSOR_STATE_PRESSED;
		}
		else if (cursor.state == CURSOR_STATE_JUST_RELEASED)
		{
			Cursors.erase(Cursors.begin() + i);
		}
	}
}

bool Input::IsKeyJustPressed (VirtualKey key)
{
	return Keyboard.States[key] && Keyboard.Changes[key];
}

bool Input::IsKeyPressed (VirtualKey key)
{
	return Keyboard.States[key];
}

bool Input::IsKeyJustReleased(VirtualKey key)
{
	return !Keyboard.States[key] && Keyboard.Changes[key];
}

bool Input::IsKeyReleased (VirtualKey key)
{
	return !Keyboard.States[key];
}

bool Input::IsCursorJustPressed(int i)
{
	return (i < Cursors.size()) ? Cursors[i].state == CURSOR_STATE_JUST_PRESSED : false;
}

bool Input::IsCursorPressed(int i)
{
	return (i < Cursors.size()) ? (Cursors[i].state == CURSOR_STATE_PRESSED || Cursors[i].state == CURSOR_STATE_JUST_PRESSED) : false;
}

bool Input::IsCursorJustReleased(int i)
{
	return (i < Cursors.size()) ? Cursors[i].state == CURSOR_STATE_JUST_RELEASED : false;
}

bool Input::IsCursorReleased(int i)
{
	return (i >= Cursors.size()) || Cursors[i].state == CURSOR_STATE_JUST_RELEASED;
}

Vector2 Input::GetCursorPosition(int i)
{
	return (i < Cursors.size()) ? Cursors[i].position : Vector2(-1);
}

Vector2 Input::GetCursorDelta(int i)
{
	return (i < Cursors.size()) ? Cursors[i].delta : Vector2(0);
}

Cursor Input::GetCursor(int i)
{
	if (i < Cursors.size())
	{
		return Cursors[i];
	}

	PERROR("ERROR_INDEX_OUT_OF_BOUNDS");
	throw;
}

int Input::GetCursorCount()
{
	return (int)Cursors.size();
}

void Cursor::Update(float x, float y)
{
	delta = Vector2(x, y) - position;
	position = Vector2(x, y);
}
