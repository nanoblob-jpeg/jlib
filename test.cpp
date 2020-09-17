#include "jlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(){
	string test = "       HeLlo";
	test = lower(ltrim(&test[0], NULL));
	println(1, &test[0]);
}