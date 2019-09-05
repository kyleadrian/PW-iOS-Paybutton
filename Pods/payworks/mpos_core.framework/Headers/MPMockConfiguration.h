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

#import "MPAccessoryUpdateRequirement.h"
#import "MPPaymentDetails.h"
#import "MPTransaction.h"


/**
 * Defines the transaction outcome on the accessory.
 * @since 2.2.0
 */
typedef NS_ENUM(NSUInteger, MPMockConfigurationPaymentAccessoryBehavior){
    
    /** The payment is approved with no customer verification */
    MPMockConfigurationPaymentAccessoryBehaviorApprove = 0,
    /** The payment is declined offline */
    MPMockConfigurationPaymentAccessoryBehaviorDeclineOffline,
    /** The payment is declined after online authorization */
    MPMockConfigurationPaymentAccessoryBehaviorDeclineOnline,
    /** The payment is aborted by the customer. If PinAsk option is set then the last pin entry will be canceled by user, else it's a card removed. */
    MPMockConfigurationPaymentAccessoryBehaviorAbort,
    /** The payment fails due to an error */
    MPMockConfigurationPaymentAccessoryBehaviorError
};


/**
 * Defines the accessory behavior during an ongoing transaction.
 * @since 2.1.0
 */
typedef NS_OPTIONS(NSUInteger, MPMockConfigurationPaymentAccessoryOptions) {
    /** None*/
    MPMockConfigurationPaymentAccessoryOptionNone                               = 0,
    /** A mock pin will be entered with the respective notifications */
    MPMockConfigurationPaymentAccessoryOptionPINAskOK                           = 1 << 0,
    /** Wrong pin will be entered and the transaction will fail*/
    MPMockConfigurationPaymentAccessoryOptionPINWrong                           = 1 << 1,
    /** First insertion of pin will be wrong and a retry will be notified. Is Ignored if PinAskOk or PinWrong is not set.*/
    MPMockConfigurationPaymentAccessoryOptionPINRetry                           = 1 << 2,
    /** Pin will be inserted wrong twice, after the fail a "last try" notification will be sent. Ignores the PINRetry option.
     Is Ignored if PinAskOk or PinWrong is not set.*/
    MPMockConfigurationPaymentAccessoryOptionPINLastTry                         = 1 << 3,
    /** Signature will be asked, if the result of the callback is NO then the transaction will fail regardless of accessory's and gateway's set behavior*/
    MPMockConfigurationPaymentAccessoryOptionAskSignature                       = 1 << 4
};


/**
 * Defines the payment source that is used during a transaction.
 * @since 2.2.0
 */

typedef NS_OPTIONS(NSUInteger, MPMockConfigurationPaymentAccessorySource){
    
    /** The payment is done with an EMV card */
    MPMockConfigurationPaymentAccessorySourceICC                    = 1 << 0,
    /** The payment is done witn an EMV card with e applications, thus the app selection callback will be executed*/
    MPMockConfigurationPaymentAccessorySourceICCWithMultipleApps    = 1 << 1,
    /** The payment is done with a magstripe card */
    MPMockConfigurationPaymentAccessorySourceMagstripe              = 1 << 2,
    /** The payment is done with a magical contactles card */
    MPMockConfigurationPaymentAccessorySourceNFC                    = 1 << 3
};


/**
 * Defines the features the mock accessory can have. Default features are Magnetic stripe and ICC and these can't be removed.
 * @since 2.16.0
 */

typedef NS_OPTIONS(NSUInteger, MPMockConfigurationPaymentAccessoryFeature){

    MPMockConfigurationPaymentAccessoryFeatureDefault = 0,
    MPMockConfigurationPaymentAccessoryFeatureNFC = 1 << 0,
};

/**
 * Defines the server outcome for a transaction.
 * @since 2.2.0
 */
