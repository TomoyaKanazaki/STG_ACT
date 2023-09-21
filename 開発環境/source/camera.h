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
	virtual HRESULT Init(void);
	void Uninit(void);
	virtual void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	D3DXVECTOR3 GetPosV(void) { return m_posV; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXMATRIX GetMtxPro(void) { return m_mtxProjection; }
	D3DXMATRIX CreateViewMatrix(void);

protected:

#define CAMERA_DISTANCE (500.0f) //視点からプレイヤーの距離
#define HEIGHT (300.0f) //視点の高さ
#define MAX_ROT (D3DX_PI * 0.99f) //視点の限界角
#define MIN_ROT (D3DX_PI * 0.01f) //視点の限界角

	//メンバ変数
	D3DXVECTOR3 m_posV; //視点
	D3DXVECTOR3 m_posR; //注視点
	D3DXVECTOR3 m_vecU; //上方向ベクトル
	D3DXMATRIX m_mtxProjection; //プロジェクションマトリックス
	D3DXMATRIX m_mtxView; //ビューマトリックス
	D3DXVECTOR3 m_rot; //Xの計算に使用する角度
	D3DXVECTOR3 m_diff; //プレイヤー座標との差分
	float m_fFov; //視野角

private:

	//メンバ関数
	void Rotate(void);

};

#endif
