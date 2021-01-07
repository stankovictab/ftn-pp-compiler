//OPIS: 2. Personalni (Loop) OK Test 2
//RETURN: 70
int main() {
	int a;
	a = 69;
	for(int i = 1 to 10 step 3)
		for(int j = 2 to 40 step 2)
			a++;
	for(int i = 1 to 10 step 3) {
		for(int j = 1 to 10 step 3) { // Isti literali ne uticu na tabelu simbola
			j++;
			//return 2;
		}
		i++;
		for(int k = 3 to 4 step 1) {
			k++;
			a = 70;
		}
	}
	return a;
}