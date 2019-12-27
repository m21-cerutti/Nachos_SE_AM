cd test/;
echo "Tests :";
ls --ignore='*.*' | grep -v --invert-match -E "Makefile|script|shell|sort" > list.txt;
cat list.txt;
echo " ";
cd ..;

make;

cd userprog;
for str in $(cat ../test/list.txt);do 
echo "Testing " $str;
./nachos -rs 1234 -x ../test/$str > /dev/null || exit 1;
echo "done";
echo "";
done;
echo "All test clear.";
cd ..;
cd ..;
