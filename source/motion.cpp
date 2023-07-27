//==========================================
//
//  モーションクラス(moton.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "motion.h"
#include "model.h"

//==========================================
//  マクロ定義
//==========================================
#define TXTFILENAME_MOTION "data\\TXT\\MotionData.txt" //モーション情報を持ったテキストファイルのパス

//==========================================
//  静的メンバ変数宣言
//==========================================
CMotion::INFO *CMotion::m_pInfo = NULL;
int CMotion::m_nNumMotion = 0;

//==========================================
//  コンストラクタ
//==========================================
CMotion::CMotion()
{
	m_ppModel = NULL;
	m_nMotion = MOTION_NONE;
	m_Info = {};
	m_nNumModel = 0;
	m_nCntFrame = 0;
	m_nCntKey = 0;
}

//==========================================
//  デストラクタ
//==========================================
CMotion::~CMotion()
{

}

//==========================================
//  更新処理
//==========================================
void CMotion::Update(void)
{
	//NULLチェック
	if (m_ppModel != NULL)
	{
		//キーの有無を確認
		if (m_Info.nNumKey > 0)
		{
			int nNowMotion = m_nMotion; //現在のモーション番号
			int nNowKey = m_nCntKey; // 現在のキー
			int nNextkey = (nNowKey + 1) % m_Info.nNumKey; //次のキー
			int nFrame = m_Info.pKeyInfo[nNowKey].nFrame;

			//差分(割合)
			float fFrame = ((float)m_nCntFrame / (float)nFrame);

			//モデル数分のモーションを設定
			for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
			{
				//前回の値を取得
				m_oldKey.pos = m_ppModel[nCntModel]->GetPos();
				m_oldKey.rot = m_ppModel[nCntModel]->GetRot();

				//差分を算出
				D3DXVECTOR3 posDeff = D3DXVECTOR3
				(
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].pos.x - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.x,
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].pos.y - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.y,
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].pos.z - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.z
				);
				D3DXVECTOR3 rotDeff = D3DXVECTOR3
				(
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].rot.x - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.x,
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].rot.y - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.y,
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].rot.z - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.z
				);

				//角度の補正
				if (rotDeff.x < -D3DX_PI) //x
				{
					rotDeff.x += D3DX_PI * 2;
				}
				else if (rotDeff.x > D3DX_PI)
				{
					rotDeff.x += -D3DX_PI * 2;
				}

				if (rotDeff.y < -D3DX_PI) //y
				{
					rotDeff.y += D3DX_PI * 2;
				}
				else if (rotDeff.y > D3DX_PI)
				{
					rotDeff.y += -D3DX_PI * 2;
				}

				if (rotDeff.z < -D3DX_PI) //z
				{
					rotDeff.z += D3DX_PI * 2;
				}
				else if (rotDeff.z > D3DX_PI)
				{
					rotDeff.z += -D3DX_PI * 2;
				}

				//現在の値を算出
				D3DXVECTOR3 posDest = D3DXVECTOR3
				(
					m_oldKey.pos.x + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.x + posDeff.x * fFrame,
					m_oldKey.pos.y + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.y + posDeff.y * fFrame,
					m_oldKey.pos.z + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.z + posDeff.z * fFrame
				);
				D3DXVECTOR3 rotDest = D3DXVECTOR3
				(
					m_oldKey.rot.x + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.x + rotDeff.x * fFrame,
					m_oldKey.rot.y + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.y + rotDeff.y * fFrame,
					m_oldKey.rot.z + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.z + rotDeff.z * fFrame
				);

				//算出した値の適用
				m_ppModel[nCntModel]->SetPos(posDest);
				m_ppModel[nCntModel]->SetRot(rotDest);
			}

			//フレームカウントを加算
			m_nCntFrame++;

			//キーの更新をチェック
			if (m_Info.pKeyInfo[nNowKey].nFrame != 0)
			{
				if (m_nCntFrame == nFrame)
				{
					//キーの更新
					m_nCntKey = nNextkey;
					m_nCntFrame = 0;
				}
			}
			else
			{
				m_nCntKey = 0;
				m_nCntFrame = 0;
			}
		}
	}
}

//==========================================
//  モデルの設定処理
//==========================================
void CMotion::SetModel(CModel **ppModel, int nNum, CHARA type)
{
	//モデルを記録
	m_ppModel = ppModel;

	//モデル数を記録
	m_nNumModel = nNum;

	//キャラクター情報を記録
	m_nMotion = type;

	//使用するモーションを設定
	m_Info = m_pInfo[type];
}

