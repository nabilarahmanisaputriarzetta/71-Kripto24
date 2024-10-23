def mod_exp(base, exp, mod):
    result = 1
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        exp = exp // 2
        base = (base * base) % mod
    return result

def elgamal_encrypt(plaintext, p, g, y, k):
    C1 = mod_exp(g, k, p)
    cipher = []
    for char in plaintext:
        M = ord(char.upper()) - 65
        C2 = (M * mod_exp(y, k, p)) % p
        cipher.append((C1, C2))
    return cipher

def elgamal_decrypt(cipher, p, x):
    decrypted_text = ""
    for C1, C2 in cipher:
        M = (C2 * mod_exp(C1, p - 1 - x, p)) % p
        decrypted_text += chr(M + 65)
    return decrypted_text

plaintext = input("Input plaintext: ")
p = 37  # Bilangan prima
g = 3   # Generator
x = 2   # Private key
k = 15  # Random key
y = mod_exp(g, x, p)

cipher = elgamal_encrypt(plaintext, p, g, y, k)
print(f"Enkripsi: {cipher}")

decrypted_text = elgamal_decrypt(cipher, p, x)
print(f"Deskripsi: {decrypted_text}")
