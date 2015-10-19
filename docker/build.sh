mkdir -p /code && \
 cd code && \
 git clone https://github.com/Ensembles/ert.git && \
 cd ert && \
 mkdir build && \
 cd build && \
 cmake ../devel && \
 make -j 4

cd /code && git clone https://github.com/OPM/opm-common.git 

cd /code && git clone https://github.com/OPM/opm-parser.git && \
 cd opm-parser && \
 mkdir build && \
 cd build && \
 cmake ../ && \
 make -j 6 

