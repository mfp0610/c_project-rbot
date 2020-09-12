
#include "stdafx.h"
#include "MapUtils.h"

// 正弦表 (将浮点数 *1024 整型化)
int	g_nSin[64] = 
{
		1024,	1019,	1004,	979,	946,	903,	851,	791,
		724,	649,	568,	482,	391,	297,	199,	100,	
        0,	   -100,	-199,	-297,	-391,	-482,	-568,	-649,	
        -724,	-791,	-851,	-903,	-946,	-979,	-1004,	-1019,	
        -1024,	-1019,	-1004,	-979,	-946,	-903,	-851,	-791,	
        -724,	-649,	-568,	-482,	-391,	-297,	-199,	-100,	
        0,	     100,	199,	297,	391,	482,	568,	649,	
        724,	791,	851,	903,	946,	979,	1004,	1019
};

//---------------------------------------------------------------------------
// 余弦表 (将浮点数 *1024 整型化)
int	g_nCos[64] = 
{
		0,	    -100,	-199,	-297,	-391,	-482,	-568,	-649,	
        -724,	-791,	-851,	-903,	-946,	-979,	-1004,	-1019,	
        -1024,	-1019,	-1004,	-979,	-946,	-903,	-851,	-791,	
        -724,	-649,	-568,	-482,	-391,	-297,	-199,	-100,	
        0,	     100,	199,	297,	391,	482,	568,	649,	
        724,	791,	851,	903,	946,	979,	1004,	1019,	
        1024,	1019,	1004,	979,	946,	903,	851,	791,	
        724,	649,	568,	482,	391,	297,	199,	100,
};

int	g_InternalDirSinCos(int pSinCosTable[], int nDir, int nMaxDir)
{
	if (nDir < 0 || nDir >= nMaxDir)
		return -1;
	
	int	nIndex = (nDir << 6) / nMaxDir;
	
	return pSinCosTable[nIndex];
}

int g_DirSin(int nDir, int nMaxDir)
{
	return g_InternalDirSinCos( g_nSin, nDir, nMaxDir );
}

int g_DirCos(int nDir, int nMaxDir)
{
	return g_InternalDirSinCos( g_nCos, nDir, nMaxDir );
}

int	g_GetDistance(int nX1, int nY1, int nX2, int nY2)
{
	return (int)sqrt((nX1 - nX2) * (nX1 - nX2) + (nY1 - nY2) * (nY1 - nY2));
}

int	g_GetDirIndex(int nX1, int nY1, int nX2, int nY2)
{
	int	nRet = -1;
	
	if (nX1 == nX2 && nY1 == nY2)
		return -1;

	nX1 = nX1 << 6;
	nY1 = nY1 << 6;
	nX2 = nX2 << 6;
	nY2 = nY2 << 6;
	
	int nDistance = g_GetDistance(nX1, nY1, nX2, nY2);
	
	if (nDistance == 0 ) return -1;
	
	int nYLength = nY2 - nY1;
	int nSin = (nYLength << 10) / nDistance;
	
	int nCompensation = 0;
	for (int i = 0; i < 32; i++)
	{
		if (nSin > g_nSin[i])
		{
			if (nSin == g_nSin[i - 1])
				nCompensation = 1;
			break;
		}
		nRet = i;
	}
	
	if (nRet != 0)
	{
		if ((nX2 - nX1) >= 0)
		{
			nRet = 63 - nRet;
			if (nCompensation == 1)
			{
				nRet += 1;
			}
		}		
	}

	return nRet;
}

int g_GetDirDiff(int nOriginX, int nOriginY, int nTargetX, int nTargetY, int nX, int nY)
{
	int nTargetDir = g_GetDirIndex(nOriginX, nOriginY, nTargetX, nTargetY);
	int nTestDir = g_GetDirIndex(nOriginX, nOriginY, nX, nY);
	int dirDiff = nTargetDir - nTestDir;
	if (dirDiff < 0)
		dirDiff += 64;
	if (dirDiff > 32)
		dirDiff = 64 - dirDiff;
	return dirDiff;
}

int g_GetDirAngle(int nOriginX, int nOriginY, int nTargetX, int nTargetY, int nX, int nY)
{
	int nTargetDir = g_GetDirIndex(nOriginX, nOriginY, nTargetX, nTargetY);
	int nTestDir = g_GetDirIndex(nOriginX, nOriginY, nX, nY);
	int dirAngle = nTargetDir - nTestDir;
	if (dirAngle < 0)
		dirAngle += 64;
	return dirAngle;
}

int g_Dir64To8(int nDir)
{
	return ((nDir + 4) >> 3) & 0x07;
}

int g_Dir8To64(int nDir)
{
	return nDir << 3;
}
