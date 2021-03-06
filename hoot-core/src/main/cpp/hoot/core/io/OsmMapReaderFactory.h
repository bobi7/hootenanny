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
 * @copyright Copyright (C) 2015, 2016, 2017, 2018 DigitalGlobe (http://www.digitalglobe.com/)
 */
#ifndef OSMMAPREADERFACTORY_H
#define OSMMAPREADERFACTORY_H

// Qt
#include <QString>

// tgs
#include <tgs/SharedPtr.h>

// hoot
#include <hoot/core/elements/Status.h>

namespace hoot
{

class OsmMap;
class OsmMapReader;

/**
 * A factory for constructing readers based on the URL (Singleton).
 */
class OsmMapReaderFactory
{

public:

  boost::shared_ptr<OsmMapReader> createReader(QString url, bool useFileId = true,
                                               Status defaultStatus = Status::Invalid);
  //Note the url as the last param here...was getting runtime overlap between these two where
  //bools were being passed as status ints and vice versa.  May need to do some more refactoring
  //here to make things cleaner.
  boost::shared_ptr<OsmMapReader> createReader(bool useFileId, bool useFileStatus, QString url);

  static OsmMapReaderFactory& getInstance();

  /**
   * Returns true if a partial reader is available for the given URL.
   */
  bool hasPartialReader(QString url);

  bool hasElementInputStream(QString url);

  static void read(boost::shared_ptr<OsmMap> map, QString url, bool useFileId = true,
                   Status defaultStatus = Status::Invalid);
  //see note for createReader
  static void read(boost::shared_ptr<OsmMap> map, bool useFileId, bool useFileStatus, QString url);

  static QString getReaderName(const QString url);

  static bool isSupportedFormat(const QString url);

private:

  OsmMapReaderFactory();

  static boost::shared_ptr<OsmMapReaderFactory> _theInstance;

  static void _read(boost::shared_ptr<OsmMap> map, boost::shared_ptr<OsmMapReader> reader,
             const QString url);

  boost::shared_ptr<OsmMapReader> _createReader(const QString url);
};

}

#endif // OSMMAPREADERFACTORY_H
