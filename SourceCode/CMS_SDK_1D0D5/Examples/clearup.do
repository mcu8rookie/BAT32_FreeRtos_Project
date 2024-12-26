#!/usr/bin/sh 

find -name "Objects"  | xargs rm -rf
#find -name "RTE"  | xargs rm -rf
find -name "Listings" | xargs rm -rf
find -name "*.uvguix.LiuYJ" | xargs rm -rf
find -name "*.uvguix.cliff" | xargs rm -rf
find -name "*.uvguix.wangjh" | xargs rm -rf
find -name "JLinkLog.txt" | xargs rm -rf 
find -name "EventRecorderStub.scvd" | xargs rm -rf 