typedef NS_ENUM(NSUInteger, MPMockConfigurationGatewayBehavior){
    
    /** The payment is approved by the bank */
    MPMockConfigurationGatewayBehaviorApprove = 0,
    /** The payment is approved by the bank and a streamlined completion process is used */
    MPMockConfigurationGatewayBehaviorApproveEarly,
    /** The payment is declined by the bank */
    MPMockConfigurationGatewayBehaviorDecline,
    /** The payment is declined on the verification step */
    MPMockConfigurationGatewayBehaviorDeclineVerificatonFailed,
    /** The payment encounters an error in the register phase */
    MPMockConfigurationGatewayBehaviorErrorDuringRegister,
    /** The payment encounters an error in the lookup phase */
    MPMockConfigurationGatewayBehaviorErrorDuringLookup,
    /** The payment encounters an error in the execute phase */
    MPMockConfigurationGatewayBehaviorErrorDuringExecute,
    /** The payment encounters an error in the finalize or void phase */
    MPMockConfigurationGatewayBehaviorErrorDuringFinalizeOrVoid,
    /** The refund encounters an error in the refund phase */
    MPMockConfigurationGatewayBehaviorErrorDuringRefundWithoutCard,
    /** The transaction fails with an inconclusive during the execute phase */
    MPMockConfigurationGatewayBehaviorInconclusiveDuringExecute,
    /** The transaction fails with an inconclusive during the finalize or void phase */
    MPMockConfigurationGatewayBehaviorInconclusiveDuringFinalizeOrVoid,
};


/**
 * Defines the payment source that is used during a transaction.
 * @since 2.2.0
 */

typedef NS_ENUM(NSUInteger, MPMockConfigurationPrinterAccessoryBehavior){
    
    /** Printer works normally */
    MPMockConfigurationPrinterAccessoryBehaviorNormal = 0,
    /** Printer is busy */
    MPMockConfigurationPrinterAccessoryBehaviorBusy,
    /** Printer is low or out of paper */
    MPMockConfigurationPrinterAccessoryBehaviorPaperEmpty,
    /** The printer's cover is open */
    MPMockConfigurationPrinterAccessoryBehaviorCoverOpen
};

/**
 * Defines the outcome of a request for a tip
 * @since 2.7.0
 */
typedef NS_ENUM(NSUInteger, MPMockConfigurationTippingComponentBehavior) {

    /** Asking for tip succeeds with suggested tip amount if provided, else with a tip amount of 1 */
    MPMockConfigurationTippingComponentBehaviorTipEntered = 0,
    /** Customer refuses to tip*/
    MPMockConfigurationTippingComponentBehaviorNoTip,
    /** Asking for tip fails with an error*/
    MPMockConfigurationTippingComponentBehaviorError
};

/**
 * Defines the outcome of a request for a confirmation
 * @since 2.10.0
 */
typedef NS_ENUM(NSUInteger, MPMockConfigurationInteractionComponentAskForConfirmationBehavior) {
    
    /** Press the Ok button */
    MPMockConfigurationInteractionComponentAskForConfirmationBehaviorPressOk = 0,
    /** Press the Cancel button */
    MPMockConfigurationInteractionComponentAskForConfirmationBehaviorPressCancel,
    /** Press the Back button */
    MPMockConfigurationInteractionComponentAskForConfirmationBehaviorPressBack,
    /** Press a Numeric button */
    MPMockConfigurationInteractionComponentAskForConfirmationBehaviorPressNumeric,
    /** Asking for confirmation fails with an error*/
    MPMockConfigurationInteractionComponentAskForConfirmationBehaviorError
};

/**
 * Defines the outcome of a request for a number
 * @since 2.10.0
 */
typedef NS_ENUM(NSUInteger, MPMockConfigurationInteractionComponentAskForNumberBehavior) {
    
    /** Asking for number succeeds with default value if provided, else with a number of 1 */
    MPMockConfigurationInteractionComponentAskForNumberBehaviorNumberEnter = 0,
    /** Number entry is aborted */
    MPMockConfigurationInteractionComponentAskForNumberBehaviorNumberAbort,
    /** Asking for number fails with an error */
    MPMockConfigurationInteractionComponentAskForNumberBehaviorNumberError
};

/**
 * The gateway behavior for an ongoing transaction.
 * @since 2.2.0
 */
typedef NS_OPTIONS(NSUInteger, MPMockConfigurationGatewayOptions){
    
    /** None*/
    MPMockConfigurationGatewayOptionNone = 0,
    /** Customers id check will be required. If the returned result is NO then the transaction will fail */
    MPMockConfigurationGatewayOptionRequireIdentification
};


/**
 * Defines the behavior an update check should mimic.
 * @since 2.2.0
 */
