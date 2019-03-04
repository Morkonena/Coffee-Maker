//
// Created by Mörkönenä on 30.12.2018
//

#ifndef CORE_INPUT_H
#define CORE_INPUT_H

#include <Standard.h>
#include <Vector2.h>

typedef char VirtualKey;

namespace Core
{
	enum CursorState
	{
		CURSOR_STATE_JUST_PRESSED,
		CURSOR_STATE_PRESSED,
		CURSOR_STATE_JUST_RELEASED
	};

	class Cursor
	{
	private:
		friend class Input;
		void Update(float x, float y);

	public:
		int id;

		Vector2 position;
		Vector2 delta;

		CursorState state;
	};

	class Input
	{
	public:
		static void Feed (int id, float x, float y, bool down);
		static void Feed (int id, float x, float y);

		static void Feed (VirtualKey key, bool down);

		static void OnCursorLeave(int i = -1);

		static void Update ();

	private:
		friend class Cursor;
		static List<Cursor> Cursors;

		static struct KeyboardInput
		{
			bool States[256];
			bool Changes[256];

		} Keyboard;

	public:
		static bool IsKeyJustPressed		(VirtualKey key);
		static bool IsKeyPressed				(VirtualKey key);
		static bool IsKeyJustReleased		(VirtualKey key);
		static bool IsKeyReleased				(VirtualKey key);

		static bool IsCursorJustPressed		(int i = 0);
		static bool IsCursorPressed				(int i = 0);
		static bool IsCursorJustReleased	(int i = 0);
		static bool IsCursorReleased			(int i = 0);

		static Vector2 GetCursorPosition	(int i = 0);
		static Vector2 GetCursorDelta			(int i = 0);

		static Cursor GetCursor						(int i = 0);

		static int GetCursorCount ();
	};
}

#endif // !CORE_INPUT_H