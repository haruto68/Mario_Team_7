#pragma once
#include"Dxlib.h"
#include<string>

#define	D_SUCCESS		(0)				// 成功
#define	D_FAILURE		(-1)			// 失敗

#define D_WIN_MAX_X		float(768.0)	// スクリーンサイズ（幅）
#define D_WIN_MAX_Y		float(720.0)	// スクリーンサイズ（高さ）
#define D_COLOR_BIT		float(32.0)		// カラービット

#define SIZE			float(1.5)		// 画像倍率

#define D_MONO			float(48.0)		// 1/1マスピクセル
#define D_HARF			float(24.0)		// 1/2マスピクセル
#define D_QUARTER		float(12.0)		// 1/4マスピクセル

#define D_GRAVITY		float(0.78)		//重力速度

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