typedef NS_ENUM(NSUInteger, MPMockConfigurationMockUpdateBehavior) {
    
	/** No updates are available */
	MPMockConfigurationMockUpdateBehaviorNoUpdate = 0,
	/** Update is available */
	MPMockConfigurationMockUpdateBehaviorUpdateAvailableAndRequired,
	/** Will fail when checking for update requirements */
	MPMockConfigurationMockUpdateBehaviorErrorDuringCheckRequirements,
	/** Will fail when trying to update the accessory */
	MPMockConfigurationMockUpdateBehaviorErrorDuringUpdate
};


/**
 * Configures the connection behavior of the accessory..
 * @since 2.18.0
 */
typedef NS_ENUM(NSUInteger, MPMockConfigurationAccessoryConnectionBehavior) {

    /** Accessory connection is successful */
    MPMockConfigurationAccessoryConnectionBehaviorSuccess = 0,
    /** Fails because accessory is busy */
    MPMockConfigurationAccessoryConnectionBehaviorBusy,
    /** Fails because accessory cannot be found */
    MPMockConfigurationAccessoryConnectionBehaviorNotFound,
};

/**
 * The available outcomes of the processing gateway
 * for provisioning an accessory.
 * @since 2.11.0
 */
typedef NS_ENUM(NSUInteger, MPMockConfigurationProvisionBehavior) {
    
    /** The accessory was provisioned */
    MPMockConfigurationProvisionBehaviorSuccess = 0,
    /** The accessory could not be provisioned. */
    MPMockConfigurationProvisionBehaviorError
};


/**
 * Configures the whitelist returned.
 * @since 2.11.0
 */
typedef NS_ENUM(NSUInteger, MPMockConfigurationWhitelistBehavior) {
    
    /** All connected accessories are included in the whitelist (both mock or real). */
    MPMockConfigurationWhitelistBehaviorIncludeConnected = 0,
    /** The connected accessories are not in the whitelist. */
    MPMockConfigurationWhitelistBehaviorExcludeConnected
};


/**
 * Configures the processing workflow behavior returned.
 * @since 2.16.0
 */
typedef NS_OPTIONS(NSUInteger, MPMockProcessingWorkflowBehavior) {

    /** Standard behavior */
    MPMockProcessingWorkflowBehaviorStandard = 0,
    /** Use quickchip workflow */
    MPMockProcessingWorkflowBehaviorQuickChip = 1 << 0
};


typedef NS_ENUM(NSUInteger, MPMockWalletApprovalBehavior) {

    /** Wallet transactions will be evaluated right away (offline for the backend) */
    MPMockWalletApprovalBehaviorOffline = 0,
    /** Wallet transactions need further evaluation (online for the backend). */
    MPMockWalletApprovalBehaviorOnline
};

/**
 * Defines the outcome of a request for a card data
 * @since 2.27.0
 */
typedef NS_ENUM(NSUInteger, MPMockConfigurationInteractionComponentAskForCardDataBehavior) {

    /** Asking for card data succeeds with all card data or card number and expiry date */
    MPMockConfigurationInteractionComponentAskForCardDataBehaviorSuccess = 0,
    /** Card data entry is aborted */
    MPMockConfigurationInteractionComponentAskForCardDataBehaviorAbort,
    /** Asking for card data fails with an error */
    MPMockConfigurationInteractionComponentAskForCardDataBehaviorError
};

/**
 * Defines the outcome DCC lookup
 * @since 2.29.0
 */
typedef NS_ENUM(NSUInteger, MPMockConfigurationDccLookupBehavior) {

    /** Lookup is successful */
    MPMockConfigurationDccLookupBehaviorSuccessful = 0,
    /** Lookup is not successful */
    MPMockConfigurationDccLookupBehaviorNotSuccessful,
    /** Same currency on lookup */
    MPMockConfigurationDccLookupBehaviorSameCurrency,
    /** Lookup fails with an error */
    MPMockConfigurationDccLookupBehaviorError
};


/**
 * Configuration describing the mocking behavior of the SDK.
 * @since 2.0.0
 */
@interface MPMockConfiguration : NSObject


/**
 * The behavior of the payment workflow.
 * @since 2.0.0
 */
@property (assign, nonatomic) MPMockConfigurationPaymentAccessoryBehavior paymentAccessoryBehavior;

/**
 * The options of the payment workflow.
 * @since 2.2.0
 */
@property (assign, nonatomic) MPMockConfigurationPaymentAccessoryOptions paymentAccessoryOptions;

/**
 * The features of the payment accessory.
 * @since 2.16.0
 */
