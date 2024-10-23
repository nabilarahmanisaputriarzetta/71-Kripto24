def mod_inverse(a, m):
    m0, x0, x1 = m, 0, 1
    if m == 1:
        return 0
    while a > 1:
        q = a // m
        m, a = a % m, m
        x0, x1 = x1 - q * x0, x0
    return x1 + m0 if x1 < 0 else x1

def affine_encrypt(text, a, b):
    result = ""
    for char in text:
        if char.isalpha():
            x = ord(char.upper()) - 65
            encrypted_char = (a * x + b) % 26
            result += chr(encrypted_char + 65)
        else:
            result += char
    return result

def affine_decrypt(cipher, a, b):
    a_inv = mod_inverse(a, 26)
    result = ""
    for char in cipher:
        if char.isalpha():
            y = ord(char.upper()) - 65
            decrypted_char = (a_inv * (y - b)) % 26
            result += chr(decrypted_char + 65)
        else:
            result += char
    return result

plain_text = input("Input plaintext: ")
a, b = 7, 10

encrypted_text = affine_encrypt(plain_text, a, b)
print(f"Enkripsi: {encrypted_text}")

decrypted_text = affine_decrypt(encrypted_text, a, b)
print(f"Deskripsi: {decrypted_text}")
