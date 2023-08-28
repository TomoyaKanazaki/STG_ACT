//==========================================
//
//  プレイヤークラス(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <windows.h>
#include "player.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "effect.h"
#include "sound.h"
#include "debugproc.h"
#include "camera.h"
#include "model.h"
#include "shadow.h"
#include "field.h"
#include "object_fan.h"
#include "collision.h"
#include "bullet.h"
#include "motion.h"
#include "collision.h"
#include "layer.h"
#include "gamemanager.h"
#include "orbit.h"
#include "particle.h"
#include "camera.h"

//==========================================
//  マクロ定義
//==========================================
#define PLAYER_SPEED (1.0f) //プレイヤーの移動速度(キーボード)

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CPlayer::mc_fExplosion = 5000.0f;

//==========================================
//  コンストラクタ
//==========================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_nLife = 0;
	m_nDeadCounter = 0;
	m_fSpeed = 0.0f;
	m_fAngle = 0.0f;
	m_bRand = true;
	m_bDead = false;
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pShadow = NULL;
	m_pMotion = NULL;
	m_orbit = NULL;
}

//==========================================
//  デストラクタ
//==========================================
CPlayer::~CPlayer()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CPlayer::Init(void)
{
	//タイプの設定
	SetType(TYPE_PLAYER);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	if (m_ppModel == NULL)
	{
		m_ppModel = new CModel*[m_pLayer->nNumModel];
	}

	//必要なモデルを生成
	for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
	{
		//空にする
		m_ppModel[nCnt] = NULL;

		//親が存在しない場合
		if (m_pLayer->pParentID[nCnt] == -1)
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt]);
		}
		else
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt], m_ppModel[m_pLayer->pParentID[nCnt]]);
		}
	}

	//モーション情報の生成
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
	}
	
	//モーション情報にモデルを追加する
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_SHOT);

	//影を生成
	if (m_pShadow == NULL)
	{
		m_pShadow = CShadow::Create(m_pos, m_size, m_rot);
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CPlayer::Uninit(void)
{
	//モデルのポインタを破棄
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Uninit();
				m_ppModel[nCnt] = NULL;
			}
		}
		delete[] m_ppModel;
		m_ppModel = NULL;
	}

	//モーションのポインタを破棄
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//軌跡を破棄
	if (m_orbit != NULL)
	{
		m_orbit->Uninit();
		delete m_orbit;
		m_orbit = NULL;
	}

	//影のポインタを破棄
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
	}

	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CPlayer::Update(void)
{
	//死亡確認
	if (m_bDead)
	{
		//死亡カウンターの加算
		m_nDeadCounter++;

		//死亡から一定時間経過していたら蘇生する
		if (m_nDeadCounter >= 60)
		{
			m_bDead = false;
			m_nDeadCounter = 0;
			m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Explosion();
			if (m_pShadow == NULL)
			{
				m_pShadow = CShadow::Create(m_pos, m_size, m_rot);
			}
			return;
		}
		else
		{
			return;
		}
	}

	//死亡判定
	if (m_pos.y < -1000.0f || Collision::CollisionEnemy(m_pos, 30.0f, false))
	{
		m_nLife--;
		m_bDead = true;
		if (m_pShadow != NULL)
		{
			m_pShadow->Uninit();
			m_pShadow = NULL;
		}
		if (m_orbit != NULL)
		{
			m_orbit->Uninit();
			delete m_orbit;
			m_orbit = NULL;
		}
		CGameManager::SetState(CGameManager::NONE);
	}

	//前回座標の保存
	m_oldPos = m_pos;

	//前回角度の保存
	m_oldRot = m_rot;

	//着地状態を取得
	m_bRand = CGameManager::GetFan()->OnMesh(m_pos);

	//存在位置の判定
	if (m_bRand)
	{
		//移動処理
		Move();
	}
	else
	{
		//落下
		m_move.y += -0.5f;
		if (m_pShadow != NULL)
		{
			m_pShadow->Uninit();
			m_pShadow = NULL;
		}
	}

	//移動量の適用
	m_pos += m_move;

	//実体を移動する
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				if (m_ppModel[nCnt]->GetParent() == NULL)
				{
					m_ppModel[nCnt]->SetTransform(m_pos, m_rot);
				}
			}
		}
	}

	//傾ける
	Slop();

	//腕を回す
	Swing();

	//腕を回す
	Aiming();

	//モーションを更新する
	m_pMotion->Update();

	//攻撃
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
	{
		Shot();
	}

	//軌跡の生成、削除
	if (CManager::GetMouse()->GetTrigger(CMouse::BUTTON_RIGHT))
	{
		if (m_orbit == NULL)
		{
			m_orbit = COrbit::Create(m_ppModel[4], D3DXCOLOR(0.0f, 1.0f, 0.1f, 0.7f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-200.0f, 0.0f, 0.0f), 10);
		}
	}
	else if (CManager::GetMouse()->GetRelease(CMouse::BUTTON_RIGHT))
	{
		if (m_orbit != NULL)
		{
			m_orbit->Uninit();
			delete m_orbit;
			m_orbit = NULL;
		}
	}

	//影の情報を更新する
	if (m_pShadow != NULL)
	{
		m_pShadow->SetTransform(m_pos, m_rot);
	}

	//大人の壁
	if (m_pos.z > 130.0f)
	{
		m_pos.z = 130.0f;
	}

	//デバッグ表示
	CManager::GetDebugProc()->Print("プレイヤー座標 : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
	CManager::GetDebugProc()->Print("プレイヤー方向 : ( %f, %f, %f )\n", m_rot.x, m_rot.y, m_rot.z);
	CManager::GetDebugProc()->Print("プレイヤー移動量 : ( %f, %f, %f )\n", m_move.x, m_move.y, m_move.z);
	CManager::GetDebugProc()->Print("プレイヤー体力 : %d\n", m_nLife);
}

