//==========================================
//
//  階層構造管理クラス(layer.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LAYER_H_
#define _LAYER_H_
#include "main.h"

//==========================================
//  前方宣言
//==========================================
class CModel;

//==========================================
//  階層構造管理クラス定義
//==========================================
class CLayer
{
public:
	//階層構造の種類
	typedef enum
	{
		PLAYER_LAYER = 0, //プレイヤー構造
		ENEMY_APPROACH_LAYER, //丸い敵構造
		ENEMY_SHOT_LAYER, //弾を撃つ敵構造
		ENEMY_BOSS_LAYER, //ボス構造
		LAYERS_MAX
	}LAYERS;

	//階層構造のデータ
	typedef struct
	{
		int nNumModel; //モデル数
		int *pModelID; //使用するモデルのインデックス
		int *pParentID; //親モデルのインデックス
		D3DXVECTOR3 *pPos; //初期位置
		D3DXVECTOR3 *pRot; //初期角度
	}LAYERDATA;

	CLayer(); //コンストラクタ
	~CLayer(); //デストラクタ

	//静的メンバ関数
	static LAYERDATA *Set(LAYERS type);
	static void Load(void);
	static void UnLoad(void);

private:

	//静的メンバ変数
	static int m_nNumLayer; //階層構造情報数
	static LAYERDATA *m_pData; //階層構造情報

};

#endif
