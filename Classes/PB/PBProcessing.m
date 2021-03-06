//
//  PBProcessing.m
//  FFProcessing
//
//  Created by Gabriel Handford on 3/31/10.
//  Copyright 2010. All rights reserved.
//

#import "PBProcessing.h"

#import "FFUtils.h"
#import "FFProcessing.h"

#import "FFEncodeProcessor.h"
#import "FFDataMoshProcessor.h"
#import "FFCanny.h"
#import "FFFilters.h"

//#import "FFMPConverter.h"
//#import "FFMPDecoder.h"

#import "FFAVDecoder.h"

@interface PBProcessing ()
@property (retain, nonatomic) NSString *outputPath;
@end

@implementation PBProcessing

@synthesize outputPath=_outputPath, delegate=_delegate;

- (void)dealloc {
  [self close];
  [_outputPath release];
  [super dealloc];
}

- (void)close {
  _processingThread.delegate = nil;
  [_processingThread cancel];
  [_processingThread release];
}  

- (void)startWithItems:(NSArray *)items {
  if ([_processingThread isExecuting]) return;
  
  [self close];
  
  NSString *outputFormat = @"mp4";
  NSString *outputCodecName = @"mpeg4";
  NSString *outputPath = [[FFUtils documentsDirectory] stringByAppendingPathComponent:[NSString stringWithFormat:@"mosh.mp4", outputFormat]];
  
  FFEncoderOptions *encoderOptions = [[[FFEncoderOptions alloc] initWithPath:outputPath formatName:outputFormat codecName:outputCodecName
                                                                      format:FFVFormatNone videoTimeBase:(FFRational){0,0}] autorelease];

  /*!
  FFDataMoshProcessor *processor = [[[FFDataMoshProcessor alloc] initWithEncoderOptions:encoderOptions] autorelease];
  processor.skipEveryIFrameInterval = 1;
  processor.smoothFrameInterval = 2;
  processor.smoothFrameRepeat = 2;  
   */

  id<FFProcessor> processor = [[[FFEncodeProcessor alloc] initWithEncoderOptions:encoderOptions] autorelease];
  
  /*!
  id<FFFilter> filter = [[FFFilters alloc] initWithFilters:[NSArray arrayWithObjects:
                                                            [[(FFMPConverter *)[FFMPConverter alloc] initWithFormat:FFVFormatMake(0, 0, kFFPixelFormatType_32BGRA)] autorelease],
                                                            //[[[FFCanny alloc] init] autorelease],
                                                            [[(FFMPConverter *)[FFMPConverter alloc] initWithFormat:FFVFormatMake(0, 0, kFFPixelFormatType_YUV420P)] autorelease],
                                                            nil]];
   */
  
  [outputPath retain];
  [_outputPath release];
  _outputPath = outputPath;
  
  //id<FFDecoder> decoder = [[FFMPDecoder alloc] init];
  id<FFDecoder> decoder = [[FFAVDecoder alloc] init];
  _processingThread = [[FFProcessingThread alloc] initWithDecoder:decoder processor:processor filter:nil items:items];
  _processingThread.delegate = self;  
  [decoder release];
  
  [_processingThread start];
}

- (void)cancel {
  [_processingThread cancel];
}

- (BOOL)isExecuting {
  return [_processingThread isExecuting];
}

#pragma mark FFProcessingThreadDelegate

- (void)processingThread:(FFProcessingThread *)processingThread didStartIndex:(NSInteger)index count:(NSInteger)count {
  FFDebug(@"Started %d/%d", index, count);
  [_delegate processing:self didStartIndex:index count:count];
}

- (void)processingThread:(FFProcessingThread *)processingThread didReadFramePTS:(int64_t)framePTS duration:(int64_t)duration 
                   index:(NSInteger)index count:(NSInteger)count {
  //FFDebug(@" - (%lld/%lld) (%d/%d)", framePTS, duration, index, count);
  [_delegate processing:self didProgress:((double)framePTS/duration) index:index count:count];
}

- (void)processingThread:(FFProcessingThread *)processingThread didFinishIndex:(NSInteger)index count:(NSInteger)count {
  FFDebug(@"Finished %d/%d", (index + 1), count);
  [_delegate processing:self didFinishIndex:index count:count];
}

- (void)processingThread:(FFProcessingThread *)processingThread didError:(NSError *)error index:(NSInteger)index count:(NSInteger)count {
  FFDebug(@"Error: %@ (%d/%d)", error, index, count);
  [_delegate processing:self didError:error index:index count:count];
}

- (void)processingThreadDidCancel:(FFProcessingThread *)processingThread {
  [_delegate processingDidCancel:self];
}

@end
