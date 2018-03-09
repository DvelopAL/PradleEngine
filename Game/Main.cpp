#include <Core.h>
#include "Test.h"

using namespace PradleEngine;

int main(void)
{
	Engine* engine = Engine::Create(CODE_PAGE::KOREAN, 30);
	engine->Init();
	engine->Excute(new Test);
	return 1;
}
