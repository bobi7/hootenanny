#!/bin/bash
set -e

mkdir -p $HOOT_HOME/test-output/cmd/slow/ApplyRubberSheetCmdTest

# First we derive a rubber sheet
hoot derive-rubber-sheet \
  --ref $HOOT_HOME/test-files/DcGisRoads.osm \
        $HOOT_HOME/test-files/DcTigerRoads.osm \
  $HOOT_HOME/test-output/cmd/slow/ApplyRubberSheetCmdTest/DcTigerToDcGis.rs |\
  sed "s/^[0-9]\{2\}:[0-9]\{2\}:[0-9]\{2\}\.[0-9]\{3\} //g" |\
  sed "s/RMSE: [0-9]\+\.[0-9]\+//g"


# Compare to known-good
goodfile=$HOOT_HOME/hoot-core-test/src/test/resources/cmd/slow/ApplyRubberSheetCmdTest/DcTigerToDcGis.rs
testfile=$HOOT_HOME/test-output/cmd/slow/ApplyRubberSheetCmdTest/DcTigerToDcGis.rs
cmp $goodfile $testfile
if [ "$?" = "1" ]; then
  echo "Rubber Sheet files are not equal! Try cmp -l $goodfile $testfile"
  exit 1
fi

# Now we apply the rubber sheet
hoot apply-rubber-sheet \
  $HOOT_HOME/test-output/cmd/slow/ApplyRubberSheetCmdTest/DcTigerToDcGis.rs \
  $HOOT_HOME/test-files/DcTigerRoads.osm \
  $HOOT_HOME/test-output/cmd/slow/ApplyRubberSheetCmdTest/DcTigerToDcGis.osm |\
  sed "s/^[0-9]\{2\}:[0-9]\{2\}:[0-9]\{2\}\.[0-9]\{3\} //g" |\
  sed "s/RMSE: [0-9]\+\.[0-9]\+//g"

goodfile=$HOOT_HOME/hoot-core-test/src/test/resources/cmd/slow/ApplyRubberSheetCmdTest/DcTigerToDcGis.osm
testfile=$HOOT_HOME/test-output/cmd/slow/ApplyRubberSheetCmdTest/DcTigerToDcGis.osm
hoot is-match $goodfile $testfile || diff $goodfile $testfile