//
//  AMErrorSpec.m
//  AMError
//
//  Created by Andy Mroczkowski on 9/12/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#import "AMError.h"


#define ERROR_DOMAIN @"net.mrox.amerror"
#define ERROR_CODE_1 1
#define ERROR_CODE_2 2


SPEC_BEGIN(AMErrorSpec)

beforeAll(^{
    [AMError setDefaultBundle:[NSBundle bundleForClass:[self class]]];
});

context(@"macro creation", ^{

    __block AMError *error;

    beforeEach(^{
        error = AMErrorMake(ERROR_DOMAIN, ERROR_CODE_1);
    });

    specify(^{
        [[error.name should] equal:@"ERROR_CODE_1"];
    });

    specify(^{
        [[error.origin should] beNonNil];
    });

    specify(^{
        [[theValue(error.code) should] equal:theValue(ERROR_CODE_1)];
    });
});

context(@"macro creation with existing error", ^{

    __block AMError *error;
    __block NSError *existingError;

    beforeEach(^{
        existingError = [NSError errorWithDomain:ERROR_DOMAIN code:ERROR_CODE_1 userInfo:nil];
        error = AMErrorWrap(existingError);
    });

    specify(^{
        [[theValue([existingError code]) should] equal:theValue(error.code)];
    });

    specify(^{
        [[[existingError domain] should] equal:error.domain];
    });

    specify(^{
        [[error.origin should] beNonNil];
    });
});

context(@"mutable copy", ^{

    __block AMError *error1;
    __block AMMutableError *error2;

    beforeEach(^{
        error1 = [AMError errorWithDomain:ERROR_DOMAIN code:ERROR_CODE_1 userInfo:nil];
        error2 = [error1 mutableCopy];
    });

    specify(^{
        [[error2 should] beKindOfClass:[AMMutableError class]];
    });

    specify(^{
        [[error1 shouldNot] beIdenticalTo:error2];
    });

    specify(^{
        [[error1 should] equal:error2];
    });

    it(@"should be able to set values", ^{
        NSString *name = @"theName";
        error2.name = name;
        [[error2.name should] equal:name];
    });
});

context(@"mutable", ^{

    __block AMMutableError *error;

    beforeEach(^{
        error = [AMMutableError errorWithDomain:ERROR_DOMAIN code:0 userInfo:nil];
    });

    void (^setAndCheck)(SEL s, id) = ^ (SEL s, id val) {
        NSString *key = NSStringFromSelector(s);
        [error setValue:val forKey:key];
        [[[error valueForKey:key] should] equal:val];
    };

    it(@"should set all fields correctly", ^{
        setAndCheck(@selector(localizedDescription), @"pineapple");
        setAndCheck(@selector(localizedFailureReason), @"pineapple");
        setAndCheck(@selector(localizedRecoverySuggestion), @"pineapple");
        setAndCheck(@selector(localizedRecoveryOptions), @[@"pineappple"]);
        setAndCheck(@selector(recoveryAttempter), @"pineapple");
        setAndCheck(@selector(helpAnchor), @"pineapple");
        setAndCheck(@selector(stringEncoding), [NSNumber numberWithInt:NSUTF8StringEncoding]);
        setAndCheck(@selector(underlyingError), [NSError errorWithDomain:ERROR_DOMAIN code:ERROR_CODE_1 userInfo:nil]);
    });
});

context(@"customized marcro", ^{

#define ERR(code) AMErrorMake(ERROR_DOMAIN, code)

    __block AMError *error;

    beforeEach(^{
        error = ERR(ERROR_CODE_1);
    });

    specify(^{
        [[[error domain] should] equal:ERROR_DOMAIN];
    });

    specify(^{
        [[theValue([error code]) should] equal:theValue(ERROR_CODE_1)];
    });
});

SPEC_END
