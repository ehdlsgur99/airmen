#pragma once

#include <windows.h>		//--- 윈도우 헤더 파일
#include <tchar.h>
#include <atlimage.h>
#include <string>
#include <mmsystem.h>

#include <vector>

#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "winmm.lib")

#include "Singleton.h"
#include "System.h"

#include "GameObject.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "Scene.h"
#include "GraphicManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SoundManager.h"

#include "enumData.h"
#include "Button.h"

using namespace std;

// 새로 추가할 오브젝트 등등은 여기에..
#include "Player.h"


// 새로 추가한 scene 들은 여기에 추가 합시다.
#include "TestScene.h"
#include "GameScene.h"
#include "VillageScene.h"

