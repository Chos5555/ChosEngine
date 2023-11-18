#pragma once

#include "Map.h"
#include "State.h"

namespace ChosEngine
{
	template <typename T> int8_t Sign(T a);
	template <typename T> T Min(T a, T b);
	template <typename T> T Max(T a, T b);

	class Engine
	{
	public:
		State state;
		Map map;

		int Run();

	private:
		void Render();
		void PollEvents();
		void Rotate(float_t rotation);
		void VerticalLine(int x, int y0, int y1, uint32_t color);
	};
}
