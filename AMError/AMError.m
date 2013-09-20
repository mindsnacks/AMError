#import "AMError.h"

NSString *const AMErrorOriginKey = @"AMErrorOrigin";
NSString *const AMErrorNameKey = @"AMErrorName";


//@interface AMError ()
//@property (nonatomic) NSString *name;
//@property (nonatomic) NSString *origin;
//@property (nonatomic) NSString *localizedFailureReason;
//@property (nonatomic) NSError *underlyingError;
//
//@property (nonatomic, strong) NSMutableDictionary *mutableUserInfo;
//@end


@implementation AMError

__strong static NSBundle *defaultBundle = nil;
__strong static NSMutableDictionary *bundleMap = nil;

+ (void)initialize
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        defaultBundle = [NSBundle mainBundle];
    });
}

- (id)mutableCopyWithZone:(NSZone *)zone
{
    return [AMMutableError errorWithDomain:[self domain] code:[self code] userInfo:[self userInfo]];
}

- (NSString *)name
{
    return self[AMErrorNameKey];
}

- (NSString *)origin
{
    return self[AMErrorOriginKey];
}

- (NSString *)underlyingError
{
    return self[NSUnderlyingErrorKey];
}

- (NSNumber *)stringEncoding
{
    return self[NSStringEncodingErrorKey];
}

- (NSURL *)URL
{
    return self[NSURLErrorKey];
}

- (NSString *)filePath
{
    return self[NSFilePathErrorKey];
}

- (id)objectForKeyedSubscript:(id <NSCopying>)key
{
    return [self userInfo][key];
}

#pragma mark -
#pragma mark Bundle class methods

+ (void)setDefaultBundle:(NSBundle *)bundle
{
    defaultBundle = bundle;
}

+ (void)setBundle:(NSBundle *)bundle forDomain:(NSString *)domain
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        bundleMap = [[NSMutableDictionary alloc] init];
    });
    bundleMap[domain] = bundle;
}

+ (NSBundle *)bundleForDomain:(NSString *)domain
{
    if (bundleMap[domain] != nil) {
        return bundleMap[domain];
    }
    return defaultBundle;
}

@end


@implementation AMMutableError
{
    NSMutableDictionary *_mutableUserInfo;
}

@dynamic name;
@dynamic origin;
@dynamic localizedDescription;
@dynamic localizedFailureReason;
@dynamic localizedRecoverySuggestion;
@dynamic localizedRecoveryOptions;
@dynamic recoveryAttempter;
@dynamic underlyingError;
@dynamic helpAnchor;
@dynamic stringEncoding;
@dynamic URL;
@dynamic filePath;

- (instancetype)initWithDomain:(NSString *)domain code:(NSInteger)code userInfo:(NSDictionary *)dict
{
    self = [super initWithDomain:domain code:code userInfo:nil];
    if (self) {
        _mutableUserInfo = [NSMutableDictionary dictionaryWithDictionary:dict];
    }
    return self;
}

+ (instancetype)errorWithDomain:(NSString *)domain code:(NSInteger)code userInfo:(NSDictionary *)dict
{
    return [[self alloc] initWithDomain:domain code:code userInfo:dict];
}

- (NSDictionary *)userInfo
{
    return [NSDictionary dictionaryWithDictionary:_mutableUserInfo];
}

- (void)setName:(NSString*)name
{
    self[AMErrorNameKey] = name;
}

- (void)setOrigin:(NSString *)origin
{
    self[AMErrorOriginKey] = origin;
}

- (void)setLocalizedDescription:(NSString *)localizedDescription
{
    self[NSLocalizedDescriptionKey] = localizedDescription;
}

- (void)setLocalizedFailureReason:(NSString *)localizedFailureReason
{
    self[NSLocalizedFailureReasonErrorKey] = localizedFailureReason;
}

- (void)setLocalizedRecoverySuggestion:(NSString *)localizedRecoverySuggestion
{
    self[NSLocalizedRecoverySuggestionErrorKey] = localizedRecoverySuggestion;
}

- (void)setLocalizedRecoveryOptions:(NSArray *)localizedRecoveryOptions
{
    self[NSLocalizedRecoveryOptionsErrorKey] = localizedRecoveryOptions;
}

- (void)setRecoveryAttempter:(id)recoveryAttempter
{
    self[NSRecoveryAttempterErrorKey] = recoveryAttempter;
}

- (void)setHelpAnchor:(NSString *)helpAnchor
{
    self[NSHelpAnchorErrorKey] = helpAnchor;
}

- (void)setUnderlyingError:(NSError *)error
{
    self[NSUnderlyingErrorKey] = error;
}

- (void)setStringEncoding:(NSNumber *)stringEncoding
{
    self[NSStringEncodingErrorKey] = stringEncoding;
}

- (void)setURL:(NSURL *)URL
{
    self[NSURLErrorKey ] = URL;
}

- (void)setFilePath:(NSString *)filePath
{
    self[NSFilePathErrorKey] = filePath;
}

- (void)setObject:(id)obj forKeyedSubscript:(id <NSCopying>)key
{
    _mutableUserInfo[key] = obj;
}

@end


static NSString *originString(char const *fileName, int lineNumber)
{
	NSString *fileNameString = [[NSString stringWithCString:fileName encoding:NSUTF8StringEncoding] lastPathComponent];
	NSString *errorOrigin = [NSString stringWithFormat:@"%@:%d", fileNameString, lineNumber];
    return errorOrigin;
}


AMMutableError *_AMErrorMake(NSInteger errorCode, char const *errorName, NSString *domain, char const *fileName, int lineNumber)
{
	NSString *errorNameString = [NSString stringWithCString:errorName encoding:NSUTF8StringEncoding];

	NSString *errorOrigin = originString(fileName, lineNumber);

	NSString *localizedDescription = [[AMError bundleForDomain:domain] localizedStringForKey:errorNameString
                                                                                       value:nil
                                                                                       table:domain];

    AMMutableError *error = [AMMutableError errorWithDomain:domain code:errorCode userInfo:nil];
    error.name = errorNameString;
    error.origin = errorOrigin;
    error.localizedDescription = localizedDescription;
    return error;
}


AMMutableError *_AMErrorWrap(NSError *origError, char const *fileName, int lineNumber)
{
	NSString *errorOrigin = originString(fileName, lineNumber);

    AMMutableError *error = [AMMutableError errorWithDomain:[origError domain] code:[origError code] userInfo:[origError userInfo]];

    error.origin = errorOrigin;

    return error;
}

