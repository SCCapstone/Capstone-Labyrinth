#include "pch.h"
#include "CppUnitTest.h"

#include "../Game/inc/Game_Engine.h"
#include "../Game/inc/MainMenu.h"

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
			delete enemies_1;

			Enemy_Spawner* enemies_2 = new Enemy_Spawner(-1, 10, Vector2f(100.0f, 150.0f), &texture, Vector2u(10, 3), 0.35f, 27.0f, 150, Vector2f(0.0f, 0.0f), Vector2f(15.0f, -19.0f));
			Assert::AreEqual(0, enemies_2->getAmount());

			enemies_2 = nullptr;
			delete enemies_2;
		}

		// tests the replinish item spawner with edge-case amounts (item count will not exceed 20 at worst, and will never be negative)
		TEST_METHOD(TestMassReplinishPopulation) {
			Texture texture;
			Replinish_Spawner* reps_1 = new Replinish_Spawner(10000, Vector2f(100.0f, 150.0f), &texture, Vector2u(4, 1), 0.5f, Vector2f(0.0f, 0.0f), Vector2f(15.0f, -19.0f));
			Assert::AreEqual(10000, reps_1->getAmount());

			reps_1 = nullptr;
			delete reps_1;

			Enemy_Spawner* reps_2 = new Enemy_Spawner(-1, 10, Vector2f(100.0f, 150.0f), &texture, Vector2u(10, 3), 0.35f, 27.0f, 150, Vector2f(0.0f, 0.0f), Vector2f(15.0f, -19.0f));
			Assert::AreEqual(0, reps_2->getAmount());

			reps_2 = nullptr;
			delete reps_2;
		}

		// tests to ensure that the proper messages are set given a winning or losing condition
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
			delete ep_1;

			// create new exit page for losing
			Exit_Page* ep_2 = new Exit_Page(10.0f);
			ep_2->setLost(true);

			Assert::AreEqual(true, ep_2->getLossCond());

			if (lossMsg.compare(ep_2->getLossMsg()) == 0)
				Assert::AreEqual(true, true);
			else
				Assert::AreEqual(true, false);

			ep_2 = nullptr;
			delete ep_2;
		}

		// tests to ensure enemies are properly intialized, even if given invalid values
		TEST_METHOD(TestEnemyStatistics) {
			Texture texture;

			Vector2f size = Vector2f(100.0f, 150.0f);
			float speed = 27.0f;
			int health = 150;
			int attack_val = 19;

			// design valid enemy
			Enemy* en_1 = new Enemy(&texture, Vector2u(10, 3), size, 0.35f, speed, health, attack_val);

			// check size, speed, health, and attack value for correct initialization
			Assert::AreEqual(size.x, en_1->getSize().x);
			Assert::AreEqual(size.y, en_1->getSize().y);
			Assert::AreEqual(speed, en_1->getSpeed());
			Assert::AreEqual(health, en_1->getOrignalHealth());
			Assert::AreEqual(attack_val, en_1->getAttackValue());

			en_1 = nullptr;
			delete en_1;

			Vector2f bad_size = Vector2f(-100.0f, -150.0f);
			float bad_speed = -27.0f;
			int bad_health = -150;
			int bad_attack_val = -19;

			// design invalid enemy
			Enemy* en_2 = new Enemy(&texture, Vector2u(10, 3), bad_size, 0.35f, bad_speed, bad_health, bad_attack_val);

			// check size, speed, health, and attack value for correct initialization
			Assert::AreNotEqual(bad_size.x, en_2->getSize().x);
			Assert::AreNotEqual(bad_size.y, en_2->getSize().y);
			Assert::AreNotEqual(bad_speed, en_2->getSpeed());
			Assert::AreNotEqual(bad_health, en_2->getOrignalHealth());
			Assert::AreNotEqual(bad_attack_val, en_2->getAttackValue());

			en_2 = nullptr;
			delete en_2;
		}

		// tests to ensure player is properly intialized, even if given invalid values
		TEST_METHOD(TestPlayerStatistics) {
			Texture texture;

			Vector2f size = Vector2f(100.0f, 150.0f);
			float speed = 27.0f;
			int health = 150;
			int attack_val = 19;

			// design valid enemy
			Player* play_1 = new Player(&texture, Vector2u(10, 3), size, 0.35f, speed, health, attack_val);

			// check size, speed, health, and attack value for correct initialization
			Assert::AreEqual(size.x, play_1->getSize().x);
			Assert::AreEqual(size.y, play_1->getSize().y);
			Assert::AreEqual(speed, play_1->getSpeed());
			Assert::AreEqual(health, play_1->getOrignalHealth());
			Assert::AreEqual(attack_val, play_1->getAttackValue());

			play_1 = nullptr;
			delete play_1;

			Vector2f bad_size = Vector2f(-100.0f, -150.0f);
			float bad_speed = -27.0f;
			int bad_health = -150;
			int bad_attack_val = -19;

			// design invalid enemy
			Player* play_2 = new Player(&texture, Vector2u(10, 3), bad_size, 0.35f, bad_speed, bad_health, bad_attack_val);

			// check size, speed, health, and attack value for correct initialization
			Assert::AreNotEqual(bad_size.x, play_2->getSize().x);
			Assert::AreNotEqual(bad_size.y, play_2->getSize().y);
			Assert::AreNotEqual(bad_speed, play_2->getSpeed());
			Assert::AreNotEqual(bad_health, play_2->getOrignalHealth());
			Assert::AreNotEqual(bad_attack_val, play_2->getAttackValue());

			play_2 = nullptr;
			delete play_2;
		}
		
		// test to ensure all quadrants get intialized with the same scale
		TEST_METHOD(TestMazeQuadrantSizeFactor) {
			Vector2f scale = Vector2f(250.0f, 250.0f);
			
			// create new maze object
			Maze_Builder* maze = new Maze_Builder(scale);

			// ensure all quadrants have been initialized with the same scale
			Assert::AreEqual(scale.x, maze->getFirstQuadSizeFactor().x);
			Assert::AreEqual(scale.y, maze->getFirstQuadSizeFactor().y);
			Assert::AreEqual(scale.x, maze->getSecondQuadSizeFactor().x);
			Assert::AreEqual(scale.y, maze->getSecondQuadSizeFactor().y);
			Assert::AreEqual(scale.x, maze->getThirdQuadSizeFactor().x);
			Assert::AreEqual(scale.y, maze->getThirdQuadSizeFactor().y);
			Assert::AreEqual(scale.x, maze->getFourthQuadSizeFactor().x);
			Assert::AreEqual(scale.y, maze->getFourthQuadSizeFactor().y);

			maze = nullptr;
			delete maze;
		}

		// test to ensure the animations are loaded properly into the animation class
		TEST_METHOD(TestAnimation) {
			Texture texture;
			Animation* ani = new Animation(&texture, Vector2u(10, 3), 0.35f);

			Assert::AreEqual(10, (int)ani->getImageCount().x);
			Assert::AreEqual(3, (int)ani->getImageCount().y);
			Assert::AreEqual(0.35f, ani->getSwitchTime());

			ani = nullptr;
			delete ani;
		}

		// test to ensure the map is set correctly given parameters (tile count, size)
		TEST_METHOD(TestBackgroundTileMap) {
			Texture texture;
			Vector2f size = Vector2f(250.0f, 250.0f);
			float x_bounds = 2.0f;
			float y_bounds = 2.0f;

			Background_Map* bgm = new Background_Map(&texture, size, 0.0f, x_bounds, 0.0f, y_bounds);

			Assert::AreEqual((int)(x_bounds*y_bounds), bgm->getTileAmount());
			Assert::AreEqual(size.x, bgm->getSizeFactor().x);
			Assert::AreEqual(size.y, bgm->getSizeFactor().y);
			Assert::AreEqual(x_bounds, bgm->getXTilesAmount());
			Assert::AreEqual(y_bounds, bgm->getYTilesAmount());

			bgm = nullptr;
			delete bgm;
		}

		// tests to ensures that the healthbar is properly intialized given a player rectangle
		TEST_METHOD(TestHealthBar) {
			RectangleShape* body = new RectangleShape(Vector2f(100.0f, 150.0f));
			Texture texture;
			HealthBar* hb = new HealthBar(body, body->getSize(), &texture, Vector2u(1, 20), 0.35f, 10.0f);

			// health bar is adjusted to aesthetically fit the player better
			Assert::AreNotEqual(body->getSize().x, hb->getHealthBarXDim());
			Assert::AreNotEqual(body->getSize().y, hb->getHealthBarYDim());

			Assert::AreEqual(10.0f, hb->getSpeed());

			body = nullptr;
			delete body;
			hb = nullptr;
			delete hb;
		}
	};
}
