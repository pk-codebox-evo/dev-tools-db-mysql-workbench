/*
 * Copyright (c) 2008, 2017, Oracle and/or its affiliates. All rights reserved.
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
#ifndef _STUB_POPUP_H_
#define _STUB_POPUP_H_

#include "stub_view.h"

namespace mforms {
  namespace stub {

    class PopupImpl : public ViewWrapper {
    protected:
      PopupImpl(::mforms::WebBrowser *self) : ViewWrapper(self) {
      }

      static bool create(Popup *, PopupStyle) {
        return true;
      }

      static void set_needs_repaint(Popup *) {
      }

      static void set_size(Popup *, int, int) {
      }

      static int show(Popup *, int, int) {
        return 0;
      }

      static base::Rect get_content_rect(Popup *) {
        base::Rect ret_val;

        return ret_val;
      }

      static void set_modal_result(Popup *, int result) {
      }

    public:
      static void init() {
        ::mforms::ControlFactory *f = ::mforms::ControlFactory::get_instance();

        f->_popup_impl.create = &PopupImpl::create;
        f->_popup_impl.get_content_rect = &PopupImpl::get_content_rect;
        f->_popup_impl.set_modal_result = &PopupImpl::set_modal_result;
        f->_popup_impl.set_needs_repaint = &PopupImpl::set_needs_repaint;
        f->_popup_impl.set_size = &PopupImpl::set_size;
        f->_popup_impl.show = &PopupImpl::show;
      }
    };
  }
}

#endif
