//==========================================
//
//  モーションクラス(motion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "motion.h"

//==========================================
//  コンストラクタ
//==========================================
CMotion::CMotion()
{
	m_apInfo = NULL;
	m_nNumAll = 0;
	m_nType = 0;
	m_nNumKey = 0;
	m_nKey = 0;
	m_nNumModel = 0;
	m_bLoop = false;
	m_bFinish = false;
	m_pModel = NULL;
}

//==========================================
//  デストラクタ
//==========================================
CMotion::~CMotion()
{

}

//==========================================
//  初期化処理
//==========================================
void CMotion::Init(char *sFileName)
{
	//ローカル変数宣言
	char aStr[128]; //廃棄用
	int nNumModel = 0; //モデル数比較用
	D3DXVECTOR3 LoadPos, LoadRot;

	//モーションファイルを読み込み
	FILE *pFile = fopen(sFileName, "r");

	//NULLチェック
	if (pFile != NULL)
	{
		//キャラクターセットまで飛ばす
		do
		{
			fscanf(pFile, "%s", &aStr[0]);
		} while (strcmp(aStr, "CHARACTERSET") != 0);

		//モデル数
		fscanf(pFile, "%s = %d	%s %s\n", &aStr[0], &nNumModel, &aStr[0], &aStr[0]);

		//モデル配置
		if(nNumModel == m_nNumModel)
		{
			for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++, m_pModel++)
			{
				fgets(&aStr[0], 128, pFile);
				fscanf(pFile, "%s = %f %f %f", &aStr[0], &LoadPos.x, &LoadPos.y, &LoadPos.z);
				fscanf(pFile, "%s = %f %f %f\n", &aStr[0], &LoadRot.x, &LoadRot.y, &LoadRot.z);
				fgets(&aStr[0], 128, pFile);
				m_pModel->SetTransform(LoadPos, LoadRot);
			}
		}
		else
		{
			return;
		}

		for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
		{
			//モーションセットまで飛ばす
			do
			{
				fscanf(pFile, "%s", &aStr[0]);
			} while (strcmp(aStr, "MOTIONSET") != 0);

			//モーション識別
			fscanf(pFile, "%s = %d	%s %s %s %s", &aStr[0], &m_apInfo[nCntMotion].nLoop, &aStr[0], &aStr[0], &aStr[0], &aStr[0]);
			fscanf(pFile, "%s = %d	%s %s\n", &aStr[0], &m_nNumKey, &aStr[0], &aStr[0]);

			//キーモーション
			for (int nCntKey = 0; nCntKey < m_nNumKey; nCntKey++)
			{
				fgets(&aStr[0], 128, pFile);
				fscanf(pFile, "%s = %d\n", &aStr[0], &m_apInfo[nCntMotion].aKeyMotion[nCntKey].nFrame);

				for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
				{
					fgets(&aStr[0], 128, pFile);
					fscanf(pFile, "%s = %f %f %f", &aStr[0], &m_apInfo[nCntMotion].aKeyMotion[nCntKey].pos[nCntModel].x, &m_apInfo[nCntMotion].aKeyMotion[nCntKey].pos[nCntModel].y, &m_apInfo[nCntMotion].aKeyMotion[nCntKey].pos[nCntModel].z);
					fscanf(pFile, "%s = %f %f %f\n", &aStr[0], &m_apInfo[nCntMotion].aKeyMotion[nCntKey].rot[nCntModel].x, &m_apInfo[nCntMotion].aKeyMotion[nCntKey].rot[nCntModel].y, &m_apInfo[nCntMotion].aKeyMotion[nCntKey].rot[nCntModel].z);
					fgets(&aStr[0], 128, pFile);
				}

				fgets(&aStr[0], 128, pFile);
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		return;
	}
}

//==========================================
//  終了処理
//==========================================
void CMotion::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CMotion::Update(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 posCurr, rotCurr;
	D3DXVECTOR3 posDiff, rotDiff;

	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++, m_pModel++)
	{
		//現在の位置、角度を保存する
		posCurr = m_pModel->GetPos();
		rotCurr = m_pModel->GetRot();

		//

		//モデルに反映
		m_pModel->SetTransform(posCurr + posDiff, rotCurr + rotDiff);
	}
}

//==========================================
//  設定処理
//==========================================
void CMotion::SetType(int Type)
{
	//モーションの種類を設定
	m_nType = Type;
}

//==========================================
//  種類の取得
//==========================================
int CMotion::GetType(void)
{
	return m_nType;
}

//==========================================
//  終わったかどうか
//==========================================
bool CMotion::IsFinish(void)
{
	return false;
}

//==========================================
//  モーションデータを作成
CMotion *CMotion::Set(CModel *pModel, int nNumAll)
{
	//インスタンス生成
	CMotion *pMotion = NULL;

	//NULLチェック
	if (pMotion == NULL)
	{
		//メモリを確保
		pMotion = new CMotion;
	}

	if (pMotion == NULL)
	{
		return NULL;
	}

	//情報を設定
	pMotion->m_pModel = pModel;
	pMotion->m_nNumModel = nNumAll;

	//ポインタを返す
	return pMotion;
}
