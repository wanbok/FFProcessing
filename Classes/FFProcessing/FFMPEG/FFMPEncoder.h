//
//  FFMPEncoder.h
//  FFProcessing
//
//  Created by Gabriel Handford on 3/24/10.
//  Copyright 2010. All rights reserved.
//

#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"

#import "FFEncoder.h"
#import "FFEncoderOptions.h"

@interface FFMPEncoder : NSObject <FFEncoder> {

  AVFormatContext *_formatContext;
  AVStream *_videoStream;
  AVStream *_audioStream;
  
  FFEncoderOptions *_options;
  
  uint8_t *_videoBuffer;
  int _videoBufferSize;
  int _frameBytesEncoded;
  
  int64_t _currentPTS;
  
  AVFrame *_avFrame;
  
}

- (id)initWithOptions:(FFEncoderOptions *)options;

- (int)encodeFrame:(FFVFrameRef)frame error:(NSError **)error;

/*!
 Encode frame to video buffer.
 */
- (int)encodeAVFrame:(AVFrame *)picture error:(NSError **)error;

/*!
 Write current video buffer.
 */
- (BOOL)writeVideoBuffer:(NSError **)error;

- (BOOL)writeVideoFrame:(AVFrame *)picture error:(NSError **)error;

@end