@property (assign, nonatomic) MPMockConfigurationPaymentAccessoryFeature paymentAccessoryFeatures;


/**
 * The payment source to use, e.g. a EMV card.
 * @since 2.0.0
 */
@property (assign, nonatomic) MPMockConfigurationPaymentAccessorySource paymentAccessorySource;

/**
 * Scheme that will be used for the mock card.
 * Currently only MPPaymentDetailsSchemeMasterCard and MPPaymentDetailsSchemeVISA are supported. If the mock is
 * provided with other value then it will default to MPPaymentDetailsSchemeVISA
 * @since 2.2.0
 */
@property (assign, nonatomic) MPPaymentDetailsScheme paymentAccessoryCardScheme;

/**
 * The behavior of the printing workflow.
 * @since 2.4.0
 */
@property (assign, nonatomic) MPMockConfigurationPrinterAccessoryBehavior printerAccessoryBehavior;


/**
 * The behavior of the tipping component
 * @since 2.7.0
 */
@property (assign, nonatomic) MPMockConfigurationTippingComponentBehavior tippingComponentBehavior;

/**
 * The behavior of the interaction component for confirmation request
 * @since 2.10.0
 */
@property (assign, nonatomic) MPMockConfigurationInteractionComponentAskForConfirmationBehavior interactionComponentAskForConfirmationBehavior;

/**
 * The behavior of the interaction component for number request
 * @since 2.10.0
 */
@property (assign, nonatomic) MPMockConfigurationInteractionComponentAskForNumberBehavior interactionComponentAskForNumberBehavior;

/**
 * The behavior of the processor.
 * @since 2.0.0
 */
@property (assign, nonatomic) MPMockConfigurationGatewayBehavior gatewayBehavior;

/**
 * The options of the processor.
 * @since 2.0.0
 */
@property (assign, nonatomic) MPMockConfigurationGatewayOptions gatewayOptions;

/**
 * Bitmask of payment sources that are allowed by the mocked processing gateway.
 * @since 2.16.0
 */
@property (assign, nonatomic) MPMockConfigurationPaymentAccessorySource gatewayProcessingOptionsAllowedSources;

/**
 * The behavior of the update workflow
 * @since 2.2.0
 */
@property (assign, nonatomic) MPMockConfigurationMockUpdateBehavior updateBehavior;

/**
 * The connection behavior of the mocked accessory
 * @since 2.18.0
 */
@property (assign, nonatomic) MPMockConfigurationAccessoryConnectionBehavior accessoryConnectionBehavior;


/**
 * Update requirement that will be used for the chekUpdateRequirements response
 * @since 2.2.0
 */
@property (assign, nonatomic) MPAccessoryUpdateRequirementComponent updateRequirementComponent;


/**
 * The provisioning behavior of the mocked processing gateway.
 * @since 2.11.0
 */
@property (assign, nonatomic) MPMockConfigurationProvisionBehavior provisionBehavior;

/**
 * The update behavior of the mocked accessory.
 * @since 2.11.0
 */
@property (assign, nonatomic) MPMockConfigurationWhitelistBehavior whitelistBehavior;


/**
 * The processing workflow
 * @since 2.16.0
 */
@property (assign, nonatomic) MPMockProcessingWorkflowBehavior processingBehavior;

/**
 * The processing workflow
 * @since 2.16.0
 */
@property (assign, nonatomic) MPMockWalletApprovalBehavior walletApprovalBehavior;

/**
 * The behavior of the interaction component for card data request
 * @since 2.27.0
 */
@property (assign, nonatomic) MPMockConfigurationInteractionComponentAskForCardDataBehavior interactionComponentAskForCardDataBehavior;

/**
 * The behavior of the dcc lookup.
 * @since 2.29.0
 */
@property (assign, nonatomic) MPMockConfigurationDccLookupBehavior dccLookupBehaviour;

/**
 * Information if DCC is enabled.
 * @since 2.29.0
 */
@property (assign, nonatomic) BOOL dccEnabled;

/**
 * Adds a random delay interval to the response callbacks, simulating user behavior and network delay.
 * @param minimumDelay The minimum delay to use, defaults to 1s
 * @param maximumDelay The maximum delay to use, defaults to 2s
 * @since 2.0.0
 */
- (void)setRandomDelayIntervalInSecondsFrom:(double)minimumDelay to:(double)maximumDelay;



@end

