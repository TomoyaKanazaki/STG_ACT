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

//==========================================
//  エネミークラス定義
//==========================================
class CEnemy : public CObject
{
public:

	//列挙型定義
	enum ENEMY_TYPE
	{
		NORMAL = 0, //のーまる
		BLOCK, //かべ
		PUSH, //おしだし
		MAX
	};

	CEnemy(int nPriority = 4); //コンストラクタ
	~CEnemy(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetLife(const int nDamage) { if (m_nLife > 0) m_nLife -= nDamage; }

	//静的メンバ変数
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, ENEMY_TYPE type);

protected:

	//メンバ関数
	void AvertEnemy(void);
	void Chain(void);
	void Move(void);

	//モデル情報
	CModel **m_ppModel; //モデル情報
	CLayer::LAYERDATA *m_pLayer; //階層構造情報
	CMotion *m_pMotion;

	//メンバ変数
	int m_nCntBullet;
	int m_nCombo;

private:

	//メンバ関数
	int GetCombo() { return m_nCombo; } //敵のコンボ数の取得

	//メンバ変数
	int m_nNumModel;
	int m_nLife;
	float m_fSpeed;
	bool m_bRand;

	//静的メンバ変数
	const static float mc_fSize; //敵同士の当たり判定の範囲

};

#endif
