cd test/;
echo "Tests :";
ls | grep -v --invert-match -E "*.h|*.c|*.coff|*.o|*.S|*.txt|Makefile" > list;
cat list;
echo " ";
cd ..;

make;

cd userprog;
for str in $(cat ../test/list);do 
echo "Testing " $str;
./nachos -rs 1234 -x ../test/$str > /dev/null || exit 1;
echo "done";
echo "";
done;
echo "All test clear.";
cd ..;
cd ..;
