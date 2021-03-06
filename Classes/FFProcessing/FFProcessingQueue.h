//
//  FFProcessingQueue.h
//  FFProcessing
//
//  Created by Gabriel Handford on 4/15/10.
//  Copyright 2010. All rights reserved.
//

#import "FFProcessing.h"
#import "FFDecoder.h"

@class FFProcessingItem;
@class FFProcessingQueue;

@protocol FFProcessingQueueDelegate <NSObject>
- (void)processingQueue:(FFProcessingQueue *)processingQueue didStartIndex:(NSInteger)index count:(NSInteger)count;
- (void)processingQueue:(FFProcessingQueue *)processingQueue didReadFramePTS:(int64_t)framePTS duration:(int64_t)duration 
             index:(NSInteger)index count:(NSInteger)count;
- (void)processingQueue:(FFProcessingQueue *)processingQueue didFinishIndex:(NSInteger)index count:(NSInteger)count;
- (void)processingQueue:(FFProcessingQueue *)processingQueue didError:(NSError *)error index:(NSInteger)index count:(NSInteger)count;
- (void)processingQueueDidCancel:(FFProcessingQueue *)processingQueue;
@end


@interface FFProcessingQueue : NSObject <FFProcessingDelegate> {
  
  FFProcessing *_processing;
  NSMutableArray *_items;
  NSInteger _index;
  
  id<FFDecoder> _decoder;
  id<FFProcessor> _processor;
  id<FFFilter> _filter;
  
  id<FFProcessingQueueDelegate> _delegate;
}

@property (assign, nonatomic) id<FFProcessingQueueDelegate> delegate;

- (id)initWithDecoder:(id<FFDecoder>)decoder processor:(id<FFProcessor>)processor filter:(id<FFFilter>)filter;

- (void)close;

- (void)cancel;

- (void)addItem:(FFProcessingItem *)item;

- (void)addItems:(NSArray */*of FFProcessingItem*/)items;

- (BOOL)hasNext;

- (BOOL)processNext;

@end

@interface FFProcessingItem : NSObject {
  NSURL *_URL;
  NSString *_format;
}

@property (readonly, nonatomic) NSURL *URL;
@property (readonly, nonatomic) NSString *format;

- (id)initWithURL:(NSURL *)URL format:(NSString *)format;

@end