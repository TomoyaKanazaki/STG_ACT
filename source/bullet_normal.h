//==========================================
//
//  直進する弾のクラス(bullet_normal.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BULLET_NORMAL_H_
#define _BULLET_NORMAL_H_
#include "main.h"
#include "bullet.h"

//==========================================
//  クラス定義
//==========================================
class CBulletNormal : public CBullet
{
public:
	CBulletNormal(); //コンストラクタ
	~CBulletNormal(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	

};

#endif
