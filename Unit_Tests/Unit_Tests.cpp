#include "pch.h"
#include "CppUnitTest.h"

#include "../Game/inc/Game_Engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		// tests the entire game engine to ensure the cheat mode status gets set correctly
		TEST_METHOD(TestCheatModeStatus) {			
			Game_Engine ge_1(true);
			Assert::AreEqual(true, ge_1.isGameCheating());

			Game_Engine ge_2(false);
			Assert::AreEqual(false, ge_2.isGameCheating());
		}

		// tests the enemy spawner with edge-case enemy amounts (enemy count will not exceed 50ish at worst, and will never be negative)
		TEST_METHOD(TestMassEnemyPopulation) {
			Texture texture;
			Enemy_Spawner* enemies_1 = new Enemy_Spawner(10000, 10, Vector2f(100.0f, 150.0f), &texture, Vector2u(10, 3), 0.35f, 27.0f, 150, Vector2f(0.0f, 0.0f), Vector2f(15.0f, -19.0f));
			Assert::AreEqual(10000, enemies_1->getAmount());

			enemies_1 = nullptr;

			Enemy_Spawner* enemies_2 = new Enemy_Spawner(-1, 10, Vector2f(100.0f, 150.0f), &texture, Vector2u(10, 3), 0.35f, 27.0f, 150, Vector2f(0.0f, 0.0f), Vector2f(15.0f, -19.0f));
			Assert::AreEqual(0, enemies_2->getAmount());

			enemies_2 = nullptr;
		}

		// tests the replinish item spawner with edge-case amounts (item count will not exceed 20 at worst, and will never be negative)
		TEST_METHOD(TestMassReplinishPopulation) {
			Texture texture;
			Replinish_Spawner* reps_1 = new Replinish_Spawner(10000, Vector2f(100.0f, 150.0f), &texture, Vector2u(4, 1), 0.5f, Vector2f(0.0f, 0.0f), Vector2f(15.0f, -19.0f));
			Assert::AreEqual(10000, reps_1->getAmount());

			reps_1 = nullptr;

			Enemy_Spawner* reps_2 = new Enemy_Spawner(-1, 10, Vector2f(100.0f, 150.0f), &texture, Vector2u(10, 3), 0.35f, 27.0f, 150, Vector2f(0.0f, 0.0f), Vector2f(15.0f, -19.0f));
			Assert::AreEqual(0, reps_2->getAmount());

			reps_2 = nullptr;
		}

		TEST_METHOD(TestWinLossMessage) {
			std::string lossMsg = "YOU HAVE BEEN TAKEN\n\t\t\tBY THE MAZE\n press Esc to return to Menu"; \
			std::string winMsg = "\t\tYOU HAVE WON\n press Esc to return to Menu";

			// create new exit page for winning
			Exit_Page* ep_1 = new Exit_Page(10.0f);
			ep_1->setLost(false);
			
			Assert::AreEqual(false, ep_1->getLossCond());
			
			if (winMsg.compare(ep_1->getWinMsg()) == 0)
				Assert::AreEqual(true, true);
			else
				Assert::AreEqual(true, false);

			ep_1 = nullptr;

			// create new exit page for losing
			Exit_Page* ep_2 = new Exit_Page(10.0f);
			ep_2->setLost(true);

			Assert::AreEqual(true, ep_2->getLossCond());

			if (lossMsg.compare(ep_2->getLossMsg()) == 0)
				Assert::AreEqual(true, true);
			else
				Assert::AreEqual(true, false);

			ep_2 = nullptr;
			
		}
	};
}
