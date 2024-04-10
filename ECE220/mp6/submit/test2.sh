#!/bin/zsh
echo "test2"
./mp6 Images/lumetta.png output2.png 2 3 Images/watermarks.png
diff output2.png Examples/lumetta_2_3_watermarks.png
./mp6 Images/tajmahal.png output2.png 2 1 Images/watermarks.png
diff output2.png Examples/tajmahal-2-1-watermarks.png
./mp6 Images/maclean-campus.png output2.png 2 5 Images/watermarks.png
diff output2.png Examples/maclean-campus-2-5-watermarks.png