# 元のバイト列
data = bytearray(b"\x02\x02\x00\x11\x1a")

#dictでキーと値を定義
byte_dict={
    "new" : 0xff,
    "old" :0x0f,
    "make":0x0a
}

# 例：3バイト目（index 2）を対象にする
index = 2
value = data[index]

print(f"Before byte[{index}]: {value:08b}")

# --- bit4〜6 を書き換える ---
# bit4〜6 を 101 に書き換える例（必要に応じて変更）
new_bits = 0b101

# 1) bit4〜6 を 0 にクリアするマスク
mask_clear = ~(0b111 << 4) & 0xFF

# 2) 新しい値をセット
value_cleared = value & mask_clear
value_new = value_cleared | (new_bits << 4)

# バイト列に反映
data[index] = value_new

print(f"After  byte[{index}]: {value_new:08b}")

# --- 全バイト列を表示 ---
print("All bytes:")
for i, b in enumerate(data):
    print(f"  byte[{i}]: {b:02x} ({b:08b})")