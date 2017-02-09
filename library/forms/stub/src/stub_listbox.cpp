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

#include "../stub_listbox.h"

using namespace mforms;
using namespace mforms::stub;

//--------------------------------------------------------------------------------------------------

ListBoxWrapper::ListBoxWrapper(mforms::ListBox *self, bool multi_select) : ViewWrapper(self) {
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::selection_changed(mforms::ListBox *self) {
}

//--------------------------------------------------------------------------------------------------

bool ListBoxWrapper::create(mforms::ListBox *self, bool multi_select) {
  return true;
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::clear(mforms::ListBox *self) {
}

//--------------------------------------------------------------------------------------------------

size_t ListBoxWrapper::add_item(mforms::ListBox *self, const std::string &item) {
  return 0;
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::add_items(mforms::ListBox *self, const std::list<std::string> &items) {
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::remove_index(mforms::ListBox *self, size_t index) {
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::remove_indexes(mforms::ListBox *self, const std::vector<size_t> &items) {
}

//--------------------------------------------------------------------------------------------------

std::string ListBoxWrapper::get_text(mforms::ListBox *self) {
  return "";
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::set_index(mforms::ListBox *self, ssize_t index) {
}

//--------------------------------------------------------------------------------------------------

ssize_t ListBoxWrapper::get_index(mforms::ListBox *self) {
  return -1;
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::set_heading(ListBox *self, const std::string &text) {
}

//--------------------------------------------------------------------------------------------------

std::vector<size_t> ListBoxWrapper::get_selected_indices(ListBox *self) {
  std::vector<size_t> res;
  return res;
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::init() {
  mforms::ControlFactory *f = mforms::ControlFactory::get_instance();

  f->_listbox_impl.create = &ListBoxWrapper::create;
  f->_listbox_impl.clear = &ListBoxWrapper::clear;
  f->_listbox_impl.add_item = &ListBoxWrapper::add_item;
  f->_listbox_impl.add_items = &ListBoxWrapper::add_items;
  f->_listbox_impl.remove_index = &ListBoxWrapper::remove_index;
  f->_listbox_impl.remove_indexes = &ListBoxWrapper::remove_indexes;
  f->_listbox_impl.set_index = &ListBoxWrapper::set_index;
  f->_listbox_impl.get_index = &ListBoxWrapper::get_index;
  f->_listbox_impl.get_selected_indices = &ListBoxWrapper::get_selected_indices;
  f->_listbox_impl.get_text = &ListBoxWrapper::get_text;
  f->_listbox_impl.set_heading = &ListBoxWrapper::set_heading;
}

//--------------------------------------------------------------------------------------------------
