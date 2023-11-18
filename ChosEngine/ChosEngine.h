#pragma once

#include "Map.h"
#include "State.h"

namespace ChosEngine
{
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
	};
}
