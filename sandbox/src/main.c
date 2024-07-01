#include <stdio.h>

#include <ctexcpp/error.h>


int main() {
	printf("Has error : %d\n", CTEX_HasError());
	CTEX_PushError("This is a really bad error");
	printf("Has error : %d\n", CTEX_HasError());
	printf("ERROR : %s\n", CTEX_GetError());
	printf("Has error : %d\n", CTEX_HasError());


	CTEX_PushError("This is a really bad error1");
	CTEX_PushError("This is a really bad error2");
	CTEX_PushError("This is a really bad error3");
	CTEX_PushError("This is a really bad error4");
	CTEX_PushError("This is a really bad error5");
	CTEX_PushError("This is a really bad error6");
	CTEX_PushError("This is a really bad error7");
	CTEX_PushError("This is a really bad error8");
	CTEX_PushError("This is a really bad error9");
	CTEX_PushError("This is a really bad error10");
	CTEX_PushError("This is a really bad error11");
	CTEX_PushError("This is a really bad error12");
	CTEX_PushError("This is a really bad error13");
	CTEX_PushError("This is a really bad error14");
	CTEX_PushError("This is a really bad error15");
	CTEX_PushError("This is a really bad error16");
	CTEX_PushError("This is a really bad error17");
	CTEX_PushError("This is a really bad error18");
	CTEX_PushError("This is a really bad error19");
	CTEX_PushError("This is a really bad error20");
	CTEX_PushError("This is a really bad error21");
	CTEX_PushError("This is a really bad error22");
	CTEX_PushError("This is a really bad error23");
	CTEX_PushError("This is a really bad error24");
	CTEX_PushError("This is a really bad error25");
	CTEX_PushError("This is a really bad error26");
	CTEX_PushError("This is a really bad error27");
	CTEX_PushError("This is a really bad error28");
	CTEX_PushError("This is a really bad error29");
	CTEX_PushError("This is a really bad error30");
	CTEX_PushError("This is a really bad error31");
	CTEX_PushError("This is a really bad error32");
	CTEX_PushError("This is a really bad error33");
	CTEX_PushError("This is a really bad error34");
	CTEX_PushError("This is a really bad error35");
	CTEX_PushError("This is a really bad error36");


	for (; CTEX_HasError();)
		printf("ERROR LOOP : %s\n", CTEX_GetError());

	return 0;
}