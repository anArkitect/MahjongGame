#pragma once

#include <unordered_map>
#include <string>
#include <algorithm>

#include <GL/glew.h>

#include "LoadTexture.h"


const int TILE_NR = 64;

static int tileSelection = 0;

static const std::string tile_vs_path("./shaders/zc_explode_vs.glsl");
static const std::string tile_gs_path("./shaders/zc_explode_gs.glsl");
static const std::string tile_fs_path("./shaders/zc_explode_fs.glsl");

std::vector<glm::vec3> tilePos =
{
	{ -1.2f,  1.75f,  0.0f },{ -0.6f,  1.75f,  0.0f },{ 0.0f,  1.75f,  0.0f },{ 0.6f,  1.75f,  0.0f },{ 1.2f,  1.75f,  0.0f },{ 1.8f,  1.75f,  0.0f },{ 2.4f,  1.75f,  0.0f },{ 3.0f,  1.75f,  0.0f },
	{ -1.2f,  1.25f,  0.0f },{ -0.6f,  1.25f,  0.0f },{ 0.0f,  1.25f,  0.0f },{ 0.6f,  1.25f,  0.0f },{ 1.2f,  1.25f,  0.0f },{ 1.8f,  1.25f,  0.0f },{ 2.4f,  1.25f,  0.0f },{ 3.0f,  1.25f,  0.0f },
	{ -1.2f,  0.75f,  0.0f },{ -0.6f,  0.75f,  0.0f },{ 0.0f,  0.75f,  0.0f },{ 0.6f,  0.75f,  0.0f },{ 1.2f,  0.75f,  0.0f },{ 1.8f,  0.75f,  0.0f },{ 2.4f,  0.75f,  0.0f },{ 3.0f,  0.75f,  0.0f },
	{ -1.2f,  0.25f,  0.0f },{ -0.6f,  0.25f,  0.0f },{ 0.0f,  0.25f,  0.0f },{ 0.6f,  0.25f,  0.0f },{ 1.2f,  0.25f,  0.0f },{ 1.8f,  0.25f,  0.0f },{ 2.4f,  0.25f,  0.0f },{ 3.0f,  0.25f,  0.0f },
	{ -1.2f, -0.25f,  0.0f },{ -0.6f, -0.25f,  0.0f },{ 0.0f, -0.25f,  0.0f },{ 0.6f, -0.25f,  0.0f },{ 1.2f, -0.25f,  0.0f },{ 1.8f, -0.25f,  0.0f },{ 2.4f, -0.25f,  0.0f },{ 3.0f, -0.25f,  0.0f },
	{ -1.2f, -0.75f,  0.0f },{ -0.6f, -0.75f,  0.0f },{ 0.0f, -0.75f,  0.0f },{ 0.6f, -0.75f,  0.0f },{ 1.2f, -0.75f,  0.0f },{ 1.8f, -0.75f,  0.0f },{ 2.4f, -0.75f,  0.0f },{ 3.0f, -0.75f,  0.0f },
	{ -1.2f, -1.25f,  0.0f },{ -0.6f, -1.25f,  0.0f },{ 0.0f, -1.25f,  0.0f },{ 0.6f, -1.25f,  0.0f },{ 1.2f, -1.25f,  0.0f },{ 1.8f, -1.25f,  0.0f },{ 2.4f, -1.25f,  0.0f },{ 3.0f, -1.25f,  0.0f },
	{ -1.2f, -1.75f,  0.0f },{ -0.6f, -1.75f,  0.0f },{ 0.0f, -1.75f,  0.0f },{ 0.6f, -1.75f,  0.0f },{ 1.2f, -1.75f,  0.0f },{ 1.8f, -1.75f,  0.0f },{ 2.4f, -1.75f,  0.0f },{ 3.0f, -1.75f,  0.0f },
};


