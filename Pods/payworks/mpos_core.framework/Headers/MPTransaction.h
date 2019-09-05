//
// PAYWORKS GMBH ("COMPANY") CONFIDENTIAL
// Copyright (c) 2013 Payworks GmbH, All Rights Reserved.
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

@class MPPaymentDetails;
@class MPProcessingDetails;
@class MPStatusDetails;
@class MPRefundDetails;
@class MPClearingDetails;
@class MPTransactionDetails;
@class MPReceipt;
@class MPCardDetails;
@class MPShopperDetails;
@class MPGiftCardDetails;
@class MPTransactionVerificationResults;
@class MPDccDetails;

/**
 * Actions requested during a transaction. Bitwise OR to stack, AND to split.
 * @since 2.0.0
 */
typedef NS_OPTIONS(NSUInteger, MPTransactionAction){
    /** No actions supported, NOP action */
    MPTransactionActionNone                                = 0,
    /** A customer signature must be provided to complete the transaction */
    MPTransactionActionCustomerSignature                   = 1 << 0,
    /** The customer must be identified by means of ID check with an official document */
    MPTransactionActionCustomerIdentification              = 1 << 1,
    /** Used to indicate that an application needs to be selected in order to continue with the transaction */
    MPTransactionActionApplicationSelection                = 1 << 2,
    /** Used to indicate that a credit or debit workflow needs to be selected */
    MPTransactionActionCreditDebitSelection                = 1 << 3,
};
static MPTransactionAction MPTransactionActionAll = MPTransactionActionCustomerSignature | MPTransactionActionCustomerIdentification | MPTransactionActionApplicationSelection | MPTransactionActionCreditDebitSelection;


/**
 * The type of transaction that will be executed.
 * @since 2.0.0
 */
typedef NS_ENUM(NSUInteger, MPTransactionType){
    /** Unknown or not available */
    MPTransactionTypeUnknown = 0,
    /** Debit transaction, where the funds are directly removed from debited from the account */
    MPTransactionTypeCharge,
    /** Refund transaction, where the funds are directly posted to the account */
    MPTransactionTypeRefund,
    /** Preauthorize transaction, where the funds are reserved on the account. Note: just available for mapping purposes and cannot be initiated by the SDK.  */
    MPTransactionTypePreauthorize,
    /** Credit transaction, where the funds are credited to an account. Note: just available for mapping purposes and cannot be initiated by the SDK. */
    MPTransactionTypeCredit,
    /** Account verification transaction, where the card is verified as valid, no funds are taken from the account. */
    MPTransactionTypeVerification,
    /** Activation transaction, where the funds are transferred to a gift card account. **/
    MPTransactionTypeActivation
};

/**
 * The final result of the transaction.
 * @since 2.0.0
 */
typedef NS_ENUM(NSUInteger, MPTransactionStatus){
    /** Unknown or not available */
    MPTransactionStatusUnknown = 0,
    /** Transaction is initialized and can be started */
    MPTransactionStatusInitialized,
    /** Transaction result is still pending (e.g. not finished or waiting for async workflow) */
    MPTransactionStatusPending,
    /** Transaction was accepted offline and must be uploaded to be executed by the backend */
    MPTransactionStatusAccepted,
    /** Transaction was approved */
    MPTransactionStatusApproved,
    /** Transaction was declined */
    MPTransactionStatusDeclined,
    /** Transaction was aborted (by merchant or shopper) */
    MPTransactionStatusAborted,
    /** An error occured, see [MPTransaction.error] for more details */
    MPTransactionStatusError,
    /** The transaction ended in a state that is inconclusive and the SDK cannot derive the outcome (e.g. due to no internet connection). This is a special case of failure. */
    MPTransactionStatusInconclusive
};

/**
 * The currency used for a transaction.
 * @since 2.0.0
 */
