cppcheck -v --enable=all --xml opm -I opm 2> build/cppcheck-report.xml
bash -c 'find opm -regex ".*\.cpp\|.*\.hpp" | ~/programs/vera/bin/vera++ -s -c build/vera3.xml'
valgrind --xml=yes --xml-file=build/report.xml build/bin/runParserTests
