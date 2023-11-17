#pragma once

#include "State.h"

namespace ChosEngine
{
	class Engine
	{
	public:
		State state;

		int Run();

	private:
		void Render();
		void PollEvents();
		void Rotate(float_t rotation);
	};
}
