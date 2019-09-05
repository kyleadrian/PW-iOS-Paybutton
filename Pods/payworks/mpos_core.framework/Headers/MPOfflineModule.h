//
// PAYWORKS GMBH ("COMPANY") CONFIDENTIAL
// Copyright (c) 2017 Payworks GmbH, All Rights Reserved.
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


#import "MPTransactionProcess.h"
#import "MPOfflineBatchUploadProcess.h"

@class MPTransactionParameters;
@class MPAccessoryParameters;
@class MPTransactionProcessParameters;


/**
 * Callback block for a transaction lookup with transaction identifier.
 * @param transaction The transaction with the provided transactionIdentifier
 * @param error The error that might have occured
 * @since 2.28.0
 */
typedef void (^MPOfflineModuleLookupByTransactionIdentifierCompleted)(MPTransaction * _Nullable transaction, NSError * _Nullable error);

/**
 * Callback block for a transaction query with transaction filter.
 * @param transactions The returned transactions (nil if error occured, may be empty if no transcations where found)
 * @param error The error that might have occured
 * @since 2.28.0
 */
typedef void (^MPOfflineModuleQueryCompleted)(NSArray<MPTransaction *> * _Nullable transactions, NSError * _Nullable error);


@interface MPOfflineModule : NSObject


/**
 * Starts and returns a new offline transaction process which will guide you through a complete transaction.
 * @param transactionParameters The parameters specifying the transaction and it's type. Make sure to use CHARGE transaction parameters.
 * @param accessoryParameters Parameters defining the accessory to be used for the transaction.
 * @param processParameters The parameters specifying extra transaction process parameters.
 * @param registered Callback that is triggered when a transaction reference is created. You can use this to lookup the status at a later stage.
 * @param statusChanged The status of the process changed and new information can be displayed to the user
 * @param actionRequired An explicit action by the merchant or customer is required
 * @param completed The transactionProcess ended and a new one can be started
 * @return The transactionProcess that can be used to request abort
 * @since 2.28.0
 */
- (nonnull MPTransactionProcess *)startTransactionWithParameters:(nonnull MPTransactionParameters *)transactionParameters
                                             accessoryParameters:(nonnull MPAccessoryParameters *)accessoryParameters
                                               processParameters:(nullable MPTransactionProcessParameters *)processParameters
                                                      registered:(nonnull MPTransactionProcessRegistered)registered
                                                   statusChanged:(nonnull MPTransactionProcessStatusChanged)statusChanged
                                                  actionRequired:(nonnull MPTransactionProcessActionRequired)actionRequired
                                                       completed:(nonnull MPTransactionProcessCompleted)completed;


/**
 * Starts an amendment process, that can be used for modifying a previous offline transactions. 
 * This does not require a connection to an accessory
 * At the moment only full refunds are supported for this action.
 * @param transactionParameters The parameters specifying the transaction and it's type. Make sure to only use REFUND transaction parameters.
 * @return Transaction process that can be used to request abort
 * @since 2.28.0
 */
- (nonnull MPTransactionProcess *)amendTransactionWithParameters:(nonnull MPTransactionParameters *)transactionParameters
                                                   statusChanged:(nonnull MPTransactionProcessStatusChanged)statusChanged
                                                       completed:(nonnull MPTransactionProcessCompleted)completed;


/**
 * Submit all currently stored offline transactions for settlment.
 * @param completed The block to be executed when done
 * @return The upload process
 * @since 2.28.0
 */
- (nonnull MPOfflineBatchUploadProcess *)submitOfflineTransactionsBatchWithCompleted:(nonnull MPOfflineBatchUploadProcessCompleted)completed;


/**
 * Queries an offline stored transaction by its identifier.
 * @param transactionIdentifier The identifier of the transaction
 * @param completed The async completion callback
 * @since 2.28.0
 */
- (void)lookupTransactionWithTransactionIdentifier:(nonnull NSString *)transactionIdentifier
                                         completed:(nonnull MPOfflineModuleLookupByTransactionIdentifierCompleted)completed;

/**
 * Queries all stored offline transactions. Transactions are sorted by time descending.
 * @param includeReceipts Defines if the returned transaction objects should have customer and merchant receipt information embedded.
 * @param range The range of transactions to be returned, *index* specifies the offset of the first transaction and *length* limits the number of transactions to return.
 * @param completed The async completion callback
 * @since 2.28.0
 */
- (void)queryTransactionsWithRange:(NSRange)range
                   includeReceipts:(BOOL)includeReceipts
                         completed:(nonnull MPOfflineModuleQueryCompleted)completed;


/**
 * Deletes all offline stored transactions. Use it only on TEST, JUNGLE mode.
 * @warning Using this on LIVE will result is irreversibly losing all transaction data.
 * @since 2.28.0
 */
- (void)deleteStoredTransactions;

/**
 * Clears the stored offline configuration.
 * @since 2.28.0
 */
- (void)deleteStoredConfigurations;

@end
