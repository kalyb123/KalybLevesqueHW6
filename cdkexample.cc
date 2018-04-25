/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <inttypes.h>

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader{
public:
  uint32_t magicNumber;  // 0xFEEDFACE
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord{
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

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
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
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }



  // use binary file io to read file header
  ifstream infile;
  infile.open("cs3377.bin", ios::binary | ios::in);
    
  // check if file is not open
  if(!infile.is_open()){
    cout << "error the file didnt open" << endl;
    exit(1);
  }
  BinaryFileRecord* record = new BinaryFileRecord();
  BinaryFileHeader* header = new BinaryFileHeader();

  // reads 8 bytes into a cell
  infile.read((char *)header, sizeof(BinaryFileHeader));
  
  ostringstream converter;

  converter << "0x" << hex << uppercase << header->magicNumber;
 
  string hexVal = "Magic: " + converter.str();
  converter.str(""); // clears it
  
  converter << dec << header->versionNumber;

  string Versions = "Versions: " + converter.str();
  converter.str(""); // clears it

  converter << header->numRecords;

  string NumRecords = "NumRecords: " + converter.str();
  converter.str(""); // clears it


  infile.read((char *)record, sizeof(BinaryFileRecord));

  converter << record -> stringBuffer;
  string BB = converter.str();
  converter.str("");
  
  // length of avbove
  converter << strlen(BB.c_str());
  string BA = "strlen: " + converter.str();
  converter.str("");

  infile.read((char *)record, sizeof(BinaryFileRecord));
  converter << record -> stringBuffer;


  string CB = converter.str();
  converter.str("");

  // length of avbove
  converter << strlen(CB.c_str());
  string CA = "strlen: " + converter.str();
  converter.str("");

  infile.read((char *)record, sizeof(BinaryFileRecord));
  converter << record -> stringBuffer;


  string DB = converter.str();
  converter.str("");

  // length of avbove
  converter << strlen(DB.c_str());
  string DA = "strlen: " + converter.str();
  converter.str("");

  infile.read((char *)record, sizeof(BinaryFileRecord));

  converter << record -> stringBuffer;
  string EB = converter.str();
  converter.str("");

  // length of avbove
  converter << strlen(EB.c_str());
  string EA = "strlen: " + converter.str();
  converter.str("");

  infile.read((char *)record, sizeof(BinaryFileRecord));

 
 
  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 1, hexVal.c_str());
  drawCDKMatrix(myMatrix, true);    /* required  */


  setCDKMatrixCell(myMatrix, 1, 2, Versions.c_str());
  drawCDKMatrix(myMatrix, true); 

  setCDKMatrixCell(myMatrix, 1, 3, NumRecords.c_str());
  drawCDKMatrix(myMatrix, true); 

 
  setCDKMatrixCell(myMatrix, 2, 1, BA.c_str());
  drawCDKMatrix(myMatrix, true);

  setCDKMatrixCell(myMatrix, 2, 2, BB.c_str());
  drawCDKMatrix(myMatrix, true);

  setCDKMatrixCell(myMatrix, 3, 1, CA.c_str());
  drawCDKMatrix(myMatrix, true);

  setCDKMatrixCell(myMatrix, 3, 2, CB.c_str());
  drawCDKMatrix(myMatrix, true);

  setCDKMatrixCell(myMatrix, 4, 1, DA.c_str());
  drawCDKMatrix(myMatrix, true);

  setCDKMatrixCell(myMatrix, 4, 2, DB.c_str());
  drawCDKMatrix(myMatrix, true);

  setCDKMatrixCell(myMatrix, 5, 1, EA.c_str());
  drawCDKMatrix(myMatrix, true);

  setCDKMatrixCell(myMatrix, 5, 2, EB.c_str());
  drawCDKMatrix(myMatrix, true);

 


  infile.close();

 /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