//==========================================
//  モーションの設定処理
//==========================================
void CMotion::Set(CHARA type)
{
	//キャラクター情報を設定
	m_nMotion = type;

	//使用するモーションを設定
	m_Info = m_pInfo[type];

	//カウンターをリセット
	m_nCntKey = 0;
	m_nCntFrame = 0;
}

//==========================================
//  読み込み処理
//==========================================
void CMotion::Load(void)
{
	//ローカル変数宣言
	FILE *pFile; //ファイル名
	char aStr[256]; //不要な文字列の記録用
	int nCntInfo = 0; //現在のモーション番号
	int nCntKey = 0; //現在のキー番号
	int nCntModel = 0; //現在のモデル番号

	//ファイルを読み取り専用で開く
	pFile = fopen(TXTFILENAME_MOTION, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			//文字列を取得
			fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(&aStr[0], "NUM_MOTION") == 0)
			{
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_nNumMotion); //モーション数取得

				//モーション数のメモリを確保
				m_pInfo = new INFO[m_nNumMotion];
			}
			else if (strcmp(&aStr[0], "LOOP") == 0)
			{
				//ループの有無を取得
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_pInfo[nCntInfo].bLoop);
			}
			else if (strcmp(&aStr[0], "NUM_KEY") == 0)
			{
				//キー数の取得
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_pInfo[nCntInfo].nNumKey);

				//キー数分のメモリを確保
				m_pInfo[nCntInfo].pKeyInfo = new KEY_INFO[m_pInfo[nCntInfo].nNumKey];
			}
			else if (strcmp(&aStr[0], "NUM_MODEL") == 0)
			{
				//モデル数の取得
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_pInfo[nCntInfo].nNumModel);

				//モデル数分のメモリを確保
				for (int nCnt = 0; nCnt < m_pInfo[nCntInfo].nNumKey; nCnt++)
				{
					m_pInfo[nCntInfo].pKeyInfo[nCnt].pKey = new KEY[m_pInfo[nCntInfo].nNumModel];
				}
			}
			else if (strcmp(&aStr[0], "FRAME") == 0)
			{
				//フレーム数を取得
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_pInfo[nCntInfo].pKeyInfo[nCntKey].nFrame);
			}
			else if (strcmp(&aStr[0], "POS") == 0)
			{
				//座標を取得
				fscanf(pFile, "%s", &aStr[0]); //=
				D3DXVECTOR3 pos;
				fscanf(pFile, "%f", &pos.x);
				fscanf(pFile, "%f", &pos.y);
				fscanf(pFile, "%f", &pos.z);

				m_pInfo[nCntInfo].pKeyInfo[nCntKey].pKey[nCntModel].pos = pos;
			}
			else if (strcmp(&aStr[0], "ROT") == 0)
			{
				//角度を取得
				fscanf(pFile, "%s", &aStr[0]); //=
				D3DXVECTOR3 rot;
				fscanf(pFile, "%f", &rot.x);
				fscanf(pFile, "%f", &rot.y);
				fscanf(pFile, "%f", &rot.z);

				m_pInfo[nCntInfo].pKeyInfo[nCntKey].pKey[nCntModel].rot = rot;
			}
			else if (strcmp(&aStr[0], "END_MOTIONSET") == 0)
			{
				//モーション番号を進める
				nCntInfo++;

				//キー番号とモデル番号をリセットする
				nCntModel = 0;
				nCntKey = 0;
			}
			else if (strcmp(&aStr[0], "END_KEYSET") == 0)
			{
				//キー番号を進める
				nCntKey++;

				//モデル番号をリセットする
				nCntModel = 0;
			}
			else if (strcmp(&aStr[0], "END_KEY") == 0)
			{
				//モデル番号を進める
				nCntModel++;
			}
			if (strcmp(&aStr[0], "END_SCRIPT") == 0)
			{
				//終端
				break;
			}
		}
		fclose(pFile);
	}
}

//==========================================
//  情報の破棄
//==========================================
void CMotion::UnLoad(void)
{
	//モーション情報の破棄
	for (int nCntMotion = 0; nCntMotion < m_nNumMotion; nCntMotion++)
	{
		for (int nCntKey = 0; nCntKey < m_pInfo[nCntMotion].nNumKey; nCntKey++)
		{
			delete[] m_pInfo[nCntMotion].pKeyInfo[nCntKey].pKey;
			m_pInfo[nCntMotion].pKeyInfo[nCntKey].pKey = NULL;
		}
		delete[] m_pInfo[nCntMotion].pKeyInfo;
		m_pInfo[nCntMotion].pKeyInfo = NULL;
	}
	delete[] m_pInfo;
	m_pInfo = NULL;
}
