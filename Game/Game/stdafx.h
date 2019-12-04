#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>
#include <map>
#include <functional>
#include <algorithm>
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include "NoncCopyable/NonCopyable.h"
//Effekseer�̃w�b�_�[�t�@�C�����C���N���[�h
#include "Effekseer.h"
#include "EffekseerRendererDX11.h"
//DirectXTK�̃C���N���[�h�t�@�C���B
#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"

//�Q�[���I�u�W�F�N�g�̃C���N���[�h
#include "gameObject/GameObjectManager.h"
#include "gameObject/IGameObject.h"

#include "HID/Pad.h"
#include "math/Vector.h"
#include "math/Matrix.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "graphics/GraphicsEngine.h"
#include "physics/Physics.h"

#include "graphics/SkinModel.h"
#include "graphics/Skeleton.h"

#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "level/Level.h"

#include "graphics/GameFont.h"
#include "Timer.h"
const float FRAME_BUFFER_W = 1280.0f;				//�t���[���o�b�t�@�̕��B
const float FRAME_BUFFER_H = 720.0f;				//�t���[���o�b�t�@�̍����B
using namespace GameEngine;
static const int MAX_BONE = 512;	//!<�{�[���̍ő吔�B