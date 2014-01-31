/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Music Player stautus observer
*
*/


#include <mpxplaybackutility.h>
#include <mpxplaybackmessage.h>
#include <mpxmedia.h>
#include <mpxmediageneraldefs.h>
#include <mpxmediamusicdefs.h>
#include <mpxmessagegeneraldefs.h>
#include <mpxplaybackmessagedefs.h>
#include <mpxalbumartutil.h>
//#include <mpxlog.h>

#include "aiplayerpluginengine.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAiPlayerPluginEngine::ConstructL
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::ConstructL()
    {
    // Get the playback utility instance from engine.
    //iPlaybackUtility = MMPXPlaybackUtility::NewL( KPbModeActivePlayer, this );
    iPlaybackUtility = MMPXPlaybackUtility::NewL( KMusicPlayerAppUid, this );
#ifndef _DEBUG
    iAlbumArtUtil = CMPXAlbumArtUtil::NewL();
#endif
    if (iPlaybackUtility->StateL() == EPbStatePlaying)
        {
    	  RequestMediaL();
        }
    }

// ---------------------------------------------------------------------------
// CAiPlayerPluginEngine::NewL
// ---------------------------------------------------------------------------
//
CAiPlayerPluginEngine* CAiPlayerPluginEngine::NewL( 
        MAiPlayerPluginEngineObserver& aObserver )
    {
    CAiPlayerPluginEngine* self = new ( ELeave ) 
            CAiPlayerPluginEngine( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CAiPlayerPluginEngine::CAiPlayerPluginEngine
// ---------------------------------------------------------------------------
//
CAiPlayerPluginEngine::CAiPlayerPluginEngine( 
        MAiPlayerPluginEngineObserver& aObserver )
    : iObserver( &aObserver ),
      iPlaybackUtility( NULL ),
      iTitle( NULL ),
      iArtist( NULL ),
      iUri( NULL ),
      iMedia( NULL ),
      iPosition( KErrNotFound ),
      iDuration( KErrNotFound ),
      iExtractingAlbumArt( EFalse ),
      iSkipping( EFalse )
    {
    }

// ---------------------------------------------------------------------------
// CAiPlayerPluginEngine::~CAiPlayerPluginEngine
// ---------------------------------------------------------------------------
//
CAiPlayerPluginEngine::~CAiPlayerPluginEngine()
    {
    if ( iPlaybackUtility )
        {
        iPlaybackUtility->Close();
        }
    delete iMedia;
    if (iAlbumArtUtil) {delete iAlbumArtUtil;}
    delete iTitle;
    delete iArtist;
    delete iUri;
        
    }

// ---------------------------------------------------------------------------
// From MMPXPlaybackObserver
// Handle playback message.
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::HandlePlaybackMessage( CMPXMessage* aMessage, 
        TInt aError )
    {
    if ( aError == KErrNone && aMessage )
        {
        TRAP_IGNORE( DoHandlePlaybackMessageL( *aMessage ) );
        }
    }

// ---------------------------------------------------------------------------
// From MMPXPlaybackCallback
// Handle playback property.
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::HandlePropertyL( TMPXPlaybackProperty aProperty, 
        TInt aValue, TInt aError )
    {
    DoHandlePropertyL( aProperty, aValue, aError );
    }

// ---------------------------------------------------------------------------
// From MMPXPlaybackCallback
// Method is called continously until aComplete=ETrue, signifying that
// it is done and there will be no more callbacks
// Only new items are passed each time
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::HandleSubPlayerNamesL(
    TUid /* aPlayer */,
    const MDesCArray* /* aSubPlayers */,
    TBool /* aComplete */,
    TInt /* aError */ )
    {
    // do nothing
    }

// ---------------------------------------------------------------------------
// From MMPXPlaybackCallback
// Handle media
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::HandleMediaL( const CMPXMedia& aMedia, 
        TInt aError )
    {
    if ( KErrNone == aError )
        {
        delete iUri;
        iUri = NULL;
        if (aMedia.IsSupported(KMPXMediaGeneralUri))
            {
            TParsePtrC filePath(aMedia.ValueText(KMPXMediaGeneralUri) );
            iUri = filePath.FullName().AllocL();
            }
        
		delete iTitle;
		iTitle = NULL;
        if ( aMedia.IsSupported( KMPXMediaGeneralTitle ) )
            {
            iTitle = ( aMedia.ValueText( KMPXMediaGeneralTitle ) ).AllocL();
            }
        else if ( aMedia.IsSupported( KMPXMediaGeneralDuration))
        {
            RDebug::Print(_L("duration found"));
            TInt val=aMedia.ValueTObjectL<TInt>( KMPXMediaGeneralDuration );
            RDebug::Print(_L("val %d"),val);
            iDuration=val/KMPXOneSecInMilliSecs;
        }
        else if ( aMedia.IsSupported( KMPXMediaGeneralUri ) )
            {
            TParsePtrC filePath( aMedia.ValueText( KMPXMediaGeneralUri ) );
            iTitle = (filePath.Name()).AllocL();
            }
		delete iArtist;
		iArtist = NULL;
		if ( aMedia.IsSupported( KMPXMediaMusicArtist ) )
		    {
		    iArtist = ( aMedia.ValueText( KMPXMediaMusicArtist ) ).AllocL();
		    }

		iObserver->TrackInfoChanged(iTitle ? *iTitle : KNullDesC(), iArtist ? *iArtist : KNullDesC());

		if (!iSkipping)
            {
            if (iExtractingAlbumArt)
                {
                if (iAlbumArtUtil){iAlbumArtUtil->CancelRequest();}
                iExtractingAlbumArt=EFalse;
                }
            
            if ( aMedia.IsSupported( KMPXMediaMusicAlbumArtFileName ) )
                {
                delete iMedia;
                iMedia=NULL;
                iMedia = CMPXMedia::NewL( aMedia );
                TRAPD(err,iAlbumArtUtil->ExtractAlbumArtL(
                        *iMedia,
                        *this,
                        KAlbumArtSize,
                        EFalse));
                
                if (err != KErrNone)
                    {
                    iObserver->AlbumArtChanged(NULL);
                    }
                }
            else
                {
                iObserver->AlbumArtChanged(NULL);
                }

            }
		else
		    {
		    iObserver->AlbumArtChanged(NULL);
		    }
        }
    }

// ---------------------------------------------------------------------------
// From MMPXPlaybackCallback
// Handle completion of a asynchronous command
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::HandlePlaybackCommandComplete( 
        CMPXCommand* /*aCommandResult*/, TInt /*aError*/ )
    {
    // do nothing
    }

// ---------------------------------------------------------------------------
// From MMPXAlbumArtUtilObserver
// Notify that extraction of album art started.
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::ExtractAlbumArtStarted()
    {
    iExtractingAlbumArt = ETrue;
    }

// ---------------------------------------------------------------------------
// From MMPXAlbumArtUtilObserver
// Notify that the extraction of album art has completed.
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::ExtractAlbumArtCompleted( 
        CFbsBitmap* aBitmap, 
        TInt aErr )
    {
    if (aErr == KErrNone)
        {
        iObserver->AlbumArtChanged(aBitmap);
        }
    else
        {
        iObserver->AlbumArtChanged(NULL);
        }
    iExtractingAlbumArt = EFalse;
    }

// ---------------------------------------------------------------------------
// Get the current state of the active player
// ---------------------------------------------------------------------------
//
TMPXPlaybackState CAiPlayerPluginEngine::PlayerState()
    {
    TMPXPlaybackState state( EPbStateNotInitialised );
    TRAP_IGNORE( state = iPlaybackUtility->StateL() );
    return state;
    }

// ---------------------------------------------------------------------------
// CAiPlayerPluginEngine::TitleL
// ---------------------------------------------------------------------------
//
const TDesC& CAiPlayerPluginEngine::TitleL()
    {

    if ( iTitle )
        {
        return *iTitle;
        }
     else
        {
        RequestMediaL();
        return KNullDesC;
        }
    }

// ---------------------------------------------------------------------------
// CAiPlayerPluginEngine::Artist
// ---------------------------------------------------------------------------
//
const TDesC& CAiPlayerPluginEngine::Artist()
    {
    if ( iArtist )
        {
        return *iArtist;
        }
     else
        {
        return KNullDesC;
        }
    }
// ---------------------------------------------------------------------------
// CAiPlayerPluginEngine::Artist
// ---------------------------------------------------------------------------
//
const TDesC& CAiPlayerPluginEngine::Uri()
    {
    if ( iUri )
        {
        return *iUri;
        }
     else
        {
        return KNullDesC;
        }
    }

// ----------------------------------------------------
// CAiPlayerPluginEngine::Position
// ----------------------------------------------------
//
TInt CAiPlayerPluginEngine::Position()
    {
    return iPosition;
    }

// ----------------------------------------------------
// CAiPlayerPluginEngine::Duration
// ----------------------------------------------------
//
TInt CAiPlayerPluginEngine::Duration()
    {
    return iDuration;
    }

// ---------------------------------------------------------------------------
// Handle playback message.
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::DoHandlePlaybackMessageL( 
        const CMPXMessage& aMessage )
    {

    TMPXMessageId id( 
            aMessage.ValueTObjectL<TMPXMessageId>( KMPXMessageGeneralId ) );
    if ( KMPXMessageGeneral == id )
        {
        TInt event( aMessage.ValueTObjectL<TInt>( KMPXMessageGeneralEvent ) );
        switch ( event )
            {
            case TMPXPlaybackMessage::EPropertyChanged:
                {
                TInt error( KErrNone );
                DoHandlePropertyL(
                    aMessage.ValueTObjectL<TInt>( KMPXMessageGeneralType ),
                    aMessage.ValueTObjectL<TInt>( KMPXMessageGeneralData ),
                    error );
                break;
                }
            case TMPXPlaybackMessage::EStateChanged:
                {
				TMPXPlaybackState state( 
				        aMessage.ValueTObjectL<TMPXPlaybackState>( 
				                KMPXMessageGeneralType ));

                DoHandleStateChangedL( state );
                break;
                }
            case TMPXPlaybackMessage::EMediaChanged:
            case TMPXPlaybackMessage::EPlaylistUpdated:
                {
                MMPXSource* s = iPlaybackUtility->Source();
                if ( s )
                    {
                    RequestMediaL();
                    }
                else
                    {
                    iObserver->PlaylisIsEmpty();
                    }
                break;
                }
            case TMPXPlaybackMessage::ECommandReceived:
                {
                break;
                }
            case TMPXPlaybackMessage::EActivePlayerChanged:
                {
                iPlaybackUtility->PropertyL( *this, EPbPropertyPosition );
                iPlaybackUtility->PropertyL( *this, EPbPropertyDuration );
                DoHandleStateChangedL( iPlaybackUtility->StateL() );
                // refresh media property
                RequestMediaL();
                break;
                }
            case TMPXPlaybackMessage::ESkipping:
                {
                if (iAlbumArtUtil){iAlbumArtUtil->CancelRequest();}
                iObserver->Opening();
                iSkipping =ETrue;
                break;
                }
            case TMPXPlaybackMessage::ESkipEnd:
                {
                iSkipping = EFalse;
                break;
                }
            default:
                {
                break;
                }
            }
        }
    }

// ---------------------------------------------------------------------------
// Handle playback property.
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::DoHandlePropertyL( TInt aProperty, TInt aValue, 
        TInt aError )
    {
    if ( KErrNone == aError )
        {
        switch ( aProperty	)
            {
            case EPbPropertyPosition:
                {
				iPosition = aValue / KMPXOneSecInMilliSecs;
                iObserver->PlaybackPositionChanged( iPosition );
                break;
                }
            case EPbPropertyDuration:
                {
				iDuration = aValue / KMPXOneSecInMilliSecs;
                break;
                }
            default:
                {
                break;
                }
            }
        }
    }

// ---------------------------------------------------------------------------
// Handle playback state changed.
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::DoHandleStateChangedL( TMPXPlaybackState aState )
    {
    //TMPlayerState state = MapState( aState );
    if (aState != EPbStateInitialising)
        {
        iObserver->PlayerStateChanged(aState);
        }
    else 
        {
        iObserver->Opening();
        }
    }

// ---------------------------------------------------------------------------
// Displays error notes.
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::HandleErrorL( TInt aError )
    {
    }

// ---------------------------------------------------------------------------
// Map states from TMPXPlaybackState to TMPlayerState
// ---------------------------------------------------------------------------
//
/*
TMPlayerState CAiPlayerPluginEngine::MapState( TMPXPlaybackState aState )
    {
	TMPlayerState state = EMPlayerStateOther;
    switch ( aState )
        {
        case EPbStatePlaying:
            state = EMPlayerStatePlaying;
            break;
        case EPbStatePaused:
            state = EMPlayerStatePaused;
            break;
        case EPbStateSeekingForward:
        case EPbStateSeekingBackward:
            state = EMPlayerStateSeeking;
            break;
        case EPbStateNotInitialised:
        case EPbStateInitialising:
            state = EMPlayerStateStarting;
            break;
        case EPbStateStopped:
            state = EMPlayerStateStopped;
            break;
        default:
            break;
        }
    return state;
    }
*/
// ---------------------------------------------------------------------------
// Requests Media.
// ---------------------------------------------------------------------------
//
void CAiPlayerPluginEngine::RequestMediaL()
    {
    MMPXSource* s = iPlaybackUtility->Source();
    if ( s )
        {
        RArray<TMPXAttribute> attrs;
        CleanupClosePushL(attrs);
        attrs.Append( KMPXMediaGeneralUri );
        attrs.Append( KMPXMediaGeneralTitle );
        attrs.Append( KMPXMediaMusicArtist );
        attrs.Append( KMPXMediaMusicAlbumArtFileName );
        iPlaybackUtility->PropertyL( *this, EPbPropertyDuration );
        s->MediaL( attrs.Array(), *this );
        CleanupStack::PopAndDestroy( &attrs );
        }
    }
//  End of File
