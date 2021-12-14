#! /bin/bash
./elfloader test5 22 30
if [ $? -ne 2 ]
then
    echo "Wrong error code"
    exit 1
else
    echo "==> Correct error code"
    exit 0
fi
