
#import <Foundation/Foundation.h>



#define AMErrorMake(domain, code) _AMErrorMake(code, #code, domain, __FILE__, __LINE__)

#define AMErrorWrap(error) _AMErrorWrap(error, __FILE__, __LINE__)

#define AMOutputErrorAssign(outError, error) _AMOutputErrorAssign(outError, error)


extern NSString *const AMErrorOriginKey;  // NSString
extern NSString *const AMErrorNameKey;  // NSString



@interface AMError : NSError <NSMutableCopying>

/**
 Corresponds to `AMErrorNameKey`.
 */
- (NSString *)name;

/**
 Corresponds to `AMErrorOriginKey`.
 */
- (NSString *)origin;

/**
 Corresponds to `NSUnderlyingErrorKey`.
 */
- (NSError *)underlyingError;

/**
 Corresponds to `NSStringEncodingErrorKey`.
 */
- (NSNumber *)stringEncoding;

/**
 Corresponds to `NSURLErrorKey`.
 */
- (NSURL *)URL;

/**
 Corresponds to `NSFilePathErrorKey`.
 */
- (NSString *)filePath;

/**
 Dictionary-like access to `userInfo`.
 */
- (id)objectForKeyedSubscript:(id <NSCopying>)key;

#pragma mark -
#pragma mark Bundle Management for Strings files

+ (void)setDefaultBundle:(NSBundle *)bundle;

+ (void)setBundle:(NSBundle *)bundle forDomain:(NSString *)domain;

@end



@interface AMMutableError : AMError 

/**
 Corresponds to `AMErrorNameKey`.
 */
@property (nonatomic) NSString *name;

/**
 Corresponds to `AMErrorOriginKey`.
 */
@property (nonatomic) NSString *origin;

/**
 Corresponds to `NSLocalizedDescriptionKey`.
 */
@property (nonatomic) NSString *localizedDescription;

/**
 Corresponds to `NSLocalizedFailureReasonErrorKey`.
 */
@property (nonatomic) NSString *localizedFailureReason;

/**
 Corresponds to `NSLocalizedRecoverySuggestionErrorKey`.
 */
@property (nonatomic) NSString *localizedRecoverySuggestion;

/**
 Corresponds to `NSLocalizedRecoveryOptionsErrorKey`
 */
@property (nonatomic) NSArray *localizedRecoveryOptions;

/**
 Corresponds to `NSRecoveryAttempterErrorKey`
 */
@property (nonatomic) id recoveryAttempter;

/**
 Corresponds to `NSHelpAnchorErrorKey`
 */
@property (nonatomic) NSString *helpAnchor;

/**
 Corresponds to `NSUnderlyingErrorKey`.
 */
@property (nonatomic) NSError *underlyingError;

/**
 Corresponds to `NSStringEncodingErrorKey`.
*/
@property (nonatomic) NSNumber *stringEncoding;

/**
 Corresponds to `NSURLErrorKey`.
*/
@property (nonatomic) NSURL *URL;

/**
 Corresponds to `NSFilePathErrorKey`.
 */
@property (nonatomic) NSString *filePath;

/**
 Dictionary-like access to `userInfo`.
 */
- (void)setObject:(id)obj forKeyedSubscript:(id <NSCopying>)key;

@end



// !!!: Internal methods, use macros instead.

#ifdef __cplusplus
extern "C" {
#endif

    extern AMMutableError *_AMErrorMake(NSInteger errorCode, char const *errorName, NSString *domain, char const *fileName, int lineNumber);

    extern AMMutableError* _AMErrorWrap(NSError *origError, char const *fileName, int lineNumber);

    static inline void _AMOutputErrorAssign(NSError **outError, NSError *error)
    {
        if (outError != nil) *outError = error;
    }

#ifdef __cplusplus
}
#endif

