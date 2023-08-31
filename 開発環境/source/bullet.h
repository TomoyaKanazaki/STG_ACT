//==========================================
//
//  バレットクラス(bullet.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  バレットクラス定義
//==========================================
class CBullet : public CObject3D
{
public:

	//弾の種類
	enum TYPE
	{
		NORMAL_BULLET = 0, //直進する弾
		HOMING_BULLET, //追尾する弾
		MAX_TYPE
	};

	//弾を使うユーザーの種類
	enum USER
	{
		USER_NONE = 0, //誰のものでもない
		PLAYER, //プレイヤーが撃った弾
		ENEMY, //敵が撃った球
		USER_MAX
	};

	CBullet(int nPriority = 4); //コンストラクタ
	~CBullet(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, USER user, TYPE type);

private:

	//メンバ変数
	int m_nLife;
	USER m_user;

};

#endif
