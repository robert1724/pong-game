#pragma once

#include "components/simple_scene.h"

namespace m1
{
	class Tema1 : public gfxc::SimpleScene
	{

	public:
		struct ViewportSpace
		{
			ViewportSpace() : x(0), y(0), width(1), height(1) {}
			ViewportSpace(int x, int y, int width, int height)
				: x(x), y(y), width(width), height(height) {
			}
			int x;
			int y;
			int width;
			int height;
		};

		struct LogicSpace
		{
			LogicSpace() : x(0), y(0), width(1), height(1) {}
			LogicSpace(float x, float y, float width, float height)
				: x(x), y(y), width(width), height(height) {
			}
			float x;
			float y;
			float width;
			float height;
		};

		struct DragnDrop
		{
			float ox = 0.0f, oy = 0.0f;
			float width = 0.0f, height = 0.0f;
			float offsetX = 0.0f, offsetY = 0.0f;
			std::string name = "";
			bool interacting = false;
			bool over = false;
		}dragndrop;

	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		glm::vec2 ScreenToLogic(int mouseX, int mouseY);

		glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
		glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
		void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

	protected:
		float length = 0.0f;
		int p = 0;
		ViewportSpace viewSpace;
		LogicSpace logicSpace;
		glm::mat3 visMatrix = {};
		
		DragnDrop cube_cannon_fix;
		DragnDrop semicircle_cannon_fix;
		DragnDrop rectagnle_cannon_long_fix;
		DragnDrop trapez_cannon_fix;
		std::vector <DragnDrop> cube_cannon_vector;
		std::vector <DragnDrop> semicircle_cannon_vector;
		std::vector <DragnDrop> rectangle_cannon_vector;
		std::vector <DragnDrop> trapez_cannon_vector;

		DragnDrop cube_bumper_fix;
		DragnDrop semicircle_bumper_fix;
		std::vector <DragnDrop> cube_bumper_vector;
		std::vector <DragnDrop> semicircle_bumper_vector;

		DragnDrop cube_basic;
		DragnDrop cube_basic_fix;
		std::vector <DragnDrop> cube_basic_vector;

		float left_time_anim = 0.0f;
		float right_time_anim = 0.0f;
		float left_scale = 0.0f;
		float right_scale = 0.0f;
		const float durata_animatie = 0.1f;
		const float scalare_animatie = 2.0f;


		int f = 0;
		float endscreen = 0.0f;
		int max_cubes = 10;
		int max_count = 0;
		bool check = false;
		int cannon_condition[9][17] = {};

		int game_start = 0;
		float left_moving = 0.0f;
		float right_moving = 0.0f;

		int direction = rand() % 2;

		float initialspeed = 30.0f;
		int score_right = 0;
		int score_left = 0;

		float pingpongballox = 0.0f;
		float pingpongballoy = 0.0f;
		float speedox = 0.0f;
		float speedoy = 0.0f;

		float rot = -glm::half_pi<float>();
		float rot2 = glm::half_pi<float>();
		int blue_wins = 0;
		int red_wins = 0;

		DragnDrop *current_object = nullptr;
		DragnDrop *current_object2 = nullptr;
		DragnDrop* current_object3 = nullptr; 
		DragnDrop* current_object4 = nullptr;

		int matrix_used[9][17] = {};
	};

}