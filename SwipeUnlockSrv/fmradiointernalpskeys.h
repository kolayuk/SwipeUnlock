/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: P&S data for FMRadio
*
*/
#ifndef FMRADIOINTERNALPSKEYS_H
#define FMRADIOINTERNALPSKEYS_H

#include <e32cmn.h>

// FMRadio Application UID
const TUid KFMRadioPSUid = { 0x10207A89 };

///////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                 ///
/// Data properties. These properties are published by fmradio and used by other applications. ///
///                                                                                                 ///
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* Currently active channel's ID.
* Value <code>KErrNotFound</code> means that no preset channel is active.
* Type <code>RProperty::EInt</code>.
*/
const TUint32 KFMRadioPSDataChannel = 0x00000000;

/**
* Currently active frequency.
* Frequency unit is in kHz.
* Type <code>RProperty::EInt</code>.
*/
const TUint32 KFMRadioPSDataFrequency = 0x00000001;
    
/**
* Current power state of the radio.
* Type <code>RProperty::EInt</code>.
* @see TFMRadioPSRadioPowerState.
*/
const TUint32 KFMRadioPSDataRadioPowerState = 0x00000002;

/**
* Power state of the radio.
*/
enum TFMRadioPSRadioPowerState
    {
    EFMRadioPSRadioPowerStateUninitialized,  /**< The key is not yet initialized. */
    EFMRadioPSRadioPowerOn,					/**< Radio power on. */
    EFMRadioPSRadioPowerOff					/**< Radio power off. */
    };

/**
* Current volume level.
* Scale is from 1-10.
* Type <code>RProperty::EInt</code>.
*/
const TUint32 KFMRadioPSDataVolume = 0x00000003;

/**
* Changing of this value means that channel
* data of specified channel ID has changed.
* The value remains indicating the last changed channel ID.
* Value <code>KErrNone</code> means that no channel data has been changed yet.
* Type <code>RProperty::EInt</code>.
*/
const TUint32 KFMRadioPSDataChannelDataChanged = 0x00000004;

/**
* The current tuning state.
* Type <code>RProperty::EInt</code>.
* @see TFMRadioPSTuningState.
*/
const TUint32 KFMRadioPSDataTuningState = 0x00000006;

/**
* Possible tuning states.
*/
enum TFMRadioPSTuningState 
    {
    EFMRadioPSTuningUninitialized,    /**< Currently not tuning. */
    EFMRadioPSTuningStarted,			 /**< Tuning has been started an lasted less than one second. */
    EFMRadioPSTuningContinues         /**< Tuning has taken more than one second. */
    };

/**
* Current mute state of radio.
* Type <code>RProperty::EInt</code>.
* @see TFMRadioPSRadioMuteState.
*/
const TUint32 KFMRadioPSDataRadioMuteState = 0x00000007;

/**
* Mute state of radio.
*/
enum TFMRadioPSRadioMuteState
    {
    EFMRadioPSMuteStateUninitialized,    /**< The key has not yet been initialized. */
    EFMRadioPSMuteStateOn,               /**< Radio mute state is on. */
    EFMRadioPSMuteStateOff               /**< Radio mute state is off. */
    };

/**
* Indicates if FM Radio is running or closing.
* Type <code>RProperty::EInt</code>.
* @see TFMRadioPSApplicationRunningState.
*/
const TUint32 KFMRadioPSDataApplicationRunning = 0x00000008;

/**
* FM Radio application running states.
*/
enum TFMRadioPSApplicationRunningState
    {
    EFMRadioPSApplicationUninitialized,  /**< FM Radio application's state is not yet initialized. */
    EFMRadioPSApplicationRunning,        /**< FM Radio application is running. */
    EFMRadioPSApplicationClosing         /**< FM Radio application is closing. */
    };

/**
* Indicates the current antenna connectivity status.
* Type <code>RProperty::EInt</code>.
* @see TFMRadioPSHeadsetStatus
*/
const TUint32 KFMRadioPSDataHeadsetStatus = 0x00000009;

/**
* Current antenna status.
*/
enum TFMRadioPSHeadsetStatus
    {
    EFMRadioPSHeadsetUninitialized,  /**< The antenna status is uninitialized. */
    EFMRadioPSHeadsetDisconnected,   /**< The antenna is disconnected. */
    EFMRadioPSHeadsetConnected       /**< The antenna is connected. */
    };

/**
* The current frequency decimal count.
* Type <code>RProperty::EInt</code>.
* @see TFMRadioPSFrequencyDecimalCount.
*/
const TUint32 KFMRadioPSDataFrequencyDecimalCount = 0x00000010;

