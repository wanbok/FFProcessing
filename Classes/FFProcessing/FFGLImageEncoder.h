//
//  FFGLImageEncoder.h
//  FFProcessing
//
//  Created by Gabriel Handford on 6/16/10.
//  Copyright 2010. All rights reserved.
//

#import <OpenGLES/ES1/gl.h>

@interface FFGLImageEncoder : NSObject {
  GLubyte *_buffer;
  int _length;
  
  GLsizei _width;
  GLsizei _height;
  GLint _format;
  
  CGColorSpaceRef _colorSpace;
}

- (id)initWithWidth:(GLsizei)width height:(GLsizei)height format:(GLint)format;

- (void)writeToPhotosAlbum;

- (void)GLReadPixels;

- (CGImageRef)createImageFromGL;

@end
