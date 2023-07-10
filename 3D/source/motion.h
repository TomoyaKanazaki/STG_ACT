//==========================================
//
//  モーションクラス(motion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"
#include "model.h"

//==========================================
//  マクロ定義
//==========================================
#define MAX_PARTS (16) //モデルの最大数
#define MAX_MOTION (32) //モーションの最大数

//==========================================
//  モーションクラス定義
//==========================================
class CMotion
{
public:

	typedef struct
	{
		D3DXVECTOR3 pos[MAX_MODEL]; //モデル数分の位置情報
		D3DXVECTOR3 rot[MAX_MODEL]; //モデル数分の角度情報
		int nFrame; //切り替わるまでにかかるフレーム数
	}KEY_INFO; //キー情報

	typedef struct
	{
		KEY_INFO aKeyMotion[MAX_MOTION]; //キー数分のキー情報
		int nLoop; //ループの有無
	}INFO;

	CMotion(); //コンストラクタ
	~CMotion(); //デストラクタ

	//メンバ関数
	void Init(char *sFileName);
	void Uninit(void);
	void Update(void);
	void SetType(int Type);
	int GetType(void);
	bool IsFinish(void);

	//静的メンバ関数
	static CMotion *Set(CModel *pModel, int nNumAll);

private:

	//メンバ変数
	INFO *m_apInfo; //モーション情報
	int m_nNumAll; //モーションの総数
	int m_nType; //実行するモーション
	int m_nNumKey; //次のキー
	int m_nKey; //現在のキー
	int m_nNumModel; //モデル数
	int m_nCounter; //キーカウンター
	bool m_bLoop; //ループフラグ
	bool m_bFinish; //
	CModel *m_pModel; //モデルのポインタ

};

#endif
