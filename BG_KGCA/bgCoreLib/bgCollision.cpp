#include "bgCollision.h"



bool RectInPoint(RECT & rectDest, POINT & posSrc)
{
	return false;
}

bool RectInRect(RECT & rectDest, RECT & rectSrc)
{
	//POINT posCenterDest, posCenterSrc;
	//posCenterDest.x = (rectDest.right + rectDest.left) / 2;
	//posCenterDest.y = (rectDest.top + rectDest.bottom) / 2;
	//posCenterSrc.x = (rectSrc.right + rectSrc.left) / 2;
	//posCenterSrc.y = (rectSrc.top + rectSrc.bottom) / 2;

	//POINT RadiusS1, RadiusS2;

	//if (Radius.x <= (RadiusS1.x + RadiusS2.x) && Radius.y <= (RadiusS1.y + RadiusS2.y))
	//{
	//	return true;
	//}
	return false;
}

bool SphereInSphere(bgSphere & sphDest, bgSphere & sphSrc)
{
	//float fDistanceRadius = sphDest.radius + sphSrc.radius;
	//float fX = abs(sphDest.pos.x - sphSrc.pos.x);
	//float fY = abs(sphDest.pos.y - sphSrc.pos.y);
	//float fDistanceCenter = sqrt((fX*fX) + (fY*fY));
	//if (fDistanceCenter <= fDistanceRadius)
	//{
	//	return true;
	//}
	return false;
}

bool SphereInSphere(RECT & rectDest, RECT & rectSrc)
{
	//POINT posCenterDest, posCenterSrc;
	//posCenterDest.x = (rectDest.right + rectDest.left) / 2;
	//posCenterDest.y = (rectDest.top + rectDest.bottom) / 2;
	//posCenterSrc.x = (rectSrc.right + rectSrc.left) / 2;
	//posCenterSrc.y = (rectSrc.top + rectSrc.bottom) / 2;

	//float fS1, fS2;
	//float fX, fY;
	//fX = rectDest.right - rectDest.left;
	//fY = rectDest.bottom - rectDest.top;
	//fS1 = (fX > fY) ? fX : fY;
	//fX = rectSrc.right - rectSrc.left;
	//fY = rectSrc.bottom - rectSrc.top;
	//fS2 = (fX > fY) ? fX : fY;

	//float fDistanceRadius = fS1 + fS2;
	//fX = abs(sphDest.pos.x - sphSrc.pos.x);
	//fY = abs(sphDest.pos.y - sphSrc.pos.y);
	//float fDistanceCenter = sqrt((fX*fX) + (fY*fY));
	//if (fDistanceCenter <= fDistanceRadius)
	//{
	//	return true;
	//}
	return false;
}

bgCollision::bgCollision()
{
}


bgCollision::~bgCollision()
{
}
