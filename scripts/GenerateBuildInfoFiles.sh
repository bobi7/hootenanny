#!/bin/bash

HOOT_VERSION=`cat ../HOOT_VERSION_FILE | grep "HOOT_VERSION" | awk '{print $3;}'`
#echo "HOOT_VERSION: " $HOOT_VERSION
#echo "USER: " $USER

SERVICES_BUILD_INFO_FILE=./src/main/resources/build.info
echo "name=Hootenanny Web Services" > $SERVICES_BUILD_INFO_FILE
echo "version="$HOOT_VERSION >> $SERVICES_BUILD_INFO_FILE
echo "user="$USER >> $SERVICES_BUILD_INFO_FILE

# assume that if we're building services, we're also building iD, since iD doesn't have its
# own makefile
for info_file in ../hoot-ui/data/buildInfo.json ../hoot-ui-2x/modules/Hoot/config/buildInfo.json ../hoot-ui-2x/data/buildInfo.json; do
    echo "{ \"name\": \"Hootenanny iD Editor\", \"version\": \"$HOOT_VERSION\", \"user\": \"$USER\" }" > $info_file
done
