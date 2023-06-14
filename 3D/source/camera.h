//==========================================
//
//  カメラクラス(camera.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//==========================================
//  カメラクラスの定義
//==========================================
class CCamera
{
public:
	CCamera(); //コンストラクタ
	~CCamera(); //デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void FirstPerson(void);
	void ThirdPerson(void);
	void Move(void);
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	D3DXVECTOR3 GetPosV(void) { return m_posV; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

private:

	//メンバ変数
	D3DXVECTOR3 m_posV; //視点
	D3DXVECTOR3 m_posR; //注視点
	D3DXVECTOR3 m_vecU; //上方向ベクトル
	D3DXMATRIX m_mtxProjection; //プロジェクションマトリックス
	D3DXMATRIX m_mtxView; //ビューマトリックス
	D3DXVECTOR3 m_rot; //Xの計算に使用する角度

};

#endif
