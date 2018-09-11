
#ifndef EXTERNAL_MERGE_ELEMENT_SORTER_H
#define EXTERNAL_MERGE_ELEMENT_SORTER_H

// Hoot
#include <hoot/core/io/ElementInputStream.h>
#include <hoot/core/io/PartialOsmMapReader.h>
#include <hoot/core/io/PartialOsmMapWriter.h>

// Qt
#include <QTemporaryFile>

// std
#include <queue>

namespace hoot
{

struct ElementComparePQ
{
  //The priority queue expects the reverse sorting priority that we use with vector sorting.
  bool operator()(const ConstElementPtr& e1, const ConstElementPtr& e2) const
  {
    const ElementType::Type type1 = e1->getElementType().getEnum();
    const ElementType::Type type2 = e2->getElementType().getEnum();
    if (type1 == type2)
    {
      return e1->getId() > e2->getId();
    }
    else
    {
      return type1 > type2;
    }
  }
};

typedef std::priority_queue<ConstElementPtr,
                            std::vector<ConstElementPtr>, ElementComparePQ> ElementPriorityQueue;

/**
  This performs element sorting outside of main memory on disk.

  Very much influenced by http://www.techiedelight.com/external-merge-sort
 */
class ExternalMergeElementSorter : public ElementInputStream
{

public:

  ExternalMergeElementSorter();
  virtual ~ExternalMergeElementSorter();

  /**
   * Sorts elements first by type, then increasing by ID
   *
   * @param input a stream of elements
   */
  void sort(ElementInputStreamPtr input);

  /**
   * @see ElementInputStream
   */
  virtual boost::shared_ptr<OGRSpatialReference> getProjection() const;

  /**
   * @see ElementInputStream
   */
  virtual void close();

  /**
   * @see ElementInputStream
   */
  virtual bool hasMoreElements();

  /**
   * @see ElementInputStream
   */
  virtual ElementPtr readNextElement();

  void setMaxElementsPerFile(long max) { _maxElementsPerFile = max; }
  void setTempFormat(QString format) { _tempFormat = format; }
  void setRetainTempFiles(bool retain) { _retainTempFiles = retain; }

  int getNumTempFiles() const { return _tempOutputFiles.size(); }

private:

  static const QString SORT_TEMP_FILE_BASE_NAME;

  //the final merged sorted element output
  boost::shared_ptr<QTemporaryFile> _sortFinalOutput;

  //a stream of sorted elements to serve
  ElementInputStreamPtr _sortedElements;

  //what formats to write the temp files to
  QString _tempFormat;

  long _maxElementsPerFile;

  bool _retainTempFiles;

  //pre-merge temp files; auto-deleted on exit
  QList<boost::shared_ptr<QTemporaryFile>> _tempOutputFiles;

  void _sort(ElementInputStreamPtr input);

  /*
   * Writes a set of OSM files filled with sorted elements; the number of files is the total
   * elements read form the source divided by the element buffer size
   */
  void _createSortedFileOutputs(ElementInputStreamPtr input);

  /*
   * Merges each sorted temp file into a final sorted file
   */
  void _mergeSortedFiles();

  /*
   * Prepares the element stream that serves up the sorted elements
   */
  void _initElementStream();

  /*
   * Order by element type (node, way, relation), then by increasing ID
   */
  static bool _elementCompare(const ConstElementPtr& e1, const ConstElementPtr& e2);

  ElementPriorityQueue _getInitializedPriorityQueue(
    QList<boost::shared_ptr<PartialOsmMapReader>>& readers);

  void _mergeSortedElements(ElementPriorityQueue& priorityQueue,
                            boost::shared_ptr<PartialOsmMapWriter> writer,
                            QList<boost::shared_ptr<PartialOsmMapReader>> readers);

  boost::shared_ptr<PartialOsmMapWriter> _getFinalOutputWriter();
};

}

#endif // EXTERNAL_MERGE_ELEMENT_SORTER_H
