/*
 * Copyright (c) 2008, 2017, Oracle and/or its affiliates. All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include "linux_utilities/plugin_editor_base.h"
#include "../backend/mysql_view_editor.h"
#include "grtdb/db_object_helpers.h"
#include "treemodel_wrapper.h"
#include "mysql_editor_priv_page.h"
#include "gtk/mforms_gtk.h"

//==============================================================================
//
//==============================================================================
class DbMySQLViewEditor : public PluginEditorBase {
  MySQLViewEditorBE *_be;
  DbMySQLEditorPrivPage *_privs_page;

  virtual bec::BaseEditor *get_be();

public:
  DbMySQLViewEditor(grt::Module *m, const grt::BaseListRef &args);

  virtual ~DbMySQLViewEditor();
  virtual void do_refresh_form_data();

  virtual bool switch_edited_object(const grt::BaseListRef &args);

  bool comment_lost_focus(GdkEventFocus *ev, Gtk::TextView *view);

private:
  virtual bool can_close() {
    return _be->can_close();
  }
};

DbMySQLViewEditor::DbMySQLViewEditor(grt::Module *m, const grt::BaseListRef &args)
  : PluginEditorBase(m, args, "modules/data/editor_view.glade"),
    _be(new MySQLViewEditorBE(db_mysql_ViewRef::cast_from(args[0]))) {
  xml()->get_widget("mysql_view_editor_notebook", _editor_notebook);

  Gtk::Image *image;
  xml()->get_widget("view_editor_image", image);
  image->set(ImageCache::get_instance()->image_from_filename("db.View.editor.48x48.png", false));
  xml()->get_widget("view_editor_image2", image);
  image->set(ImageCache::get_instance()->image_from_filename("db.View.editor.48x48.png", false));

  _be->set_refresh_ui_slot(std::bind(&DbMySQLViewEditor::refresh_form_data, this));

  _editor_notebook->reparent(*this);
  _editor_notebook->show();

  Gtk::Box *ddl_win;
  xml()->get_widget("editor_placeholder", ddl_win);
  embed_code_editor(_be->get_sql_editor()->get_container(), ddl_win);
  _be->load_view_sql();

  if (!is_editing_live_object()) {
    _privs_page = new DbMySQLEditorPrivPage(_be);
    _editor_notebook->append_page(_privs_page->page(), "Privileges");

    Gtk::TextView *tview(0);
    xml()->get_widget("viewcomment", tview);
    tview->get_buffer()->set_text(_be->get_comment());

    tview->signal_focus_out_event().connect(
      sigc::bind(sigc::mem_fun(this, &DbMySQLViewEditor::comment_lost_focus), tview), false);
  } else {
    _editor_notebook->remove_page(1);
    _privs_page = NULL;
  }

  refresh_form_data();

  _be->reset_editor_undo_stack();

  show_all();
}

//------------------------------------------------------------------------------
DbMySQLViewEditor::~DbMySQLViewEditor() {
  delete _privs_page;

  delete _be;
}

//------------------------------------------------------------------------------
bool DbMySQLViewEditor::switch_edited_object(const grt::BaseListRef &args) {
  MySQLViewEditorBE *old_be = _be;
  Gtk::Box *ddl_win;
  xml()->get_widget("editor_placeholder", ddl_win);

  _be = new MySQLViewEditorBE(db_mysql_ViewRef::cast_from(args[0]));
  embed_code_editor(_be->get_sql_editor()->get_container(), ddl_win);
  _be->load_view_sql();

  if (!is_editing_live_object())
    _privs_page->switch_be(_be);

  _be->set_refresh_ui_slot(std::bind(&DbMySQLViewEditor::refresh_form_data, this));

  do_refresh_form_data();

  delete old_be;
  old_be = 0;

  return true;
}

//------------------------------------------------------------------------------

bool DbMySQLViewEditor::comment_lost_focus(GdkEventFocus *ev, Gtk::TextView *view) {
  if (_be) {
    _be->set_comment(view->get_buffer()->get_text());
  }
  return false;
}

//------------------------------------------------------------------------------
bec::BaseEditor *DbMySQLViewEditor::get_be() {
  return _be;
}

//------------------------------------------------------------------------------
void DbMySQLViewEditor::do_refresh_form_data() {
  Gtk::Entry *entry(0);
  xml()->get_widget("view_name", entry);
  if (entry->get_text() != _be->get_name()) {
    entry->set_text(_be->get_name());
    _signal_title_changed.emit(_be->get_title());
  }

  if (!_be->is_editing_live_object()) {
    Gtk::TextView *tview(0);
    xml()->get_widget("viewcomment", tview);
    tview->get_buffer()->set_text(_be->get_comment());
  }
  //_sql_editor.set_text(_be->get_query());

  _be->load_view_sql();

  if (!is_editing_live_object())
    _privs_page->refresh();
}

//------------------------------------------------------------------------------
extern "C" {
GUIPluginBase *createDbMysqlViewEditor(grt::Module *m, const grt::BaseListRef &args) {
  return Gtk::manage(new DbMySQLViewEditor(m, args));
}
};
