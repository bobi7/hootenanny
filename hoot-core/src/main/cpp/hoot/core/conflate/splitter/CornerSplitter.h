/*
 * This file is part of Hootenanny.
 *
 * Hootenanny is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * --------------------------------------------------------------------
 *
 * The following copyright notices are generated automatically. If you
 * have a new notice to add, please use the format:
 * " * @copyright Copyright ..."
 * This will properly maintain the copyright information. DigitalGlobe
 * copyrights will be updated automatically.
 *
 * @copyright Copyright (C) 2017 DigitalGlobe (http://www.digitalglobe.com/)
 */

#ifndef CORNERSPLITTER_H
#define CORNERSPLITTER_H

// Hoot
#include <hoot/core/ops/OsmMapOperation.h>

// Qt
#include <QMultiHash>
#include <QSet>
#include <QMap>
#include <vector>

namespace hoot
{

class OsmMap;
class Way;

/**
 * Given an OsmMap, ways are split at sharp corners. This can help when conflating data
 * that is mostly major roads with data that contains a lot of neighborhood - level data.
 *
 */
class CornerSplitter : public OsmMapOperation
{
public:

  static std::string className() { return "hoot::CornerSplitter"; }

  CornerSplitter();

  CornerSplitter(boost::shared_ptr<OsmMap> map);

  void apply(boost::shared_ptr<OsmMap>& map);

  static void splitCorners(boost::shared_ptr<OsmMap> map);

  void splitCorners();

private:
  boost::shared_ptr<OsmMap> _map;
  std::vector<long> _todoWays;

  // Split the way at the given node, using the WaySplitter, then process the results
  void _splitWay(long wayId, long nodeIdx, long nodeId);
};

}

#endif // CORNERSPLITTER_H
