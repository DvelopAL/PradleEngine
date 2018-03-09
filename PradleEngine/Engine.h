#pragma once

#include <Windows.h>
#include <vector>
#include "Defines.h"

namespace PradleEngine
{
	class ConsoleBuffer;
	class Scene;
	class Engine
	{
	public:
		static Engine* Create();
		static Engine* Create(int syncFrame);
		static Engine* Create(CODE_PAGE codePage);
		static Engine* Create(CODE_PAGE codePage, int syncFrame);

		void SetCodePage(CODE_PAGE codePage);
		void SetSync(int syncFrame);
		void Excute(Scene* startScene);

		bool Init();

	protected:
		Engine();
		~Engine() = default;

	private:
		void WaitForSync();

	private:
		int _syncFrame;

	};
}