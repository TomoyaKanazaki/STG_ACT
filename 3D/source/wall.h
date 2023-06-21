//==========================================
//
//  床クラス(field.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  弾クラスの定義
//==========================================
class CWall : public CObject3D
{
public:
	CWall(int nPriority = 0); //コンストラクタ
	~CWall(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static CWall *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

};

#endif
