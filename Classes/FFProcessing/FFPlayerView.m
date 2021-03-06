//
//  FFProcessingView.m
//
//  Created by Gabriel Handford on 3/10/10.
//  Copyright 2010. All rights reserved.
//

#import "FFPlayerView.h"
#import "FFUtils.h"

#import "FFReader.h"
#import "FFGLDrawable.h"

//#import "FFGLTestDrawable.h"

@implementation FFPlayerView

@synthesize delegate=_delegate;

- (id)initWithFrame:(CGRect)frame {
  if ((self = [super initWithFrame:frame])) {
    
    // FFGLTestDrawable *drawable = [[FFGLTestDrawable alloc] init];

    /*!
    _displayLabel = [[UILabel alloc] initWithFrame:CGRectMake(-145, 240, 320, 30)];
    _displayLabel.textColor = [UIColor whiteColor];
    _displayLabel.backgroundColor = [UIColor blackColor];
    _displayLabel.font = [UIFont fontWithName:@"Helvetica" size:14];
    _displayLabel.transform = CGAffineTransformMakeRotation(M_PI/2);
    [self addSubview:_displayLabel];
     */
  }
  return self;
}

- (void)dealloc {
  [_displayLabel release];
  [super dealloc];
}

- (void)_onDisplay:(NSNotification *)notification {
  NSString *text = [notification object];
  FFDebug(@"%@", text);
  _displayLabel.hidden = NO;
  _displayLabel.text = text;
}

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event {
  return self;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {  
  [super touchesBegan:touches withEvent:event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
  [super touchesMoved:touches withEvent:event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
  [super touchesEnded:touches withEvent:event];
  FFDebug(@"Touches ended");
  [_delegate playerViewDidTouch:self];
}


@end
