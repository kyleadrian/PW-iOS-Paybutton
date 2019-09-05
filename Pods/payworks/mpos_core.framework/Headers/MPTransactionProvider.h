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

#import "MPTransactionProcess.h"
#import "MPPrintingProcess.h"
#import "MPTransaction.h"
#import "MPConfigurationDetails.h"

@class MPLocalizationToolbox;
@class MPTransactionParameters;
@class MPAccessoryParameters;
@class MPAccountParameters;
@class MPTransactionModule;
@class MPTransactionProcessParameters;
@class MPAccessoryModule;
@class MPOfflineModule;

/**
* Completion block for a configuration synchronization.
* @param details The details object containing the information about the configuration.
* @param error The error object with further information about the failure.
* @since 2.33.0
*/
typedef void (^MPSynchronizeConfigurationProcessCompleted)(MPConfigurationDetails * _Nullable details, NSError * _Nullable error);


/**
 * Provider that simplifies the process of making a single transaction by encapsulating the necessary steps inbetween.
 * @since 2.2.0
 */
@interface MPTransactionProvider : NSObject

/**
 * Returns a toolbox for formatting various kinds of strings and values
 * @since 2.3.0
 */
@property (strong, readonly, nonatomic, nonnull) MPLocalizationToolbox *localizationToolbox;

/**
 * Returns a transaction module, which can be used for operations on past transactions,
 * i.e. looking up old transactions or fetching and sending receipts.
 * @since 2.6.0
 */
@property (strong, readonly, nonatomic, nonnull) MPTransactionModule *transactionModule;


/**
 * Returns an accessory module, which can be used for operations on the reader.
 * @since 2.18.0
 */
@property (strong, readonly, nonatomic, nonnull) MPAccessoryModule *accessoryModule;

/**
 * Returns an offline module, which give access to offline functionality of the SDK.
 * @since 2.28.0
 */
@property (strong, readonly, nonatomic, nonnull) MPOfflineModule *offlineModule;


/**
 * Starts and returns a new transaction process which guide you through a complete transaction.
 * This method is used if the session has already been created on the backend.
 * @param sessionIdentifier The sessionIdentifier of the transaction to start
 * @param accountParameters The parameters specifying the data needed for the execution of the transaction.
 * @param statusChanged The status of the process changed and new information can be displayed to the user
 * @param completed The transactionProcess ended and a new one can be started
 * @since 2.32.0
 */
- (nonnull MPTransactionProcess *)startTransactionWithSessionIdentifier:(nonnull NSString *)sessionIdentifier
                                                      accountParameters:(nonnull MPAccountParameters *)accountParameters
                                                          statusChanged:(nonnull MPTransactionProcessStatusChanged)statusChanged
                                                              completed:(nonnull MPTransactionProcessCompleted)completed;


/**
 * Starts and returns a new transaction process which guide you through a complete transaction.
 * This method is used if the session has already been created on the backend.
 * @param sessionIdentifier The sessionIdentifier of the transaction to start
 * @param accessoryParameters Parameters defining the accessory to be used for the transaction.
 * @param statusChanged The status of the process changed and new information can be displayed to the user
 * @param actionRequired An explicit action by the merchant or customer is required
 * @param completed The transactionProcess ended and a new one can be started
 * @since 2.5.0
 */
- (nonnull MPTransactionProcess *)startTransactionWithSessionIdentifier:(nonnull NSString *)sessionIdentifier
                                                    accessoryParameters:(nonnull MPAccessoryParameters *)accessoryParameters
                                                          statusChanged:(nonnull MPTransactionProcessStatusChanged)statusChanged
                                                         actionRequired:(nonnull MPTransactionProcessActionRequired)actionRequired
                                                              completed:(nonnull MPTransactionProcessCompleted)completed;


/**
 * Starts and returns a new transaction process which guide you through a complete transaction.
 * This method is used if the session has already been created on the backend.
 * @param sessionIdentifier The sessionIdentifier of the transaction to start
 * @param accessoryParameters Parameters defining the accessory to be used for the transaction.
 * @param processParameters The parameters specifying extra transaction process parameters.
 * @param statusChanged The status of the process changed and new information can be displayed to the user
 * @param actionRequired An explicit action by the merchant or customer is required
 * @param completed The transactionProcess ended and a new one can be started
 * @since 2.5.0
 */
- (nonnull MPTransactionProcess *)startTransactionWithSessionIdentifier:(nonnull NSString *)sessionIdentifier
                                                    accessoryParameters:(nonnull MPAccessoryParameters *)accessoryParameters
                                                      processParameters:(nonnull MPTransactionProcessParameters *)processParameters
                                                          statusChanged:(nonnull MPTransactionProcessStatusChanged)statusChanged
                                                         actionRequired:(nonnull MPTransactionProcessActionRequired)actionRequired
                                                              completed:(nonnull MPTransactionProcessCompleted)completed;


