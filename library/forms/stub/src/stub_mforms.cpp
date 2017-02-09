/*
 * Copyright (c) 2009, 2017, Oracle and/or its affiliates. All rights reserved.
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

#include "workbench/wb_context.h"

#include "../stub_app.h"
#include "../stub_button.h"
#include "../stub_radiobutton.h"
#include "../stub_mforms.h"
#include "../stub_checkbox.h"
#include "../stub_textentry.h"
#include "../stub_textbox.h"
#include "../stub_imagebox.h"
#include "../stub_label.h"
#include "../stub_selector.h"
#include "../stub_listbox.h"
#include "../stub_tabview.h"
#include "../stub_form.h"
#include "../stub_panel.h"
#include "../stub_box.h"
#include "../stub_table.h"
#include "../stub_progressbar.h"
#include "../stub_filechooser.h"
#include "../stub_scrollpanel.h"
#include "../stub_wizard.h"
#include "../stub_utilities.h"
#include "../stub_drawbox.h"
#include "../stub_menu.h"
#include "../stub_menuitem.h"
#include "../stub_splitter.h"
#include "../stub_treeview.h"
#include "../stub_codeeditor.h"
#include "../stub_toolbar.h"
#include "mforms/dockingpoint.h"

class DockingPointDelegate : public mforms::DockingPointDelegate {
  virtual std::string get_type() {
    return "MainWindow";
  }
  virtual void dock_view(mforms::AppView *view, const std::string &arg1, int arg2) {
  }
  virtual bool select_view(mforms::AppView *view) {
    return false;
  }
  virtual void undock_view(mforms::AppView *view) {
  }
  virtual void set_view_title(mforms::AppView *view, const std::string &title) {
  }
  virtual std::pair<int, int> get_size() {
    return std::make_pair(0, 0);
  }

  virtual mforms::AppView *selected_view() {
    return NULL;
  }
  virtual int view_count() {
    return 0;
  }
  virtual mforms::AppView *view_at_index(int index) {
    return NULL;
  }
};

DockingPointDelegate deleg;

std::function<void(std::string)> mforms::stub::UtilitiesWrapper::open_url_slot;

void ::mforms::stub::init(wb::WBOptions *options) {
  App::instantiate(&deleg, false);
  AppWrapper::init(options);
  ViewWrapper::init();
  BoxWrapper::init();
  FormWrapper::init();
  ButtonWrapper::init();
  RadioButtonWrapper::init();
  CheckBoxWrapper::init();
  TextEntryWrapper::init();
  TextBoxWrapper::init();
  LabelWrapper::init();
  ImageBoxWrapper::init();
  SelectorWrapper::init();
  ListBoxWrapper::init();
  PanelWrapper::init();
  TabViewWrapper::init();
  FileChooserWrapper::init();
  ProgressBarWrapper::init();
  TableWrapper::init();
  ScrollPanelWrapper::init();
  WizardWrapper::init();
  UtilitiesWrapper::init();
  DrawBoxWrapper::init();
  SplitterWrapper::init();
  MenuWrapper::init();
  MenuItemWrapper::init();
  CodeEditorWrapper::init();
  ToolBarWrapper::init();
  TreeViewWrapper::init();

  if (getenv("VERBOSE"))
    puts("done setting up mforms stubs...");
}

void ::mforms::stub::check() {
  mforms::ControlFactory *f = mforms::ControlFactory::get_instance();
  f->check_impl();
}
