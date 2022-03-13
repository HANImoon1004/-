#pragma once

typedef struct tagInfo
{
	float		fX;
	float		fY;

	float		fCX;	// 가로 길이
	float		fCY;	// 세로 길이

	int			iRX; //render할 부분
	int			iRY;
}INFO;


typedef struct tagLinePos
{
	float	fX;
	float	fY;

	tagLinePos()
	{
		ZeroMemory(this, sizeof(tagLinePos));
	}
	tagLinePos(float _fX, float _fY)
		: fX(_fX), fY(_fY)
	{

	}

}LINEPOS;

typedef	struct tagLineInfo
{
	LINEPOS		tLeftPoint;
	LINEPOS		tRightPoint;

	tagLineInfo()
	{
		ZeroMemory(this, sizeof(tagLineInfo));
	}
	tagLineInfo(LINEPOS& tLPoint, LINEPOS& tRPoint)
		: tLeftPoint(tLPoint), tRightPoint(tRPoint)
	{

	}

}LINEINFO;


typedef struct tagDraw
{
	int iX;
	int iY;

	int iCX; //실제 가로(이미지)
	int iCY; //실제 세로(이미지)

	tagDraw()
	{
		ZeroMemory(this, sizeof(tagDraw));
	}
	tagDraw(int _iX, int _iY, int _iCX, int _iCY)
		: iX(_iX), iY(_iY), iCX(_iCX), iCY(_iCY) {}
}DRAW;


enum class EDrawWay
{
	RE_UP_DOWN,
	RE_LEFT_RIGHT,
	RE_ALL,
	ROTATE,
	END
};

typedef	struct tagFrame
{
	DRAW	tDraw;
	EDrawWay eDrawWay;
	DWORD	dwDelay;
	int iOffsetX;
	int iOffsetY;
	float fAngle;
	int		iFrameStart;		// 프레임 시작 시점
	int		iFrameEnd;			// 프레임 종료 지점
	int		iFrameAnimation;	// 재생할 애니메이션 인덱스
	DWORD	dwSpeed;			// 애니메이션 재생 속도
	DWORD	dwFrameTime;		// 애니메이션 시작 시간
	UINT	tRGB;
	TCHAR* szImgKey;

	//tagFrame() {}

	/*tagFrame()
		: eDir(DIR_DOWN), iFrameStart(0), iFrameEnd(0), iFrameAnimation(0), dwSpeed(200), dwFrameTime(0)
	{}

	tagFrame(DIRECTION Dir, TCHAR* ImgKey, int FrameStart, int FrameEnd, int FrameAnimation, DWORD Speed, DWORD FrameTime)
		: eDir(Dir), szImgKey(ImgKey), iFrameStart(FrameStart), iFrameEnd(FrameEnd), iFrameAnimation(FrameAnimation), dwSpeed(Speed), dwFrameTime(FrameTime)
	{}
*/
	tagFrame()
		:tDraw({}), szImgKey(nullptr), dwDelay(0), iOffsetX(0), iOffsetY(0), tRGB(0) {}

	tagFrame(const DRAW& _tDraw, TCHAR* const& _pImgKey,
		const DWORD& _dwDelay = 100,
		const int& _iOffsetX = 0, const int& _iOffsetY = 0,
		const EDrawWay& _eReverse = EDrawWay::END,
		const float& _fAngle = 0.f,
		const UINT _tRGB = RGB(255, 255, 255))
		:tDraw(_tDraw), szImgKey(_pImgKey), dwDelay(_dwDelay), iOffsetX(_iOffsetX), iOffsetY(_iOffsetY), eDrawWay(_eReverse), fAngle(_fAngle), tRGB(_tRGB) {}

}FRAME;

typedef struct tagBodyInfo
{
	FRAME tFrame;

	tagBodyInfo()
	{};

	tagBodyInfo(FRAME Frame)
		: tFrame(Frame)
	{}
};

typedef struct tagHairInfo
{
	FRAME tFrame;

	tagHairInfo()
	{};

	tagHairInfo(FRAME Frame)
		: tFrame(Frame)
	{}
};

typedef struct tagHandsInfo
{
	FRAME tFrame;

	tagHandsInfo()
	{};

	tagHandsInfo(FRAME Frame)
		: tFrame(Frame)
	{}
};

typedef struct tagShirtInfo
{
	FRAME tFrame;

	tagShirtInfo()
	{};
	tagShirtInfo(FRAME Frame)
		: tFrame(Frame)
	{}
};
typedef struct tagFileObj
{
	INFO		tInfo;
	OBJID		eID;
	BLOCK_TYPE	eBlockType;

	tagFileObj()
	{
		ZeroMemory(&tInfo, sizeof(INFO));
		eID = OBJ_END;
		eBlockType = END_BLOCK;
	}
}FILEOBJ;

typedef struct tagImgInfo
{
	DIRECTION eDir;
	int		iFrameStart;		// 프레임 시작 시점
	int		iFrameEnd;			// 프레임 종료 지점
	int		iFrameAnimation;	// 재생할 애니메이션 인덱스
	DWORD	dwSpeed;			// 애니메이션 재생 속도
	DWORD	dwFrameTime;		// 애니메이션 시작 시간

	TCHAR* szImgKey;


};