typedef NS_ENUM(NSUInteger, MPCurrency){
    /** An unknown currency. Is actually part of the ISO standard, but should be treated as an error. */
    MPCurrencyUnknown,
    /** United Arab Emirates Dirham */
    MPCurrencyAED,
    /** Afghan Afghani */
    MPCurrencyAFN,
    /** Albanian Lek */
    MPCurrencyALL,
    /** Armenian Dram */
    MPCurrencyAMD,
    /** Argentine Peso */
    MPCurrencyARS,
    /** Australian Dollar */
    MPCurrencyAUD,
    /** Azerbaijani Manat */
    MPCurrencyAZN,
    /** Barbadian Dollar */
    MPCurrencyBBD,
    /** Bangladeshi Taka */
    MPCurrencyBDT,
    /** Bulgarian Lev */
    MPCurrencyBGN,
    /** Bahraini Dinar */
    MPCurrencyBHD,
    /** Bermudan Dollar */
    MPCurrencyBMD,
    /** Brunei Dollar */
    MPCurrencyBND,
    /** Bolivian Boliviano */
    MPCurrencyBOB,
    /** Brazilian Real */
    MPCurrencyBRL,
    /** Bahamian Dollar */
    MPCurrencyBSD,
    /** Botswana Pula */
    MPCurrencyBWP,
    /** Belize Dollar */
    MPCurrencyBZD,
    /** Canadian Dollar */
    MPCurrencyCAD,
    /** Swiss Franc */
    MPCurrencyCHF,
    /** Chilean Peso */
    MPCurrencyCLP,
    /** Chinese Yuan */
    MPCurrencyCNY,
    /** Colombian Peso */
    MPCurrencyCOP,
    /** Costa Rican Colon */
    MPCurrencyCRC,
    /** Czech Koruna */
    MPCurrencyCZK,
    /** Danish Krone */
    MPCurrencyDKK,
    /** Dominican Peso */
    MPCurrencyDOP,
    /** Algerian Dinar */
    MPCurrencyDZD,
    /** Egyptian Pound */
    MPCurrencyEGP,
    /** Euro */
    MPCurrencyEUR,
    /** Pound Sterling */
    MPCurrencyGBP,
    /** Ghanaian Cedi */
    MPCurrencyGHS,
    /** Guatemalan Quetzal */
    MPCurrencyGTQ,
    /** Hong Kong Dollar */
    MPCurrencyHKD,
    /** Honduran Lempira */
    MPCurrencyHNL,
    /** Croatian Kuna */
    MPCurrencyHRK,
    /** Hungarian Forint */
    MPCurrencyHUF,
    /** Indonesian Rupiah */
    MPCurrencyIDR,
    /** Israeli New Shekel */
    MPCurrencyILS,
    /** Indian Rupee */
    MPCurrencyINR,
    /** Jamaican Dollar */
    MPCurrencyJMD,
    /** Jordanian Dinar */
    MPCurrencyJOD,
    /** Japanese Yen */
    MPCurrencyJPY,
    /** Kenyan Shilling */
    MPCurrencyKES,
    /** South Korean Won */
    MPCurrencyKRW,
    /** Kuwaiti Dinar */
    MPCurrencyKWD,
    /** Kazakhstani Tenge */
    MPCurrencyKZT,
    /** Lebanese Pound */
    MPCurrencyLBP,
    /** Sri Lankan Rupee */
    MPCurrencyLKR,
    /** Liberian Dollar */
    MPCurrencyLRD,
    /** Moroccan Dirham */
    MPCurrencyMAD,
    /** Macanese Pataca */
    MPCurrencyMOP,
    /** Mauritian Rupee */
    MPCurrencyMUR,
    /** Mexican Peso */
    MPCurrencyMXN,
    /** Malaysian Ringgit */
    MPCurrencyMYR,
    /** Nigerian Naira */
    MPCurrencyNGN,
    /** Norwegian Krone */
    MPCurrencyNOK,
    /** New Zealand Dollar */
    MPCurrencyNZD,
    /** Omani Rial */
    MPCurrencyOMR,
    /** Panamanian Balboa */
    MPCurrencyPAB,
    /** Peruvian Nuevo Sol */
    MPCurrencyPEN,
    /** Philippine Peso */
    MPCurrencyPHP,
    /** Pakistani Rupee */
    MPCurrencyPKR,
    /** Polish Zloty */
    MPCurrencyPLN,
    /** Qatari Rial */
    MPCurrencyQAR,
    /** Romanian Leu */
    MPCurrencyRON,
    /** Serbian Dinar */
    MPCurrencyRSD,
    /** Russian Ruble */
    MPCurrencyRUB,
    /** Saudi Riyal */
    MPCurrencySAR,
    /** Seychellois Rupee */
    MPCurrencySCR,
    /** Swedish Krona */
    MPCurrencySEK,
    /** Singapore Dollar */
    MPCurrencySGD,
    /** Thai Baht */
    MPCurrencyTHB,
    /** Tunisian Dinar */
    MPCurrencyTND,
    /** Turkish Lira */
    MPCurrencyTRY,
    /** Trinidad & Tobago Dollar */
    MPCurrencyTTD,
    /** New Taiwan Dollar */
    MPCurrencyTWD,
    /** Ukrainian Hryvnia */
    MPCurrencyUAH,
    /** US Dollar */
    MPCurrencyUSD,
    /** Vietnamese Dong */
    MPCurrencyVND,
    /** East Caribbean Dollar */
    MPCurrencyXCD,
    /** Yemeni Rial */
    MPCurrencyYER,
    /** South African Rand */
    MPCurrencyZAR
};


