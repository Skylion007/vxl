#include <testlib/testlib_register.h>

DECLARE( test_image_2d_of );
DECLARE( test_sample_profile_bilin );
DECLARE( test_sample_grid_bilin );
DECLARE( test_transform_2d );
DECLARE( test_gaussian_pyramid_builder_2d );

void
register_tests()
{
  REGISTER( test_image_2d_of );
  REGISTER( test_sample_profile_bilin );
  REGISTER( test_sample_grid_bilin );
  REGISTER( test_transform_2d );
  REGISTER( test_gaussian_pyramid_builder_2d );
}

DEFINE_MAIN;
