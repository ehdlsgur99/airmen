#pragma once

#include "Define.h"

#include <windows.h>		//--- 윈도우 헤더 파일
#include <tchar.h>
#include <atlimage.h>
#include <string>
#include <mmsystem.h>
#include "time.h"
#include "stdlib.h"



#include <vector>

#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "winmm.lib")

#include "Singleton.h"
#include "System.h"
#include "UserInfo.h"


#include "GameObject.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "Scene.h"
#include "GraphicManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SoundManager.h"

#include "enumData.h"



using namespace std;


// 새로 추가할 오브젝트 등등은 여기에..
#include "PlayerUI.h"
#include "Tail.h"
#include "PlayerBar.h"
#include "Player.h"
#include "GameBG.h"
#include "Camera.h"
#include "Npc.h"
#include "Monster.h"
#include "MonsterControl.h"
#include "VillageMG.h"
#include "Button.h"


// 새로 추가한 scene 들은 여기에 추가 합시다.
#include "TestScene.h"
#include "GameScene.h"
#include "VillageScene.h"
#include "IntroScene.h"
#include "EndScene.h"
#include "PVPScene.h"
//#include "Client.h"