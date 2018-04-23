// Jonathan Snead
// jcs160330@utdallas.edu
// CS 3377.002

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <stdint.h>
#include <inttypes.h>
#include <sstream>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

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
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"0", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */

  BinaryFileHeader *mySecRecord = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();

  ifstream binFile("cs3377.bin", ios::in | ios::binary);

  if (binFile.is_open())
    {
      binFile.read((char *)mySecRecord, sizeof(BinaryFileHeader));
      binFile.read((char *)myRecord, sizeof(BinaryFileRecord));

      ostringstream trans;

      trans << "0x" << hex << uppercase << mySecRecord->magicNumber;
      string boxAA = "Magic: " + trans.str();
      trans.str("");

      trans << dec << mySecRecord->versionNumber;
      string boxAB = "Version: " + trans.str();
      trans.str("");

      trans << mySecRecord->numRecords;
      string boxAC = "NumRecords: " + trans.str();
      trans.str("");


      trans << myRecord->stringBuffer;
      string boxBB = trans.str();
      trans.str("");

      trans << strlen(boxBB.c_str());
      string boxBA = "strlen: " + trans.str();
      trans.str("");

      binFile.read((char *)myRecord, sizeof(BinaryFileRecord));
      trans << myRecord->stringBuffer;
      string boxCB = trans.str();
      trans.str("");

      trans << strlen(boxCB.c_str());
      string boxCA = "strlen: " + trans.str();
      trans.str("");

      binFile.read((char *)myRecord, sizeof(BinaryFileRecord));
      trans << myRecord->stringBuffer;
      string boxDB = trans.str();
      trans.str("");

      trans << strlen(boxDB.c_str());
      string boxDA = "strlen: " + trans.str();
      trans.str("");

      binFile.read((char *)myRecord, sizeof(BinaryFileRecord));
      trans << myRecord->stringBuffer;
      string boxEB = trans.str();
      trans.str("");

      trans << strlen(boxEB.c_str());
      string boxEA = "strlen: " + trans.str();
      trans.str("");


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
    }

  else 
    printf("Error opening Binary file\n");

  binFile.close();

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  delete [] mySecRecord;

  // Cleanup screen
  endCDK();
}

/*
      int row = 1;
      int col = 1;
      char *buffer = (char *)malloc(100);
      ostringstream transferVar;
      while (binFile.read((char*)mySecRecord, sizeof(BinaryFileHeader)))
	{
	  if (binFile.read((char*)mySecRecord, sizeof(BinaryFileHeader)) != "\n")
	    {
	      transferVar << mySecRecord->magicNumber;
	      // strcpy(buffer, (mySecRecord->magicNumber));
	      // buffer = reinterpret_cast<const char *>(mySecRecord->magicNumber);
	    }
	   else 
	     {
	     }
	}
      string str = transferVar.str();
	  setCDKMatrixCell(myMatrix, row, col, "First Box");
	  drawCDKMatrix(myMatrix, true);    // required  
	   // required  
	  //printf("0x%02" PRIu32 "\n", mySecRecord->magicNumber);
*/
