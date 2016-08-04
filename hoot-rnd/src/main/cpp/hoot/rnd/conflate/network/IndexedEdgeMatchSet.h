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
 * @copyright Copyright (C) 2016 DigitalGlobe (http://www.digitalglobe.com/)
 */
#ifndef __INDEXED_EDGE_MATCH_SET_H__
#define __INDEXED_EDGE_MATCH_SET_H__

#include "EdgeMatchSet.h"
#include "IndexedEdgeLinks.h"

namespace hoot
{

/**
 * Contains an indexed set of EdgeMatches. This allows efficient retrieval of specific matches based
 * on various criteria.
 */
class IndexedEdgeMatchSet : public EdgeMatchSet
{
public:
  typedef QHash<ConstEdgeMatchPtr, double> MatchHash;

  IndexedEdgeMatchSet();
  
  /**
   * The edge match should not be modified after it has been added to the index.
   */
  void addEdgeMatch(const ConstEdgeMatchPtr& em, double score);

  shared_ptr<IndexedEdgeLinks> calculateEdgeLinks();

  shared_ptr<IndexedEdgeMatchSet> clone() const;

  /**
   * Returns true if the specified element (or the reversed equivalent) is contained in this set.
   */
  virtual bool contains(const ConstEdgeMatchPtr &em) const;

  const MatchHash& getAllMatches() const { return _matches; }
  MatchHash& getAllMatches() { return _matches; }

  QSet<ConstEdgeMatchPtr> getMatchesThatContain(ConstNetworkEdgePtr e) const;

  /**
   * Return all matches that overlap with e. This may include e.
   */
  QSet<ConstEdgeMatchPtr> getMatchesThatOverlap(ConstEdgeMatchPtr e) const;

  /**
   * Return all matches that overlap with str.
   */
  QSet<ConstEdgeMatchPtr> getMatchesThatOverlap(ConstEdgeStringPtr str) const;

  /**
   * Return all the edges that either start at v1/v2 or end at v1/v2.
   */
  QSet<ConstEdgeMatchPtr> getMatchesWithTermination(ConstNetworkVertexPtr v1, ConstNetworkVertexPtr v2)
    const;

  /**
   * This is handy if you want to de-duplicate edge matches. The equivalent stored pointer will be
   * returned if it exists.
   *
   * An exception is thrown if the match doesn't exist.
   */
  ConstEdgeMatchPtr getMatch(const ConstEdgeMatchPtr &em) const;

  /**
   * Return the score associated with an edge match.
   */
  double getScore(ConstEdgeMatchPtr em) const { return _matches[em]; }

  int getSize() const { return _matches.size(); }

  void setScore(ConstEdgeMatchPtr em, double score) { _matches[em] = score; }

  virtual QString toString() const;

private:
  typedef QHash<ConstNetworkEdgePtr, QSet<ConstEdgeMatchPtr> > EdgeToMatchMap;

  EdgeToMatchMap _edgeToMatch;
  MatchHash _matches;

  void _addEdgeToMatchMapping(ConstEdgeStringPtr str, const ConstEdgeMatchPtr &em);
};

typedef shared_ptr<IndexedEdgeMatchSet> IndexedEdgeMatchSetPtr;
typedef shared_ptr<const IndexedEdgeMatchSet> ConstIndexedEdgeMatchSetPtr;

// not implemented
bool operator<(ConstIndexedEdgeMatchSetPtr, ConstIndexedEdgeMatchSetPtr);

}

#endif // __EDGE_MATCH_SET_INDEX_H__