/**
 * The state the transaction is currently in. Not all transactions run through all of the steps.
 * @since 2.0.0
 */
typedef NS_ENUM(NSUInteger, MPTransactionState)
{
    /** Unkndown or not available */    
    MPTransactionStateUnknown = 0,
    /** The transaction is waiting to be executed */
    MPTransactionStateIdle,
    /** The transaction is waiting for the card to be inserted */
    MPTransactionStateAwaitingCardPresentation,
    /** The card is currently being analyzed */
    MPTransactionStateAwaitingCardIdentification,
    /** The card requires an application selection by the cardholder */
    MPTransactionStateAwaitingApplicationSelection,
    /** The card requires credit/debit to be selected */
    MPTransactionStateAwaitingCreditDebitSelection,
    /** The transaction requires an amount confirmation by the cardholder */
    MPTransactionStateAwaitingAmountConfirmation,
    /** The transaction requires a PIN to be inserted */
    MPTransactionStateAwaitingPIN,
    /** The transaction is a being executed with the remote system */
    MPTransactionStateAwaitingExecution,
    /** The transaction is waiting for the card to be removed */
    MPTransactionStateAwaitingCardRemoval,
    /** The transaction requires a signature by the cardholder */
    MPTransactionStateAwaitingSignature,
    /** The transaction requires an identificatio by the cardholder */
    MPTransactionStateAwaitingIdentification,
    /** The transaction is being finalized with the remote host */
    MPTransactionStateAwaitingCompletion,
    /** The transaction is waiting for the card data input */
    MPTransactionStateAwaitingCardDataInput,
    /** The transaction is waiting for address input */
    MPTransactionStateAwaitingAddressInput,
    /** The transaction is waiting for verification data confirmation */
    MPTransactionStateAwaitingVerificationResultsConfirmation,
    /** The transaction is in a final state and no changes can be made to it anymore */
    MPTransactionStateEnded
};

/**
 * The mode the transaction was executed
 * @since 2.14.0
 */
typedef NS_ENUM(NSUInteger, MPTransactionMode) {

    /** Transaction was executed and finalized online*/
    MPTransactionModeOnline = 0,
    /** Transaction was executed offline*/
    MPTransactionModeOffline
};

/**
 * Describes the type of transaction workflow.
 * @since 2.27.0
 */
typedef NS_ENUM(NSUInteger, MPTransactionWorkflowType) {
    MPTransactionWorkflowTypeUnknown,
    MPTransactionWorkflowTypePos,
    MPTransactionWorkflowTypeAlternativePaymentMethod,
    MPTransactionWorkflowTypeMoto,
    MPTransactionWorkflowTypeGiftCard
};

/**
 * A transaction contains all information required to make a transaction. It goes through specifically defined states and offers additional details after successful execution.
 * @since 2.0.0
 */
@interface MPTransaction : NSObject

#pragma mark -
#pragma mark General Information
/**
 * @name General Information 
 */

/**
 * The amount of the transaction.
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nonnull) NSDecimalNumber *amount;

/**
 * The currency used for the transaction.
 * @since 2.0.0
 */
@property (assign, readonly, nonatomic) MPCurrency currency;

/**
 * The subject line for the transaction.
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nullable) NSString *subject;

/**
 * An arbitrary string to be displayed on your customer's credit card statement.
 * @since 2.4.7
 */
@property (strong, readonly, nonatomic, nonnull) NSString *statementDescriptor;


#pragma mark -
#pragma mark Transaction Setup (must be set manually)
/**
 * @name Transaction Setup (must be set manually) 
 */

/**
 * The type of transaction to be executed.
 * @since 2.0.0
 */
@property (assign, readonly, nonatomic) MPTransactionType type;

/**
 * The mode the transaction was executed
 * @since 2.14.0
 */
@property (assign, readonly, nonatomic) MPTransactionMode mode;

/**
 * Indicates if the transaction has been captured.
 * @since 2.8.0
 */
