#!/bin/zsh
echo "test1"
./mp6 Images/watermarks.png output1.png 1 0
diff output1.png Examples/watermarks_1_0.png
./mp6 Images/watermarks.png output1.png 1 7
diff output1.png Examples/watermarks_1_7.png