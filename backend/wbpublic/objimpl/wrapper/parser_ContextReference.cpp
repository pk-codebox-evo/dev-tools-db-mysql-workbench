/*
 * Copyright (c) 2014, 2017, Oracle and/or its affiliates. All rights reserved.
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

#include "grts/structs.wrapper.h"

#include "parser_ContextReference_impl.h"

using namespace parser;

//--------------------------------------------------------------------------------------------------

class parser_ContextReference::ImplData {
public:
  parser::MySQLParserContext::Ref _ref;
  ImplData(const MySQLParserContext::Ref &ref) {
    _ref = ref;
  }
};

//--------------------------------------------------------------------------------------------------

parser_ContextReference::~parser_ContextReference() {
  delete _data;
}

//--------------------------------------------------------------------------------------------------

void parser_ContextReference::init() {
  // Nothing to do. Use the reference only via parser_context_to_grt().
}

//--------------------------------------------------------------------------------------------------

grt::IntegerRef parser_ContextReference::valid() const {
  if (_data)
    return grt::IntegerRef(1);
  else
    return grt::IntegerRef(0);
}

//--------------------------------------------------------------------------------------------------

void parser_ContextReference::set_data(ImplData *data) {
  _data = data;
}

//--------------------------------------------------------------------------------------------------

MySQLParserContext::Ref parser_context_from_grt(parser_ContextReferenceRef object) {
  if (!object.is_valid() || !*object->valid())
    return MySQLParserContext::Ref();
  return object->get_data()->_ref;
}

//--------------------------------------------------------------------------------------------------

parser_ContextReferenceRef parser_context_to_grt(const MySQLParserContext::Ref &context) {
  if (context != NULL) {
    parser_ContextReferenceRef ref(grt::Initialized);
    parser_ContextReference::ImplData *data = new parser_ContextReference::ImplData(context);
    ref->set_data(data);
    return ref;
  }
  return parser_ContextReferenceRef();
}

//--------------------------------------------------------------------------------------------------
