#pragma once

#include <stack>
#include <string>



namespace ctexcpp::internals {
	class ErrorStack {
		public:
			static void load();
			static void unload();

			static void push(const std::string &error);
			static std::string pop();
			static bool empty(); 
	};

} // namespace ctexcpp::internals
