/*
 * Copyright (c) 2010, 2017, Oracle and/or its affiliates. All rights reserved.
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

#ifndef _DB_QUERY_EDITABLERESULTSET_H_
#define _DB_QUERY_EDITABLERESULTSET_H_

#include <grts/structs.db.query.h>
#include "sqlide/recordset_be.h"

#include "wbpublic_public_interface.h"

db_query_EditableResultsetRef WBPUBLICBACKEND_PUBLIC_FUNC grtwrap_editablerecordset(GrtObjectRef owner,
                                                                                    Recordset::Ref rset);

#endif
