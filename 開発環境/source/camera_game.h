//==========================================
//
//  ゲームカメラクラス(camera.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_
#include "main.h"
#include "camera.h"

//==========================================
//  カメラクラスの定義
//==========================================
class CCameraGame : public CCamera
{
public:
	CCameraGame(); //コンストラクタ
	~CCameraGame(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Update(void) override;

private:

	//メンバ関数
	void FirstPerson(void);
	void ThirdPerson(void);
	void Move(void);

};

#endif
