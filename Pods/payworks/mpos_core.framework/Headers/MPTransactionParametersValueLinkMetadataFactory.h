//
//  MPTransactionParametersValueLinkMetadataFactory.h
//  mpos_core
//
//  Created by Juliano Rotta on 17.04.18.
//  Copyright © 2018 payworks GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MPTransactionParametersValueLinkMetadataFactory : NSObject

+ (nonnull NSDictionary<NSString*, NSString*>*) create:(nullable NSString*)user1 user2:(nullable NSString*)user2 transactionPostalCode:(nullable NSString*)transactionPostalCode clerkId:(nullable NSString*)clerkId;

@end
