#include <math/CoolMatrix_to_vnl_matrix.h>
#include <math/CoolVector_to_vnl_vector.h>
#include <math/IUE_matrix_to_vnl_matrix.h>
#include <math/IUE_vector_to_vnl_vector.h>
#include <math/vnl_matrix_to_CoolMatrix.h>
#include <math/vnl_matrix_to_IUE_matrix.h>
#include <math/vnl_vector_to_CoolVector.h>
#include <math/vnl_vector_to_IUE_vector.h>

#include <vnl/vnl_test.h>

void test_matrix_conversions()
{
  int data[] = { 1, 2, 3, 2, 4, 6, 3, 6, 9 };
  CoolMatrix<int> m1(data,3,3);
  vnl_matrix<int> m2 = CoolMatrix_to_vnl_matrix(m1);
  TEST("CoolMatrix_to_vnl_matrix", m2.rows(), 3);
  TEST("CoolMatrix_to_vnl_matrix", m2.columns(), 3);
  TEST("CoolMatrix_to_vnl_matrix", m2[1][2], 6);
  IUE_matrix<int> m3 = vnl_matrix_to_IUE_matrix(m2);
  TEST("vnl_matrix_to_IUE_matrix", m3(1,1), 4);
  TEST("vnl_matrix_to_IUE_matrix", m3, m1);

  CoolVector<int> v1(data,9);
  vnl_vector<int> v2 = CoolVector_to_vnl_vector(v1);
  TEST("CoolVector_to_vnl_vector", v2.size(), 9);
  TEST("CoolVector_to_vnl_vector", v2[1], 2);
  IUE_vector<int> v3 = vnl_vector_to_IUE_vector(v2);
  TEST("vnl_vector_to_IUE_vector", v3(2), 3);
  TEST("vnl_vector_to_IUE_vector", v3, v1);
}

TESTMAIN(test_matrix_conversions);
