//==========================================
//
//  �I�u�W�F�N�g3D�N���X(object3D.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object3D.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const D3DXVECTOR3 CObject3D::mc_sizeExplosion = D3DXVECTOR3(30.0f, 30.0f, 30.0f);

//==========================================
//  �R���X�g���N�^
//==========================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_mtxWorld = {};
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bBillboard = false;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CObject3D::~CObject3D()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CObject3D::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���[�J���ϐ��錾
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.z * m_size.z) * 0.5f;

	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (GetType() == TYPE_FIELD || GetType() == TYPE_SHADOW)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, 0.0f, m_fLength);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, 0.0f, m_fLength);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, 0.0f, -m_fLength);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, 0.0f, -m_fLength);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, m_fLength, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, m_fLength, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, -m_fLength, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, -m_fLength, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//���_�J���[�̐ݒ�
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].col = m_col;
	}

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	m_oldPos = m_pos;

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CObject3D::Uninit(void)
{
	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CObject3D::Update(void)
{
	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�T�C�Y�̍X�V
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.z * m_size.z) * 0.5f;

	if (GetType() == TYPE_FIELD || GetType() == TYPE_SHADOW)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, 0.0f, m_fLength);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, 0.0f, m_fLength);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, 0.0f, -m_fLength);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, 0.0f, -m_fLength);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, m_fLength, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, m_fLength, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, -m_fLength, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, -m_fLength, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//���_�J���[�̐ݒ�
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].col = m_col;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	m_oldPos = m_pos;
}

