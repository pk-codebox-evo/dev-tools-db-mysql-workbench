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

#ifndef _GEOM_DRAW_BOX_H_
#define _GEOM_DRAW_BOX_H_

#include <mforms/drawbox.h>
#include <gdal/ogr_geometry.h>
#include "wbpublic_public_interface.h"

class WBPUBLICBACKEND_PUBLIC_FUNC GeomDrawBox : public mforms::DrawBox {
  OGRGeometry *_geom;
  int _srid;

public:
  GeomDrawBox() : _geom(NULL), _srid(0) {
  }

  void draw_ring(cairo_t *cr, OGRRawPoint *points, int num_points, double scale, double x, double y, double height);

  void draw_ring_vertices(cairo_t *cr, OGRRawPoint *points, int num_points, double scale, double x, double y,
                          double height);

  void draw_geometry(cairo_t *cr, OGRGeometry *geom, double scale, double x, double y, double height);

  void draw_polygon(cairo_t *cr, OGRPolygon *poly, double scale, double x, double y, double height);
  void set_data(const std::string &text);

  virtual void repaint(cairo_t *cr, int x, int y, int w, int h);

  int getSrid() const;
};

#endif
