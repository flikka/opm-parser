cppcheck -v --enable=all --xml ../opm -I ../opm 2>../build/cppcheck-report.xml
bash -c 'find ../opm -regex ".*\.cpp\|.*\.hpp" | vera++ -s -c ../build/vera-report.xml'
valgrind --xml=yes --xml-file=../build/valgrind-report.xml ../build/bin/runParserTests
