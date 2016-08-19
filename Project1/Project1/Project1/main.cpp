#include "Manager.h"

int main(int argc, char* args[])
{
	Manager gm;
	gm.Init();
	while (gm.Update());
	gm.Close();
		

	return 0;
}