std::vector<glm::vec3> spotLightPos =
{
	{ -1.2f,  1.75f,  3.0f },{ -0.6f,  1.75f,  0.0f },{ 0.0f,  1.75f,  0.0f },{ 0.6f,  1.75f,  0.0f },{ 1.2f,  1.75f,  0.0f },{ 1.8f,  1.75f,  0.0f },{ 2.4f,  1.75f,  0.0f },{ 3.0f,  1.75f,  0.0f },
	{ -1.2f,  1.25f,  0.0f },{ -0.6f,  1.25f,  0.0f },{ 0.0f,  1.25f,  0.0f },{ 0.6f,  1.25f,  0.0f },{ 1.2f,  1.25f,  0.0f },{ 1.8f,  1.25f,  0.0f },{ 2.4f,  1.25f,  0.0f },{ 3.0f,  1.25f,  0.0f },
	{ -1.2f,  0.75f,  0.0f },{ -0.6f,  0.75f,  0.0f },{ 0.0f,  0.75f,  0.0f },{ 0.6f,  0.75f,  0.0f },{ 1.2f,  0.75f,  0.0f },{ 1.8f,  0.75f,  0.0f },{ 2.4f,  0.75f,  0.0f },{ 3.0f,  0.75f,  0.0f },
	{ -1.2f,  0.25f,  0.0f },{ -0.6f,  0.25f,  0.0f },{ 0.0f,  0.25f,  0.0f },{ 0.6f,  0.25f,  0.0f },{ 1.2f,  0.25f,  0.0f },{ 1.8f,  0.25f,  0.0f },{ 2.4f,  0.25f,  0.0f },{ 3.0f,  0.25f,  0.0f },
	{ -1.2f, -0.25f,  0.0f },{ -0.6f, -0.25f,  0.0f },{ 0.0f, -0.25f,  0.0f },{ 0.6f, -0.25f,  0.0f },{ 1.2f, -0.25f,  0.0f },{ 1.8f, -0.25f,  0.0f },{ 2.4f, -0.25f,  0.0f },{ 3.0f, -0.25f,  0.0f },
	{ -1.2f, -0.75f,  0.0f },{ -0.6f, -0.75f,  0.0f },{ 0.0f, -0.75f,  0.0f },{ 0.6f, -0.75f,  0.0f },{ 1.2f, -0.75f,  0.0f },{ 1.8f, -0.75f,  0.0f },{ 2.4f, -0.75f,  0.0f },{ 3.0f, -0.75f,  0.0f },
	{ -1.2f, -1.25f,  0.0f },{ -0.6f, -1.25f,  0.0f },{ 0.0f, -1.25f,  0.0f },{ 0.6f, -1.25f,  0.0f },{ 1.2f, -1.25f,  0.0f },{ 1.8f, -1.25f,  0.0f },{ 2.4f, -1.25f,  0.0f },{ 3.0f, -1.25f,  0.0f },
	{ -1.2f, -1.75f,  0.0f },{ -0.6f, -1.75f,  0.0f },{ 0.0f, -1.75f,  0.0f },{ 0.6f, -1.75f,  0.0f },{ 1.2f, -1.75f,  0.0f },{ 1.8f, -1.75f,  0.0f },{ 2.4f, -1.75f,  0.0f },{ 3.0f, -1.75f,  0.0f },
};


//Mahjong files and IDs
GLuint tileShaderPrograms[TILE_NR];

