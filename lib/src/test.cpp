#include "test.hpp"

#include <iostream>


namespace test {
	void sayHello() {
		#ifdef CTEX_WINDOWS
			std::cout << "Hello from Windows testlib !" << std::endl;
		#elifdef CTEX_LINUX
			std::cout << "Hello from Linux testlib !" << std::endl;
		#elifdef CTEX_APPLE
			std::cout << "Hello from Apple testlib !" << std::endl;
		#endif
	}
}