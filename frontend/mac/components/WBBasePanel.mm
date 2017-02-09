/* 
 * Copyright (c) 2008, 2016, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the
 * License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#import "WBBasePanel.h"
#include "mforms/../cocoa/MFMenuBar.h"
#include "mforms/../cocoa/MFToolBar.h"

@interface WBToolBarContainer : NSView
{
}
@end

@implementation WBToolBarContainer

- (void)resizeSubviewsWithOldSize:(NSSize)size
{
  NSView *toolBar = self.subviews[0];
  NSView *content = self.subviews[1];
  if (toolBar && content)
  {
    NSRect r = self.frame;
    NSRect frame = toolBar.frame;
    frame.origin = NSZeroPoint;
    frame.size.width = r.size.width;
    toolBar.frame = frame;
    
    frame.origin.y += NSHeight(frame);
    frame.size.height = r.size.height - NSHeight(frame);
    content.frame = frame;
  }
}

- (BOOL)isFlipped
{
  return YES;
}

@end

@implementation WBBasePanel

@synthesize topView;

- (NSView*)decoratedTopView
{
  bec::UIForm *form = self.formBE;
  mforms::ToolBar *tbar = form->get_toolbar();
  if (form != NULL && tbar != NULL)
  {
    NSView *tbview = nsviewForView(tbar);
    if (tbview)
    {
      if (!decoratorView)
      {
        NSRect r = topView.frame;
        WBToolBarContainer *container = [[WBToolBarContainer alloc] initWithFrame: NSMakeRect(0, 0, NSWidth(r), NSHeight(r) + NSHeight(tbview.frame))];
        decoratorView = container;
        [container addSubview: tbview];
        [topView removeFromSuperview];
        [container addSubview: topView];
        [container resizeSubviewsWithOldSize: NSZeroSize];
      }
      return decoratorView;
    }
  }
  return topView;
}

- (NSMenu*)menuBar
{
  bec::UIForm *form = self.formBE;
  if (form)
  {
    mforms::MenuBar *menubar = form->get_menubar();
    if (menubar)
      return menubar->get_data();
  }
  return nil;
}

- (NSString*)title
{
  bec::UIForm *form = self.formBE;
  if (form)
    return @(form->get_title().c_str());
  return @"";
}

- (NSString*)identifier
{
  return nil;
}

- (bec::UIForm *)formBE
{
  return NULL;
}

- (NSImage*)tabIcon
{
  return nil;
}

- (BOOL)willClose
{
  return YES;
}

- (void)didOpen
{
}

- (void)didActivate
{
}

@end
