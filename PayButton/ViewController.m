//
//  ViewController.m
//  PayButton
//
//  Created by Kyle Wiltshire on 7/16/18.
//  Copyright © 2018 Payworks. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

@synthesize textfield;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.

}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


NSString *transactionIdentifier = @"";


- (IBAction)paymentButtonClicked:(id)sender {
    
    MPUMposUi *ui = [MPUMposUi initializeWithProviderMode:MPProviderModeTEST
                                       merchantIdentifier:@"837363ff-4430-4741-9e56-709fba07ad62"
                                           merchantSecret:@"JkjyTiAHihQcxRw84EQKVajtWXwyeRtY"];
    
    
    
    
    
    
    // MPAccessoryParameters *ap = [MPAccessoryParameters externalAccessoryParametersWithFamily:MPAccessoryFamilyMiuraMPI
    //                                                                                 protocol:@"com.miura.shuttle"
    //                                                                                optionals:nil];
    
    
    
     MPAccessoryParameters *ap = [MPAccessoryParameters tcpAccessoryParametersWithFamily:MPAccessoryFamilyVerifoneVIPA
                                                                                  remote:@"10.4.25.113"
                                                                                    port:16107
                                                                               optionals:nil];
    
    
    
    MPTransactionParameters *tp = [MPTransactionParameters chargeWithAmount:[NSDecimalNumber decimalNumberWithString:@"10.00"]
                                                                   currency:MPCurrencyUSD
                                                                  optionals:^(id<MPTransactionParametersOptionals>  _Nonnull optionals) {
                                                                      optionals.subject = @"Bouquet of Flowers";
                                                                      optionals.customIdentifier = @"yourReferenceForTheTransaction";
                                                                  }];
    
    ui.configuration.terminalParameters = ap;
    
    ui.configuration.summaryFeatures = MPUMposUiConfigurationSummaryFeatureSendReceiptViaEmail | MPUMposUiConfigurationSummaryFeatureRefundTransaction;
    
    UIViewController *viewController = [ui createTransactionViewControllerWithTransactionParameters:tp
                                                                                          completed:^(UIViewController * _Nonnull controller, MPUTransactionResult result, MPTransaction * _Nullable transaction)
                                        
                                        {
                                            
                                            [self dismissViewControllerAnimated:YES completion:NULL];
                                            
                                            UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"Result"
                                                                                            message:@""
                                                                                           delegate:nil
                                                                                  cancelButtonTitle:nil
                                                                                  otherButtonTitles:@"OK",nil];
                                
                                        
                                            
                                            if (result == MPUTransactionResultApproved) {
                                                alert.message = @"Payment was approved!";
                                            } else {
                                                alert.message = @"Payment was declined/aborted!";
                                            }
                                            
                                            [alert show];
                                            
                                        }];
    
    
    UINavigationController *modalNav = [[UINavigationController alloc] initWithRootViewController:viewController];
    modalNav.navigationBar.barStyle = UIBarStyleBlack;
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
        modalNav.modalPresentationStyle = UIModalPresentationFullScreen;
    } else { // Show as Form on iPad
        modalNav.modalPresentationStyle = UIModalPresentationFormSheet;
    }
    [self presentViewController:modalNav animated:YES completion:NULL];
    

}

@end

