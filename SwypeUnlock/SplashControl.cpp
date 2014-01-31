/*
 ============================================================================
 Name		: DragDetector.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CSplashScreen implementation
 ============================================================================
 */

#include "SplashControl.h"
#include <eikenv.h>
#include <w32std.h>
#include <apgwgnam.h>
#include <apgcli.h>

CSplashScreen::CSplashScreen()
	{
	// No implementation required
	}

CSplashScreen::~CSplashScreen()
	{
	}

CSplashScreen* CSplashScreen::NewLC(TDes& aPathToPicPortrait,TDes& aPathToPicLandscape)
	{
    CSplashScreen* self = new (ELeave) CSplashScreen();
	CleanupStack::PushL(self);
    self->ConstructL(aPathToPicPortrait,aPathToPicLandscape);
    return self;
}

void CSplashScreen::Hide()
{
    iSprite->Close();
    iWinGroup->Close();
}

CSplashScreen* CSplashScreen::NewL(TDes& aPathToPicPortrait,TDes& aPathToPicLandscape)
	{
    CSplashScreen* self = CSplashScreen::NewLC(aPathToPicPortrait,aPathToPicLandscape);
	CleanupStack::Pop(); // self;
	return self;
	}

void CSplashScreen::ConstructL(TDes& aPathToPicPortrait,TDes& aPathToPicLandscape)
	{

    iWinGroup = new (ELeave) RWindowGroup(CEikonEnv::Static()->WsSession());
    iWinGroup->Construct((TUint32)iWinGroup);
    iWinGroup->EnableReceiptOfFocus(EFalse); // Don't capture any key events.
    iWinGroup->SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront);

    iSprite= new (ELeave) RWsSprite(CEikonEnv::Static()->WsSession());
    iSprite->Construct(*iWinGroup,TPoint(0,0),0);
    if (CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth==360) {LoadImage(aPathToPicPortrait);}
    else LoadImage(aPathToPicLandscape);
    TSpriteMember Member;
    Member.iBitmap=BitMap;
    Member.iMaskBitmap=NULL;
    Member.iOffset=TPoint(0,0);
    Member.iInterval=TTimeIntervalMicroSeconds32(60*1000000);
    Member.iInvertMask=EFalse;
    iSprite->AppendMember(Member);

    iSprite->SetPosition(TPoint(0,0));
    iSprite->Activate();
    CEikonEnv::Static()->WsSession().Flush();
	}

void CSplashScreen::LoadImage(TDesC& path)
{
    TBuf8<255> type;
    GetFileType(path,type);
    CImageDecoder* iImage=CImageDecoder::FileNewL(CCoeEnv::Static()->FsSession(),path,type,CImageDecoder::EOptionAlwaysThread);
    BitMap = new (ELeave) CFbsBitmap;
    TFrameInfo iFrameInfo = iImage->FrameInfo(0);
    BitMap->Create(iFrameInfo.iOverallSizeInPixels, iFrameInfo.iFrameDisplayMode );
    TRequestStatus ReqStat;
    iImage->Convert(&ReqStat,*BitMap);
    User::WaitForRequest(ReqStat);
    delete iImage;
}
void CSplashScreen::GetFileType(const TDesC& aFileName, TDes8& aFileType)
{
    TEntry FileEntry;
    if(CCoeEnv::Static()->FsSession().Entry(aFileName,FileEntry) == KErrNone)
    {
        TBuf8<255> FileBuffer;
        if(!FileEntry.IsDir())
        {
            TInt FileSize = FileEntry.iSize;
            if(FileSize > 255){FileSize = 255;}
            if(CCoeEnv::Static()->FsSession().ReadFileSection(aFileName,0,FileBuffer,FileSize) == KErrNone)
            {
                RApaLsSession RSession;
                if(RSession.Connect() == KErrNone)
                {
                    TDataRecognitionResult FileDataType;
                    RSession.RecognizeData(aFileName,FileBuffer,*&FileDataType);
                    aFileType.Copy(FileDataType.iDataType.Des8());
                    RSession.Close();
                }
            }
        }
    }
}


