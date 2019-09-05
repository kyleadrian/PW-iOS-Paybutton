//
// PAYWORKS GMBH ("COMPANY") CONFIDENTIAL
// Copyright (c) 2018 Payworks GmbH, All Rights Reserved.
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


/**
 * Provides the status of the offline module
 * @since 2.33.0
 */
typedef NS_ENUM(NSUInteger, MPOfflineModuleStatus) {
    /**
     * The status of the offline module is unknown.
     * @since 2.33.0
     */
    MPOfflineModuleStatusUnknown = 0,
    /**
     * The offline module is enabled.
     * @since 2.33.0
     */
    MPOfflineModuleStatusEnabled,
    /**
     * The offline module is disabled.
     * @since 2.33.0
     */
    MPOfflineModuleStatusDisabled
};

@interface MPConfigurationDetails : NSObject

/**
 * Provides the status of the offline module
 * @since 2.33.0
 */
@property (assign, readonly, nonatomic) MPOfflineModuleStatus offlineModuleStatus;

@end
