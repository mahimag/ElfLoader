#! /bin/bash
./elfloader test4 22 30
if [ $? -ne 3 ]
then
    echo "Wrong error code was returned"
    exit 1
else
    echo "==> Correct error code was returned"
    exit 0
fi
