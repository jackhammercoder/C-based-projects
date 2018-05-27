#!/bin/bash

echo "[CORE TEST]:"
echo "(CORE) Tests swc with no options and reading from stdin."
echo
~kmammen-grader/public/357/Project2/swc > stdin1.expect
echo
./a.out > stdin1.out
diff -q stdin1.out stdin1.expect
echo

echo "[CORE TEST]:"
echo Tests swc with the -l flag reading from stdin
echo
~kmammen-grader/public/357/Project2/swc -l > stdinlflag.expect
./a.out -l > stdinlflag.out
diff -q stdinlflag.expect stdinlflag.out        
echo


echo "[FEATURE TEST]:"
echo Tests swc with the -w flag reading from stdin
echo
~kmammen-grader/public/357/Project2/swc -w > stdinwflag.expect
./a.out -w > stdinwflag.out
diff -q stdinwflag.expect stdinwflag.out        
echo

echo "[FEATURE TEST]:"
echo Tests swc with the -c flag reading from stdin
echo
~kmammen-grader/public/357/Project2/swc -c > stdincflag.expect
./a.out -c > stdincflag.out
diff -q stdincflag.expect stdincflag.out        
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
stdin."
echo
~kmammen-grader/public/357/Project2/swc -l -w > stdinlwflag.expect
./a.out -l -w > stdinlwflag.out
diff -q stdinlwflag.expect stdinlwflag.out        
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
stdin."
echo
~kmammen-grader/public/357/Project2/swc -l -c > stdinlcflag.expect
./a.out -l -c > stdinlcflag.out
diff -q stdinlcflag.expect stdinlcflag.out        
echo


echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
stdin."
echo
~kmammen-grader/public/357/Project2/swc -w -l > stdinwlflag.expect
./a.out -w -l > stdinwlflag.out
diff -q stdinwlflag.expect stdinwlflag.out        
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
stdin."
echo
~kmammen-grader/public/357/Project2/swc -w -c > stdinwcflag.expect
./a.out -w -c > stdinwcflag.out
diff -q stdinwcflag.expect stdinwcflag.out        
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
stdin."
echo
~kmammen-grader/public/357/Project2/swc -c -l > stdinclflag.expect
./a.out -c -l > stdinclflag.out
diff -q stdinclflag.expect stdinclflag.out        
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of two correct flags reading from
stdin."
echo
~kmammen-grader/public/357/Project2/swc -c -w > stdincwflag.expect
./a.out -c -w > stdincwflag.out
diff -q stdincwflag.expect stdincwflag.out        
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either stdin"
echo
~kmammen-grader/public/357/Project2/swc -l -w -c > stdlwcflag.expect
./a.out -l -w -c > stdlwcflag.out
diff -q stdlwcflag.expect stdlwcflag.out        
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either stdin"
echo
~kmammen-grader/public/357/Project2/swc -l -c -w > stdlcwflag.expect
./a.out -l -c -w > stdlcwflag.out
diff -q stdlcwflag.expect stdlcwflag.out        
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either stdin"
echo
~kmammen-grader/public/357/Project2/swc -w -l -c > stdwlcflag.expect
./a.out -w -l -c > stdwlcflag.out
diff -q stdwlcflag.expect stdwlcflag.out        
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either stdin"
echo
~kmammen-grader/public/357/Project2/swc -w -c -l > stdwclflag.expect
./a.out -w -c -l > stdwclflag.out
diff -q stdwclflag.expect stdwclflag.out        
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either stdin"
echo
~kmammen-grader/public/357/Project2/swc -c -l -w > stdclwflag.expect
./a.out -c -l -w > stdclwflag.out
diff -q stdclwflag.expect stdclwflag.out        
echo

echo "[FEATURE TEST]:"
 echo "Tests swc with a unique combination of three correct flags reading from
either stdin"
echo
~kmammen-grader/public/357/Project2/swc -c -w -l > stdcwlflag.expect
./a.out -c -w -l > stdcwlflag.out
diff -q stdcwlflag.expect stdcwlflag.out        
echo


