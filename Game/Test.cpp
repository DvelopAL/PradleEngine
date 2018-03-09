#include "Test.h"

void Test::OnEnter()
{
	SetBGColor(WHITE);
}

void Test::Update()
{
	static COORD coordition = { 0, 0 };
	if (Input::IsKey(KEY::RIGHT))
	{
		coordition.X++;
	}
	else if (Input::IsKey(KEY::LEFT))
	{
		coordition.X--;
	}

	if (Input::IsKey(KEY::UP))
	{
		coordition.Y--;
	}
	else if (Input::IsKey(KEY::DOWN))
	{
		coordition.Y++;
	}
	Renderer::DrawChar(Input::GetMouseCoordinate(), ' ', RED, RED);
	Renderer::DrawChar(coordition, '^', YELLOW, RED);
}

void Test::OnExit()
{

}
