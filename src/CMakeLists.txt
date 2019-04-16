

add_executable(Matrusse main.c testVerification.h testVerification.c fourRussianAlgorithm.c fourRussianAlgorithm.h matrix.h matrix.c)
add_executable(Test test.c testVerification.h testVerification.c fourRussianAlgorithmV2.c fourRussianAlgorithmV2.h matrix.h matrix.c utils.h utils.c)
add_executable(Tests tests/tests.cpp tests/tests-matrix.cpp matrix.h matrix.c)
add_executable(TestIntrin testIntrin.c 4RusIntrin.c 4RusIntrin.h matrix.c matrix.h utils.c utils.h)
include_directories( ${MY_SOURCE_DIR}/src)