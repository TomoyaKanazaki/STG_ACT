//==========================================
//
//  �w�i�N���X(bg.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object.h"
#include "layer.h"

//==========================================
//  �O���錾
//==========================================
class CModel;

//==========================================
//  �N���X��`
//==========================================
class CBg : public CObject
{
public:

	//�����o�֐�
	CBg(int nPriority = 6);
	~CBg();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CBg *Create(void);

private:

	//���f�����
	CModel **m_ppModel; //���f�����
	CLayer::LAYERDATA *m_pLayer; //�K�w�\�����

};

#endif
