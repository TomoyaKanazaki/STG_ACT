//==========================================
//
//  ゲームカメラクラス(camera_result.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_RESULT_H_
#define _CAMERA_RESULT_H_
#include "main.h"
#include "camera.h"

//==========================================
//  カメラクラスの定義
//==========================================
class CCameraResult : public CCamera
{
public:
	CCameraResult(); //コンストラクタ
	~CCameraResult(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Update(void) override;

private:

	//メンバ変数
	float m_fAngle;

};

#endif
