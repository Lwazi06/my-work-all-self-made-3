d = int(input()) # base i want to convert from
r = input() # numbers/characters that will be converted to decimal
w = list() 

while r!='-1':
	w.append(r)
	r = input()

u = list()
for i in w :
	s = int(i, d)
	u.append(s)
	
for f in u :
	print(f)
	
	

	
	
	
		
	

	