@property (assign, readonly, nonatomic) BOOL captured;


#pragma mark -
#pragma mark Payment Details
/**
 * @name Payment Details 
 */

/**
 * The payment details used for the transaction.
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nonnull) MPPaymentDetails *paymentDetails;

/**
 * The refund details associated with the transaction.
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nonnull) MPRefundDetails *refundDetails;

/**
 * The clearing details associated with the transaction.
 * @since 2.6.0
 */
@property (strong, readonly, nonatomic, nonnull) MPClearingDetails *clearingDetails;

/**
 * The details of the card used for this transaction
 * @since 2.8.0
 */
@property (strong, readonly, nonatomic, nonnull) MPCardDetails *cardDetails;

/**
 * The details of the shopper
 * @since 2.8.0
 */
@property (strong, readonly, nonatomic, nonnull) MPShopperDetails *shopperDetails;

/**
 * Gift card details, e.g. balance or expiry date.
 * @since 2.32.0
 */
@property (strong, readonly, nonatomic, nonnull) MPGiftCardDetails *giftCardDetails;

/**
 * Extra transaction details, e.g. fees or tips.
 * @since 2.7.0
 */
@property (strong, readonly, nonatomic, nonnull) MPTransactionDetails *details;


#pragma mark -
#pragma mark Transaction Result

/**
 * Current state of the transaction. Approved, Declined and Error are the final states.
 * @since 2.0.0
 */
@property (assign, readonly, nonatomic) MPTransactionStatus status;

/**
 * Additional details associated with the current status, providing more detailed information for the current status and debug information.
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nullable) MPStatusDetails *statusDetails;


/**
 * The current workflow state the transaction is in.
 * @since 2.0.0
 */
@property (assign, readonly, nonatomic) MPTransactionState state;

/**
 * If the transaction execution fails for any reason, this will contain the last error message. Otherwise nil.
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nullable) NSError *error;

#pragma mark -
#pragma mark Global References
/**
 * @name Global Refrences 
 */

/**
 * The (temporary) session that references the transaction.
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nullable) NSString *sessionIdentifier;


/**
 * The reference within our infrastructure to identify the transaction (payworks identifier).
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nullable) NSString *identifier;


/**
 * A reference to a group of transactions that logically belong together.
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nullable) NSString *groupIdentifier;

/**
 * A reference to a transaction that the current transaction is building up on.
 * @since 2.0.0
 */

@property (strong, readonly, nonatomic, nullable) NSString *referencedTransactionIdentifier;

/**
 * An identifier that can be set by the developer/user. Must be in the range [0-9a-zA-Z]. This will normally be a reference to a order in your system.
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nullable) NSString *customIdentifier;

/**
 * Timestamp when the transaction was created. This timestamp will always be UTC.
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nullable) NSDate *created;

/**
 * The timezone offset in which the transaction was performed. When combining this information with `created` (always UTC) you are able to calculate the local transaction time.
 * @since 2.31.0
 */
@property (strong, readonly, nonatomic, nullable) NSTimeZone *createdTimeZone;


/**
 * Indicates if the transaction can still be aborted.
 * @return YES if the transaction can be aborted, NO otherwise
 * @since 2.0.0
 */
- (BOOL)canBeAborted;

#pragma mark -
#pragma mark Customer Information

/**
 * Information and identifiers returned by the processor.
 * @since 2.0.0
 */
@property (strong, readonly, nonatomic, nonnull) MPProcessingDetails *processingDetails;


#pragma mark -
#pragma mark Customer Information

/**
 * Receipt that can be printed for the customer
 * @since 2.6.0
 */
@property (strong, readonly, nonatomic, nullable) MPReceipt *customerReceipt;

/**
 * Receipt that can be printed for the merchant
 * @since 2.6.0
 */
@property (strong, readonly, nonatomic, nullable) MPReceipt *merchantReceipt;

/**
 * Determines transaction expected workflow. By default is MPTransactionWorkflowTypeUnknown.
 * @since 2.27.0
 */
@property (readonly, nonatomic) MPTransactionWorkflowType workflow;

/**
 * Verification result for MOTO transaction.
 * @since 2.27.0
 */
@property (readonly, nonatomic, nonnull) MPTransactionVerificationResults *verificationResults;

/**
 * The details of the DCC (Dynamic Currency Conversion)
 * @since 2.29.0
 */
@property (readonly, nonatomic, nonnull) MPDccDetails *dccDetails;

@end

