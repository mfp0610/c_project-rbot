
#ifndef _Map_Utils_H
#define _Map_Utils_H

#include <math.h>

// 正弦表 (将浮点数 *1024 整型化)
extern int	g_nSin[64];

// 余弦表 (将浮点数 *1024 整型化)
extern int	g_nCos[64];

int	g_InternalDirSinCos(int pSinCosTable[], int nDir, int nMaxDir);

int g_DirSin(int nDir, int nMaxDir);

int g_DirCos(int nDir, int nMaxDir);

int	g_GetDistance(int nX1, int nY1, int nX2, int nY2);

int	g_GetDirIndex(int nX1, int nY1, int nX2, int nY2);

int g_GetDirDiff(int nOriginX, int nOriginY, int nTargetX, int nTargetY, int nX, int nY);

int g_GetDirAngle(int nOriginX, int nOriginY, int nTargetX, int nTargetY, int nX, int nY);

int g_Dir64To8(int nDir);

int g_Dir8To64(int nDir);

#endif