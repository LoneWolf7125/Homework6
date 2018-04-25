// Jonathan Snead
// jcs160330@utdallas.edu
// CS 3377.002

// Includes
#include <iostream>
#include "cdk.h"
#include <fstream>
#include <stdint.h>
#include <inttypes.h>
#include <sstream>

// Define statments 
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

// Got from the instructions
class BinaryFileHeader
{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;
class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           

  const char 		*rowTitles[] = {"0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"0", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  // Initialize the Cdk screen.
  // Make sure the putty terminal is large enough.
  window = initscr();
  cdkscreen = initCDKScreen(window);

  // Start CDK Colors 
  initCDKColor();

  // Create the matrix.  Need to manually cast (const char**) to (char **)
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL) // Can't create the CDK matrix
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  // Header of the binary file
  BinaryFileHeader *mySecRecord = new BinaryFileHeader();
  // The actual records 
  BinaryFileRecord *myRecord = new BinaryFileRecord();

  // Opens the file
  ifstream binFile("cs3377.bin", ios::in | ios::binary);

  if (binFile.is_open()) // Checks if it is open
    {
      // Read the first line for header
      binFile.read((char *)mySecRecord, sizeof(BinaryFileHeader));
      // Read the second line for the record
      //binFile.read((char *)myRecord, sizeof(BinaryFileRecord));

      // For number conversions
      ostringstream trans;

      // First box is the hex value so this converts it
      trans << "0x" << hex << uppercase << mySecRecord->magicNumber;
      string boxAA = "Magic: " + trans.str(); // Box 1 1
      trans.str(""); // Clear it

      // Second box is the number of versions so this converts it
      trans << dec << mySecRecord->versionNumber;
      string boxAB = "Version: " + trans.str(); // Box 1 2
      trans.str(""); // Clear it 

      // Third box is for the number of records so this gets it
      trans << mySecRecord->numRecords;
      string boxAC = "NumRecords: " + trans.str(); // Box 1 3
      trans.str(""); // Clear it

      /*
      // Second line already read above
      // Put line in to convert it
      trans << myRecord->stringBuffer;
      string boxBB = trans.str(); // Box 2 2
      trans.str(""); // Clear it

      // Get the length of the previous box
      trans << strlen(boxBB.c_str());
      string boxBA = "strlen: " + trans.str(); // Box 2 1
      trans.str(""); // Clear it

      // Third line read in here
      binFile.read((char *)myRecord, sizeof(BinaryFileRecord));
      // Put line in to convert it
      trans << myRecord->stringBuffer;
      string boxCB = trans.str(); // Box 3 2
      trans.str(""); // Clear it

      // Get the length of the previous box
      trans << strlen(boxCB.c_str());
      string boxCA = "strlen: " + trans.str(); // Box 3 1
      trans.str(""); // Clear it

      // Fourth line read here
      binFile.read((char *)myRecord, sizeof(BinaryFileRecord));
      // Put line in to convert it
      trans << myRecord->stringBuffer;
      string boxDB = trans.str(); // Box 4 2
      trans.str(""); // Clear it

      // Get the length of the previous box
      trans << strlen(boxDB.c_str());
      string boxDA = "strlen: " + trans.str(); // Box 4 1
      trans.str(""); // Clear it

      // Fifth line read here
      binFile.read((char *)myRecord, sizeof(BinaryFileRecord));
      // Put line in to convert it
      trans << myRecord->stringBuffer;
      string boxEB = trans.str(); // Box 5 2
      trans.str(""); // Clear it

      // Get the length of the previous box
      trans << strlen(boxEB.c_str());
      string boxEA = "strlen: " + trans.str(); // Box 5 1
      trans.str(""); // Clear it


      // Print each one in their designated box in the CDK
      setCDKMatrixCell(myMatrix, 1, 1, boxAA.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 1, 2, boxAB.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 1, 3, boxAC.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 2, 1, boxBA.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 2, 2, boxBB.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 3, 1, boxCA.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 3, 2, boxCB.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 4, 1, boxDA.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 4, 2, boxDB.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 5, 1, boxEA.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 5, 2, boxEB.c_str());
      drawCDKMatrix(myMatrix, true);   
    }*/
      
      // Recursive run of the record section
      for (int i = 1; i <= 5; i++)
	{
	  // Read in the next line everytime 
	  binFile.read((char *)myRecord, sizeof(BinaryFileRecord));
	  
	  // Get the values into the string
	  trans << myRecord->stringBuffer;
	  string buffer = trans.str();
	  trans.str(""); // Clear it
	  
	  // Get the values into the string
	  trans << strlen(buffer.c_str());
	  string strlen = "strlen: " + trans.str();
	  trans.str(""); // Clear it
	  
	  // Print record section 
	  setCDKMatrixCell(myMatrix, (i+1), 1, strlen.c_str());
	  setCDKMatrixCell(myMatrix, (i+1), 2, buffer.c_str());
	  drawCDKMatrix(myMatrix, true);
	}

      // Print header section
      setCDKMatrixCell(myMatrix, 1, 1, boxAA.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 1, 2, boxAB.c_str());
      drawCDKMatrix(myMatrix, true);   

      setCDKMatrixCell(myMatrix, 1, 3, boxAC.c_str());
      drawCDKMatrix(myMatrix, true);   
    }

  else // Can't open binary file
    printf("Error opening Binary file\n");

  // Close the binary file
  binFile.close();

  // So we can see results, pause until a key is pressed. 
  unsigned char x;
  cin >> x;

  // Delete for space 
  delete [] mySecRecord;
  delete [] myRecord;

  // Cleanup screen
  endCDK();
}
