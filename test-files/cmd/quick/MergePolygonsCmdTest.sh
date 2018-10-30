#!/bin/bash
#set -e

#DEBUG_OPT="--trace"

INPUTFILEDIR=$HOOT_HOME/test-files/cmd/quick/MergePolygonsCmdTest
OUTPUTFILEDIR=$HOOT_HOME/test-output/cmd/quick/MergePolygonsCmdTest

mkdir -p $OUTPUTFILEDIR

# Input: 2 x polygons
# Output: 1 x polygon 
INPUTFILE1=$INPUTFILEDIR/square_polygon.osm
INPUTFILE2=$INPUTFILEDIR/diamond_polygon.osm
OUTPUTFILE=$OUTPUTFILEDIR/union_polygon.osm
COMPAREFILE=$INPUTFILEDIR/union_polygon.osm

hoot merge-polygons $DEBUG_OPT $OUTPUTFILE $INPUTFILE1 $INPUTFILE2
hoot diff $COMPAREFILE $OUTPUTFILE || diff $COMPAREFILE $OUTPUTFILE

# Input: 2 x multipolygons
# Output: 1 x polygon 
INPUTFILE1=$INPUTFILEDIR/multi_polygon1.osm
INPUTFILE2=$INPUTFILEDIR/multi_polygon2.osm
OUTPUTFILE=$OUTPUTFILEDIR/union_multi_both.osm
COMPAREFILE=$INPUTFILEDIR/union_multi_both.osm

hoot merge-polygons $DEBUG_OPT $OUTPUTFILE $INPUTFILE1 $INPUTFILE2
hoot diff $COMPAREFILE $OUTPUTFILE || diff $COMPAREFILE $OUTPUTFILE
