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

private:

	//メンバ変数
	D3DXVECTOR3 m_posV; //視点
	D3DXVECTOR3 m_posR; //注視点
	D3DXVECTOR3 m_vecU; //上方向ベクトル
	D3DXMATRIX m_mtxProjection; //プロジェクションマトリックス
	D3DXMATRIX m_mtxView; //ビューマトリックス
	D3DXVECTOR3 m_rot; //Xの計算に使用する角度

};

//==========================================
//  カメラ構造体定義
//==========================================
typedef struct
{
	D3DXVECTOR3 posV; //視点
	D3DXVECTOR3 posR; //注視点
	D3DXVECTOR3 vecU; //上方向ベクトル
	D3DXMATRIX mtxProjection; //プロジェクションマトリックス
	D3DXMATRIX mtxView; //ビューマトリックス
	D3DXVECTOR3 rot; //Xの計算に使用する角度
}Camera;

//==========================================
//  プロトタイプ宣言
//==========================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
void FPSCamera(void);
void TPSCamera(void);
void CameraMove(void);

#endif