//==========================================
//  �`�揈��
//==========================================
void CObject3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans, mtxView; //�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���{�[�h�����
	if (m_bBillboard)
	{
		//�r���[�}�g���b�N�X�̎擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);

		//�l�̕␳
		m_mtxWorld._41 = m_pos.x;
		m_mtxWorld._42 = m_pos.y;
		m_mtxWorld._43 = m_pos.z;
	}
	else
	{
		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==========================================
//  �e�N�X�`�����W�̕ύX
//==========================================
void CObject3D::SetTex(D3DXVECTOR2 min, D3DXVECTOR2 max)
{
	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(min.x, min.y);
	pVtx[1].tex = D3DXVECTOR2(max.x, min.y);
	pVtx[2].tex = D3DXVECTOR2(min.x, max.y);
	pVtx[3].tex = D3DXVECTOR2(max.x, max.y);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==========================================
//  �F�̐ݒ�
//==========================================
void CObject3D::SetCol(const D3DXCOLOR col)
{
	//�F��ݒ肷��
	m_col = col;

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ݒ肵���F�̓K�p
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==========================================
//  �������擾���鏈��
//==========================================
float CObject3D::GetHeight(const D3DXVECTOR3 TargetPos)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 VtxPos[4]; //���_�̈ʒu��ۑ�����
	D3DXVECTOR3 NorPlane[2]; //�ΏۂɂȂ�@��
	float fHeight = 0.0f; //�Ԃ�l

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̒��_���擾
	VtxPos[0] = pVtx[0].pos;
	VtxPos[1] = pVtx[1].pos;
	VtxPos[2] = pVtx[2].pos;
	VtxPos[3] = pVtx[3].pos;

	//�@�����擾
	NorPlane[0] = pVtx[0].nor;
	NorPlane[1] = pVtx[3].nor;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	if
		(
			((VtxPos[1].z - VtxPos[0].z) * (TargetPos.x - VtxPos[0].x)) - ((VtxPos[1].x - VtxPos[0].x) * (TargetPos.z - VtxPos[0].z)) > 0.0f &&
			((VtxPos[2].z - VtxPos[1].z) * (TargetPos.x - VtxPos[1].x)) - ((VtxPos[2].x - VtxPos[1].x) * (TargetPos.z - VtxPos[1].z)) > 0.0f &&
			((VtxPos[0].z - VtxPos[2].z) * (TargetPos.x - VtxPos[2].x)) - ((VtxPos[0].x - VtxPos[2].x) * (TargetPos.z - VtxPos[2].z)) > 0.0f
		)
	{
		//�@���������łȂ��ꍇ
		if (NorPlane[0].y != 0.0f)
		{
			fHeight = (-(TargetPos.x * NorPlane[0].x + TargetPos.z * NorPlane[0].z) + (VtxPos[0].x * NorPlane[0].x + VtxPos[0].y * NorPlane[0].y + VtxPos[0].z * NorPlane[0].z)) / NorPlane[0].y;
		}
	}

	if
		(
			((VtxPos[2].z - VtxPos[3].z) * (TargetPos.x - VtxPos[3].x)) - ((VtxPos[2].x - VtxPos[3].x) * (TargetPos.z - VtxPos[3].z)) > 0.0f &&
			((VtxPos[1].z - VtxPos[2].z) * (TargetPos.x - VtxPos[2].x)) - ((VtxPos[1].x - VtxPos[2].x) * (TargetPos.z - VtxPos[2].z)) > 0.0f &&
			((VtxPos[3].z - VtxPos[1].z) * (TargetPos.x - VtxPos[1].x)) - ((VtxPos[3].x - VtxPos[1].x) * (TargetPos.z - VtxPos[1].z)) > 0.0f
		)
	{
		//�@���������łȂ��ꍇ
		if (NorPlane[1].y != 0.0f)
		{
			fHeight = (-(TargetPos.x * NorPlane[1].x + TargetPos.z * NorPlane[1].z) + (VtxPos[3].x * NorPlane[1].x + VtxPos[3].y * NorPlane[1].y + VtxPos[3].z * NorPlane[1].z)) / NorPlane[1].y;
		}
	}

	return fHeight;
}

//==========================================
//  �����蔻��
//==========================================
bool CObject3D::Collision(CObject::TYPE type)
{
	//���[�J���ϐ��錾
	bool bHit = false;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�����̃A�h���X���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() == type)
			{
				//���_�o�b�t�@�̌Ăяo��
				VERTEX_3D *pVtx;

				//���_�o�b�t�@�����b�N
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//����ɕK�v�ȃx�N�g�����Z�o����
				D3DXVECTOR3 vecToPos = pObj->GetPos() - (m_pos + D3DXVECTOR3(cosf(-m_rot.y) * pVtx[0].pos.x, 0.0f, sinf(-m_rot.y) * pVtx[0].pos.z));
				D3DXVECTOR3 vecToMove = pObj->GetPos() - pObj->GetOldPos();
				D3DXVECTOR3 vecVtx = (m_pos + D3DXVECTOR3(cosf(m_rot.y) * pVtx[1].pos.x, 0.0f, sinf(m_rot.y) * pVtx[1].pos.z)) - (m_pos + D3DXVECTOR3(cosf(-m_rot.y) * pVtx[0].pos.x, 0.0f, sinf(-m_rot.y) * pVtx[0].pos.z));
				D3DXVECTOR3 posBase = (m_pos + D3DXVECTOR3(cosf(-m_rot.y) * pVtx[0].pos.x, 0.0f, sinf(-m_rot.y) * pVtx[0].pos.z));

				//���_�o�b�t�@���A�����b�N
				m_pVtxBuff->Unlock();

				//��_�̌v�Z�ɕK�v�Ȓl���Z�o
				float fPosMove = (vecToPos.z * vecToMove.x) - (vecToPos.x * vecToMove.z);
				float fVtxMove = (vecVtx.z * vecToMove.x) - (vecVtx.x * vecToMove.z);
				float fRate = fPosMove / fVtxMove;

				//�ڐG�𔻒肷��
				if (0.0f <= fRate && fRate <= 1.0f)
				{
					bHit = true;
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}

	//�l��Ԃ�
	return bHit;
}

//==========================================
//  �����蔻��
//==========================================
bool CObject3D::Collision(CObject::TYPE type, D3DXVECTOR3 *pCrossPoint)
{
	//���[�J���ϐ��錾
	bool bHit = false;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�����̃A�h���X���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() == type)
			{
				//���_�o�b�t�@�̌Ăяo��
				VERTEX_3D *pVtx;

				//���_�o�b�t�@�����b�N
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//����Ɏg�p���钸�_�̍��W���擾
				D3DXVECTOR3 Vtx0 = (m_pos + D3DXVECTOR3(cosf(m_rot.y) * pVtx[0].pos.x, 0.0f, sinf(m_rot.y) * pVtx[0].pos.y));
				D3DXVECTOR3 Vtx3 = (m_pos + D3DXVECTOR3(cosf(m_rot.y) * pVtx[3].pos.x, 0.0f, sinf(m_rot.y) * pVtx[3].pos.y));

				//���_�o�b�t�@���A�����b�N
				m_pVtxBuff->Unlock();

				//����Ώۂ̑O��ƍ���̍��W���擾
				D3DXVECTOR3 pos = pObj->GetPos();
				D3DXVECTOR3 posOld = pObj->GetOldPos();

				//����ɕK�v�ȃx�N�g�����Z�o����
				D3DXVECTOR3 vecToPos = pos - Vtx0; //���_���獡��̍��W
				D3DXVECTOR3 vecToMove = pos - posOld; //�O��̍��W���獡��̍��W
				D3DXVECTOR3 vecVtx = Vtx3 - Vtx0; //���[�̒��_����E�[�̒��_

				//�ڐG�𔻒肷��
				if ((Vtx3.z - Vtx0.z) * (pos.x - Vtx0.x) - (Vtx3.x - Vtx0.x) * (pos.z - Vtx0.z) < 0.0f)
				{
					//��_�̌v�Z�ɕK�v�Ȓl���Z�o
					float fPosMove = (vecToPos.z * vecToMove.x) - (vecToPos.x * vecToMove.z);
					float fVtxMove = (vecVtx.z * vecToMove.x) - (vecVtx.x * vecToMove.z);
					float fRate = fPosMove / fVtxMove;

					//��_���ɒ��_�Ԃɂ������ꍇ
					if (0.0f <= fRate && fRate <= 1.0f)
					{
						//�ڐG�t���O�𗧂Ă�
						bHit = true;

						//��_���Z�o
						D3DXVECTOR3 CrossPoint = Vtx0 + (vecVtx * fRate);
						CrossPoint.y = 0.0f;
						*pCrossPoint = CrossPoint;
						pObj->SetPos(CrossPoint);

						//�������Ăяo��
						CParticle::Create
						(
							CrossPoint,
							mc_sizeExplosion * (float)pObj->GetCombo() * 0.5f,
							mc_sizeExplosion * (float)pObj->GetCombo() * 0.5f,
							D3DXCOLOR(1.0f, 1.0f - (0.12f * (float)pObj->GetCombo()), 0.0f, 1.0f),
							30, 10 * pObj->GetCombo(), 10 * pObj->GetCombo(), 3
						);

						//�Ώۂ̃I�u�W�F�N�g��j��
						pObj->Uninit();
					}
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}

	//�l��Ԃ�
	return bHit;
}
