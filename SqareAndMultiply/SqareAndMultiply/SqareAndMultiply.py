def squareAndMultipy(basis, exponent, modulo):
	basis %= modulo     # we can modulo reduce the basis
	result = 1 % modulo # just in case modulo = 1 (which is always 0)
	multiplier = basis
	while exponent > 0:
		if exponent & 1:
			result = (result * multiplier) % modulo
		multiplier = (multiplier * multiplier) % modulo
		exponent >>= 1
	return result

# Test the function squareAndMultipy() and compare with value calulated by standard notation
def test(basis, exponent, modulo):
	myResult = squareAndMultipy(basis, exponent, modulo)
	rightResult = (basis ** exponent) % modulo
	assert myResult == rightResult
	print(str(basis)+"^"+str(exponent)+" mod "+str(modulo)+" = "+str(myResult))


# Test the function squareAndMultipy() with 5^37 mod 41
test(5, 37, 41)

# Test the function squareAndMultipy() with a range of values
if False:
	for basis in range(20):
		for exponent in range(20):
			for modulo in range(1, 20):
				if basis != 0 or exponent != 0: # 0^0 is undefined!
					test(basis, exponent, modulo)