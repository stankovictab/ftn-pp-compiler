//OPIS: test-temp
//RETURN: 1
int main() {
	int b = 2 + 3, a = b + 6; // 5 i 11
	for(int k = 1 to 3) {
		a = 1;
		// skip;
		a = 2;
		terminate;
		for(int j = 1 to 3) {
			int l;
			l = 1;
			skip;
			a++;
		}
	}
	return a;
}
