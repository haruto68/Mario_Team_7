#pragma once
#include"Dxlib.h"
#include<string>

#define	D_SUCCESS		(0)				// ����
#define	D_FAILURE		(-1)			// ���s

#define D_WIN_MAX_X		float(768.0)	// �X�N���[���T�C�Y�i���j
#define D_WIN_MAX_Y		float(720.0)	// �X�N���[���T�C�Y�i�����j
#define D_COLOR_BIT		float(32.0)		// �J���[�r�b�g

#define SIZE			float(1.5)		// �摜�{��

#define D_MONO			float(48.0)		// 1/1�}�X�s�N�Z��
#define D_HARF			float(24.0)		// 1/2�}�X�s�N�Z��
#define D_QUARTER		float(12.0)		// 1/4�}�X�s�N�Z��

#define D_GRAVITY		float(0.78)		//�d�͑��x

class Singleton
{
protected:
	Singleton();
	~Singleton();

	Singleton(const Singleton&);

	Singleton& operator = (const Singleton&) = delete;

public:
	//static class Type* GetInstance();
};