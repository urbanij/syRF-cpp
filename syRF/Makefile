

test:
	g++ -std=c++17 tests_y_s_parameters.cpp s_parameters.cpp y_parameters.cpp utils.cpp -lgtest -lgtest_main -pthread -o tests_y_s_parameters && ./tests_y_s_parameters
	g++ -std=c++17 tests_regex.cpp utils.cpp -lgtest -lgtest_main -pthread -o tests_regex && ./tests_regex
	g++ -std=c++17 tests_ccomplex.cpp ccomplex.cpp -lgtest -lgtest_main -pthread -o tests_ccomplex && ./tests_ccomplex


syRF:
	cd build-syRF-Desktop_x86_darwin_generic_mach_o_64bit-Debug && make
	
