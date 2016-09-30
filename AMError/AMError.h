
#import <Foundation/Foundation.h>

FOUNDATION_EXPORT double AMErrorVersionNumber;
FOUNDATION_EXPORT const unsigned char AMErrorVersionString[];

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

extern  NSString * _Nonnull const AMErrorOriginKey;  // NSString
extern NSString * _Nonnull const AMErrorNameKey;  // NSString


/**
 `AMError` is an `NSError` subclass that adds the following features:
 
   - Accessors for all "userInfo" keys defined by `NSError`

 */
@interface AMError : NSError <NSMutableCopying>

/**
 Corresponds to `AMErrorNameKey`.
 */
- (nonnull NSString *)name;

/**
 Corresponds to `AMErrorOriginKey`.
 */
- (nonnull NSString *)origin;

/**
 Corresponds to `NSUnderlyingErrorKey`.
 */
- (nullable NSError *)underlyingError;

/**
 Corresponds to `NSStringEncodingErrorKey`.
 */
- (nullable NSNumber *)stringEncoding;

/**
 Corresponds to `NSURLErrorKey`.
 */
- (nullable NSURL *)URL;

/**
 Corresponds to `NSFilePathErrorKey`.
 */
- (nullable NSString *)filePath;



/**
 Dictionary-like access to `userInfo`.
 */
- (nullable id)objectForKeyedSubscript:(nonnull id <NSCopying>)key;

#pragma mark -
#pragma mark Bundle Management for Strings files

+ (void)setDefaultBundle:(NSBundle * _Nullable)bundle;

+ (void)setBundle:(NSBundle * _Nullable)bundle forDomain:(NSString * _Nonnull)domain;

+ (NSString * _Nullable)stringsTableNameForDomain:(NSString * _Nonnull)domain;

/**
 By default, AMError will look for <domain>.strings. If you wish to use a
 different strings file you can specify it here
 */
+ (void)setStringsTableName:(NSString * _Nullable)tableName forDomain:(NSString * _Nonnull)domain;

@end



/**
 `AMMutableError`

 */
@interface AMMutableError : AMError 

/**
 Corresponds to `AMErrorNameKey`.
 */
@property (nonnull, atomic, strong) NSString  *name;

/**
 Corresponds to `AMErrorOriginKey`.
 */
@property (nonnull, atomic, strong) NSString *origin;

/**
 Corresponds to `NSLocalizedDescriptionKey`.
 
 NOTE: NSError provides a default value for `localizedDescription` that 
 this subclass does NOT override. If this property is set to nil, it will
 fall back to the superclasses implementation, and NOT return nil.
 */
@property (nullable, atomic, copy) NSString *localizedDescription;

/**
 Corresponds to `NSLocalizedFailureReasonErrorKey`.
 */
@property (nullable, atomic, copy) NSString *localizedFailureReason;

/**
 Corresponds to `NSLocalizedRecoverySuggestionErrorKey`.
 */
@property (nullable, atomic, copy) NSString *localizedRecoverySuggestion;

/**
 Corresponds to `NSLocalizedRecoveryOptionsErrorKey`
 */
@property (nullable, atomic, copy) NSArray *localizedRecoveryOptions;

/**
 Corresponds to `NSRecoveryAttempterErrorKey`
 */
@property (nullable, strong) id recoveryAttempter;

/**
 Corresponds to `NSHelpAnchorErrorKey`
 */
@property (nullable, copy) NSString *helpAnchor;

/**
 Corresponds to `NSUnderlyingErrorKey`.
 */
@property (nullable, copy) NSError *underlyingError;

/**
 Corresponds to `NSStringEncodingErrorKey`.
*/
@property (nullable, copy) NSNumber *stringEncoding;

/**
 Corresponds to `NSURLErrorKey`.
*/
@property (nullable, copy) NSURL *URL;

/**
 Corresponds to `NSFilePathErrorKey`.
 */
@property (nullable, copy) NSString *filePath;

/**
 Dictionary-like access to `userInfo`.
 */
- (void)setObject:(nullable id)obj forKeyedSubscript:(nonnull id <NSCopying>)key;

@end



// WARNING: Internal functions, use macros instead.

#ifdef __cplusplus
extern "C" {
#endif

    extern AMMutableError * _Null_unspecified _AMErrorMake(NSInteger errorCode, char const * _Null_unspecified errorName, NSString * _Null_unspecified domain, char const * _Null_unspecified fileName, int lineNumber, NSDictionary * _Null_unspecified userInfo);

    extern AMMutableError  * _Null_unspecified  _AMErrorWrap(NSError * _Null_unspecified origError, char const * _Null_unspecified fileName, int lineNumber);

    static inline void _AMOutputErrorAssign(NSError * _Null_unspecified * _Null_unspecified outError, NSError *_Null_unspecified error)
    {
        if (outError != nil) *outError = error;
    }

#ifdef __cplusplus
}
#endif