//==========================================
//  描画処理
//==========================================
void CPlayer::Draw()
{

}

//==========================================
//  オブジェクト生成処理
//==========================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CPlayer *pPlayer = NULL;

	//NULLチェック
	if (pPlayer == NULL)
	{
		//メモリを確保
		pPlayer = new CPlayer;
	}

	//各種情報の保存
	pPlayer->m_pos = pos;
	pPlayer->m_size = size;
	pPlayer->m_rot = rot;

	//初期化
	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	//ポインタを返す
	return pPlayer;
}

//==========================================
//  移動処理
//==========================================
void CPlayer::Move(void)
{
	//慣性による移動の停止
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//移動量の取得
	D3DXVECTOR3 move = CManager::GetKeyboard()->GetWASD();

	//移動量を適用
	m_move += move;
}

//==========================================
//  移動方向に傾ける
//==========================================
void CPlayer::Slop(void)
{
	//計算用変数宣言
	float rot = m_rot.y + D3DX_PI;
	D3DXVECTOR3 move = m_move;

	//Y軸の補正
	move.x = m_move.z * cosf(rot) + m_move.x * sinf(rot);
	move.z = m_move.z * sinf(rot) + -m_move.x * cosf(rot);

	//角度を算出
	m_rot.x = atan2f(-move.x, 30.0f);
	m_rot.z = atan2f(-move.z, 30.0f);
}

//==========================================
//  射撃
//==========================================
void CPlayer::Shot(void)
{
	//弾の発射位置を算出
	D3DXVECTOR3 BulletPos = D3DXVECTOR3
	(
		m_ppModel[3]->GetMtx()._41,
		m_ppModel[3]->GetMtx()._42,
		m_ppModel[3]->GetMtx()._43
	);

	//カメラの注視点を取得
	D3DXVECTOR3 vecPosR = CGameManager::GetCamera()->GetPosR();

	//移動量を算出
	D3DXVECTOR3 BulletMove = vecPosR - BulletPos;
	BulletMove.y = 0.0f;
	D3DXVec3Normalize(&BulletMove, &BulletMove);
	BulletMove *= 5.0f;

	//弾の生成
	CBullet::Create(BulletPos, m_size * 0.5f, BulletMove, CBullet::PLAYER, CBullet::HOMING_BULLET);
}

//==========================================
//  復活時に爆発して敵を倒す処理
//==========================================
void CPlayer::Explosion(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//自分のアドレスを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY || pObj->GetType() == CObject::TYPE_BULLET) //敵の場合
			{
				//近くにいるかの判定
				D3DXVECTOR3 vecToObj = m_pos - pObj->GetPos();
				float fLengh = (vecToObj.x * vecToObj.x) + (vecToObj.z * vecToObj.z);
				if (fLengh < mc_fExplosion * mc_fExplosion)
				{
					//殺す
					pObj->Uninit();
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}

//==========================================
//  腕を振る処理
//==========================================
void CPlayer::Swing(void)
{
	//マウスの横方向の移動量を取得する
	float fMove = CManager::GetMouse()->GetMouseMove().x;

	//角度を取得
	D3DXVECTOR3 rot = m_ppModel[4]->GetRot();

	//腕の角度を変える
	rot.y += -fMove;

	//角度の補正
	if (rot.y < -2.7f)
	{
		rot.y = -2.7f;
	}
	if (rot.y > 0.0f)
	{
		rot.y = 0.0f;
	}

	//角度を適用
	m_ppModel[4]->SetRot(rot);
}

//==========================================
//  狙う処理
//==========================================
void CPlayer::Aiming(void)
{
	//ローカル変数宣言
	D3DXMATRIX mtx = m_ppModel[3]->GetMtx();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX mtxParent; //親マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtx);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_ppModel[3]->GetPos().x, m_ppModel[3]->GetPos().y, m_ppModel[3]->GetPos().z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	//親マトリックスの設定
	mtxParent = m_ppModel[3]->GetParent()->GetMtx();

	//ワールドマトリックスと親マトリックスをかけ合わせる
	D3DXMatrixMultiply
	(
		&mtx,
		&mtx,
		&mtxParent
	);

	//座標を抽出
	D3DXVECTOR3 pos = D3DXVECTOR3(mtx._41, mtx._42, mtx._43);

	//カメラの注視点を取得
	D3DXVECTOR3 rotCamera = CGameManager::GetCamera()->GetRot();

	//モデルの角度を取得
	D3DXVECTOR3 rot = m_ppModel[3]->GetRot();
	rot.y = rotCamera.y;

	//角度を適用
	m_ppModel[3]->SetRot(rot);
}
