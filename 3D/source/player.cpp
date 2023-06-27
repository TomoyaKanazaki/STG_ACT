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
#include "object_mesh.h"
#include "collision.h"

//==========================================
//  マクロ定義
//==========================================
#define PLAYER_SPEED (1.0f) //プレイヤーの移動速度(キーボード)
#define TXTFILENAME_PLAYER "data\\TXT\\PlayerData.txt" //プレイヤー情報を持ったテキストファイルのパス
#define SHARE_PASS_PLAYER "data\\MODEL\\Player\\" //全てのプレイヤーモデルファイルに共通する相対パス

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
	m_apModel = NULL;
	m_bRand = true;
	m_bDead = false;
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
HRESULT CPlayer::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//各種情報の保存
	m_pos = pos;
	m_size = size;
	m_rot = rot;

	//タイプの設定
	SetType(TYPE_PLAYER);

	//実体を生成
	Load();

	//影を生成
	m_pShadow = CShadow::Create(m_pos, m_size, m_rot);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CPlayer::Uninit(void)
{
	if (m_apModel != NULL)
	{
		delete m_apModel;
		m_apModel = NULL;
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
		}
		else
		{
			return;
		}
	}

	//着地状態を取得
	m_bRand = CManager::GetMesh()->OnMesh(m_pos);

	//前回座標の保存
	D3DXVECTOR3 m_oldPos = m_pos;

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
		CManager::GetDebugProc()->Print("\n\n\n外に出ている\n");
	}

	//移動量の適用
	m_pos += m_move;

	//回転処理
	Rotate();

	//エフェクトを呼び出す
	CEffect::Create(m_pos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), m_rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100);

	m_apModel[0]->SetTransform(m_pos, m_rot);

	//影の情報を更新する
	m_pShadow->SetTransform(m_pos, m_rot);
	
	//死亡判定
	if (m_pos.y < -500.0f)
	{
		m_nLife--;
		m_bDead = true;
	}

	//デバッグ表示
	CManager::GetDebugProc()->Print("\n\n\nプレイヤー座標 : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
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

	//初期化
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, size, rot);
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
	m_move += CManager::GetKeyboard()->GetWASD();
}

//==========================================
//  回転処理
//==========================================
void CPlayer::Rotate(void)
{
	//マウスカーソル位置の取得
	D3DXVECTOR2 CursorPos = CManager::GetMouse()->GetCursor();

	//プレイヤー方向の取得
	m_fAngle = atan2f(-CursorPos.x, CursorPos.y);

	//方向転換用変数
	float fRotMove, fRotDest, fRotDiff;

	//現在の角度と目的の角度の差分を計算
	fRotMove = m_rot.y;
	fRotDest = m_fAngle;
	fRotDiff = fRotDest - fRotMove;

	//角度の補正
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= D3DX_PI * 2.0f;
	}
	else if (fRotDiff <= -D3DX_PI)
	{
		fRotDiff += D3DX_PI * 2.0f;
	}

	//方向転換の慣性
	fRotMove += fRotDiff * 0.5f;

	//角度の補正
	if (fRotMove > D3DX_PI)
	{
		fRotMove -= D3DX_PI * 2.0f;
	}
	else if (fRotMove <= -D3DX_PI)
	{
		fRotMove += D3DX_PI * 2.0f;
	}

	//方向を適用する
	m_rot.y = fRotMove;
}

//==========================================
//  プレイヤー情報の読み込み
//==========================================
void CPlayer::Load(void)
{
	//ローカル変数宣言
	FILE *pFile; //ファイル名
	char aStr[256]; //不要な文字列の記録用

	//ファイルを読み取り専用で開く
	pFile = fopen(TXTFILENAME_PLAYER, "r");

	if (pFile != NULL)
	{
		//不要な文字列の読み込み
		for (int nCntDiscard = 0; nCntDiscard < 13; nCntDiscard++)
		{
			fscanf(pFile, "%s", &aStr[0]);
		}

		//モデル数の取得
		fscanf(pFile, "%d", &m_nNumModel);

		//モデルが存在する場合
		if (m_nNumModel > 0)
		{
			//必要なメモリを確保する
			if (m_apModel == NULL)
			{
				m_apModel = new CModel*[m_nNumModel];
			}
		}

		//メモリを確保した場合
		if (m_apModel != NULL)
		{
			//不要な文字列の読み込み
			for (int nCntDiscard = 0; nCntDiscard < 4; nCntDiscard++)
			{
				fscanf(pFile, "%s", &aStr[0]);
			}

			//各モデルを生成する
			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				//モデル生成用変数
				D3DXVECTOR3 pos, size = D3DXVECTOR3(0.0f, 5.0f, 0.0f), rot;
				int nModelID, nParentID;

				//不要な文字列の読み込み
				for (int nCntDiscard = 0; nCntDiscard < 3; nCntDiscard++)
				{
					fscanf(pFile, "%s", &aStr[0]);
				}

				//位置情報を取得
				fscanf(pFile, "%f", &pos.x); fscanf(pFile, "%f", &pos.y); fscanf(pFile, "%f", &pos.z);

				//不要な文字列の読み込み
				fscanf(pFile, "%s", &aStr[0]);

				//角度を取得
				fscanf(pFile, "%f", &rot.x); fscanf(pFile, "%f", &rot.y); fscanf(pFile, "%f", &rot.z);

				//不要な文字列の読み込み
				fscanf(pFile, "%s", &aStr[0]);

				//使用するモデルの情報を取得
				fscanf(pFile, "%d", &nModelID);

				//不要な文字列の読み込み
				fscanf(pFile, "%s", &aStr[0]);

				//親の情報を取得
				fscanf(pFile, "%d", &nParentID);

				//取得した情報からモデルを生成
				if (nParentID == -1)
				{
					m_apModel[nCnt] = CModel::Create(pos, size, rot, nModelID);
				}
				else
				{
					m_apModel[nCnt] = CModel::Create(pos, size, rot, nModelID, m_apModel[nParentID]);
				}
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{

	}
}
