#include "pch.h"
#include "CppUnitTest.h"

#include "../Game/inc/Game_Engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		// test go here
		TEST_METHOD(TestCheatModeStatus)
		{
			
			Game_Engine ge(true);
			Assert::AreEqual(true, ge.isGameCheating());
		}

		TEST_METHOD(TestMassEnemyPopulation)
		{
			Texture min_texture;
			Enemy_Spawner* enemies_1 = new Enemy_Spawner(10000, 10, Vector2f(100.0f, 150.0f), &min_texture, Vector2u(10, 3), 0.35f, 27.0f, 150, Vector2f(0.0f, 0.0f), Vector2f(15.0f, -19.0f));
			Assert::AreEqual(10000, enemies_1->getAmount());

			enemies_1 = nullptr;

			Enemy_Spawner* enemies_2 = new Enemy_Spawner(-1, 10, Vector2f(100.0f, 150.0f), &min_texture, Vector2u(10, 3), 0.35f, 27.0f, 150, Vector2f(0.0f, 0.0f), Vector2f(15.0f, -19.0f));
			Assert::AreEqual(0, enemies_2->getAmount());

			enemies_2 = nullptr;
		}
	};
}
