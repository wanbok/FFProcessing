//
//  YKDefines.h
//  YelpKit
//
//  Created by Gabriel Handford on 4/8/09.
//  Copyright 2009. All rights reserved.
//

/*!
 Generates description from key-value coding.
 For example,
 @code
 - (NSString *)description {
  return YKDescription(@"foo", @"bar", @"someInteger");
 }
 @endcode 
 */
#define YKDescription(...) [NSString stringWithFormat:@"%@; %@", [super description], [[self dictionaryWithValuesForKeys:[NSArray arrayWithObjects:__VA_ARGS__, nil]] description]]
#define YPDebugProps(obj, ...) [[obj dictionaryWithValuesForKeys:[NSArray arrayWithObjects:__VA_ARGS__, nil]] description]

#define YKIntervalToMillis(interval, defaultValue) (interval >= 0 ? (long long)round(interval * 1000) : defaultValue)

/*!
 Constants.
 */
#define YKTimeIntervalMinute (60)
#define YKTimeIntervalHour (YKTimeIntervalMinute * 60)
#define YKTimeIntervalDay (YKTimeIntervalHour * 24)
#define YKTimeIntervalWeek (YKTimeIntervalDay * 7)
#define YKTimeIntervalYear (YKTimeIntervalDay * 365.242199)


/*!
 Macro defaults.
 */
#define YPDebug(fmt, ...) do {} while(0)
#define YPException(e) do {} while(0)
#define YPWarn(fmt, ...) do {} while(0)
#define YPInfo(fmt, ...) do {} while(0)
#define YPError(fmt, ...) do {} while(0)
#define YPNSError(fmt, ...) do {} while(0)

/*!
 Logging macros.
 */
#if DEBUG
#import "GTMLogger.h"
#import "GTMStackTrace.h"
#undef YPDebug
#define YPDebug(fmt, ...) GTMLoggerDebug(@"%@", [NSString stringWithFormat:fmt, ##__VA_ARGS__])
#undef YPException
#define YPException(__EXCEPTION__) GTMLoggerDebug(@"%@", [NSString stringWithFormat:@"\n\n%@\n%@\n\n", [__EXCEPTION__ description], GTMStackTrace()])
#undef YPWarn
#define YPWarn(fmt, ...) GTMLoggerInfo(@"%@", [NSString stringWithFormat:fmt, ##__VA_ARGS__])
#undef YPInfo
#define YPInfo(fmt, ...) GTMLoggerInfo(@"%@", [NSString stringWithFormat:fmt, ##__VA_ARGS__])
#undef YPError
#define YPError(fmt, ...) GTMLoggerError(@"%@", [NSString stringWithFormat:fmt, ##__VA_ARGS__])
#undef YPNSError
#define YPNSError(__ERROR__) do { if (__ERROR__) GTMLoggerError(@"%@", [__ERROR__ gh_fullDescription]); } while(0)
#endif

// YP_DEBUG is in between debug and release
#if YP_DEBUG
#import "GTMLogger.h"
#import "GTMStackTrace.h"
#undef YPException
#define YPException(__EXCEPTION__) GTMLoggerDebug(@"%@", [NSString stringWithFormat:@"\n\n%@\n%@\n\n", [__EXCEPTION__ description], GTMStackTrace()])
#undef YPWarn
#define YPWarn(fmt, ...) GTMLoggerInfo(@"%@", [NSString stringWithFormat:fmt, ##__VA_ARGS__])
#undef YPInfo
#define YPInfo(fmt, ...) GTMLoggerInfo(@"%@", [NSString stringWithFormat:fmt, ##__VA_ARGS__])
#undef YPError
#define YPError(fmt, ...) GTMLoggerError(@"%@", [NSString stringWithFormat:fmt, ##__VA_ARGS__])
#undef YPNSError
#define YPNSError(__ERROR__) do { if (__ERROR__) GTMLoggerError(@"%@", [__ERROR__ gh_fullDescription]); } while(0)
#endif

#define YKIsEqualWithAccuracy(n1, n2, accuracy) (n1 >= (n2-accuracy) && n1 <= (n2+accuracy))

#define YKIsEqualObjects(obj1, obj2) ((obj1 == nil && obj2 == nil) || ([obj1 isEqual:obj2]))

#ifndef __has_feature      // Optional.
#define __has_feature(x) 0 // Compatibility with non-clang compilers.
#endif

#ifndef NS_RETURNS_RETAINED
#if __has_feature(attribute_ns_returns_retained)
#define NS_RETURNS_RETAINED __attribute__((ns_returns_retained))
#else
#define NS_RETURNS_RETAINED
#endif
#endif

#ifndef NS_RETURNS_NOT_RETAINED
#if __has_feature(attribute_ns_returns_not_retained)
#define NS_RETURNS_NOT_RETAINED __attribute__((ns_returns_not_retained))
#else
#define NS_RETURNS_NOT_RETAINED
#endif
#endif

#if YP_DEMO
#define YPDemoMode (YES)
#else
#define YPDemoMode (NO)
#endif

// Deprecated
#define YPOrNSNull(obj) (obj ? obj : (id)[NSNull null])

/*!
 This is pulled from GData obj-c API
 @see http://code.google.com/p/gdata-objectivec-client/source/browse/trunk/Source/Networking/GDataHTTPFetcher.m
 */
static inline void YKAssertSelectorNilOrImplementedWithArguments(id obj, SEL sel, ...) {
  
  // verify that the object's selector is implemented with the proper
  // number and type of arguments
#if YP_DEBUG
  va_list argList;
  va_start(argList, sel);
  
  if (obj && sel) {
    // check that the selector is implemented
    if (![obj respondsToSelector:sel]) {
      [NSException raise:NSInvalidArgumentException format:@"\"%@\" selector \"%@\" is unimplemented or misnamed", 
       NSStringFromClass([obj class]), 
       NSStringFromSelector(sel)];
    } else {
      const char *expectedArgType;
      unsigned int argCount = 2; // skip self and _cmd
      NSMethodSignature *sig = [obj methodSignatureForSelector:sel];
      
      // check that each expected argument is present and of the correct type
      while ((expectedArgType = va_arg(argList, const char*)) != 0) {
        
        if ([sig numberOfArguments] > argCount) {
          const char *foundArgType = [sig getArgumentTypeAtIndex:argCount];
          
          if(0 != strncmp(foundArgType, expectedArgType, strlen(expectedArgType))) {
            [NSException raise:NSInvalidArgumentException format:@"\"%@\" selector \"%@\" argument %d should be type %s", 
             NSStringFromClass([obj class]), 
             NSStringFromSelector(sel), (argCount - 2), expectedArgType];
          }
        }
        argCount++;
      }
      
      // check that the proper number of arguments are present in the selector
      if (argCount != [sig numberOfArguments]) {
        [NSException raise:NSInvalidArgumentException format:@"\"%@\" selector \"%@\" should have %d arguments",
         NSStringFromClass([obj class]), 
         NSStringFromSelector(sel), (argCount - 2)];
      }
    }
  }
  
  va_end(argList);
#endif
}

