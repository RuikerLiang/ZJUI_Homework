#!/bin/zsh
echo "test3"
./mp6 Images/maclean-campus-reformatted.png output3.png 3 Images/watermarks.png
diff output3.png Examples/maclean-campus-reformatted-3-watermarks.png