 #!/bin/sh 
 # Create Sysc Static Libraries Symlink
MACHINE_TYPE=`uname -m`
if [ ${MACHINE_TYPE} == 'x86_64' ]; then
  LDLIBS=/usr/local/systemc-2.3.2/lib-linux6
else
  LDLIBS=/usr/local/systemc-2.3.2/lib-linux
fi

sudo ln -s $LDLIBS/libsystemc-2.3.2.so /usr/lib/libsystemc-2.3.2.so