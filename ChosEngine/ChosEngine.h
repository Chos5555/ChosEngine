#pragma once

namespace ChosEngine
{
	class State;

	class Engine
	{
	public:
		int Run();

	private:
		void Render(State state);
		void PollEvents(State* state);
	};
}
