//==========================================
//
//  �I�u�W�F�N�g�t�@���N���X(object_fan.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object_fan.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CObject_Fan::CObject_Fan(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_mtxWorld = {};
	m_pTexture = NULL;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fRadius = 0.0f;
	m_nNumPrimitive = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CObject_Fan::~CObject_Fan()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CObject_Fan::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * m_nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);

	//���_�o�b�t�@�̏���ݒ�
	SetVtx();

	//��ނ�ݒ�
	SetType(TYPE_FIELD);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CObject_Fan::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CObject_Fan::Update(void)
{

}

//==========================================
//  �`�揈��
//==========================================
void CObject_Fan::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans, mtxView; //�v�Z�p�}�g���b�N�X

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, m_nNumPrimitive);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//==========================================
//  �����蔻�菈��
//==========================================
bool CObject_Fan::OnMesh(const D3DXVECTOR3 pos)
{
	//���[�J���ϐ��錾
	//int nCntPoint = 0;

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//����
	for (int nCnt = 1; nCnt <= m_nNumPrimitive; nCnt++)
	{
		int IdxStart = nCnt; //��
		int IdxEnd = nCnt + 1; //�E
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//�͈͊O�������ꍇfalse
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return true;
}

//==========================================
//  �����蔻�菈��
//==========================================
bool CObject_Fan::OnMesh(const D3DXVECTOR3 pos, const D3DXVECTOR3 oldpos, D3DXVECTOR3 * pVecLine, D3DXVECTOR3 * pVecToPos)
{
	return false;
}

//==========================================
//  �|���S���̏�ɂ��锻��
//==========================================
bool CObject_Fan::CheckOnMesh(const D3DXVECTOR3 &posJudge, const D3DXVECTOR3 &posStart, const D3DXVECTOR3 &posEnd) const
{
	return (posEnd.z - posStart.z) * (posJudge.x - posStart.x) - (posEnd.x - posStart.x) * (posJudge.z - posStart.z) < 0.0f;
}

//==========================================
//  ��������
//==========================================
CObject_Fan *CObject_Fan::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumPrimitive, float fRadius)
{
	//�C���X�^���X����
	CObject_Fan *pFan = NULL;

	//NULL�`�F�b�N
	if (pFan == NULL)
	{
		//���������m��
		pFan = new CObject_Fan;
	}

	if (pFan == NULL)
	{
		return NULL;
	}

	//��������ݒ�
	pFan->m_pos = pos;
	pFan->m_rot = rot;
	pFan->m_nNumPrimitive = nNumPrimitive;
	pFan->m_nNumVtx = pFan->m_nNumPrimitive + 2;
	pFan->m_fRadius = fRadius;

	//������
	pFan->Init();

	//�e�N�X�`�������蓖�Ă�
	pFan->BindTexture(CManager::GetTexture()->GetAddress(CTexture::FIELD));

	//�|�C���^��Ԃ�
	return pFan;
}

//==========================================
//  ���_�̐ݒ�
//==========================================
void CObject_Fan::SetVtx(void)
{
	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_nNumPrimitive + 2; nCntVtx++)
	{
		//�@���̐ݒ�
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCntVtx].col = m_Color;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���S���W��ݒ�

	//�O���̒��_��ݒ�
	for (int nCntVtx = 1; nCntVtx <= m_nNumPrimitive; nCntVtx++)
	{
		//�p�x���Z�o
		float fAngle = ((nCntVtx / (float)(m_nNumPrimitive)) * (360.0f)) - 180.0f;
		fAngle = D3DXToRadian(fAngle);

		//�e���_�ɍ��W��^����
		pVtx[nCntVtx].pos = D3DXVECTOR3
		(
			sinf(fAngle) * m_fRadius,
			0.0f,
			cosf(fAngle) * m_fRadius
		);
	}

	//�Ō�̒��_��ݒ�
	pVtx[m_nNumVtx - 1] = pVtx[1];

	//�e�N�X�`�����W��ݒ�
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		//���W�𐳋K������
		D3DXVECTOR2 texPos = D3DXVECTOR2(pVtx[nCnt].pos.x, pVtx[nCnt].pos.z);
		D3DXVec2Normalize(&pVtx[nCnt].tex, &texPos);
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
