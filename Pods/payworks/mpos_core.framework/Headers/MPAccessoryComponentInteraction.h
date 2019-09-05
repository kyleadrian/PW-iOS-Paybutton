//
// PAYWORKS GMBH ("COMPANY") CONFIDENTIAL
// Copyright (c) 2016 Payworks GmbH, All Rights Reserved.
//
// NOTICE:  All information contained herein is, and remains the property of COMPANY. The intellectual and technical concepts contained
// herein are proprietary to COMPANY and may be covered by European or foreign Patents, patents in process, and are protected by trade secret or copyright law.
// Dissemination of this information or reproduction of this material is strictly forbidden unless prior written permission is obtained
// from COMPANY.  Access to the source code contained herein is hereby forbidden to anyone except current COMPANY employees, managers or contractors who have executed
// Confidentiality and Non-disclosure agreements explicitly covering such access.
//
// The copyright notice above does not evidence any actual or intended publication or disclosure of this source code, which includes
// information that is confidential and/or proprietary, and is a trade secret, of COMPANY.
// ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC  PERFORMANCE,
// OR PUBLIC DISPLAY OF OR THROUGH USE  OF THIS  SOURCE CODE  WITHOUT  THE EXPRESS WRITTEN CONSENT OF COMPANY IS STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE
// LAWS AND INTERNATIONAL TREATIES.  THE RECEIPT OR POSSESSION OF  THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
// TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT  MAY DESCRIBE, IN WHOLE OR IN PART.


#import "MPAccessoryComponent.h"
#import "MPTransaction.h"

#import "MPAccessoryComponentInteractionAskForNumberParameters.h"
#import "MPAccessoryComponentInteractionAskForConfirmationParameters.h"
#import "MPAccessoryComponentInteractionAskForCardDataParameters.h"
#import "MPAccessoryComponentInteractionCardData.h"

@class MPAccessoryComponentInteraction;

/**
 * Ask for confirmation completion handler
 * @param component The component that triggered the callback
 * @param key The key that was pressed on the device
 * @since 2.10.0
 */
typedef void (^MPAccessoryComponentInteractionConfirmationSuccess)(MPAccessoryComponentInteraction * _Nonnull component, MPAccessoryComponentInteractionConfirmationKey key);

/**
 * Ask for confirmation failure handler
 * @param component The component that triggered the callback
 * @param error Error that describes why the confirmation failed
 * @since 2.10.0
 */
typedef void (^MPAccessoryComponentInteractionConfirmationFailure)(MPAccessoryComponentInteraction * _Nonnull component, NSError * _Nonnull error);

/**
 * Asking for confirmation was aborted
 * @param component The component that triggered the callback
 * @since 2.11.0
 */
typedef void (^MPAccessoryComponentInteractionConfirmationAbort)(MPAccessoryComponentInteraction * _Nonnull component);


/**
 * Ask for number completion handler
 * @param component The component that triggered the callback
 * @param number The number entered as a string. This could include leading zeroes so parse it appropriately in case where a 0 is expected.
 * @since 2.11.1
 */
typedef void (^MPAccessoryComponentInteractionAskForNumberSuccess)(MPAccessoryComponentInteraction * _Nonnull component, NSString * _Nonnull number);

/**
 * Ask for number failure handler
 * @param component The component that triggered the callback
 * @param error Error that describes why it failed
 * @since 2.10.0
 */
typedef void (^MPAccessoryComponentInteractionAskForNumberFailure)(MPAccessoryComponentInteraction * _Nonnull component, NSError * _Nonnull error);

/**
 * Asking for confirmation was aborted
 * @param component The component that triggered the callback
 * @since 2.11.0
 */
typedef void (^MPAccessoryComponentInteractionAskForNumberAbort)(MPAccessoryComponentInteraction * _Nonnull component);


/**
 * Display text completion handler
 * @param component The component that triggered the callback
 * @since 2.11.0
 */
typedef void (^MPAccessoryComponentInteractionDisplayTextSuccess)(MPAccessoryComponentInteraction * _Nonnull component);

/**
 * Display text failure handler
 * @param component The component that triggered the callback
 * @param error Error that occurred during the process
 * @since 2.11.0
 */
typedef void (^MPAccessoryComponentInteractionDisplayTextFailure)(MPAccessoryComponentInteraction * _Nonnull component, NSError * _Nonnull error);


/**
 * Display idle screen completion handler
 * @param component The component that triggered the callback
 * @since 2.11.0
 */
