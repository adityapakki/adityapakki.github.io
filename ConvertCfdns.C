// *****************************************************************************
/*!
  \file      src/IO/ConvertCfdns.C
  \author    A. Pakki
  \copyright 2012-2015, Jozsef Pakki, 2016, Los Alamos National Security, LLC.
  \brief     Binary file output to ROOT
  \details   Convert binary data to ROOT layout.

*Input Header layout 
  1 to  16: cfdnsrun1.0; 
 17 to  24: time; 
 25 to  32: dt; 
 33 to  36: dimension (here 3); 
 37 to  40: NXT (here 256); 
 41 to  44: NYT (here 256); 
 45 to  48: NZT (here 256); 
 49 to  56: 8; 
 57 to  64: 0.0; 
 65 to  72: 0.0; 
 73 to  80: 0.0;
 81 to  88: lx (here 2pi);
 89 to  96: ly (here 2pi);
 97 to 104: lz (here 2pi);
105 to 108: geometry of the problem (here 0 corresponding to Cartesian coord); 
109 to 112: the number of fields that are saved (here 5);
113 to 128:”density” 
129 to 144:”velocity_x” 
145 to 160:”velocity_y”; 
161 to 176:”velocity_z”; 
177 to 192(end):”pressure”.
*/
// *****************************************************************************

#include <iostream>
#include <fstream>

int main( int argc, char* argv[] ) {
  
  const char* ifile;
  std::ifstream inputFile;

  // layout of the file.
  typedef struct __attribute__((packed)) FileLayout {
    char run[16];
    double time;
    double difftime;
    int ndims;
    int x_size;
    int y_size;
    int z_size;
    double size;
    double misc_1;
    double misc_2;
    double misc_3;
    double coord_1;
    double coord_2;
    double coord_3;
    int geom_;
    int fields_count;
    long double var_fields_1;
    long double var_fields_2;
    long double var_fields_3;
    long double var_fields_4;
    long double var_fields_5;
  } layout;

  if (argc > 1 )
    ifile = argv[1];
  else
    ifile = "rstrt.0000.bin";
  
  //open the file
  inputFile.open( ifile, std::ios::binary );
  if( ! inputFile.is_open() ) {
    std::cerr <<  "File "<<ifile << "can't be opened" << std::endl;
    return 1;
  }

  for (int i = 0 ; i < 10; i++ ) {
  layout l;
  inputFile.read(l.run, sizeof(l.run) );
  inputFile.read(reinterpret_cast<char *>(&l.time), sizeof(l.time));
  inputFile.read(reinterpret_cast<char *>(&l.difftime), sizeof(l.difftime));
  inputFile.read(reinterpret_cast<char *>(&l.ndims), sizeof(l.ndims));
  inputFile.read(reinterpret_cast<char *>(&l.x_size), sizeof(l.x_size));
  inputFile.read(reinterpret_cast<char *>(&l.y_size), sizeof(l.y_size));
  inputFile.read(reinterpret_cast<char *>(&l.z_size), sizeof(l.z_size));
  inputFile.read(reinterpret_cast<char *>(&l.size), sizeof(l.size));
  inputFile.read(reinterpret_cast<char *>(&l.misc_1), sizeof(l.misc_1));
  inputFile.read(reinterpret_cast<char *>(&l.misc_2), sizeof(l.misc_2));
  inputFile.read(reinterpret_cast<char *>(&l.misc_3), sizeof(l.misc_3));
  inputFile.read(reinterpret_cast<char *>(&l.coord_1), sizeof(l.coord_1));
  inputFile.read(reinterpret_cast<char *>(&l.coord_2), sizeof(l.coord_2));
  inputFile.read(reinterpret_cast<char *>(&l.coord_3), sizeof(l.coord_3));
  inputFile.read(reinterpret_cast<char *>(&l.geom_), sizeof(l.geom_));
  inputFile.read(reinterpret_cast<char *>(&l.fields_count),
     sizeof(l.fields_count));
  inputFile.read(reinterpret_cast<char *>(&l.var_fields_1), 
     sizeof(l.var_fields_1));
  inputFile.read(reinterpret_cast<char *>(&l.var_fields_2), 
     sizeof(l.var_fields_2));
  inputFile.read(reinterpret_cast<char *>(&l.var_fields_3), 
     sizeof(l.var_fields_3));
  inputFile.read(reinterpret_cast<char *>(&l.var_fields_4), 
     sizeof(l.var_fields_4));
  inputFile.read(reinterpret_cast<char *>(&l.var_fields_5), 
     sizeof(l.var_fields_5));
  
  /*std::cout<< l.run << 
	      l.time << 
	      l.difftime <<
	      l.ndims << l.x_size << " " << l.y_size << " " << l.z_size <<
	      " " << l.size << " " << std::endl <<
	      l.misc_1 << " " << l.misc_2 << " " << l.misc_3 << std::endl
	      << l.coord_1 << " " << l.coord_2 << " " << l.coord_3 
	      << std::endl << l.geom_ << " " << l.fields_count << std::endl
  */
  std::cout   << l.var_fields_1 << " " << l.var_fields_2 << " " 
	      << l.var_fields_3 << " " << l.var_fields_4 << " " 
	      << l.var_fields_5 << " " << sizeof(float) << std::endl;

  }

  //Close the file
  inputFile.close();

  return 0;
}

