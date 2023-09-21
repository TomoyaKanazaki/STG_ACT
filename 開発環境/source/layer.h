//==========================================
//
//  �K�w�\���Ǘ��N���X(layer.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LAYER_H_
#define _LAYER_H_
#include "main.h"

//==========================================
//  �O���錾
//==========================================
class CModel;

//==========================================
//  �K�w�\���Ǘ��N���X��`
//==========================================
class CLayer
{
public:
	//�K�w�\���̎��
	typedef enum
	{
		PLAYER_LAYER = 0, //�v���C���[�\��
		NORMAL_LAYER, //�G�\��
		BLOCK_LAYER, //�G�\��
		PUSH_LAYER, //�G�\��
		BG_LAYER, //�w�i
		LAYERS_MAX
	}LAYERS;

	//�K�w�\���̃f�[�^
	typedef struct
	{
		int nNumModel; //���f����
		int *pModelID; //�g�p���郂�f���̃C���f�b�N�X
		int *pParentID; //�e���f���̃C���f�b�N�X
		D3DXVECTOR3 *pPos; //�����ʒu
		D3DXVECTOR3 *pRot; //�����p�x
	}LAYERDATA;

	CLayer(); //�R���X�g���N�^
	~CLayer(); //�f�X�g���N�^

	//�ÓI�����o�֐�
	static LAYERDATA *Set(LAYERS type);
	static void Load(void);
	static void UnLoad(void);

private:

	//�ÓI�����o�ϐ�
	static int m_nNumLayer; //�K�w�\�����
	static LAYERDATA *m_pData; //�K�w�\�����

};

#endif
