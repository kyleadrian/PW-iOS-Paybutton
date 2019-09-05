//
//  MPCommunicationModule.h
//  payworks.connect.ios
//
//  Created by Simon Eumes on 4/24/13.
//  Copyright (c) 2016 Payworks GmbH. All rights reserved.
//

#import "MPCommunicationModuleDelegate.h"
#import "MPCommunicationModule.h"
#import "MPAccessory.h"

@class MPCommunicationModule;
@class MPAccessoryParameters;

@interface MPAbstractCommunicationModule : NSObject <MPCommunicationModule>

@property (weak, nonatomic) id<MPCommunicationModuleDelegate> delegate;
@property (assign, nonatomic) MPAccessoryConnectionType connectionType;
@property (assign, nonatomic) MPAccessoryConnectionState connectionState;

@property (copy, nonatomic) MPCommunicationModuleConnectSuccess connectSuccess;
@property (copy, nonatomic) MPCommunicationModuleConnectFailure connectFailure;

@property (copy, nonatomic) MPCommunicationModuleDisconnectSuccess disconnectSuccess;
@property (copy, nonatomic) MPCommunicationModuleDisconnectFailure disconnectFailure;

+ (instancetype)moduleForParameters:(MPAccessoryParameters *)parameters error:(NSError *__autoreleasing *)error;

@end
