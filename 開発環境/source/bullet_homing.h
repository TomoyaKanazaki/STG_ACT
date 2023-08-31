//==========================================
//
//  追尾弾のクラス(bullet_homing.h)
//  Author :Tomoya Kanazaki
//
//==========================================
#ifndef _BULET_HOMING_H_
#define _BULET_HOMING_H_
#include "main.h"
#include "bullet.h"

//==========================================
//  クラス定義
//==========================================
class CBulletHoming : public CBullet
{
public:
	CBulletHoming(); //コンストラクタ
	~CBulletHoming(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//ホーミングの処理に使用するデータ構造体
	struct Homing
	{
		CObject *pObj; // 0 : Priority, 1 : ID
		int nCounter;
		bool bHoming;
	};

	//メンバ関数
	void Follow(void);

	//メンバ変数
	Homing m_Target;

};

#endif
