#pragma once

#include "State.h"

namespace ChosEngine
{
	class State;

	class Engine
	{
	public:
		State state;

		int Run();

	private:
		void Render();
		void PollEvents();
	};
}
