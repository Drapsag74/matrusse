

add_executable(Matrusse main.c testVerification.h testVerification.c fourRussianAlgorithm.c fourRussianAlgorithm.h matrix.h matrix.c fourRussianAlgorithmV2.c fourRussianAlgorithmV2.h utils.c utils.h 4RusIntrin.c 4RusIntrin.h 4RusThread.h 4RusThread.c)
add_executable(Test test.c testVerification.h testVerification.c matrix.h matrix.c fourRussianAlgorithmV2.c fourRussianAlgorithmV2.h fourRussianAlgorithm.c fourRussianAlgorithm.h utils.c utils.h 4RusThread.h 4RusThread.c)
add_executable(Tests tests/tests.cpp tests/tests-matrix.cpp matrix.h matrix.c utils.c utils.h 4RusIntrin.c 4RusIntrin.h fourRussianAlgorithmV2.c fourRussianAlgorithmV2.h fourRussianAlgorithm.c fourRussianAlgorithm.h testVerification.c testVerification.h )
add_executable(TestIntrin TestIntrin.c 4RusIntrin.c 4RusIntrin.h matrix.c matrix.h utils.c utils.h )
include_directories( ${MY_SOURCE_DIR}/src)