std::unordered_map<std::string, std::string> mesh_texture;
static std::vector<std::string> tileNames =
{
	"assets/Amago0.3ds", "assets/Amago0.3ds", "assets/Amemasu0.3ds", "assets/Amemasu0.3ds", "assets/Angel0.3ds", "assets/Angel0.3ds", "assets/AngelShark0.3ds", "assets/AngelShark0.3ds",
	
	"assets/AsiaArowana0.3ds", "assets/AsiaArowana0.3ds", "assets/Ayu0.3ds", "assets/Ayu0.3ds", "assets/Bandouiruka0.3ds", "assets/Bandouiruka0.3ds", "assets/Barramundi0.3ds", "assets/Barramundi0.3ds",
	
	"assets/Benizake0.3ds", "assets/Benizake0.3ds", "assets/Blackbass0.3ds", "assets/Blackbass0.3ds", "assets/Bluegill0.3ds", "assets/Bluegill0.3ds", "assets/BlueTang0.3ds", "assets/BlueTang0.3ds",
	
	"assets/Bocaccio0.3ds", "assets/Bocaccio0.3ds", "assets/Bora0.3ds", "assets/Bora0.3ds", "assets/BrownTrout0.3ds", "assets/BrownTrout0.3ds", "assets/Kuromaguro0.3ds", "assets/Kuromaguro0.3ds",
	
	"assets/Chinook0.3ds", "assets/Chinook0.3ds", "assets/DemeKin0.3ds", "assets/DemeKin0.3ds", "assets/Dozyou0.3ds", "assets/Dozyou0.3ds", "assets/GuppyBlueGrass0.3ds", "assets/GuppyBlueGrass0.3ds",
	
	"assets/HariyoM0.3ds", "assets/HariyoM0.3ds", "assets/MangroveJack0.3ds", "assets/MangroveJack0.3ds", "assets/Hera0.3ds", "assets/Hera0.3ds", "assets/Manbou0.3ds", "assets/Manbou0.3ds",
	
	"assets/Kamuruti0.3ds", "assets/Kamuruti0.3ds", "assets/Katuo0.3ds", "assets/Katuo0.3ds", "assets/Kazika0.3ds", "assets/Kazika0.3ds", "assets/KelpBass0.3ds", "assets/KelpBass0.3ds",
	
	"assets/Kihada0.3ds", "assets/Kihada0.3ds", "assets/Koi0.3ds", "assets/Koi0.3ds", "assets/Kumanomi0.3ds", "assets/Kumanomi0.3ds", "assets/Zatou0.3ds", "assets/Zatou0.3ds",
};

MeshData tileData[TILE_NR];

std::string textureNames[TILE_NR] =
{
	"assets/AmagoT.bmp", "assets/AmagoT.bmp", "assets/AmemasT.bmp", "assets/AmemasT.bmp", "assets/AngelT.bmp", "assets/AngelT.bmp", "assets/AngelST.bmp", "assets/AngelST.bmp",
	
	"assets/AsiaArT.bmp", "assets/AsiaArT.bmp", "assets/AyuT.bmp", "assets/AyuT.bmp", "assets/BandouT.bmp", "assets/BandouT.bmp", "assets/BarramT.bmp", "assets/BarramT.bmp",
	
	"assets/BenizaT.bmp", "assets/BenizaT.bmp", "assets/BlackbT.bmp", "assets/BlackbT.bmp", "assets/BluegiT.bmp", "assets/BluegiT.bmp", "assets/BlueTaT.bmp", "assets/BlueTaT.bmp",
	
	"assets/BocaccT.bmp", "assets/BocaccT.bmp", "assets/BoraT.bmp", "assets/BoraT.bmp", "assets/BrownTT.bmp", "assets/BrownTT.bmp", "assets/KuromaT.bmp", "assets/KuromaT.bmp",
	
	"assets/ChinooT.bmp", "assets/ChinooT.bmp", "assets/DemeKiT.bmp", "assets/DemeKiT.bmp", "assets/DozyouT.bmp", "assets/DozyouT.bmp", "assets/GuppyBT.bmp", "assets/GuppyBT.bmp",
	
	"assets/HariyoT.bmp", "assets/HariyoT.bmp", "assets/MangroT.bmp", "assets/MangroT.bmp", "assets/HeraT.bmp", "assets/HeraT.bmp", "assets/ManbouT.bmp", "assets/ManbouT.bmp",
	
	"assets/KamuruT.bmp", "assets/KamuruT.bmp", "assets/KatuoT.bmp", "assets/KatuoT.bmp", "assets/KazikaT.bmp", "assets/KazikaT.bmp", "assets/KelpBaT.bmp", "assets/KelpBaT.bmp",
	
	"assets/KihadaT.bmp", "assets/KihadaT.bmp", "assets/KoiT.bmp", "assets/KoiT.bmp", "assets/KumanoT.bmp", "assets/KumanoT.bmp", "assets/ZatouT.bmp", "assets/ZatouT.bmp",
};

GLuint textureIDs[TILE_NR] = 
{
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
};

