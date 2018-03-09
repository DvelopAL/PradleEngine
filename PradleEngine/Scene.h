#pragma once

namespace PradleEngine
{
	class Scene
	{
	public:
		Scene() { }
		virtual ~Scene() { }

		virtual void OnEnter() { }
		virtual void OnExit() { }
		virtual void Update() { }

		void SetBGColor(WORD color) { _bgColor = color; }
		WORD GetBGColor() { return _bgColor; }

		void ReleaseScene()
		{
			OnExit();
			delete this;
		}

	private:
		WORD _bgColor = BLACK;
	};
}