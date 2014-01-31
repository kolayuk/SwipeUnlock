/*
 ============================================================================
 Name		: DragDetector.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CSplashScreen declaration
 ============================================================================
 */

#ifndef DRAGDETECTOR_H
#define DRAGDETECTOR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <w32std.h>
#include <ImageConversion.h>

// CLASS DECLARATION
class CSplashScreen : public CCoeControl
	{
public:
    ~CSplashScreen();
    static CSplashScreen* NewL(TDes& aPathToPicPortrait,TDes& aPathToPicLandscape);
    static CSplashScreen* NewLC(TDes& aPathToPicPortrait,TDes& aPathToPicLandscape);
    RWsSprite* iSprite;
    void Hide();
private:
    CSplashScreen();
    TSpriteMember Member;
    void ConstructL(TDes& aPathToPicPortrait,TDes& aPathToPicLandscape);
	RWindowGroup* iWinGroup;
    CFbsBitmap* BitMap;
    void LoadImage(TDesC& path);
    void GetFileType(const TDesC& aFileName, TDes8& aFileType);
	};

#endif // DRAGDETECTOR_H
