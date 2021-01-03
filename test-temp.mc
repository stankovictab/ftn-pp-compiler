//OPIS: 2. Personalni (Loop) SemErr Test 2
int main() {
	int zbir;
	int razlika;
	for(int i = 1 to 5 step 2) {
		zbir = zbir + i;
		razlika = razlika - i;
	}
	for(int i = 0 to 3)
		razlika = zbir - i;
	return 1;
}