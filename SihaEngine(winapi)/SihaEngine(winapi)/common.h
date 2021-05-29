#pragma once

#include <windows.h>		//--- ������ ��� ����
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

// ���� �߰��� ������Ʈ ����� ���⿡..
#include "Player.h"


// ���� �߰��� scene ���� ���⿡ �߰� �սô�.
#include "TestScene.h"
#include "GameScene.h"
#include "VillageScene.h"

