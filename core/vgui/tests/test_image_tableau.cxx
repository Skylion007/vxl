#include <vgui/vgui_image_tableau.h>

#include <testlib/testlib_test.h>

#include <vil1/vil1_image.h>
#include <vil1/vil1_load.h>

#include <vxl_config.h>

MAIN( test_image_tableau )
{
  // Supply a test image as the first argument

  START( "test_image_tableau" );

  // Make sure that constructing a vgui_image_tableau with a filename
  // results in the vil1_image being loaded, since this is expected by
  // older code.
  //
  vil1_image img = vil1_load( argv[1] );
  if( !img ) {
    vcl_cout << "Couldn't load test image \"" << argv[1] << "\"" << vcl_endl;
  } else {
    testlib_test_begin( "Construct with filename" );
    vgui_image_tableau_new img_tab( argv[1] );
    vil1_image img2 = img_tab->get_image();
    testlib_test_perform( img2 );

    testlib_test_begin( "Size is correct" );
    testlib_test_perform( img.width()      == img2.width() &&
                          img.height()     == img2.height() &&
                          img.components() == img2.components() &&
                          img.planes()     == img2.planes() && 
                          img.bits_per_component() == img2.bits_per_component() );
 
    testlib_test_begin( "Contents are correct" );
    unsigned buf_size = img.width() * img.height() *
                        img.planes() * img.components() *
                        (img.bits_per_component()+7) / 8;
    char* img1_buf = new char[buf_size];
    char* img2_buf = new char[buf_size];

    bool okay = true;

    if( !img.get_section( img1_buf, 0, 0, img.width(), img.height() ) ) {
      vcl_cout << "Couldn't read from img1" << vcl_endl;
      okay = false;
    }
    if( !img2.get_section( img2_buf, 0, 0, img2.width(), img2.height() ) ) {
      vcl_cout << "Couldn't read from img2" << vcl_endl;
      okay = false;
    }

    for( unsigned i = 0; i < buf_size; ++i ) {
      if( img1_buf[i] != img2_buf[i] ) {
        okay = false;
        break;
      }
    }

    delete img1_buf;
    delete img2_buf;
  
    testlib_test_perform( okay );
  }
  
  SUMMARY();
}
