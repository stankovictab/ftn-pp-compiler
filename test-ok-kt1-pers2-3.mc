//OPIS: 2. Personalni (Loop) OK Test 3
//RETURN: 5
int main() {
	int zbir;
	int razlika;
	zbir = 1;
	razlika = 1;
	for(int i = 1 to 5 step 2) {
		zbir = zbir + 1;
		razlika = razlika - 1;
	}
	for(int i = 0 to 3)
		razlika = zbir - 1;
	return zbir + razlika;
}