typedef void (^MPAccessoryComponentInteractionDisplayIdleScreenSuccess)(MPAccessoryComponentInteraction * _Nonnull component);

/**
 * Display idle screen failure handler
 * @param component The component that triggered the callback
 * @param error Error that occurred during the process
 * @since 2.11.0
 */
typedef void (^MPAccessoryComponentInteractionDisplayIdleScreenFailure)(MPAccessoryComponentInteraction * _Nonnull component, NSError * _Nonnull error);


/**
 * Ask for encrypted data completion handler
 * @param component The component that triggered the callback
 * @param cardData The card data that was collected via the accessory
 * @since 2.27.0
 */
typedef void (^MPAccessoryComponentInteractionAskForCardDataSuccess)(MPAccessoryComponentInteraction * _Nonnull component, MPAccessoryComponentInteractionCardData * _Nonnull cardData);

/**
 * Asking for encrypted data was aborted
 * @param component The component that triggered the callback
 * @since 2.27.0
 */
typedef void (^MPAccessoryComponentInteractionAskForCardDataAbort)(MPAccessoryComponentInteraction * _Nonnull component);

/**
 * Ask for encrypted data failure handler
 * @param component The component that triggered the callback
 * @param error Error that describes why the ask for secure information failed
 * @since 2.27.0
 */
typedef void (^MPAccessoryComponentInteractionAskForCardDataFailure)(MPAccessoryComponentInteraction * _Nonnull component, NSError * _Nonnull error);


/**
 * An additional component of an accessory which provides a way to ask user for a confirmation
 * @since 2.10.0
 */
@interface MPAccessoryComponentInteraction : MPAccessoryComponent

/**
 * The component asks the user for a custom confirmation
 * @param parameters Parameters used to customize the request
 * @param success Executed when user confirms/declines
 * @param abort Executed when the entry wa aborted
 * @param failure Executed when something went wrong
 * @since 2.10.0
 */
- (void)askForConfirmationWithParameters:(nonnull MPAccessoryComponentInteractionAskForConfirmationParameters*)parameters
                                 success:(nonnull MPAccessoryComponentInteractionConfirmationSuccess)success
                                   abort:(nonnull MPAccessoryComponentInteractionConfirmationAbort)abort
                                 failure:(nonnull MPAccessoryComponentInteractionConfirmationFailure)failure;


/**
 * The component asks the user for a number, displaying one or more prompts
 * @param parameters Parameters used to customize the request
 * @param success Executed when user entered a number
 * @param abort Executed when the entry wa aborted
 * @param failure Executed when something went wrong
 * @since 2.10.0
 */
- (void)askForNumberWithParameters:(nonnull MPAccessoryComponentInteractionAskForNumberParameters*)parameters
                           success:(nonnull MPAccessoryComponentInteractionAskForNumberSuccess)success
                             abort:(nonnull MPAccessoryComponentInteractionAskForNumberAbort)abort
                           failure:(nonnull MPAccessoryComponentInteractionAskForNumberFailure)failure;



/**
 * Displays the text on the accessory.
 * @param text The text to display on the accessory. Array of NSString where each string represents a line of text
 * @param success Executed when text was displayed successfully
 * @param failure Executed when something went wrong
 * @since 2.11.0
 */
- (void)displayText:(nonnull NSArray *)text
            success:(nonnull MPAccessoryComponentInteractionDisplayTextSuccess)success
            failure:(nonnull MPAccessoryComponentInteractionDisplayTextFailure)failure;


/**
 * Displays the idle screen on the accessory.
 * @param success Executed when idle screen was displayed successfully
 * @param failure Executed when something went wrong
 * @since 2.11.0
 */
- (void)displayIdleScreenSuccess:(nonnull MPAccessoryComponentInteractionDisplayIdleScreenSuccess)success
                         failure:(nonnull MPAccessoryComponentInteractionDisplayIdleScreenFailure)failure;

/**
 * The component asks the user for specified card data encrypted
 * @param parameters Parameters defining about what to ask
 * @param success Executed when user entered a value which we want to ask
 * @param failure Executed when something went wrong
 * @since 2.27.0
 */
- (void)askForCardDataWithParameters:(nonnull MPAccessoryComponentInteractionAskForCardDataParameters *)parameters
                             success:(nonnull MPAccessoryComponentInteractionAskForCardDataSuccess)success
                               abort:(nonnull MPAccessoryComponentInteractionAskForCardDataAbort)abort
                             failure:(nonnull MPAccessoryComponentInteractionAskForCardDataFailure)failure;

@end
