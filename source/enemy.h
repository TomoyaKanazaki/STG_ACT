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
#include "layer.h"

//==========================================
//  前方宣言
//==========================================
class CModel;
class CMotion;
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
		TYPE_SHOT, //遠距離攻撃の敵
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
	void SetLife(const int nDamage) { if (m_nLife > 0) m_nLife -= nDamage; }

	//静的メンバ変数
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, CEnemy::TYPE type);
	static int m_nCntEnemy;

protected:

	//モデル情報
	CModel **m_ppModel; //モデル情報
	CLayer::LAYERDATA *m_pLayer; //階層構造情報
	CMotion *m_pMotion;
	CShadow *m_pShadow;

private:

	//メンバ変数
	D3DXVECTOR3 m_oldPos;
	int m_nNumModel;
	int m_nLife;
	float m_fSpeed;
	bool m_bRand;

};

#endif
