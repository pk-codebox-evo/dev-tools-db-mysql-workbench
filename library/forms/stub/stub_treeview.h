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

#pragma once

#include "stub_view.h"
#include "stub_treenode.h"

namespace mforms {
  namespace stub {

    class TreeViewWrapper : public ViewWrapper {
    private:
      TreeNodeWrapper *_root;

      TreeViewWrapper(TreeView *self, mforms::TreeOptions opts) : ViewWrapper(self) {
        _root = new TreeNodeWrapper();
      }

      int add_column(TreeColumnType type, const std::string &name, int initial_width, bool editable) {
        return 0;
      }

      void end_columns() {
      }

      static bool create(TreeView *self, mforms::TreeOptions opt) {
        new TreeViewWrapper(self, opt);
        return true;
      }

      static int add_column(TreeView *self, TreeColumnType type, const std::string &name, int width, bool editable) {
        return 0;
      }

      static int add_column(TreeView *self, TreeColumnType type, const std::string &name, int width, bool editable,
                            bool a) {
        return 0;
      }

      static void end_columns(TreeView *self) {
      }

      static void clear(TreeView *self) {
      }

      static TreeSelectionMode get_selection_mode(TreeView *self) {
        return TreeSelectSingle;
      }

      static void set_selection_mode(TreeView *self, TreeSelectionMode mode) {
      }

      static TreeNodeRef get_selected_node(TreeView *self) {
        return TreeNodeRef();
      }

      static TreeNodeRef root_node(TreeView *tree) {
        TreeViewWrapper *ptree_node_view = dynamic_cast<TreeViewWrapper *>(ObjectWrapper::getData(tree));
        return ptree_node_view->root_node();
      }

      TreeNodeRef root_node() {
        return mforms::TreeNodeRef(_root);
      }

      static std::list<TreeNodeRef> get_selection(TreeView *self) {
        return std::list<TreeNodeRef>();
      }

      static void set_selected(TreeView *self, TreeNodeRef node, bool flag) {
      }

      static void set_allow_sorting(TreeView *self, bool) {
      }

      static void freeze_refresh(TreeView *self, bool) {
      }

      static int row_for_node(TreeView *self, TreeNodeRef node) {
        return 0;
      }

      static TreeNodeRef node_at_row(TreeView *self, int row) {
        return self->root_node();
      }

      static void set_row_height(TreeView *self, int height) {
      }

      static void clear_selection(TreeView *self) {
      }

      static TreeNodeRef node_with_tag(TreeView *self, const std::string &tag) {
        return TreeNodeRef();
      }

    public:
      static void init() {
        ::mforms::ControlFactory *f = ::mforms::ControlFactory::get_instance();

        f->_treeview_impl.create = &TreeViewWrapper::create;
        f->_treeview_impl.add_column = &TreeViewWrapper::add_column;
        f->_treeview_impl.end_columns = &TreeViewWrapper::end_columns;
        f->_treeview_impl.clear = &TreeViewWrapper::clear;
        f->_treeview_impl.get_selected_node = &TreeViewWrapper::get_selected_node;
        f->_treeview_impl.set_selected = &TreeViewWrapper::set_selected;
        f->_treeview_impl.get_selection = &TreeViewWrapper::get_selection;
        f->_treeview_impl.set_allow_sorting = &TreeViewWrapper::set_allow_sorting;
        f->_treeview_impl.freeze_refresh = &TreeViewWrapper::freeze_refresh;
        f->_treeview_impl.set_selection_mode = &TreeViewWrapper::set_selection_mode;
        f->_treeview_impl.get_selection_mode = &TreeViewWrapper::get_selection_mode;
        f->_treeview_impl.root_node = &TreeViewWrapper::root_node;
        f->_treeview_impl.node_at_row = &TreeViewWrapper::node_at_row;
        f->_treeview_impl.row_for_node = &TreeViewWrapper::row_for_node;
        f->_treeview_impl.set_row_height = &TreeViewWrapper::set_row_height;
        f->_treeview_impl.clear_selection = &TreeViewWrapper::clear_selection;
        f->_treeview_impl.node_with_tag = &TreeViewWrapper::node_with_tag;
      }
    };
  }
}
