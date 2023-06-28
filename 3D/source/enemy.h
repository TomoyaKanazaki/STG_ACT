//==========================================
//
//  エネミークラス(enemy.h)
//  Author : Tomoay Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "object.h"

//==========================================
//  前方宣言
//==========================================
class CModel;
class CShadow;

//==========================================
//  エネミークラス定義
//==========================================
class CEnemy : public CObject
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0, //普通の敵
		TYPE_MAX
	}TYPE;

	CEnemy(int nPriority = 4); //コンストラクタ
	~CEnemy(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }

	//静的メンバ変数
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, CEnemy::TYPE type);

private:

	//メンバ関数
	void Load(void); //エネミー情報の読み込み

	//メンバ変数
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_oldPos;
	int m_nLife;
	int m_nNumModel;
	float m_fSpeed;
	bool m_bRand;

	//モデル情報
	CModel **m_apModel;
	CShadow *m_pShadow;

};

#endif
