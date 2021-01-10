//OPIS: 3. Personalni (Switch) OK Test 6
//RETURN: 0
// Bez otherwise-a skace na case0_no2 koji zapravo nema telo, ne postoji, samo je za ulazak u switch_exit0

int main() {
	int x = 3, a = 0;
	switch
	[x] { 
		case 1->
			{
				a = 1;
			}
		case 2->
			{
				a = 1;
			}
	}
	return a;
}