/**
 * Starts and returns a new transaction process which guide you through a complete transaction. This method registers the transaction locally without requiring a backend for this.
 * @param transactionParameters The parameters specifying the transaction and it's type. Make sure to use CHARGE transaction parameters.
 * @param accessoryParameters Parameters defining the accessory to be used for the transaction.
 * @param registered Callback when the transaction has been registered with the backend. Use this information to save a reference to it.
 * @param statusChanged The status of the process changed and new information can be displayed to the user
 * @param actionRequired An explicit action by the merchant or customer is required
 * @param completed The transactionProcess ended and a new one can be started
 * @since 2.5.0
 */
- (nonnull MPTransactionProcess *)startTransactionWithParameters:(nonnull MPTransactionParameters *)transactionParameters
                                             accessoryParameters:(nonnull MPAccessoryParameters *)accessoryParameters
                                                      registered:(nonnull MPTransactionProcessRegistered)registered
                                                   statusChanged:(nonnull MPTransactionProcessStatusChanged)statusChanged
                                                  actionRequired:(nonnull MPTransactionProcessActionRequired)actionRequired
                                                       completed:(nonnull MPTransactionProcessCompleted)completed;

/**
 * Starts and returns a new transaction process which guide you through a complete transaction. This method registers the transaction locally without requiring a backend for this.
 * @param transactionParameters The parameters specifying the transaction and it's type. Make sure to use CHARGE transaction parameters.
 * @param accessoryParameters Parameters defining the accessory to be used for the transaction.
 * @param processParameters The parameters specifying extra transaction process parameters.
 * @param registered Callback when the transaction has been registered with the backend. Use this information to save a reference to it.
 * @param statusChanged The status of the process changed and new information can be displayed to the user.
 * @param actionRequired An explicit action by the merchant or customer is required.
 * @param completed The transactionProcess ended and a new one can be started
 * @since 2.5.0
 */
- (nonnull MPTransactionProcess *)startTransactionWithParameters:(nonnull MPTransactionParameters *)transactionParameters
                                             accessoryParameters:(nonnull MPAccessoryParameters *)accessoryParameters
                                               processParameters:(nullable MPTransactionProcessParameters *)processParameters
                                                      registered:(nonnull MPTransactionProcessRegistered)registered
                                                   statusChanged:(nonnull MPTransactionProcessStatusChanged)statusChanged
                                                  actionRequired:(nonnull MPTransactionProcessActionRequired)actionRequired
                                                       completed:(nonnull MPTransactionProcessCompleted)completed;


/**
 * Starts and returns a new transaction process which guides you through a complete transaction using an alternative payment method.
 * This method requires all necessary processing data for the transaction and executes it without requiring other interaction.
 *
 * @param transactionParameters The parameters specifying the transaction and it's type.
 * @param accountParameters   The parameters specifying the data needed for the execution of the transaction.
 * @param statusChanged The status of the process changed and new information can be displayed to the user.
 * @param completed The transactionProcess ended and a new one can be started.
 * @since 2.23.0
 */
- (nonnull MPTransactionProcess *)startTransactionWithParameters:(nonnull MPTransactionParameters *)transactionParameters
                                               accountParameters:(nonnull MPAccountParameters *)accountParameters
                                                      registered:(nonnull MPTransactionProcessRegistered)registered
                                                   statusChanged:(nonnull MPTransactionProcessStatusChanged)statusChanged
                                                       completed:(nonnull MPTransactionProcessCompleted)completed;


/**
 * Starts and returns a transaction process which somehow makes an amendment to an existing transaction, i.e. refunds it or captures it.
 * This does not require a connection to an accessory
 *
 * @param transactionParameters The parameters specifying the transaction and it's type. Make sure to use REFUND or CAPTURE transaction parameters.
 * @since 2.8.0
 */
- (nonnull MPTransactionProcess *)amendTransactionWithParameters:(nonnull MPTransactionParameters*)transactionParameters
                                                   statusChanged:(nonnull MPTransactionProcessStatusChanged)statusChanged
                                                       completed:(nonnull MPTransactionProcessCompleted)completed;

/**
 * Prints a customer receipt for the given transaction identifier.
 * A convenience method which first fetches the transaction.
 *
 * @param transactionIdentifier Transaction identifier of the transaction.
 * @param accessoryParameters Parameters defining the accessory to be used for the printing.
 * @param statusChanged The status of the process changed and new information can be displayed to the user
 * @param completed The printingProcess ended and a new one can be started
 * @since 2.5.0
 */
- (nonnull MPPrintingProcess *)printCustomerReceiptForTransactionIdentifier:(nonnull NSString *)transactionIdentifier
                                                        accessoryParameters:(nonnull MPAccessoryParameters*)accessoryParameters
                                                              statusChanged:(nonnull MPPrintingProcessStatusChanged)statusChanged
                                                                  completed:(nonnull MPPrintingProcessCompleted)completed;


/**
 * Synchronizes the SDK configurations
 *
 * @param completed The completion block for the synchronization process, containing the details of the configuration.
 * @since 2.33.0
 */
- (void)synchronizeConfigurationWithCompleted:(nonnull MPSynchronizeConfigurationProcessCompleted)completed;

@end

