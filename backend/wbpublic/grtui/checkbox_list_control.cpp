/*
 * Copyright (c) 2007, 2017, Oracle and/or its affiliates. All rights reserved.
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

#include "checkbox_list_control.h"
#include <algorithm>

StringCheckBoxList::StringCheckBoxList() : mforms::ScrollPanel(), _box(false) {
  _box.set_padding(8);
  add(&_box);
}

void StringCheckBoxList::set_strings(const std::vector<std::string> &strings) {
  for (std::vector<mforms::CheckBox *>::const_iterator iter = _items.begin(); iter != _items.end(); ++iter)
    _box.remove(*iter);
  _items.clear();

  for (std::vector<std::string>::const_iterator iter = strings.begin(); iter != strings.end(); ++iter) {
    mforms::CheckBox *cb = mforms::manage(new mforms::CheckBox());
    cb->set_text(*iter);
    cb->set_name(*iter);

    scoped_connect(cb->signal_clicked(), std::bind(&StringCheckBoxList::toggled, this));

    _box.add(cb, false, false);
    _items.push_back(cb);
  }
}

void StringCheckBoxList::set_strings(const grt::StringListRef &strings) {
  for (std::vector<mforms::CheckBox *>::const_iterator iter = _items.begin(); iter != _items.end(); ++iter) {
    _box.remove(*iter);
  }
  _items.clear();

  for (grt::StringListRef::const_iterator iter = strings.begin(); iter != strings.end(); ++iter) {
    mforms::CheckBox *cb = mforms::manage(new mforms::CheckBox());
    cb->set_text(*iter);
    cb->set_name(*iter);

    scoped_connect(cb->signal_clicked(), std::bind(&StringCheckBoxList::toggled, this));

    _box.add(cb, false, false);
    _items.push_back(cb);
  }
}

bool StringCheckBoxList::has_selection() {
  for (std::vector<mforms::CheckBox *>::const_iterator iter = _items.begin(); iter != _items.end(); ++iter) {
    if ((*iter)->get_active())
      return true;
  }
  return false;
}

void StringCheckBoxList::set_selected(const std::string &name, bool flag) {
  for (std::vector<mforms::CheckBox *>::const_iterator iter = _items.begin(); iter != _items.end(); ++iter) {
    if ((*iter)->get_name() == name) {
      (*iter)->set_active(flag);
    }
  }
}

std::vector<std::string> StringCheckBoxList::get_selection() {
  std::vector<std::string> list;

  for (std::vector<mforms::CheckBox *>::const_iterator iter = _items.begin(); iter != _items.end(); ++iter) {
    if ((*iter)->get_active())
      list.push_back((*iter)->get_name());
  }
  return list;
}

void StringCheckBoxList::toggled() {
  _signal_changed();
}
