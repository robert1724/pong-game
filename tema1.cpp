#include "lab_m1/tema1/tema1.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{

	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	visMatrix = VisualizationTransf2DUnif(logicSpace, viewSpace);

	logicSpace.x = 0.0f;
	logicSpace.y = 0.0f;
	logicSpace.width = 101.65f;
	logicSpace.height = 57.0f;

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 17; j++)
			matrix_used[i][j] = 0;

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 17; j++)
			cannon_condition[i][j] = 0;

	if (direction == 0) {
		speedox = initialspeed;
		speedoy = 5.0f;
	}
	else if (direction == 1) {
		speedox = -initialspeed;
		speedoy = 5.0f;
	}
	pingpongballox = 0.0f;
	pingpongballoy = 0.0f;
	direction = 2;

	cube_cannon_fix = { -43.75f, -5.5f, 3.5f, 3.5f, 0, 0, "grayfilled", false, false };
	semicircle_cannon_fix = { -41.6f, -3, 3.5f, 2, 0, 0, "whitecannonsemicircle", false, false };
	rectagnle_cannon_long_fix = { -43.375f, -2, 3.50f, 8, 0, 0, "darkgraycannon", false, false };
	trapez_cannon_fix = { 0, 0, 4, 0.9f, 0, 0, "trapezshotcannon", false, false };

	cube_bumper_fix = { -43.75f, 15, 3.5f, 3.5f, 0, 0, "grayfilled", false, false };
	semicircle_bumper_fix = { -41.75f, 19.20f, 12.25f, 4.25f, 0, 0, "semicircle", false, false };

	cube_basic_fix = { -43.75f, -21, 3.5f, 3.5f, 0, 0, "grayfilled", false, false };


	glm::vec3 corner(0, 0, 0);

	Mesh* fullscreen = object2D::CreateRectangle("fullscreen", corner, 101.60f, 57, glm::vec3(1, 0, 0), false);
	Mesh* bluescreen = object2D::CreateRectangle("bluescreen", corner, 76, 40, glm::vec3(0, 0, 1), false);
	Mesh* square1 = object2D::CreateSquare("square1", corner, 19, glm::vec3(1, 0, 0), false);

	Mesh* greenfilled = object2D::CreateSquare("greenfilled", corner, 4.75f, glm::vec3(0, 1, 0), true);
	Mesh* bluefilled = object2D::CreateSquare("bluefilled", corner, 2.75f, glm::vec3(0, 0, 1), true);
	Mesh* grayfilled = object2D::CreateSquare("grayfilled", corner, 4.25f, glm::vec3(0.5, 0.5, 0.5), true);
	Mesh* grayfilledsmall = object2D::CreateSquare("grayfilledsmall", corner, 2.4f, glm::vec3(0.5, 0.5, 0.5), true);

	Mesh* semicircle = object2D::CreateSemicircle("semicircle", corner, 12.25f, 4.25f, glm::vec3(1, 1, 0), true);
	Mesh* semicirclesmall = object2D::CreateSemicircle("semicirclesmall", corner, 7.2f, 2.4f, glm::vec3(1, 1, 0), true);

	Mesh* pingpongball = object2D::CreateCircle("pingpongball", corner, 1, glm::vec3(1, 1, 1), true);
	Mesh* whitecannonsemicircle = object2D::CreateSemicircle("whitecannonsemicircle", corner, 4.25f, 2, glm::vec3(1, 1, 1), true);
	Mesh* whitecannonsemicirclesmall = object2D::CreateSemicircle("whitecannonsemicirclesmall", corner, 2.4f, 1.129f, glm::vec3(1, 1, 1), true);
	Mesh* darkgraycannon = object2D::CreateRectangle("darkgraycannon", corner, 3.50f, 8, glm::vec3(0.25f, 0.25f, 0.25f), true);
	Mesh* darkgraycannonsmall = object2D::CreateRectangle("darkgraycannonsmall", corner, 1.9764f, 4.517647f, glm::vec3(0.25f, 0.25f, 0.25f), true);
	Mesh* trapezshotcannon = object2D::CreateTrapez("trapezshotcannon", glm::vec3(-44, 6.9f, 0), glm::vec3(-39.25f, 6.9f, 0), glm::vec3(-39.85f, 6, 0), glm::vec3(-43.35f, 6, 0), glm::vec3(0.15f, 0.15f, 0.15f), true);
	Mesh* trapezshotcannonsmall = object2D::CreateTrapez("trapezshotcannonsmall", glm::vec3(0.2f, 0, 0), glm::vec3(2.2f, 0, 0), glm::vec3(3, 0.8f, 0), glm::vec3(-0.4f, 0.8f, 0), glm::vec3(0.15f, 0.15f, 0.15f), true);
	Mesh* trapezshotcannonsmallright = object2D::CreateTrapez("trapezshotcannonsmallright", glm::vec3(0.2f, 0, 0), glm::vec3(2.2f, 0, 0), glm::vec3(3, 0.8f, 0), glm::vec3(-0.4f, 0.8f, 0), glm::vec3(0.15f, 0.15f, 0.15f), true);

	Mesh* blackfullscreen = object2D::CreateRectangle("blackfullscreen", corner, 150, 100, glm::vec3(0, 0, 0), true);
	Mesh* bluefullscreen = object2D::CreateRectangle("bluefullscreen", corner, 150, 100, glm::vec3(0, 0, 1), true);
	Mesh* redfullscreen = object2D::CreateRectangle("redfullscreen", corner, 150, 100, glm::vec3(1, 0, 0), true);
	Mesh* whitefullscreen = object2D::CreateRectangle("whitefullscreen", corner, 101.60f, 57, glm::vec3(1, 1, 1), false);
	Mesh* whitescreengame = object2D::CreateRectangle("whitescreengame", corner, 70, 40, glm::vec3(1, 1, 1), false);
	Mesh* smallgrayrectangle = object2D::CreateRectangle("smallgrayrectangle", corner, 0.75f, 2, glm::vec3(0.25f, 0.25f, 0.25f), true);

	Mesh* blueballpointright = object2D::CreateCircle("blueballpointright", corner, 1, glm::vec3(0, 0, 1), true);
	Mesh* redballpointleft = object2D::CreateCircle("redballpointleft", corner, 1, glm::vec3(1, 0, 0), true);

	AddMeshToList(square1);
	AddMeshToList(fullscreen);
	AddMeshToList(blackfullscreen);
	AddMeshToList(pingpongball);
	AddMeshToList(grayfilledsmall);
	AddMeshToList(semicirclesmall);
	AddMeshToList(darkgraycannonsmall);
	AddMeshToList(trapezshotcannonsmall);
	AddMeshToList(whitecannonsemicirclesmall);
	AddMeshToList(bluefullscreen);
	AddMeshToList(redfullscreen);
	AddMeshToList(whitescreengame);
	AddMeshToList(bluescreen);
	AddMeshToList(greenfilled);
	AddMeshToList(smallgrayrectangle);
	AddMeshToList(whitefullscreen);
	AddMeshToList(trapezshotcannon);
	AddMeshToList(trapezshotcannonsmallright);
	AddMeshToList(bluefilled);
	AddMeshToList(whitecannonsemicircle);
	AddMeshToList(grayfilled);
	AddMeshToList(darkgraycannon);
	AddMeshToList(semicircle);
	AddMeshToList(blueballpointright);
	AddMeshToList(redballpointleft);
}

