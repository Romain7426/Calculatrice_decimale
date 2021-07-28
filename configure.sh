#! /bin/sh


if which gmake > /dev/null ; then 
 gmake -r -R -S -j 1 --warn-undefined-variables -f ./Makefile-gen.mkf 
 exit $? 
fi; 

if which make ; then 
  make -r -R -S -j 1 --warn-undefined-variables -f ./Makefile-gen.mkf 
  exit $? 
fi; 


echo "I could not find GNU Make" 






exit 1; 


which gmake && (gmake -r -R -S -j 1 --warn-undefined-variables -f ./Makefile-gen.mkf ;  exit $? ) 

which make && (make -r -R -S -j 1 --warn-undefined-variables -f ./Makefile-gen.mkf ;  exit $? ) 

echo "I cannot find GNU Make" 



