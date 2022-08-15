

auto tests for part-I programs.

Conventions:

  each program has some number of tests.
   
  median3 tests files begin with p1
  stairs test files begin with p2
  num_ones test files begin with p3
  histogram test files begin with p4

There is a script calld batch to run all tests, but
it might help to understand the setup a bit:

-----------------------

example:  Test 3 for stairs is captured
   in the files p2t3:

       p2t3.inp   :  text you would type when running
                     the program interactively
       p2t3.ref   :  expected correct output (with blank 
                    lines stripped)


   If you do the following:

      $ ./stairs < p2t3.inp | grep -e -v '^$' > p2t3.out

   then the file p2t3.out will (hopefully) be identical to 
   p2t3.ref
     
--------------------------

Running batch:  you may have to do the following to make
  the batch script 'runnable':

   chmod +x batch

Then:  you can simply type

   ./batch

it will compile the 4 programs (your .c files should be in 
the same folder of course), and run each test and report 
results if all goes as planned
  
NOTE:  some of the .ref files will look a little funky because
the new-lines you see interactively are not part of the program
'output', but rather the 'input' (the user types RETURN after 
entering an input); this means that the text
for prompts will be smashed onto one line
