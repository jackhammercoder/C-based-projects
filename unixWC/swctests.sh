#!/bin/bash
echo "[CORE TEST]:"
echo "(CORE)Tests swc with no options and processing an existing and readable single text file."
echo 
~kmammen-grader/public/357/Project2/swc readable.txt > singleread.expect
./a.out readable.txt > singleread.out
diff -q singleread.expect singleread.out
echo


echo "[CORE TEST]:"
echo "(CORE)Tests swc with no options and processing multiple existing and readable text files."
echo 
~kmammen-grader/public/357/Project2/swc readable* > multiread.expect
./a.out readable* > multiread.out
diff -q multiread.expect multiread.out  
echo

echo "[CORE TEST]:"
echo Tests swc with no options and processing a readable binary file. 
echo 
~kmammen-grader/public/357/Project2/swc ./a.out > singlebinary.expect
./a.out ./a.out > singlebinary.out
diff -q singlebinary.expect singlebinary.out  
echo

echo "[FEATURE TEST]:"
 echo Tests swc with the -l flag reading from file 
echo 
~kmammen-grader/public/357/Project2/swc -l readable.txt > singlereadlflag.expect
./a.out -l readable.txt > singlereadlflag.out
diff -q singlereadlflag.expect singlereadlflag.out  
echo

echo "[FEATURE TEST]:"
 echo Tests swc with the -w flag reading from file 
echo 
~kmammen-grader/public/357/Project2/swc -w readable.txt > singlereadwflag.expect
./a.out -w readable.txt > singlereadwflag.out
diff -q singlereadwflag.expect singlereadwflag.out  
echo

echo "[FEATURE TEST]:"
 echo Tests swc with the -c flag reading from file 
echo 
~kmammen-grader/public/357/Project2/swc -c readable.txt > singlereadcflag.expect
./a.out -c readable.txt > singlereadcflag.out
diff -q singlereadcflag.expect singlereadcflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
a file."
 echo 
~kmammen-grader/public/357/Project2/swc -l -w readable.txt > singlereadlwflag.expect
./a.out -l -w readable.txt > singlereadlwflag.out
diff -q singlereadlwflag.expect singlereadlwflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
a file."
 echo 
~kmammen-grader/public/357/Project2/swc -l -c readable.txt > singlereadlcflag.expect
./a.out -l -c readable.txt > singlereadlcflag.out
diff -q singlereadlcflag.expect singlereadlcflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
a file."
 echo 
~kmammen-grader/public/357/Project2/swc -w -l readable.txt > singlereadwlflag.expect
./a.out -w -l readable.txt > singlereadwlflag.out
diff -q singlereadwlflag.expect singlereadwlflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
a file."
 echo 
~kmammen-grader/public/357/Project2/swc -w -c readable.txt > singlereadwcflag.expect
./a.out -w -c readable.txt > singlereadwcflag.out
diff -q singlereadwcflag.expect singlereadwcflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
a file."
 echo 
~kmammen-grader/public/357/Project2/swc -c -l readable.txt > singlereadclflag.expect
./a.out -c -l readable.txt > singlereadclflag.out
diff -q singlereadclflag.expect singlereadclflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
a file."
 echo 