glm::vec2 Tema1::ScreenToLogic(int mouseX, int mouseY)
{
	glm::ivec2 resolution = window->GetResolution();
	glm::vec3 screenPos(mouseX, resolution.y - mouseY, 1);
	glm::mat3 inversVisMatrix = glm::inverse(visMatrix);
	glm::vec3 logicPos = inversVisMatrix * screenPos;

	return glm::vec2(logicPos.x, logicPos.y);
}

bool pointInTriangle(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3)
{
	//verific sa nu se afle in triunghiul negru de la start
	float denom = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3);
	float a = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / denom;
	float b = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / denom;
	float c = 1.0f - a - b;

	if (a >= 0 && b >= 0 && c >= 0)
		return true;
	else
		return false;
}

void DFS(int i, int j, int visited[9][17], int matrix_used[9][17]) {
	if (i < 0 || i >= 9 || j < 0 || j >= 17)
		return;
	if (visited[i][j] == 1)
		return;
	if (matrix_used[i][j] != 1 && matrix_used[i][j] != 2 && matrix_used[i][j] != 3)
		return;

	visited[i][j] = 1;

	DFS(i + 1, j, visited, matrix_used);
	DFS(i - 1, j, visited, matrix_used);
	DFS(i, j + 1, visited, matrix_used);
	DFS(i, j - 1, visited, matrix_used);
}

int detect_collision_aabb(float ball_x, float ball_y, float ball_radius, float shapex, float shapey, float shapew, float shapeh) {
	float minx = ball_x;
	float miny = ball_y;

	if (minx < shapex)
		minx = shapex;
	else if (minx > shapex + shapew)
		minx = shapex + shapew;

	if (miny < shapey)
		miny = shapey;
	else if (miny > shapey + shapeh)
		miny = shapey + shapeh;

	float dx = ball_x - minx;
	float dy = ball_y - miny;

	if (dx * dx + dy * dy <= ball_radius * ball_radius)
		return 1;
	else return 0;
}

glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx = viewSpace.width / logicSpace.width;
	float sy = viewSpace.height / logicSpace.height;
	float tx = viewSpace.x - sx * logicSpace.x;
	float ty = viewSpace.y - sy * logicSpace.y;

	return glm::transpose(glm::mat3(
		sx, 0.0f, tx,
		0.0f, sy, ty,
		0.0f, 0.0f, 1.0f));
}

glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx = viewSpace.width / logicSpace.width;
	float sy = viewSpace.height / logicSpace.height;
	float smin = (sx < sy) ? sx : sy;

	float tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
	float ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}

void Tema1::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST); //pentru a nu avea probleme cu suprapunerea

	glm::ivec2 resolution = window->GetResolution();
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);

	glViewport(0, 0, resolution.x, resolution.y);
	visMatrix = VisualizationTransf2DUnif(logicSpace, viewSpace);
}

