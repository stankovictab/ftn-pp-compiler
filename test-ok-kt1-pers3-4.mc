//OPIS: test-temp
//RETURN: 2

int main() {
	int x;
	x = 1;
	switch
	[x] { 
		case 1->
			{
				if(x == 1) {
					x = 2;
				}
			}
			finish;
		otherwise->
			{
				x = 3;
			}
	}
	return x;
}