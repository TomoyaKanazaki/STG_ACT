//==========================================
//
//  ゲームカメラクラス(camera.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_TITLE_H_
#define _CAMERA_TITLE_H_
#include "main.h"
#include "camera.h"

//==========================================
//  カメラクラスの定義
//==========================================
class CCameraTitle : public CCamera
{
public:
	CCameraTitle(); //コンストラクタ
	~CCameraTitle(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Update(void) override;

private:

	//メンバ変数
	float m_fAngle;

};

#endif
