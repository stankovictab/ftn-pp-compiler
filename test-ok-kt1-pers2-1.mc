//OPIS: 2. Personalni (Loop) OK Test 1
//RETURN: 3
int main() {
	int a;
	a = 69;

	for(int i = 1 to 5)
		i++;

	for(int k = 1 to 2) {
		for(int j = 1 to 3) {
			int l;
			a++;
		}
	}

	for(int i = 1 to 2) {
		a++;
		i++;
		i = a + i;
	}
	for(int i = 1 to 4 step 3) {
		if(i > 2) {
			a = 3;
		}
	}
	return a;
}