/**
* The current frequency decimal count.
*/
enum TFMRadioPSFrequencyDecimalCount
    {
	EFMRadioPSFrequencyDecimalCountUninitialized,	/**< Frequency decimal count has not yet been initialized. */
    EFMRadioPSFrequencyOneDecimal,     				/**< Frequency accuracy is one decimal. */
    EFMRadioPSFrequencyTwoDecimals,    				/**< Frequency accuracy is two decimals. */
    EFMRadioPSFrequencyThreeDecimals   				/**< Frequency accuracy is three decimals. */
    };

/**
* Current moving state of application.
* Note that even if user activates the moving state,
* the move can be still canceled.
* Type <code>RProperty::EInt</code>.
* @see TFMRadioPSMovingState
*/
const TUint32 KFMRadioPSDataMovingState = 0x00000011;

/**
* The current moving state.
*/
enum TFMRadioPSMovingState
    {
    EFMRadioPSMovingStateUninitialized,      /**< Moving state is uninitialized. */
    EFMRadioPSMovingStateOn,                 /**< User has activated moving state. */
    EFMRadioPSMovingStatePerforming,         /**< User has performed a channel move. */
    EFMRadioPSMovingStateOff                 /**< Moving state is off. */
    };

/**
* Flag to indicate if we're connected to the network.
*/
const TUint32 KFMRadioPSDataNetworkConnected = 0x00000014;

/**
* Flag to indicate if loudspeaker is in use
*/
const TUint32 KFMRadioPSDataLoudspeakerStatus = 0x00000015;
/**
* Current speaker status.
*/
enum TFMRadioPSLoudspeakerStatus
    {
    EFMRadioPSLoudspeakerUninitialized,  /**< The speaker status is uninitialized. */
    EFMRadioPSLoudspeakerNotInUse,   /**< The speaker is not in use. */
    EFMRadioPSLoudpeakerInUse       /**< The speaker is in use. */
    };

/**
* RDS Program Service information, property type is text.
*/

const TUint32 KFMRadioPSDataRDSProgramService = 0x00000016;

/**
* RDS Radio Text information.
* Type <code>RProperty::EText</code>.
*/
const TUint32 KFMRadioPSDataRDSRadioText = 0x00000017;

/**
 * Name of the current channel.
 * Type <code>RProperty::EText</code>.
 */
const TUint32 KFMRadioPSDataChannelName = 0x00000018;


//////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                    ///
/// Control properties. These properties are published by other applications and used by FMRadio. 	   ///
///                                                                                                    ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* Sets mute state on or off.
* Type <code>RProperty::EInt</code>.
* @see TFMRadioPSRadioMuteState.
*/
const TUint32 KFMRadioPSControlSetRadioMuteState = 0x00001006;


/**
* Increases or decreases volume level.
* Type <code>RProperty::EInt</code>.
* @see TFMRadioPSAdjustVolume.
*/
const TUint32 KFMRadioPSControlAdjustVolume = 0x00001005;

/**
* Volume step direction.
*/
enum TFMRadioPSAdjustVolume
    {
    EFMRadioPSAdjustVolumeUninitialized = 0, /**< The key has not yet been initialized. */
    EFMRadioPSIncreaseVolume,				/**< Increase volume. */
    EFMRadioPSDecreaseVolume					/**< Decrease volume. */
    };

//////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                    ///
/// Control properties. These properties are published by other applications and used by FM Radio. ///
///                                                                                                    ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* Steps up or down a channel in channel list.
* Type <code>RProperty::EInt</code>.
* @see TFMRadioPSStepToChannel.
*/
const TUint32 KFMRadioPSControlStepToChannel = 0x00001000;

/**
* Step direction of channel step.
*/
enum TFMRadioPSStepToChannel
    {
    EFMRadioPSStepToChannelUninitialized,    /**< Value of the key has not yet been initialized. */
    EFMRadioPSStepToChannelUp,				/**< Step to next channel up. */
    EFMRadioPSStepToChannelDown				/**< Step to next channel down. */
    };
    
/**
* Seeks to next active frequency up or down.
* Type <code>RProperty::EInt</code>.
* @see TFMRadioPSSeek.
*/
const TUint32 KFMRadioPSControlSeek = 0x00001002;

/**
* Seek direction.
*/
enum TFMRadioPSSeek
    {
    EFMRadioPSSeekUninitialized, /**< Value of the key has not yet been initialized. */
    EFMRadioPSSeekUp,			/**< Seek up. */
    EFMRadioPSSeekDown			/**< Seek down. */
    };

const TUint32 KFMRadioActiveIdlePresetListCount = 0x00001003;
const TUint32 KFMRadioActiveIdlePresetListFocus = 0x00001004;


#endif
