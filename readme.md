Computer Matchmaking Program Information:

File Descriptions:
1. Computer Matchmaking.CPP- C++ Program code (can be edited and recompiled)
2. Database.txt- Default database file.
3. Header.txt- Default header file.
4. Results.doc- Default output file.
4. Computer Matchmaking.exe- The actual program.
5. Settings.txt- The default settings file. 

Note: If the file you are using for the database or header is not in the same folder as the program, you must enter the full path in Settings.txt, or else the program will not find the file. If the output file is not in the same folder as the program, you must enter the full path or else the program will create a same-name output page in its current folder.

About the Settings file
This file contains the paths for the database file, header file, and output file, and the number to process. The file has a four line layout as follows:

(1) ASCII database file 
(2) Output file
(3) Header file
(4) Number to process

By default it looks like this:

Database.txt
Results.doc
Header.txt
999

About the Database file:
The database file should be laid out in the following way:
last name,first name,grade,sex, 29 responses ranging 1-5

Example:
Alequin,Ryan,12,m,44431352114221241111124323323

Warning: Attempting to run the program while the database is empty will cause a crash.

About the program:
This program has two modes:  A processing mode and a menu mode.
When you first start the program, it is in processing mode. To begin processing records, you type a record number (#), a range of record numbers (#-#), or record numbers/ranges separated by commas (#,#-#). Then press enter. You can also press Q or X followed by enter to close the program, or . (period) to enter the menu mode. Once in menu mode, the following commands are available:

D – (Display) Shows the current settings (this reflects what is entered in Settings.txt)

L – (List) Lists all records in the database.

N- (Number) Allows you change number to process temporarily (it can permanently be changed in Settings.txt)

O- (Output) Changes the output file temporarily (it can permanently be changed in Settings.txt)

S- (Search) Searches records to find a specific person

Q– (Quit) Returns to the processing mode

?- Displays help for these commands within the program

About the Header file:
 When modifying the header file you must keep the `N, `G, and `A marks in place to designate where the name, grade, and percentages should go.

To print the output pages: 
1. Open the output file in Microsoft Word
2. If prompted to choose an encoding, select Unicode (UTF-8)
3. Click file-> page setup and set your margins as follows:    Top: 0.5”    Bottom: 1”
4. On the first line of the first page press enter three times

Every page should now have five blank lines at the head and be equally spaced. If your pages are still uneven, try turning on the  marks to help you space evenly.