void Tema1::Update(float deltaTimeSeconds)
{
	Mesh* greenstart = nullptr;
	if (check == true) {
		greenstart = object2D::CreateStartButton("greenstart", glm::vec3(45, 17, 0), glm::vec3(49.75, 17, 0), glm::vec3(47.2375, 19.375, 0), glm::vec3(49.75, 21.75, 0), glm::vec3(45, 21.75, 0), glm::vec3(0, 1, 0), true);
	}
	else {
		greenstart = object2D::CreateStartButton("greenstart", glm::vec3(45, 17, 0), glm::vec3(49.75, 17, 0), glm::vec3(47.2375, 19.375, 0), glm::vec3(49.75, 21.75, 0), glm::vec3(45, 21.75, 0), glm::vec3(1, 0, 0), true);
	}

	AddMeshToList(greenstart);

	glm::mat3 fullscreenmat = glm::mat3(1);
	fullscreenmat *= transform2D::Translate(-51, -28.50);
	glm::mat3 bluescreenmat = glm::mat3(1);
	bluescreenmat *= transform2D::Translate(-28, -27);

	RenderMesh2D(meshes["fullscreen"], shaders["VertexColor"], fullscreenmat);
	RenderMesh2D(meshes["bluescreen"], shaders["VertexColor"], bluescreenmat);

	for (int i = 0; i < 3; i++) {
		glm::mat3 reds = glm::mat3(1);
		float oy = 9.50f - i * 19;
		reds *= transform2D::Translate(-51, oy);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], reds);
	}

	for (int i = 0; i < 10 - max_count; i++) {
		glm::mat3 greens = glm::mat3(1);
		float ox = i * 7.5f - 30.0f;
		greens *= transform2D::Translate(ox, 17);
		RenderMesh2D(meshes["greenfilled"], shaders["VertexColor"], greens);
	}

	glm::mat3 greenstartmat = glm::mat3(1);
	greenstartmat *= transform2D::Translate(0, 0);
	RenderMesh2D(meshes["greenstart"], shaders["VertexColor"], greenstartmat);

	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 9; j++) {
			glm::mat3 blues = glm::mat3(1);
			float ox = -25.50f + i * 4.25f;
			float oy = 8.50f - j * 4.25f;
			blues *= transform2D::Translate(ox, oy);
			RenderMesh2D(meshes["bluefilled"], shaders["VertexColor"], blues);
		}
	}

	//cub gri
	glm::mat3 graymat_fix = glm::mat3(1);
	graymat_fix *= transform2D::Translate(cube_basic_fix.ox, cube_basic_fix.oy);

	for (auto& cube : cube_basic_vector) {
		glm::mat3 graymat = glm::mat3(1);
		graymat *= transform2D::Translate(cube.ox, cube.oy);
		RenderMesh2D(meshes["grayfilled"], shaders["VertexColor"], graymat);
	}

	//bumper
	glm::mat3 graymat2 = glm::mat3(1);
	graymat2 *= transform2D::Translate(cube_bumper_fix.ox, cube_bumper_fix.oy);
	glm::mat3 semicirclemat = glm::mat3(1);
	semicirclemat *= transform2D::Translate(semicircle_bumper_fix.ox, semicircle_bumper_fix.oy);

	for (auto& cube : cube_bumper_vector) {
		glm::mat3 graymat = glm::mat3(1);
		graymat *= transform2D::Translate(cube.ox, cube.oy);
		RenderMesh2D(meshes["grayfilled"], shaders["VertexColor"], graymat);
	}

	for (auto& semi : semicircle_bumper_vector) {
		glm::mat3 semicirclemat2 = glm::mat3(1);
		semicirclemat2 *= transform2D::Translate(semi.ox, semi.oy);
		RenderMesh2D(meshes["semicircle"], shaders["VertexColor"], semicirclemat2);
	}

	//cannon
	glm::mat3 darkgraycannonmat = glm::mat3(1);
	darkgraycannonmat *= transform2D::Translate(rectagnle_cannon_long_fix.ox, rectagnle_cannon_long_fix.oy);
	RenderMesh2D(meshes["darkgraycannon"], shaders["VertexColor"], darkgraycannonmat);
	glm::mat3 graymat3 = glm::mat3(1);
	graymat3 *= transform2D::Translate(cube_cannon_fix.ox, cube_cannon_fix.oy);
	RenderMesh2D(meshes["grayfilled"], shaders["VertexColor"], graymat3);
	glm::mat3 whitecannonsemicirclemat = glm::mat3(1);
	whitecannonsemicirclemat *= transform2D::Translate(semicircle_cannon_fix.ox, semicircle_cannon_fix.oy);
	RenderMesh2D(meshes["whitecannonsemicircle"], shaders["VertexColor"], whitecannonsemicirclemat);
	glm::mat3 trapezshotcannonmat = glm::mat3(1);
	trapezshotcannonmat *= transform2D::Translate(trapez_cannon_fix.ox, trapez_cannon_fix.oy);
	RenderMesh2D(meshes["trapezshotcannon"], shaders["VertexColor"], trapezshotcannonmat);

	for (auto& cube : cube_cannon_vector) {
		glm::mat3 graymat = glm::mat3(1);
		graymat *= transform2D::Translate(cube.ox, cube.oy);
		RenderMesh2D(meshes["grayfilled"], shaders["VertexColor"], graymat);
	}

	for (auto& rect : rectangle_cannon_vector) {
		glm::mat3 darkgraycannonmat2 = glm::mat3(1);
		darkgraycannonmat2 *= transform2D::Translate(rect.ox, rect.oy);
		RenderMesh2D(meshes["darkgraycannon"], shaders["VertexColor"], darkgraycannonmat2);
	}

	for (auto& semi : semicircle_cannon_vector) {
		glm::mat3 semicirclemat3 = glm::mat3(1);
		semicirclemat3 *= transform2D::Translate(semi.ox, semi.oy);
		RenderMesh2D(meshes["whitecannonsemicircle"], shaders["VertexColor"], semicirclemat3);
	}

	for (auto& trap : trapez_cannon_vector) {
		glm::mat3 trapezshotcannonmat3 = glm::mat3(1);
		trapezshotcannonmat3 *= transform2D::Translate(trap.ox, trap.oy);
		RenderMesh2D(meshes["trapezshotcannon"], shaders["VertexColor"], trapezshotcannonmat3);
	}


	RenderMesh2D(meshes["grayfilled"], shaders["VertexColor"], graymat_fix);
	RenderMesh2D(meshes["grayfilled"], shaders["VertexColor"], graymat2);
	RenderMesh2D(meshes["semicircle"], shaders["VertexColor"], semicirclemat);

	//logica de dupa game start
	if (game_start == 1 && blue_wins == 0 && red_wins == 0) {

		const float durata_animatie = 0.25f;
		const float scalare_animatie = 1.5f;

		if (left_time_anim > 0.0f) {
			left_time_anim -= float(deltaTime);
			if (left_time_anim < 0.0f) {
				left_time_anim = 0.0f;
			}
		}

		if (right_time_anim > 0.0f) {
			right_time_anim -= float(deltaTime);
			if (right_time_anim < 0.0f) {
				right_time_anim = 0.0f;
			}
		}

		if (left_time_anim > 0.0f) {
			left_scale = scalare_animatie;
		}
		else {
			left_scale = 1.0f;
		}

		if (right_time_anim > 0.0f) {
			right_scale = scalare_animatie;
		}
		else {
			right_scale = 1.0f;
		}

		glm::mat3 blackmat = glm::mat3(1);
		blackmat *= transform2D::Translate(-55, -30);
		RenderMesh2D(meshes["blackfullscreen"], shaders["VertexColor"], blackmat);

		glm::mat3 whitefullscreenmat = glm::mat3(1);
		whitefullscreenmat *= transform2D::Translate(-51, -28.50);
		RenderMesh2D(meshes["whitefullscreen"], shaders["VertexColor"], whitefullscreenmat);

		glm::mat3 whitescreenmat = glm::mat3(1);
		whitescreenmat *= transform2D::Translate(-35.35f, -20);
		RenderMesh2D(meshes["whitescreengame"], shaders["VertexColor"], whitescreenmat);


		for (float y = 17.75f; y >= -19.75f; y -= 2.5f) {
			glm::mat3 smallrectanglemat = glm::mat3(1);
			smallrectanglemat *= transform2D::Translate(-0.72f, y);
			RenderMesh2D(meshes["smallgrayrectangle"], shaders["VertexColor"], smallrectanglemat);
		}

		float originY = 15;
		int counter = 0;
		int count_the_cubes = 0;
		int bumpers_poz[5];
		int cannon_poz[5];
		int k = 0;
		int k2 = 0;
		float moving = 35.0f * float(deltaTime);

		for (int j = 0; j < 17; j++) {
			for (int i = 0; i < 9; i++) {
				if (matrix_used[i][j] == 1 || matrix_used[i][j] == 2 || matrix_used[i][j] == 3) {

					float baseY = originY - counter * 2.4f;

					if (matrix_used[i][j] == 1) {
						glm::mat3 mat = glm::mat3(1);
						mat *= transform2D::Translate(-31, baseY + left_moving);
						mat *= transform2D::Scale(1.0f, left_scale);
						mat *= transform2D::Translate(31, -(baseY + left_moving));
						mat *= transform2D::Translate(-31, baseY + left_moving);
						mat *= transform2D::Rotate(rot);
						mat *= transform2D::Translate(-1.2f, -1.2f);
						RenderMesh2D(meshes["grayfilledsmall"], shaders["VertexColor"], mat);

						glm::mat3 matdupe = glm::mat3(1);
						matdupe *= transform2D::Translate(31, baseY + right_moving);
						matdupe *= transform2D::Scale(1.0f, right_scale);
						matdupe *= transform2D::Translate(-31, -(baseY + right_moving));
						matdupe *= transform2D::Translate(31, baseY + right_moving);
						matdupe *= transform2D::Rotate(rot2);
						matdupe *= transform2D::Translate(-1.2f, -1.2f);
						RenderMesh2D(meshes["grayfilledsmall"], shaders["VertexColor"], matdupe);

						count_the_cubes++;
					}

					else if (matrix_used[i][j] == 2) {
						glm::mat3 mat1 = glm::mat3(1);
						mat1 *= transform2D::Translate(-31, baseY + left_moving);
						mat1 *= transform2D::Scale(1.0f, left_scale);
						mat1 *= transform2D::Translate(31, -(baseY + left_moving));
						mat1 *= transform2D::Translate(-31, baseY + left_moving);
						mat1 *= transform2D::Rotate(rot);
						mat1 *= transform2D::Translate(-1.2f, -1.2f);
						RenderMesh2D(meshes["grayfilledsmall"], shaders["VertexColor"], mat1);

						glm::mat3 mat2 = glm::mat3(1);
						mat2 *= transform2D::Translate(-31 + 2.57f, baseY - 4.2f + left_moving);
						mat2 *= transform2D::Rotate(rot);
						mat2 *= transform2D::Translate(-4.125f, -1.375f);
						RenderMesh2D(meshes["semicirclesmall"], shaders["VertexColor"], mat2);

						glm::mat3 mat1dupe = glm::mat3(1);
						mat1dupe *= transform2D::Translate(31, baseY + right_moving);
						mat1dupe *= transform2D::Scale(1.0f, right_scale);
						mat1dupe *= transform2D::Translate(-31, -(baseY + right_moving));
						mat1dupe *= transform2D::Translate(31, baseY + right_moving);
						mat1dupe *= transform2D::Rotate(rot2);
						mat1dupe *= transform2D::Translate(-1.2f, -1.2f);
						RenderMesh2D(meshes["grayfilledsmall"], shaders["VertexColor"], mat1dupe);

						glm::mat3 mat2dupe = glm::mat3(1);
						mat2dupe *= transform2D::Translate(31 - 2.57f, baseY + 4.2f + right_moving);
						mat2dupe *= transform2D::Rotate(rot2);
						mat2dupe *= transform2D::Translate(-4.125f, -1.375f);
						RenderMesh2D(meshes["semicirclesmall"], shaders["VertexColor"], mat2dupe);

						count_the_cubes++;
						bumpers_poz[k] = count_the_cubes;
						k++;
					}

					else if (matrix_used[i][j] == 3) {
						glm::mat3 mat1 = glm::mat3(1);
						mat1 *= transform2D::Translate(-31, baseY + left_moving);
						mat1 *= transform2D::Scale(1.0f, left_scale);
						mat1 *= transform2D::Translate(31, -(baseY + left_moving));
						mat1 *= transform2D::Translate(-31, baseY + left_moving);
						mat1 *= transform2D::Rotate(rot);
						mat1 *= transform2D::Translate(-1.2f, -1.2f);
						RenderMesh2D(meshes["grayfilledsmall"], shaders["VertexColor"], mat1);

						glm::mat3 mat3 = glm::mat3(1);
						mat3 *= transform2D::Translate(-31 + 2.4f, baseY - 0.175f + left_moving);
						mat3 *= transform2D::Scale(1.0f, left_scale);
						mat3 *= transform2D::Translate(31 - 2.4f, -(baseY - 0.175f + left_moving));
						mat3 *= transform2D::Translate(-31 + 2.4f, baseY - 0.175f + left_moving);
						mat3 *= transform2D::Rotate(rot);
						mat3 *= transform2D::Translate(-1.2f, -1.2f);
						RenderMesh2D(meshes["darkgraycannonsmall"], shaders["VertexColor"], mat3);

						glm::mat3 mat2 = glm::mat3(1);
						mat2 *= transform2D::Translate(-31 + 2.3f, baseY - 2.15f + left_moving);
						mat2 *= transform2D::Rotate(rot);
						mat2 *= transform2D::Translate(-2.125f, -2.125f);
						RenderMesh2D(meshes["whitecannonsemicirclesmall"], shaders["VertexColor"], mat2);

						glm::mat3 mat4 = glm::mat3(1);
						mat4 *= transform2D::Translate(-31 + 6.3f, baseY + left_moving);
						mat4 *= transform2D::Scale(1.0f, left_scale);
						mat4 *= transform2D::Translate(31 - 6.3f, -(baseY + left_moving));
						mat4 *= transform2D::Translate(-31 + 6.3f, baseY + left_moving);
						mat4 *= transform2D::Rotate(rot);
						mat4 *= transform2D::Translate(-1.2f, -0.6f);
						RenderMesh2D(meshes["trapezshotcannonsmall"], shaders["VertexColor"], mat4);

						//dreapta ecranului
						glm::mat3 mat1dupe = glm::mat3(1);
						mat1dupe *= transform2D::Translate(31, baseY + right_moving);
						mat1dupe *= transform2D::Scale(1.0f, right_scale);
						mat1dupe *= transform2D::Translate(-31, -(baseY + right_moving));
						mat1dupe *= transform2D::Translate(31, baseY + right_moving);
						mat1dupe *= transform2D::Rotate(rot2);
						mat1dupe *= transform2D::Translate(-1.2f, -1.2f);
						RenderMesh2D(meshes["grayfilledsmall"], shaders["VertexColor"], mat1dupe);

						glm::mat3 mat3dupe = glm::mat3(1);
						mat3dupe *= transform2D::Translate(31 - 2.4f, baseY + 0.175f + right_moving); //2.40
						mat3dupe *= transform2D::Scale(1.0f, right_scale);
						mat3dupe *= transform2D::Translate(-31 + 2.4f, -(baseY + 0.175f + right_moving));
						mat3dupe *= transform2D::Translate(31 - 2.4f, baseY + 0.175f + right_moving);
						mat3dupe *= transform2D::Rotate(rot2);
						mat3dupe *= transform2D::Translate(-1.2f, -1.2f);
						RenderMesh2D(meshes["darkgraycannonsmall"], shaders["VertexColor"], mat3dupe);

						glm::mat3 mat2dupe = glm::mat3(1);
						mat2dupe *= transform2D::Translate(31 - 2.3f, baseY + 2.15f + right_moving);
						mat2dupe *= transform2D::Rotate(rot2);
						mat2dupe *= transform2D::Translate(-2.125f, -2.125f);
						RenderMesh2D(meshes["whitecannonsemicirclesmall"], shaders["VertexColor"], mat2dupe);

						glm::mat3 mat4dupe = glm::mat3(1);
						mat4dupe *= transform2D::Translate(31 - 6.3f, baseY + right_moving);
						mat4dupe *= transform2D::Scale(1.0f, right_scale);
						mat4dupe *= transform2D::Translate(-31 + 6.3f, -(baseY + right_moving));
						mat4dupe *= transform2D::Translate(31 - 6.3f, baseY + right_moving);
						mat4dupe *= transform2D::Rotate(rot2);
						mat4dupe *= transform2D::Translate(-1.2f, -0.6f);
						RenderMesh2D(meshes["trapezshotcannonsmall"], shaders["VertexColor"], mat4dupe);

						count_the_cubes++;
						cannon_poz[k2] = count_the_cubes;
						k2++;
					}
					counter++;
				}
			}
		}


		glm::mat3 mat5 = glm::mat3(1);
		mat5 *= transform2D::Translate(pingpongballox, pingpongballoy);
		RenderMesh2D(meshes["pingpongball"], shaders["VertexColor"], mat5);

		if (window->KeyHold(GLFW_KEY_W)) {
			left_moving += moving;
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			left_moving -= moving;
		}

		if (window->KeyHold(GLFW_KEY_UP)) {
			right_moving += moving;
		}

		if (window->KeyHold(GLFW_KEY_DOWN)) {
			right_moving -= moving;
		}

		if (originY + left_moving > 18.75f)
			left_moving = 3.75f;

		float new_min = -19.25f + (count_the_cubes - 1) * 2.4f;

		if (originY + left_moving < new_min)
			left_moving = new_min - 15;

		if (originY + right_moving > 18.75f)
			right_moving = 3.75f;

		if (originY + right_moving < new_min)
			right_moving = new_min - 15;

		pingpongballox += speedox * float(deltaTime);
		pingpongballoy += speedoy * float(deltaTime); //are radius = 1

		if (pingpongballox + 1 >= 34.65f) {
			pingpongballox = 0.0f;
			pingpongballoy = 0.0f;
			speedox = -30;
			speedoy = 5;
			score_left++;
		}

		if (pingpongballox - 1 <= -35.35f) {
			pingpongballox = 0.0f;
			pingpongballoy = 0.0f;
			speedox = 30;
			speedoy = 5;
			score_right++;
		}

		for (int t = 0; t < score_left; t++) {
			glm::mat3 redballmat = glm::mat3(1);
			redballmat *= transform2D::Translate(-38.7f, 25 - t * 2.5f);
			RenderMesh2D(meshes["redballpointleft"], shaders["VertexColor"], redballmat);
		}

		for (int t = 0; t < score_right; t++) {
			glm::mat3 blueballmat = glm::mat3(1);
			blueballmat *= transform2D::Translate(38, 25 - t * 2.5f);
			RenderMesh2D(meshes["blueballpointright"], shaders["VertexColor"], blueballmat);
		}

		if (score_right == 5) {
			blue_wins = 1;
		}

		if (score_left == 5) {
			red_wins = 1;
		}

		if (pingpongballoy + 1 >= 20) {
			pingpongballoy = 20 - 1;
			speedoy = -speedoy;
		}

		if (pingpongballoy - 1 <= -20) {
			pingpongballoy = -20 + 1;
			speedoy = -speedoy;
		}

		float left_shape_x = -31;
		float left_shape_width = 2.4f;
		float left_shape_height = 2.4f * count_the_cubes;
		float left_shape_y = (originY + left_moving) - left_shape_height / 2.0f;

		int coll = detect_collision_aabb(pingpongballox, pingpongballoy, 1, left_shape_x, left_shape_y, left_shape_width, left_shape_height);
		if (coll == 1) {
			float left_shape_center = left_shape_y + left_shape_height / 2.0f;
			float collision = (pingpongballoy - left_shape_center) / (left_shape_height / 2.0f);
			float v = sqrt(speedox * speedox + speedoy * speedoy);
			speedox = v * cos(collision);
			speedoy = v * sin(collision);
			pingpongballox = left_shape_x + left_shape_width + 0.1f;
			left_time_anim = durata_animatie;
		}

		float right_shape_x = 31;
		float right_shape_width = 2.4f;
		float right_shape_height = 2.4f * count_the_cubes;
		float right_shape_y = (originY + right_moving) - right_shape_height / 2.0f;

		int coll2 = detect_collision_aabb(pingpongballox, pingpongballoy, 1, right_shape_x, right_shape_y, right_shape_width, right_shape_height);
		if (coll2 == 1) {
			float right_shape_center = right_shape_y + right_shape_height / 2.0f;
			float collision2 = (pingpongballoy - right_shape_center) / (right_shape_height / 2.0f);
			float v = sqrt(speedox * speedox + speedoy * speedoy);
			speedox = -v * cos(collision2);
			speedoy = v * sin(collision2);
			pingpongballox = right_shape_x - right_shape_width - 1 - 0.1f;
			right_time_anim = durata_animatie;
		}

		for (int p = 0; p < 10; p++) {
			if (bumpers_poz[p] >= 0 && bumpers_poz[p] <= 10) {
				float left_bumper_x = -28.6f;
				float left_bumper_w = 2.4f;
				float left_bumper_h = 7.2f;
				int bumper_index = bumpers_poz[p];
				float bumper_center_y = originY + left_moving - 2.4f * bumper_index + 2.4f / 2.0f;
				float left_bumper_y = bumper_center_y - left_bumper_h / 2.0f;

				int coll3 = detect_collision_aabb(pingpongballox, pingpongballoy, 1, left_bumper_x, left_bumper_y, left_bumper_w, left_bumper_h);
				if (coll3 == 1) {
					float collision3 = (pingpongballoy - bumper_center_y) / (left_bumper_h / 2.0f);
					float v = sqrt(speedox * speedox + speedoy * speedoy);
					v *= 1.1;
					speedox = v * cos(collision3);
					speedoy = v * sin(collision3);
					pingpongballox = left_bumper_x + left_bumper_w + 0.1f;
					left_time_anim = durata_animatie;
				}

				float right_bumper_x = 28.6f;
				float right_bumper_w = 2.4f;
				float right_bumper_h = 7.2f;
				int bumper_index2 = bumpers_poz[p];
				float bumper_center_y2 = originY + right_moving - 2.4f * bumper_index2 + 2.4f / 2.0f;
				float right_bumper_y = bumper_center_y2 - right_bumper_h / 2.0f;

				int coll4 = detect_collision_aabb(pingpongballox, pingpongballoy, 1, right_bumper_x, right_bumper_y, right_bumper_w, right_bumper_h);
				if (coll4 == 1) {
					float collision4 = (pingpongballoy - bumper_center_y2) / (right_bumper_h / 2.0f);
					float v = sqrt(speedox * speedox + speedoy * speedoy);
					v *= 1.1;
					speedox = -v * cos(collision4);
					speedoy = v * sin(collision4);
					pingpongballox = right_bumper_x - right_bumper_w - 0.1f;
					right_time_anim = durata_animatie;
				}
			}
		}

		float left_scale = 1.0f;
		if (left_time_anim > 0.0f) {
			float t = left_time_anim / durata_animatie;
			left_scale = 1.0f + (scalare_animatie - 1.0f) * t;
		}

		float right_scale = 1.0f;
		if (right_time_anim > 0.0f) {
			float t = right_time_anim / durata_animatie;
			right_scale = 1.0f + (scalare_animatie - 1.0f) * t;
		}

	}

	else if (game_start == 1 && blue_wins == 1) {
		glm::mat3 bluemat = glm::mat3(1);
		bluemat *= transform2D::Translate(-55, -30);
		RenderMesh2D(meshes["bluefullscreen"], shaders["VertexColor"], bluemat);
		f = 1;
	}

	else if (game_start == 1 && red_wins == 1) {
		glm::mat3 redmat = glm::mat3(1);
		redmat *= transform2D::Translate(-55, -30);
		RenderMesh2D(meshes["redfullscreen"], shaders["VertexColor"], redmat);
		f = 1;
	}

	if (f == 1) {
		endscreen += deltaTimeSeconds;
		if (endscreen >= 3.0f) {
			window->Close();
		}
	}
}