~kmammen-grader/public/357/Project2/swc -c -w readable.txt > singlereadcwflag.expect
./a.out -c -w readable.txt > singlereadcwflag.out
diff -q singlereadcwflag.expect singlereadcwflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either readable file"
echo 
~kmammen-grader/public/357/Project2/swc -l -w -c  readable.txt> singlereadlwcflag.expect
./a.out -l -w -c readable.txt > singlereadlwcflag.out
diff -q singlereadlwcflag.expect singlereadlwcflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either readable file"
echo 
~kmammen-grader/public/357/Project2/swc -l -c -w  readable.txt> singlereadlcwflag.expect
./a.out -l -c -w  readable.txt> singlereadlcwflag.out
diff -q singlereadlcwflag.expect singlereadlcwflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either readable file"
echo 
~kmammen-grader/public/357/Project2/swc -w -l -c  readable.txt> singlereadwlcflag.expect
./a.out -w -l -c  readable.txt> singlereadwlcflag.out
diff -q singlereadwlcflag.expect singlereadwlcflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either readable file"
echo 
~kmammen-grader/public/357/Project2/swc -w -c -l  readable.txt> singlereadwclflag.expect
./a.out -w -c -l  readable.txt> singlereadwclflag.out
diff -q singlereadwclflag.expect singlereadwclflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either readable file"
echo 
~kmammen-grader/public/357/Project2/swc -c -l -w readable.txt > singlereadclwflag.expect
./a.out -c -l -w  readable.txt> singlereadclwflag.out
diff -q singlereadclwflag.expect singlereadclwflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either readable file"
echo 
~kmammen-grader/public/357/Project2/swc -c -w -l readable.txt > singlereadcwlflag.expect
./a.out -c -w -l  readable.txt> singlereadcwlflag.out
diff -q singlereadcwlflag.expect singlereadcwlflag.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with some number of correct flags after file(s)."
echo 
~kmammen-grader/public/357/Project2/swc readable* bob bobby readbin* -w -c &> wcflagafter.expect
./a.out readable* bob bobby readbin* -w -c &> wcflagafter.out
diff -q wcflagafter.expect wcflagafter.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with some number of correct flags after file(s)."
echo 
~kmammen-grader/public/357/Project2/swc readable* bob noread* bobby readbin* -c &> cflagafter.expect
./a.out readable* bob noread*  bobby readbin* -c &> cflagafter.out
diff -q cflagafter.expect cflagafter.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with some number of correct flags after file(s)."
echo 
~kmammen-grader/public/357/Project2/swc readable* bob noread* bobby readbin* -c -l -w &> allflagafter.expect
./a.out readable* bob noread* bobby readbin* -c -l -w &> allflagafter.out
diff -q allflagafter.expect allflagafter.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with some number of correct flags between files."
echo 
~kmammen-grader/public/357/Project2/swc bob noread* readable* -c readbin* &> cflagbewtween.expect
./a.out bob noread* readable* -c readbin* &> cflagbewtween.out
diff -q cflagbewtween.expect cflagbewtween.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with some number of correct flags between files."
echo 
~kmammen-grader/public/357/Project2/swc bob noread* readable* -c -w readbin* &> cwflagbewtween.expect
./a.out bob noread* readable* -c -w readbin* &> cwflagbewtween.out
diff -q cwflagbewtween.expect cwflagbewtween.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with some number of correct flags between files."
echo 
~kmammen-grader/public/357/Project2/swc bob noread* readable* -c -w -l readbin* &> cwlflagbewtween.expect
./a.out bob noread* readable* -c -w -l readbin*  &> cwlflagbewtween.out
diff -q cwlflagbewtween.expect cwlflagbewtween.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with correct flags before, between, and after files."
echo 
~kmammen-grader/public/357/Project2/swc -w -w -c bob -c -l noread* -c -c readable* -w readbin* -w -w &> spreadflags.expect
./a.out  -w -w -c bob -c -l noread* -c -c readable* -w readbin* -w -w &> spreadflags.out
diff -q spreadflags.expect spreadflags.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with some number of invalid flags reading from stdin or some
number of files."
echo 
~kmammen-grader/public/357/Project2/swc -bob -bobby -dog readable* &> invalidflags.expect
./a.out -bob -bobby -dog readable* &> invalidflags.out
diff -q invalidflags.expect invalidflags.out  
echo


echo "[FEATURE TEST]:"
 echo "Tests swc with some number of invalid flags mixed with some number of
valid flags reading from stdin or some number of files."
echo 
~kmammen-grader/public/357/Project2/swc -w -c -bob -tit readable* &> mixflags.expect
./a.out -w -c -bob -tit readable* &> mixflags.out
diff -q mixflags.expect mixflags.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with some number of duplicate valid flags and reading from 
stdin or some number of files."
echo 
~kmammen-grader/public/357/Project2/swc -w -c -w -l -l -w -c readable* readbin** > repeatflags.expect
./a.out  -w -c -w -l -l -w -c readable* readbin* > repeatflags.out
diff -q repeatflags.expect repeatflags.out  
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with some number of duplicate valid and invalid flags and reading from 
stdin or some number of files."
echo 
~kmammen-grader/public/357/Project2/swc -w -c -w -tit -l -bob -l -w -c readable* readbin* &> mixedwithinvalid.expect
./a.out  -w -c -w -tit -l -l -bob -w -c readable* readbin* &> mixedwithinvalid.out
diff -q mixedwithinvalid.expect mixedwithinvalid.out  
echo
