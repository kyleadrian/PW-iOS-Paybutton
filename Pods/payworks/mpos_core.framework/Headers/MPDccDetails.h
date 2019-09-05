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

#import <Foundation/Foundation.h>
#import "MPTransaction.h"

/**
 * DCC (Dynamic Currency Conversion) status
 * @since 2.29.0
 */
typedef NS_ENUM(NSUInteger, MPDccStatus) {
    /**
     * DCC Not available status
     * @since 2.29.0
     */
    MPDccStatusNotAvailable,
    /**
     * DCC Applied status
     * @since 2.29.0
     */
    MPDccStatusApplied,
    /**
     * DCC Not applied status
     * @since 2.29.0
     */
    MPDccStatusNotApplied,
    /**
     * DCC Error status
     * @since 2.29.0
     */
    MPDccStatusError
};

/**
 * DCC Client status
 * @since 2.29.0
 */
typedef NS_ENUM(NSUInteger, MPDccStatusDetails) {
    /**
     * Not available state of DCC status details
     * @since 2.29.0
     */
    MPDccStatusDetailsNotAvailable,
    /**
     * Applied to make the currency exchange
     * @since 2.29.0
     */
    MPDccStatusDetailsApplied,
    /**
     * Not applied to make the currency exchange
     * @since 2.29.0
     */
    MPDccStatusDetailsNotApplied,
    /**
     * Not applied by shopper
     * @since 2.29.0
     */
    MPDccStatusDetailsNotAppliedByShopper,
    /**
     * There was an server error during query execution
     * @since 2.29.0
     */
    MPDccStatusDetailsErrorDccQueryServer,
    /**
     * There was an internal error during query execution
     * @since 2.29.0
     */
    MPDccStatusDetailsErrorDccQueryClient,
    /**
     * Not applied because of the same currency
     * @since 2.29.0
     */
    MPDccStatusDetailsNotAppliedSameCurrency
};

/**
 * DCC (Dynamic Currency Conversion) Lookup status
 * @since 2.29.0
 */
typedef NS_ENUM(NSUInteger, MPDccLookupStatus) {
    /**
     * No information about DCC Lookup, unknown status
     * @since 2.29.0
     */
    MPDccLookupStatusUnknown,
    /**
     * DCC Lookup went successful, currency exchange can be apply
     * @since 2.29.0
     */
    MPDccLookupStatusSuccessful,
    /**
     * DCC Lookup found the same currencies, no need to apply exchange
     * @since 2.29.0
     */
    MPDccLookupStatusSameCurrency,
    /**
     * DCC Lookup status is unsuccessful
     * @since 2.29.0
     */
    MPDccLookupStatusNotSuccessful
};

@interface MPDccDetails : NSObject<NSCopying>

/**
 * Provides the DCC status
 * @since 2.29.0
 */
@property (readonly, nonatomic) MPDccStatus status;

/**
 * Provides the DCC lookup status
 * @since 2.29.0
 */
@property (readonly, nonatomic) MPDccLookupStatus lookupStatus;

/**
 * Provides DCC status details
 * @since 2.29.0
 */
@property (readonly, nonatomic) MPDccStatusDetails statusDetails;

/**
 * Provides converted amount of the new currency
 * @since 2.29.0
 */
@property (readonly, nonatomic, nullable) NSDecimalNumber *convertedAmount;

/**
 * Provides the new currency
 * @since 2.29.0
 */
@property (readonly, nonatomic) MPCurrency convertedCurrency;

/**
 * Provides the exchange rate
 * @since 2.29.0
 */
@property (readonly, nonatomic, nullable) NSDecimalNumber *rate;

/**
 * Provides markup
 * @since 2.29.0
 */
@property (readonly, nonatomic, nullable) NSDecimalNumber *markup;

/**
 * Provides supported schemes
 * @since 2.29.0
 */
@property (readonly, nonatomic, nullable) NSSet<NSNumber *> *supportedSchemes;

/**
 * Provides conversion hint
 * @since 2.29.0
 */
@property (readonly, nonatomic, nullable) NSString *conversionHint;

@end
