
#import <Foundation/Foundation.h>

///---------------------
/// @name Main Functions
//----------------------

#define AMErrorMake(domain, code) _AMErrorMake(code, #code, domain, __FILE__, __LINE__, nil)

#define AMErrorMakeWithInfo(domain, code, info) _AMErrorMake(code, #code, domain, __FILE__, __LINE__, info)

#define AMErrorWrap(error) _AMErrorWrap(error, __FILE__, __LINE__)

#define AMOutputErrorAssign(outError, error) _AMOutputErrorAssign(outError, error)


///-------------------------------
/// @name Additional UserInfo Keys
//--------------------------------

extern NSString *const AMErrorOriginKey;  // NSString
extern NSString *const AMErrorNameKey;  // NSString


/**
 `AMError`

 */
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

+ (NSString *)stringsTableNameForDomain:(NSString *)domain;

/**
 By default, AMError will look for <domain>.strings. If you wish to use a
 different strings file you can specify it here
 */
+ (void)setStringsTableName:(NSString *)tableName forDomain:(NSString *)domain;

@end



/**
 `AMMutableError`

 */
@interface AMMutableError : AMError 

/**
 Corresponds to `AMErrorNameKey`.
 */
@property (nonatomic, strong) NSString *name;

/**
 Corresponds to `AMErrorOriginKey`.
 */
@property (nonatomic, strong) NSString *origin;

/**
 Corresponds to `NSLocalizedDescriptionKey`.
 
 NOTE: NSError provides a default value for `localizedDescription` that 
 this subclass does NOT override. If this property is set to nil, it will
 fall back to the superclasses implementation, and NOT return nil.
 */
@property (nonatomic, strong) NSString *localizedDescription;

/**
 Corresponds to `NSLocalizedFailureReasonErrorKey`.
 */
@property (nonatomic, strong) NSString *localizedFailureReason;

/**
 Corresponds to `NSLocalizedRecoverySuggestionErrorKey`.
 */
@property (nonatomic, strong) NSString *localizedRecoverySuggestion;

/**
 Corresponds to `NSLocalizedRecoveryOptionsErrorKey`
 */
@property (nonatomic, strong) NSArray *localizedRecoveryOptions;

/**
 Corresponds to `NSRecoveryAttempterErrorKey`
 */
@property (nonatomic, strong) id recoveryAttempter;

/**
 Corresponds to `NSHelpAnchorErrorKey`
 */
@property (nonatomic, strong) NSString *helpAnchor;

/**
 Corresponds to `NSUnderlyingErrorKey`.
 */
@property (nonatomic, strong) NSError *underlyingError;

/**
 Corresponds to `NSStringEncodingErrorKey`.
*/
@property (nonatomic, strong) NSNumber *stringEncoding;

/**
 Corresponds to `NSURLErrorKey`.
*/
@property (nonatomic, strong) NSURL *URL;

/**
 Corresponds to `NSFilePathErrorKey`.
 */
@property (nonatomic, strong) NSString *filePath;

/**
 Dictionary-like access to `userInfo`.
 */
- (void)setObject:(id)obj forKeyedSubscript:(id <NSCopying>)key;

@end



// WARNING: Internal functions, use macros instead.

#ifdef __cplusplus
extern "C" {
#endif

    extern AMMutableError *_AMErrorMake(NSInteger errorCode, char const *errorName, NSString *domain, char const *fileName, int lineNumber, NSDictionary *userInfo);

    extern AMMutableError* _AMErrorWrap(NSError *origError, char const *fileName, int lineNumber);

    static inline void _AMOutputErrorAssign(NSError **outError, NSError *error)
    {
        if (outError != nil) *outError = error;
    }

#ifdef __cplusplus
}
#endif