void Tema1::FrameEnd()
{
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	glm::vec2 logic = ScreenToLogic(mouseX, mouseY);

	float modelX = logic.x - logicSpace.width / 2.0f;
	float modelY = logic.y - logicSpace.height / 2.0f;

	if (game_start == 1)
		return;

	if (button == 1) {

		glm::ivec2 resolution = window->GetResolution();

		//apas pe cannon
		if (max_count < max_cubes && (logic.x >= 7.45 && logic.x <= 11.7) && (logic.y >= 22.95 && logic.y <= 27.2)) {

			DragnDrop new_cube_cannon = { -43.75, -5.5, 3.5, 3.5, 0, 0, "grayfilled", false, false };
			new_cube_cannon.interacting = true;
			new_cube_cannon.offsetX = logic.x - new_cube_cannon.ox;
			new_cube_cannon.offsetY = logic.y - new_cube_cannon.oy;
			cube_cannon_vector.push_back(new_cube_cannon);
			current_object = &cube_cannon_vector.back();

			DragnDrop new_semicircle_cannon = { -41.6f, -3, 3.5f, 2, 0, 0, "whitecannonsemicircle", false, false };
			new_semicircle_cannon.interacting = true;
			new_semicircle_cannon.offsetX = logic.x - new_semicircle_cannon.ox;
			new_semicircle_cannon.offsetY = logic.y - new_semicircle_cannon.oy;
			semicircle_cannon_vector.push_back(new_semicircle_cannon);
			current_object2 = &semicircle_cannon_vector.back();

			DragnDrop new_rectangle_cannon = { -43.375, -2, 3.50, 8, 0, 0, "darkgraycannon", false, false };
			new_rectangle_cannon.interacting = true;
			new_rectangle_cannon.offsetX = logic.x - new_rectangle_cannon.ox;
			new_rectangle_cannon.offsetY = logic.y - new_rectangle_cannon.oy;
			rectangle_cannon_vector.push_back(new_rectangle_cannon);
			current_object3 = &rectangle_cannon_vector.back();

			DragnDrop new_trapez_cannon = { 0, 0, 4, 0.9f, 0, 0, "trapezshotcannon", false, false };
			new_trapez_cannon.interacting = true;
			new_trapez_cannon.offsetX = logic.x - new_trapez_cannon.ox;
			new_trapez_cannon.offsetY = logic.y - new_trapez_cannon.oy;
			trapez_cannon_vector.push_back(new_trapez_cannon);
			current_object4 = &trapez_cannon_vector.back();

		}

		//apas pe bumper
		if (max_count < max_cubes && (logic.x >= 7.45 && logic.x <= 11.7) && (logic.y >= 43.73 && logic.y <= 47.98)) {

			DragnDrop new_cube_bumper = { -43.75, 15, 3.5, 3.5, 0, 0, "grayfilled", false, false };
			new_cube_bumper.interacting = true;
			new_cube_bumper.offsetX = logic.x - new_cube_bumper.ox;
			new_cube_bumper.offsetY = logic.y - new_cube_bumper.oy;
			cube_bumper_vector.push_back(new_cube_bumper);
			current_object = &cube_bumper_vector.back();

			DragnDrop new_semicircle_bumper = { -41.75f, 19.20f, 12.75f, 4.25f, 0, 0, "semicircle", false, false };
			new_semicircle_bumper.interacting = true;
			new_semicircle_bumper.offsetX = logic.x - new_semicircle_bumper.ox;
			new_semicircle_bumper.offsetY = logic.y - new_semicircle_bumper.oy;
			semicircle_bumper_vector.push_back(new_semicircle_bumper);
			current_object2 = &semicircle_bumper_vector.back();


		}

		//apas pe bloc simplu
		if (max_count < max_cubes && (logic.x >= 7.45 && logic.x <= 11.7) && (logic.y >= 7.25 && logic.y <= 11.5)) {

			DragnDrop new_cube_basic = { -43.75, -21, 3.5, 3.5, 0, 0, "grayfilled", false, false };
			new_cube_basic.interacting = true;
			new_cube_basic.offsetX = logic.x - new_cube_basic.ox;
			new_cube_basic.offsetY = logic.y - new_cube_basic.oy;
			cube_basic_vector.push_back(new_cube_basic);
			current_object = &cube_basic_vector.back();

		}

		//apas pe butonul de start
		if ((modelX > 45 && modelX < 49.75 && modelY > 17 && modelY < 21.75) && pointInTriangle(modelX, modelY, 47.2375f, 19.375f, 49.75f, 21.75f, 49.75f, 17) == false && check == true) {
			game_start = 1;
		}

	}

	else if (button == 2) {

		float cube_center_x = logic.x - logicSpace.width / 2.0f;
		float cube_center_y = logic.y - logicSpace.height / 2.0f;

		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 9; j++) {
				if (cube_center_x >= -26.25 + i * 4.25 && cube_center_x <= -22 + i * 4.25 && cube_center_y >= 7.75 - j * 4.25 && cube_center_y <= 12 - j * 4.25) {

					if (matrix_used[j][i] == 1) {

						if (cannon_condition[j][i] == 1) {
							cannon_condition[j][i] = 0;
						}

						int copy_j = j + 1;
						int copy_i = i;
						int cannonflag = 0;
						int bumperflag = 0;
						while (copy_j <= 8) {
							if (matrix_used[copy_j][copy_i] == 3) {
								cannonflag = 1;
							}
							if (matrix_used[copy_j][copy_i] == 2) {
								bumperflag = 1;
							}
							if (matrix_used[copy_j][copy_i - 1] == 2) {
								bumperflag = 1;
							}
							if (matrix_used[copy_j][copy_i + 1] == 2) {
								bumperflag = 1;
							}
							copy_j++;
						}

						if (cannonflag == 1)
							matrix_used[j][i] = 5;
						else if (bumperflag == 1)
							matrix_used[j][i] = 4;
						else if (cannonflag == 0 && bumperflag == 0)
							matrix_used[j][i] = 0;

						max_count--;

						for (int k = 0; k < cube_basic_vector.size(); k++) {
							DragnDrop& cube = cube_basic_vector[k];

							float cx = cube.ox + logicSpace.width / 2.0f;
							float cy = cube.oy + logicSpace.height / 2.0f;

							if (logic.x >= cx && logic.x <= cx + 4.25 &&
								logic.y >= cy && logic.y <= cy + 4.25) {
								cube_basic_vector.erase(cube_basic_vector.begin() + k);
								break;
							}
						}
					}

					else if (matrix_used[j][i] == 2) {

						if (cannon_condition[j][i] == 1)
							cannon_condition[j][i] = 0;

						int copy_j = j + 1;
						int copy_i = i;
						int cannonflag = 0;
						int bumperflag = 0;
						while (copy_j <= 8) {
							if (matrix_used[copy_j][copy_i] == 3) {
								cannonflag = 1;
							}
							if (matrix_used[copy_j][copy_i] == 2) {
								bumperflag = 1;
							}
							if (matrix_used[copy_j][copy_i - 1] == 2) {
								bumperflag = 1;
							}
							if (matrix_used[copy_j][copy_i + 1] == 2) {
								bumperflag = 1;
							}
							copy_j++;
						}

						if (cannonflag == 1)
							matrix_used[j][i] = 5;
						else if (bumperflag == 1)
							matrix_used[j][i] = 4;
						else if (cannonflag == 0 && bumperflag == 0)
							matrix_used[j][i] = 0;

						int copy_j2 = j;
						int copy_i2 = i;
						int count = 0;
						while (copy_j2 >= 1 && count < 4) {
							if (cannon_condition[copy_j2 - 1 - count][copy_i2] == 1) {
								cannon_condition[copy_j2 - 1 - count][copy_i2] = 0;
							}
							if (cannon_condition[copy_j2 - 1 - count][copy_i2 - 1] == 1) {
								cannon_condition[copy_j2 - 1 - count][copy_i2 - 1] = 0;
							}
							if (cannon_condition[copy_j2 - 1 - count][copy_i2 + 1] == 1) {
								cannon_condition[copy_j2 - 1 - count][copy_i2 + 1] = 0;
							}
							if (matrix_used[copy_j2 - 1 - count][copy_i2] == 4) {
								matrix_used[copy_j2 - 1 - count][copy_i2] = 0;
							}
							if (matrix_used[copy_j2 - 1 - count][copy_i2 - 1] == 4) {
								matrix_used[copy_j2 - 1 - count][copy_i2 - 1] = 0;
							}
							if (matrix_used[copy_j2 - 1 - count][copy_i2 + 1] == 4) {
								matrix_used[copy_j2 - 1 - count][copy_i2 + 1] = 0;
							}
							copy_j2--;
							count++;
						}

						max_count--;

						for (int k = 0; k < cube_bumper_vector.size(); k++) {
							DragnDrop& cube = cube_bumper_vector[k];

							float cx = cube.ox + logicSpace.width / 2.0f;
							float cy = cube.oy + logicSpace.height / 2.0f;

							if (logic.x >= cx && logic.x <= cx + 4.25 &&
								logic.y >= cy && logic.y <= cy + 4.25) {
								cube_bumper_vector.erase(cube_bumper_vector.begin() + k);
								semicircle_bumper_vector.erase(semicircle_bumper_vector.begin() + k);
								break;
							}
						}
					}

					else if (matrix_used[j][i] == 3) {

						if (cannon_condition[j][i] == 1)
							cannon_condition[j][i] = 0;

						int copy_j = j + 1;
						int copy_i = i;
						int cannonflag = 0;
						int bumperflag = 0;
						while (copy_j <= 8) {
							if (matrix_used[copy_j][copy_i] == 3) {
								cannonflag = 1;
							}
							if (matrix_used[copy_j][copy_i] == 2) {
								bumperflag = 1;
							}
							if (matrix_used[copy_j][copy_i - 1] == 2) {
								bumperflag = 1;
							}
							if (matrix_used[copy_j][copy_i + 1] == 2) {
								bumperflag = 1;
							}
							copy_j++;
						}

						if (cannonflag == 1)
							matrix_used[j][i] = 5;
						else if (bumperflag == 1)
							matrix_used[j][i] = 4;
						else if (cannonflag == 0 && bumperflag == 0)
							matrix_used[j][i] = 0;

						int copy_j2 = j;
						int copy_i2 = i;
						while (copy_j2 >= 1) {
							if (cannon_condition[copy_j2 - 1][copy_i2] == 1) {
								cannon_condition[copy_j2 - 1][copy_i2] = 0;
							}
							if (matrix_used[copy_j2 - 1][copy_i2] == 5) {
								matrix_used[copy_j2 - 1][copy_i2] = 0;
							}
							copy_j2--;
						}

						max_count--;

						for (int k = 0; k < cube_cannon_vector.size(); k++) {
							DragnDrop& cube = cube_cannon_vector[k];

							float cx = cube.ox + logicSpace.width / 2.0f;
							float cy = cube.oy + logicSpace.height / 2.0f;

							if (logic.x >= cx && logic.x <= cx + 4.25 &&
								logic.y >= cy && logic.y <= cy + 4.25) {
								cube_cannon_vector.erase(cube_cannon_vector.begin() + k);
								semicircle_cannon_vector.erase(semicircle_cannon_vector.begin() + k);
								rectangle_cannon_vector.erase(rectangle_cannon_vector.begin() + k);
								trapez_cannon_vector.erase(trapez_cannon_vector.begin() + k);
								break;
							}
						}
					}
				}
			}
		}

		int start_dfs_i = -1;
		int start_dfs_j = -1;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 17; j++) {
				if (matrix_used[i][j] == 1 || matrix_used[i][j] == 2 || matrix_used[i][j] == 3) {
					start_dfs_i = i;
					start_dfs_j = j;
					break;
				}
			}
			if (start_dfs_i != -1)
				break;
		}

		int visited[9][17] = { 0 };

		DFS(start_dfs_i, start_dfs_j, visited, matrix_used);

		check = true;

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 17; j++) {
				if ((matrix_used[i][j] == 1 || matrix_used[i][j] == 2 || matrix_used[i][j] == 3) && visited[i][j] == 0) {
					check = false;
					break;
				}
			}
			if (check == false)
				break;
		}

		int flag_nocubes = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 17; j++) {
				if (cannon_condition[i][j] == 1)
					check = false;
				if (matrix_used[i][j] == 1 || matrix_used[i][j] == 2 || matrix_used[i][j] == 3)
					flag_nocubes = 1;
			}
		}

		if (flag_nocubes == 0)
			check = false;

	}

}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	//caz cannon
	if (current_object != nullptr && current_object2 != nullptr && current_object3 != nullptr && current_object4 != nullptr &&
		current_object->interacting == true && current_object2->interacting == true && current_object3->interacting == true &&
		current_object4->interacting == true) {

		glm::vec2 logic = ScreenToLogic(mouseX, mouseY);
		current_object->ox = logic.x - current_object->offsetX;
		current_object->oy = logic.y - current_object->offsetY;
		current_object2->ox = logic.x - current_object2->offsetX;
		current_object2->oy = logic.y - current_object2->offsetY;
		current_object3->ox = logic.x - current_object3->offsetX;
		current_object3->oy = logic.y - current_object3->offsetY;
		current_object4->ox = logic.x - current_object4->offsetX;
		current_object4->oy = logic.y - current_object4->offsetY;
	}

	//caz bumper
	else if (current_object != nullptr && current_object2 != nullptr && current_object->interacting == true && current_object2->interacting == true) {

		glm::vec2 logic = ScreenToLogic(mouseX, mouseY);
		current_object->ox = logic.x - current_object->offsetX;
		current_object->oy = logic.y - current_object->offsetY;
		current_object2->ox = logic.x - current_object2->offsetX;
		current_object2->oy = logic.y - current_object2->offsetY;
	}

	//caz bloc simplu
	else if (current_object != nullptr && current_object->interacting == true) {

		glm::vec2 logic = ScreenToLogic(mouseX, mouseY);
		current_object->ox = logic.x - current_object->offsetX;
		current_object->oy = logic.y - current_object->offsetY;
	}


}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	if (button == 1) {

		//cannon
		if (current_object != nullptr && current_object2 != nullptr && current_object3 != nullptr && current_object4 != nullptr && current_object->interacting == true && current_object2->interacting == true && current_object3->interacting == true && current_object4->interacting == true) {

			glm::vec2 logic = ScreenToLogic(mouseX, mouseY);

			float cube_center_x = logic.x - logicSpace.width / 2.0f;
			float cube_center_y = logic.y - logicSpace.height / 2.0f;

			int p = 0;


			for (int i = 0; i < 17; i++) {
				for (int j = 0; j < 9; j++) {

					if (cube_center_x >= -26.25 + i * 4.25 && cube_center_x <= -22 + i * 4.25 && cube_center_y >= 7.75 - j * 4.25 && cube_center_y <= 12 - j * 4.25) {

						if (matrix_used[j][i] == 1 || matrix_used[j][i] == 2 || matrix_used[j][i] == 3) {
							break;
						}

						if (matrix_used[j][i] == 4 || matrix_used[j][i] == 5) {
							cannon_condition[j][i] = 1;
						}

						matrix_used[j][i] = 3;

						int copy_j = j;
						int copy_i = i;
						while (copy_j >= 0) {
							if (matrix_used[copy_j][copy_i] == 0) {
								matrix_used[copy_j][copy_i] = 5;
							}
							else if (matrix_used[copy_j - 1][copy_i] == 1 || matrix_used[copy_j - 1][copy_i] == 2 || matrix_used[copy_j - 1][copy_i] == 3) {
								cannon_condition[copy_j - 1][copy_i] = 1;
							}
							copy_j--;
						}

						current_object->ox = -24.125f - 4.25f / 2 + i * 4.25f;
						current_object->oy = 9.875f - 4.25f / 2 - j * 4.25f;
						current_object2->ox = -24.125f + i * 4.25f;
						current_object2->oy = 9.875f - j * 4.25f;
						current_object3->ox = -24.125f - 3.50f / 2 + i * 4.25f;
						current_object3->oy = 11 - j * 4.25f;
						current_object4->ox = 17.50f + i * 4.25f;
						current_object4->oy = 13 - j * 4.25f;
						p = 1;

					}
				}
			}

			if (p == 0) {
				//daca nu a gasit un loc bun, il readuc in pozitia initiala
				current_object->ox = cube_cannon_fix.ox;
				current_object->oy = cube_cannon_fix.oy;
				current_object2->ox = semicircle_cannon_fix.ox;
				current_object2->oy = semicircle_cannon_fix.oy;
				current_object3->ox = rectagnle_cannon_long_fix.ox;
				current_object3->oy = rectagnle_cannon_long_fix.oy;
				current_object4->ox = trapez_cannon_fix.ox;
				current_object4->oy = trapez_cannon_fix.oy;
				max_count--;
			}

			current_object->interacting = false;
			current_object2->interacting = false;
			current_object3->interacting = false;
			current_object4->interacting = false;
			max_count++;
		}

		//bumper
		else if (current_object != nullptr && current_object2 != nullptr && current_object->interacting == true && current_object2->interacting == true) {


			glm::vec2 logic = ScreenToLogic(mouseX, mouseY);

			float cube_center_x = logic.x - logicSpace.width / 2.0f;
			float cube_center_y = logic.y - logicSpace.height / 2.0f;

			int p = 0;

			for (int i = 0; i < 17; i++) {
				for (int j = 0; j < 9; j++) {

					if (cube_center_x >= -26.25 + i * 4.25 && cube_center_x <= -22 + i * 4.25 && cube_center_y >= 7.75 - j * 4.25 && cube_center_y <= 12 - j * 4.25) {

						if (matrix_used[j][i] == 1 || matrix_used[j][i] == 2 || matrix_used[j][i] == 3) {
							break;
						}

						//daca il pun intr o pozitie invalida il marchez invalid
						if (matrix_used[j][i] == 4 || matrix_used[j][i] == 5) {
							cannon_condition[j][i] = 1;
						}

						current_object->ox = -24.125f - 4.25f / 2 + i * 4.25f;
						current_object->oy = 9.875f - 4.25f / 2 - j * 4.25f;
						current_object2->ox = -24.125f + i * 4.25f;
						current_object2->oy = 9.875f + 4.25f / 2 - j * 4.25f;
						p = 1;

						matrix_used[j][i] = 2;

						int copy_j = j;
						int copy_i = i;
						int count = 0;
						while (copy_j >= 1 && count < 4) {
							if (matrix_used[copy_j - 1][copy_i] == 1 || matrix_used[copy_j - 1][copy_i] == 2 || matrix_used[copy_j - 1][copy_i] == 3) {
								cannon_condition[copy_j - 1][copy_i] = 1;
							}
							if (matrix_used[copy_j - 1][copy_i - 1] == 1 || matrix_used[copy_j - 1][copy_i - 1] == 2 || matrix_used[copy_j - 1][copy_i - 1] == 3) {
								cannon_condition[copy_j - 1][copy_i - 1] = 1;
							}
							if (matrix_used[copy_j - 1][copy_i + 1] == 1 || matrix_used[copy_j - 1][copy_i + 1] == 2 || matrix_used[copy_j - 1][copy_i + 1] == 3) {
								cannon_condition[copy_j - 1][copy_i + 1] = 1;
							}
							copy_j--;
							count++;
						}


						if (j >= 1) {
							if (matrix_used[j - 1][i] == 0)
								matrix_used[j - 1][i] = 4;
							if (matrix_used[j - 1][i - 1] == 0)
								matrix_used[j - 1][i - 1] = 4;
							if (matrix_used[j - 1][i + 1] == 0)
								matrix_used[j - 1][i + 1] = 4;
						}


						if (j >= 2) {
							if (matrix_used[j - 2][i] == 0)
								matrix_used[j - 2][i] = 4;
							if (matrix_used[j - 2][i - 1] == 0)
								matrix_used[j - 2][i - 1] = 4;
							if (matrix_used[j - 2][i + 1] == 0)
								matrix_used[j - 2][i + 1] = 4;
						}


						if (j >= 3) {
							if (matrix_used[j - 3][i] == 0)
								matrix_used[j - 3][i] = 4;
							if (matrix_used[j - 3][i - 1] == 0)
								matrix_used[j - 3][i - 1] = 4;
							if (matrix_used[j - 3][i + 1] == 0)
								matrix_used[j - 3][i + 1] = 4;
						}


						if (j >= 4) {
							if (matrix_used[j - 4][i] == 0)
								matrix_used[j - 4][i] = 4;
							if (matrix_used[j - 4][i - 1] == 0)
								matrix_used[j - 4][i - 1] = 4;
							if (matrix_used[j - 4][i + 1] == 0)
								matrix_used[j - 4][i + 1] = 4;
						}
					}
				}
			}

			if (p == 0) {
				current_object->ox = cube_bumper_fix.ox;
				current_object->oy = cube_bumper_fix.oy;
				current_object2->ox = semicircle_bumper_fix.ox;
				current_object2->oy = semicircle_bumper_fix.oy;
				max_count--;
			}

			current_object->interacting = false;
			current_object2->interacting = false;
			max_count++;

		}

		//bloc simplu
		else if (current_object != nullptr && current_object->interacting == true) {

			glm::vec2 logic = ScreenToLogic(mouseX, mouseY);

			float cube_center_x = logic.x - logicSpace.width / 2.0f;
			float cube_center_y = logic.y - logicSpace.height / 2.0f;

			int p = 0;

			for (int i = 0; i < 17; i++) {
				for (int j = 0; j < 9; j++) {

					if (cube_center_x >= -26.25 + i * 4.25 && cube_center_x <= -22 + i * 4.25 && cube_center_y >= 7.75 - j * 4.25 && cube_center_y <= 12 - j * 4.25) {

						if (matrix_used[j][i] == 1 || matrix_used[j][i] == 2 || matrix_used[j][i] == 3)
							break;

						if (matrix_used[j][i] == 4 || matrix_used[j][i] == 5)
							cannon_condition[j][i] = 1;

						current_object->ox = -24.125f - 4.25f / 2 + i * 4.25f;
						current_object->oy = 9.875f - 4.25f / 2 - j * 4.25f;
						p = 1;
						matrix_used[j][i] = 1;

						int copy_j = j + 1;
						int copy_i = i;
						while (copy_j <= 8) {
							if (matrix_used[copy_j][copy_i] == 3 || matrix_used[copy_j][copy_i] == 2) {
								cannon_condition[j][i] = 1;
							}
							if (matrix_used[copy_j][copy_i - 1] == 2) {
								cannon_condition[j][i] = 1;
							}
							if (matrix_used[copy_j][copy_i + 1] == 2) {
								cannon_condition[j][i] = 1;
							}
							copy_j++;
						}
					}
				}
			}

			if (p == 0) {
				current_object->ox = cube_basic_fix.ox;
				current_object->oy = cube_basic_fix.oy;
				max_count--;
			}

			current_object->interacting = false;
			max_count++;
		}

		int start_dfs_i = -1;
		int start_dfs_j = -1;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 17; j++) {
				if (matrix_used[i][j] == 1 || matrix_used[i][j] == 2 || matrix_used[i][j] == 3) {
					start_dfs_i = i;
					start_dfs_j = j;
					break;
				}
			}
			if (start_dfs_i != -1)
				break;
		}

		int visited[9][17] = { 0 };

		DFS(start_dfs_i, start_dfs_j, visited, matrix_used);

		if (check == true) {


			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 17; j++) {
					if ((matrix_used[i][j] == 1 || matrix_used[i][j] == 2 || matrix_used[i][j] == 3) && visited[i][j] == 0) {
						check = false;
						break;
					}
				}
				if (check == false)
					break;
			}
		}

		else if (check == false) {

			int m = 0;

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 17; j++) {
					if ((matrix_used[i][j] == 1 || matrix_used[i][j] == 2 || matrix_used[i][j] == 3) && visited[i][j] == 0) {
						m = 1;
						break;
					}
				}
				if (m == 1)
					break;
			}
			if (m == 0)
				check = true;
		}

		int flag_nocubes = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 17; j++) {
				if (cannon_condition[i][j] == 1)
					check = false;
				if (matrix_used[i][j] == 1 || matrix_used[i][j] == 2 || matrix_used[i][j] == 3)
					flag_nocubes = 1;
			}
		}

		if (flag_nocubes == 0)
			check = false;

		bool check_vecini = true;

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 16; j++) {
				int a = matrix_used[i][j];
				int b = matrix_used[i][j + 1];

				if ((a == 2 && b == 2) ||
					(a == 3 && b == 3) ||
					(a == 2 && b == 3) ||
					(a == 3 && b == 2)) {
					check_vecini = false;
					break;
				}
			}
			if (!check_vecini) break;
		}

		if (check_vecini == false)
			check = false;
	}
}