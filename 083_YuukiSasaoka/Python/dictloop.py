scores = {
    "math": 0x80,
    "english": 0x70,
    "science": 0x90
}

# 1バイト目を決めるbyte_data = bytearray(byte_data)
if byte_data[1] == 0xfe:
    byte_data[1] = scores["math"]  # 置きたい値を明示する
print(bytes(byte_data))
first_byte = scores["english"] if True else 0xfe  # 条件は好きに書ける

byte_data = b""
byte_data += bytes([0xfe])          # 0番目
byte_data += bytes([first_byte])    # 1番目 ← 条件で決めた値
byte_data += b"\x00\xff"
byte_data += b"\xff" * 120
byte_data += b"\x00\x00\xde\xde"

print(byte_data)

#byte_dataにある分と一致するかを1byteずつ確認する
for i in range(len(byte_data)):
    if byte_data[i] == 0xfe:
        print(f"Index {i}: Found 0xfe")